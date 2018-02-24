#include "stdafx.h"
#include "Lock.h"
#include "Thread.h"

#ifdef _DEBUG
#define STERN_MODE
#endif
const int INVALID_LINE = -1;

// Lock
Lock::Lock(WCHAR *name)
{
	mLockId = LockManager::GetInstance()->generalId();
}

Lock::~Lock()
{
	mName.clear();
}

const WCHAR* Lock::GetName()
{
	return mName.c_str();
}

size_t Lock::GetLockId()
{
	return mLockId;
}

lock_t& Lock::GetMutex()
{
	return mMutex;
}

void Lock::DoLock(const WCHAR *fileName, int lineNo)
{
	mMutex.lock();

	mLockingFile = fileName;
	mLockingLine = lineNo;
}

void Lock::Unlock()
{
	mMutex.unlock();

	mLockingFile.clear();
	mLockingLine = INVALID_LINE;
}

void Lock::SetThreadId(size_t id)
{
	mThreadId = id;
}

size_t Lock::GetThreadId()
{
	return mThreadId;
}


// LockSafeScope
// 생성자에서 락을걸고, 스코프 빠져나가는 객체 해제시 락을 푼다.
// std::lock_guard(lock_t> guard(lock)과 같지만 데드락 감지를 위해 직접 구현.
LockSafeScope::LockSafeScope(Lock *lock, const WCHAR* fileName, int lineNo)
{
	if (lock == nullptr)
	{
		return;
	}
	if (mbShutdown == true)
	{
		return;
	}

	mLock = lock;
	Lock *deadLock = LockManager::GetInstance()->CheckDeadLock(mLock);

	if (deadLock != nullptr)
	{
#ifndef STERN_MODE
	
#else
		std::lock(mLock->GetMutex(), deadLock->GetMutex());

#endif
		return;
	}
	mLock->DoLock(fileName, lineNo);
	std::hash<std::thread::id> hasher;
	mLock->SetThreadId(hasher(std::this_thread::get_id()));
}

LockSafeScope::~LockSafeScope()
{
	if (!mLock)
	{
		return;
	}
	if (mbShutdown == true)
	{
		return;
	}
	mLock->Unlock();
	mLock->SetThreadId(0);
}



// LockManager
LockManager::LockManager()
{
	mIdSeed = 0;
}

Lock* LockManager::SearchLockCycle(Lock *newLock)
{
	std::hash<std::thread::id> hasher;
	Thread *thread = ThreadManager::GetInstance()->GetThreadById(hasher(std::this_thread::get_id()));
	if (!thread)
	{
		return nullptr;
	}

	std::vector<Lock *> trace;  // 데드락 탐지시, 걸린 락 추적
	trace.push_back(newLock);
	Lock *deadLock = nullptr;
	while (true)
	{
		Lock* threadLock = thread->GetLock();
		if (threadLock == nullptr)
		{
			break;
		}
		if (threadLock->GetLockId() == trace[0]->GetLockId())
		{
			deadLock = threadLock;
			break;
		}
		trace.push_back(threadLock);
		thread = ThreadManager::GetInstance()->GetThreadById(threadLock->GetThreadId());
		if (!thread)
		{
			break;
		}
	}
	trace.empty();
	return deadLock;
}

Lock* LockManager::CheckDeadLock(Lock *newLock)
{
	Lock *deadLock = this->SearchLockCycle(newLock);
	if (deadLock)
	{
		return deadLock;
	}
	return nullptr;
}

size_t LockManager::generalId()
{
	size_t id = mIdSeed++;
	return id;
}
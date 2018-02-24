#include "stdafx.h"
#include "Thread.h"
#include "Lock.h"

// Thread
Thread::Thread(thread_t *thread, wstr_t name)
{
	std::hash<std::thread::id> hasher;
	mName = name;
	mThread = thread;
	mId = hasher(mThread->get_id());

	ThreadManager::GetInstance()->Put(this);
}

Thread::~Thread()
{
	mThread->join();
	SAFE_DELETE(mThread);
	SAFE_DELETE(mLock);
}

size_t Thread::GetId()
{
	return mId;
}

wstr_t &Thread::GetName()
{
	return mName;
}

void Thread::SetLock(Lock *lock)
{
	mLock = lock;
}

Lock* Thread::GetLock()
{
	return mLock;
}


// ThreadManager
ThreadManager::~ThreadManager()
{
	for (auto thread : mThreadPool)
	{
		SAFE_DELETE(thread.second);
	}
}

void ThreadManager::Put(Thread *thread)
{
	std::pair<size_t, Thread *> node(thread->GetId(), thread);
	mThreadPool.insert(node);
	// TODO: SLog(L"* created thread : id[0x%X] name[%s], pool size[%d]", thread->GetId(), thread->GetName().c_str(), mThreadPool.size());
}

void ThreadManager::Remove(size_t id)
{
	auto iter = mThreadPool.find(id);
	if (iter == mThreadPool.end())
	{
		return;
	}
	auto thread = iter->second;
	mThreadPool.erase(iter);
}

Thread* ThreadManager::GetThreadById(size_t id)
{
	if (mThreadPool.empty())
	{
		return nullptr;
	}
	auto iter = mThreadPool.find(id);
	if (iter == mThreadPool.end())
	{
		return nullptr;
	}
	auto thread = iter->second;
	return thread;
}
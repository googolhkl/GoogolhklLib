#pragma once
#include "stdafx.h"

class Lock
{
public:
	Lock(WCHAR* name);
	virtual ~Lock();

	const WCHAR* GetName();
	size_t GetLockId();

	lock_t& GetMutex();
	void DoLock(const WCHAR *fileName, int lineNo);
	void Unlock();
	void SetThreadId(size_t id);
	size_t GetThreadId();
private:
	lock_t mMutex;
	wstr_t mName;
	size_t mLockId;
	size_t mThreadId;

	wstr_t mLockingFile;
	int mLockingLine;
};

class LockSafeScope
{
private:
	Lock *mLock;
	bool mbShutdown;
public:
	LockSafeScope(Lock *lock, const WCHAR *fileName, int lineNo);
	~LockSafeScope();
};

#define SAFE_LOCK(lock) LockSafeScope __lockSafe(&lock, _W(__FILE__), __LINE__);

// 데드락 탐지
class LockManager : public Singleton <LockManager>
{
private:
	size_t mIdSeed;
public:
	LockManager();

	Lock* SearchLockCycle(Lock *newLock);
	Lock* CheckDeadLock(Lock *lock);
	size_t generalId();
};
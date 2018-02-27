#pragma once
#include "stdafx.h"
#include <queue>
#include <stdexcept>

template <class T>
class ThreadJobQueue
{
public:
	ThreadJobQueue(WCHAR *name) : mLock(name)
	{
		mWriteQueue = &mQueue[WRITE_QUEUE];
		mReadQueue = &mReadQueue[READ_QUEUE];
	}

	~ThreadJobQueue()
	{
		mReadQueue->empty();
		mWriteQueue->empty();
	}

	inline void Push(const T &t)
	{
		SAFE_LOCK(mLock);
		mWriteQueue->push(t);
	}

	inline bool Pop(T &t)
	{
		SAFE_LOCK(mLock);
		size_t size = this->Size();
		if (size == 0)
		{
			return false;
		}
		if (mReadQueue->empty())
		{
			this->Swap();
		}
		t = mReadQueue->front();
		mReadQueue->pop();
		return true;
	}

	inline void Swap()
	{
		SAFE_LOCK(mLock);
		if (mWriteQueue == &mQueue[WRITE_QUEUE])
		{
			mWriteQueue = &mQueue[READ_QUEUE];
			mReadQueue = &mQueue[WRITE_QUEUE];
		}
		else
		{
			mWriteQueue = &mQueue[WRITE_QUEUE];
			mReadQueue = &mQueue[READ_QUEUE];
		}
	}

	inline bool IsEmpty()
	{
		return mReadQueue->empty();
	}

	inline void Size()
	{
		SAFE_LOCK(mLock);
		size_t size = (size_t)(mQueue[WRITE_QUEUE].size() + mQueue[READ_QUEUE].size());
		return size;
	}

private:
	enum {
		WRITE_QUEUE,
		READ_QUEUE,
		MAX_QUEUE,
	};
	std::queue<T> mQueue[MAX_QUEUE];
	std::queue<T> *mWriteQueue;  // for input, 여러 쓰레드에서 입력 받음
	std::queue<T> *mReadQueue;  // for output, 한 쓰레드에서 출력함

	Lock mLock;
};

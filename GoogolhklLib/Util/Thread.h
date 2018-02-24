#include "stdafx.h"

#define MAKE_THREAD(className, process) (new Thread(new thread_t(&className##::##process, this), L#className))
//#define GET_CURRENT_THREAD_ID hasher(std::this_thread::get_id())
class Lock;
typedef std::function<void(void *)> ThreadFunction;

class Thread
{
public:
	Thread(thread_t *thread, wstr_t name);
	~Thread();

	size_t GetId();
	wstr_t &GetName();

	void SetLock(Lock *lock);
	Lock *GetLock();
private:
	size_t mId;
	wstr_t mName;
	thread_t *mThread;
	Lock *mLock;
};

//#define THREAD_POOL_HASHMAP
class ThreadManager : public Singleton <ThreadManager>
{
public:
	~ThreadManager();
	void Put(Thread *thread);
	void Remove(size_t id);
	Thread *GetThreadById(size_t id);
private:
#ifdef THREAD_POOL_HASHMAP
	hash_map <size_t, Thread*> mThreadPool;
#else
	map <size_t, Thread*> mThreadPool;
#endif
};

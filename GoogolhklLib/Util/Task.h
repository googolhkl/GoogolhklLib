#pragma once
#include "stdafx.h"

#define TICK_INFINITY 0

class Work;
class TaskNode
{
public:
	TaskNode(Work *workObject, int frequencySec, int durationSec);
	~TaskNode();
	void NextTick();
	bool Expired();
	void Tick();
private:
	Work *mWorkObject;
	int mFrequencySec;
	int mDurationSec;
	tick_t mNextTick;
};

class Task
{
public:
	Task(int id);
	~Task();
	void Add(TaskNode *taskNode);
	void Remove(TaskNode *taskNode);
	void Process();
	void Run();
private:
	std::list<TaskNode *> mTaskList;
	Thread *mThread;
	int mId;
};

class TaskManager : public Singleton <TaskManager>
{
public:
	TaskManager();
	virtual ~TaskManager();
	void Initialize(int threadCount); // TODO: json or xml 파일로 설정하기
	void Add(Work *workObject, int frequencySec, int durationSec);
private:
	int mThreadCount;
	std::vector<Task *> mTaskPool;
};
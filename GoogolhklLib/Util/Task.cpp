#include "stdafx.h"
#include "Task.h"

// TaskNode
TaskNode::TaskNode(Work *workObject, int frequencySec, int durationSec)
{
	mWorkObject = workObject;
	mFrequencySec = frequencySec;
	mDurationSec = durationSec;
	this->NextTick();
}

TaskNode::~TaskNode()
{
	SAFE_DELETE(mWorkObject);
}

void TaskNode::NextTick()
{
	mNextTick = NOW_TICK() + (tick_t)mFrequencySec;
}

bool TaskNode::Expired()
{
	if (mWorkObject == nullptr)
	{
		return true;
	}
	if (mDurationSec != TICK_INFINITY)
	{
		if (mDurationSec < NOW_TICK())
		{
			return true;
		}
	}
	return false;
}

void TaskNode::Tick()
{
	if (mNextTick < NOW_TICK())
	{
		mWorkObject->Tick();
		this->NextTick();
	}
}


// Task
Task::Task(int id)
{
	mId = id;
}

Task::~Task()
{
	for (auto node : mTaskList)
	{
		SAFE_DELETE(node);
	}
}

void Task::Add(TaskNode *taskNode)
{
	mTaskList.push_back(taskNode);
}

void Task::Remove(TaskNode *taskNode)
{
	mTaskList.remove(taskNode);
}

void Task::Process()
{
	while (!_shutdown)
	{
		std::vector<TaskNode *> deleteNodes;
		for (auto taskNode : mTaskList)
		{
			if (taskNode->Expired())
			{
				deleteNodes.push_back(taskNode);
				continue;
			}
			taskNode->Tick();
		}

		for (auto node : deleteNodes)
		{
			this->Remove(node);
		}
		CONTEXT_SWITCH;
	}
}

void Task::Run()
{
	mThread = MAKE_THREAD(Task, Process);
}


// TaskManager
TaskManager::TaskManager()
{
	this->Initialize(2); // TODO: Default Thread값 xml or json으로 설정하기
}

void TaskManager::Initialize(int threadCount)
{
	for (int i = 0; i < mThreadCount; i++)
	{
		Task *task = new Task(i);
		mTaskPool.push_back(task);
		task->Run();
	}
}

TaskManager::~TaskManager()
{
	for (auto task : mTaskPool)
	{
		SAFE_DELETE(task);
	}
}

void TaskManager::Add(Work *workObject, int frequencySec, int durationSec)
{
	static int nodeCount = 0;
	TaskNode *node = new TaskNode(workObject, frequencySec, durationSec);
	int index = nodeCount % mThreadCount;
	Task *task = mTaskPool[index];
	task->Add(node);

	++nodeCount;
}
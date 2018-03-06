#pragma once
#include "stdafx.h"

class Object
{
private:
	wstr_t mAllocFile;
	int mAllocLine;
};

class NameObject
{
public:
	wstr_t& GetName()
	{
		return mName;
	}
	void SetName(wstr_t name)
	{
		mName = name;
	}
private:
	wstr_t mName;
};

class Work
{
public:
	virtual void Tick() = 0;
	virtual void WakeUp() {};
	virtual void Suspend() {};
	virtual void Stop() {};
	virtual void Start() {};
};

class GameObject : public NameObject, public Work
{
public:
	virtual ~GameObject()
	{
		this->Free();
	}
	virtual void Initialize() {};
	virtual void Free() {};
private:
	POINT mPosition;
	float mDirection;
};
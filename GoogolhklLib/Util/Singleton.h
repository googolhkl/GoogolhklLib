#pragma once
#include "stdafx.h"

template <class T>
class Singleton
{
public:
	static T *GetInstance()
	{
		if (instance == NULL)
		{
			instance = new T;
		}
		return instance;
	};
	static void DestroyInstance()
	{
		if (instance)
		{
			delete instance;
			instance = NULL;
		}
	};
protected:
	Singleton() {}
	virtual ~Singleton() {}
private:
	static T * instance;

};

template <class T> T *Singleton<T>::instance = 0;
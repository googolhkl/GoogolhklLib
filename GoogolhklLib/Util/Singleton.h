#pragma once
#include "stdafx.h"


template <class T>
class Singleton {
private:
	static T * instance;
protected:
	Singleton() {}
	virtual ~Singleton() {}
public:
	static T *getInstance() {
		if (instance == NULL) {
			instance = new T;
		}
		return instance;
	};
	static void destroyInstance() {
		if (instance) {
			delete instance;
			instance = NULL;
		}
	};
};

template <class T> T *Singleton<T>::instance = 0;
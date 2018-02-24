﻿#pragma once
#include "stdafx.h"

#define RAND(type, maxVal) (type) RandomMT::GetInstance()->Rand(maxVal)

class RandomMT : public Singleton<RandomMT>
{
public:
	RandomMT() {};
	~RandomMT() {};
	uint64_t Rand(int maxVal)
	{
		// MT19937 난수 엔진
		std::hash<std::thread::id> hasher;
		std::mt19937 engine((uint32_t)time(nullptr) + (uint32_t)hasher(std::this_thread::get_id()));
		std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);
		auto generator = bind(distribution, engine);

		return (uint64_t)(generator() % maxVal);
	}
};

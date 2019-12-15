#pragma once
#include <random>
#include <vector>

class IdGenerator
{
	int previouslyGenerated = 0;
	
public:
	int Get();
};
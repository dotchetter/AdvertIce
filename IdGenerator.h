#pragma once
#include <random>
#include <vector>

using namespace std;

class IdGenerator
{
	int previouslyGenerated = 0;
	
public:
	int Get()
	{
		previouslyGenerated += 1;
		return previouslyGenerated;
	}
};
#pragma once
#include <random>
#include <vector>
#include "IdGenerator.h"

using namespace std;

int IdGenerator::Get()
{
	previouslyGenerated += 1;
	return previouslyGenerated;
}
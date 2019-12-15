#pragma once
#include <random>
#include <vector>
#include "IdGenerator.h"

int IdGenerator::Get()
{
	previouslyGenerated += 1;
	return previouslyGenerated;
}
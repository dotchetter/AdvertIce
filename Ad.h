#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "AdType.h"

class Ad
{

private:

	std::string name;
	std::string adText;
	AdType adType; 
	int id;

public:

	Ad(std::string name, std::string text, int id, AdType type);

	std::string GetName();

	void SetName(std::string name);

	int GetId();

	void SetId(int id);

	AdType GetType();

	void SetType(AdType type);

	std::string GetText();

	void SetText(std::string adText);
};
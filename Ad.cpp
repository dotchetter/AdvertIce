#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "AdType.h"
#include "Ad.h"

using namespace std;

class Ad
{

private:

	string name;
	string adText;
	AdType adType;
	int id;

public:

	Ad(string name, string text, int id, AdType type = AdType::PLAINTEXT)
	{
		this->name = name;
		this->adText = text;
		this->id = id;
		this->adType = type;
	}

	string GetName()
	{
		return name;
	}

	void SetName(string name)
	{
		this->name = name;
	}

	int GetId()
	{
		return id;
	}

	void SetId(int id)
	{
		this->id = id;
	}

	AdType GetType()
	{
		return adType;
	}

	void SetType(AdType type)
	{
		this->adType = type;
	}

	string GetText()
	{
		return adText;
	}

	void SetText(string adText)
	{
		this->adText = adText;
	}
};
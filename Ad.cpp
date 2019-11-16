#pragma once
#include "Ad.h"

using namespace std;

Ad::Ad(string name, string text, int id, AdType type)
{
	this->name = name;
	this->adText = text;
	this->id = id;
	this->adType = type;
}

string Ad::GetName()
{
	return name;
}

void Ad::SetName(string name)
{
	this->name = name;
}

int Ad::GetId()
{
	return id;
}

void Ad::SetId(int id)
{
	this->id = id;
}

AdType Ad::GetType()
{
	return adType;
}

void Ad::SetType(AdType type)
{
	this->adType = type;
}

string Ad::GetText()
{
	return adText;
}

void Ad::SetText(string adText)
{
	this->adText = adText;
}
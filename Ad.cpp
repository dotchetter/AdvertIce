#pragma once
#include "Ad.h"

Ad::Ad(std::string name, std::string text, int id, AdType type = AdType::PLAINTEXT)
{
	this->name = name;
	this->adText = text;
	this->id = id;
	this->adType = type;
}

std::string Ad::GetName()
{
	return name;
}

void Ad::SetName(std::string name)
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

std::string Ad::GetText()
{
	return adText;
}

void Ad::SetText(std::string adText)
{
	this->adText = adText;
}
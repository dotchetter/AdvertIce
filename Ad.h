#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "AdType.h"

class Ad
{

private:

public:

	Ad(string name, string text, int id, AdType type = AdType::PLAINTEXT);
	
	string GetName();

	void SetName(string name);
	
	int GetId();
	
    void SetId(int id);

	AdType GetType();
	
	void SetType(AdType type);
	
	string GetText();

	void SetText(string adText);
	
};
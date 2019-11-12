#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include "campaign.h"

using namespace std;

class Customer
{
	string name;
	int id;
	vector<Campaign> campaigns;

public:
	Customer(string name, int id)
	{
		this->name = name;
		this->id = id;
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

	bool AddCampaign(Campaign campaignObject)
	{
		campaigns.push_back(campaignObject);
		return true;
	}

	bool hasActiveCampaigns()
	{
		for (Campaign i : campaigns)
		{
			if (i.IsActive())
			{
				return true;
			}
		}
		return false;
	}

	vector<Campaign> GetAllCampaigns()
	{
		return campaigns;
	}
};
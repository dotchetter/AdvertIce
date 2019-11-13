#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <ctime>
#include "Ad.h"

using namespace std;


class Campaign
{
	string name;
	int id;
	time_t fromDateTime;
	time_t toDateTime;
	float campaignCost;
	vector<Ad> ads;

public:
	Campaign(time_t fromDateTime, time_t toDateTime, int id, string name, float campaignCost)
	{
		this->fromDateTime = fromDateTime;
		this->toDateTime = toDateTime;
		this->id = id;
		this->name = name;
		this->campaignCost = campaignCost;
	}

	time_t GetFromDateTime()
	{
		return fromDateTime;
	}

	void SetFromDateTime(time_t fromDateTime)
	{
		this->fromDateTime = fromDateTime;
	}

	time_t GetToDateTime()
	{
		return toDateTime;
	}

	void SetToDateTime(time_t toDateTime)
	{
		this->toDateTime = toDateTime;
	}

	int GetId()
	{
		return id;
	}

	void SetId(int id)
	{
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

	float GetCampaignCost()
	{
		return campaignCost;
	}

	void SetCampaignCost(float campaignCost)
	{
		this->campaignCost = campaignCost;
	}

	vector<Ad> GetAllAds()
	{
		return ads;
	}

	bool CommitAdvertisement(Ad ad)
	{
		for (int i = 0; i < ads.size(); i++)
		{
			if (ads[i].GetId() == id)
			{
				return false;
			}
		}
		this->ads.push_back(ad);
	}

	bool DeleteAdvertisement(int id)
	{
		for (int i = 0; i < ads.size(); i++)
		{
			if (ads[i].GetId() == id)
			{
				ads.erase(ads.begin() + i);
				return false;
			}
		}
		return false;
	}
};
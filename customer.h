#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include "campaign.h"

using namespace std;

class Customer
{
	vector<Campaign> campaigns;
	string name;
	int id;

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

	bool DeleteCampaign(int id)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == id)
			{
				campaigns.erase(campaigns.begin() + i);
				return true;
			}
		}
		return false;
	}

	bool CommitAdvertisement(Ad ad, int campaignID)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == campaignID)
			{
				campaigns[i].CommitAdvertisement(ad);
				return true;
			}
		}
		return false;
	}

	bool DeleteAdvertisement(int id, int campaignID)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == campaignID)
			{
				campaigns[i].DeleteAdvertisement(id);
			}
		}
		return false;
	}

	bool RenameAdvertisement(int id, int campaignID, string name)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == campaignID)
			{
				campaigns[i].RenameAdvertisement(id, name);
			}
		}
		return false;
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

	void renameCampaign(int campaignID, string name)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == campaignID)
			{
				campaigns[i].SetName(name);
			}
		}
	}

	bool campaignExists(int id)
	{
		for (Campaign c : campaigns)
		{
			if (c.GetId() == id)
			{
				return true;
			}
		}
		return false;
	}

	int numberOfCampaigns()
	{
		return campaigns.size();
	}

	float GetTotalDeposit()
	{
		float sum = 0;
		for (Campaign c : campaigns)
		{
			sum += c.GetCampaignCost();
		}
		return sum;
	}

	vector<Campaign> GetAllCampaigns()
	{
		return campaigns;
	}

	vector<Ad> GetAllAdsForCampaign(int campaignID)
	{
		for (int i = 0; i < campaigns.size(); i++)
		{
			if (campaigns[i].GetId() == campaignID)
			{
				return campaigns[i].GetAllAds();
			}
		}
	}
};
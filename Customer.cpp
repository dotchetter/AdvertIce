#pragma once
#include "customer.h"

Customer::Customer(std::string name, int id)
{
	this->name = name;
	this->id = id;
}

std::string Customer::GetName()
{
	return name;
}

void Customer::SetName(std::string name)
{
	this->name = name;
}

int Customer::GetId()
{
	return id;
}

void Customer::SetId(int id)
{
	this->id = id;
}

bool Customer::AddCampaign(Campaign campaignObject)
{
	campaigns.push_back(campaignObject);
	return true;
}

bool Customer::DeleteCampaign(int id)
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

bool Customer::CommitAdvertisement(Ad ad, int campaignID)
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

bool Customer::DeleteAdvertisement(int id, int campaignID)
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

bool Customer::RenameAdvertisement(int id, int campaignID, std::string name)
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

bool Customer::hasActiveCampaigns()
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

void Customer::renameCampaign(int campaignID, std::string name)
{
	for (int i = 0; i < campaigns.size(); i++)
	{
		if (campaigns[i].GetId() == campaignID)
		{
			campaigns[i].SetName(name);
		}
	}
}

bool Customer::campaignExists(int id)
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

int Customer::numberOfCampaigns()
{
	return campaigns.size();
}

float Customer::GetTotalDeposit()
{
	float sum = 0;
	for (Campaign c : campaigns)
	{
		sum += c.GetCampaignCost();
	}
	return sum;
}

std::vector<Campaign> Customer::GetAllCampaigns()
{
	return campaigns;
}

std::vector<Ad> Customer::GetAllAdsForCampaign(int campaignID)
{
	for (int i = 0; i < campaigns.size(); i++)
	{
		if (campaigns[i].GetId() == campaignID)
		{
			return campaigns[i].GetAllAds();
		}
	}
}

#include "campaign.h"

Campaign::Campaign(time_t fromDateTime, time_t toDateTime, int id, std::string name, float campaignCost)
{
	this->fromDateTime = fromDateTime;
	this->toDateTime = toDateTime;
	this->id = id;
	this->name = name;
	this->campaignCost = campaignCost;
}

time_t Campaign::GetFromDateTime()
{
	return fromDateTime;
}

void Campaign::SetFromDateTime(time_t fromDateTime)
{
	this->fromDateTime = fromDateTime;
}

time_t Campaign::GetToDateTime()
{
	return toDateTime;
}

void Campaign::SetToDateTime(time_t toDateTime)
{
	this->toDateTime = toDateTime;
}

int Campaign::GetId()
{
	return id;
}

void Campaign::SetId(int id)
{
	this->id = id;
}

std::string Campaign::GetName()
{
	return name;
}

void Campaign::SetName(std::string name)
{
	this->name = name;
}

float Campaign::GetCampaignCost()
{
	return campaignCost;
}

void Campaign::SetCampaignCost(float campaignCost)
{
	this->campaignCost = campaignCost;
}

Ad Campaign::GetRandomAd()
{
	if (ads.size() > 0)
	{
		int randomAdIndex = rand() % ads.size();
		return ads[randomAdIndex];
	}
}

bool Campaign::IsActive()
{
	time_t now = time(NULL);
	if (fromDateTime <= now && toDateTime >= now)
	{
		return true;
	}
	return false;
}

bool Campaign::CommitAdvertisement(Ad ad)
{
	for (Ad i : ads)
	{
		if (i.GetId() == ad.GetId())
		{
			return false;
		}
	}
	ads.push_back(ad);
	return true;
}

bool Campaign::DeleteAdvertisement(int id)
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

bool Campaign::RenameAdvertisement(int id, std::string name)
{
	for (int i = 0; i < ads.size(); i++)
	{
		if (ads[i].GetId() == id)
		{
			ads[i].SetName(name);
			return false;
		}
	}
	return false;
}

std::vector<Ad> Campaign::GetAllAds()
{
	return ads;
}

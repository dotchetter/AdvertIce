#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include "campaign.h"

class Customer
{
	std::vector<Campaign> campaigns;
	std::string name;
	int id;

public:
	
	Customer(std::string name, int id);

	std::string GetName();

	void SetName(std::string name);

	int GetId();

	void SetId(int id);

	bool AddCampaign(Campaign campaignObject);

	bool DeleteCampaign(int id);

	bool CommitAdvertisement(Ad ad, int campaignID);

	bool DeleteAdvertisement(int id, int campaignID);

	bool RenameAdvertisement(int id, int campaignID, std::string name);

	bool hasActiveCampaigns();

	void renameCampaign(int campaignID, std::string name);

	bool campaignExists(int id);

	int numberOfCampaigns();

	float GetTotalDeposit();

	std::vector<Campaign> GetAllCampaigns();

	std::vector<Ad> GetAllAdsForCampaign(int campaignID);
};
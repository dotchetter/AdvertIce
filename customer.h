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
	
	Customer(string name, int id);

	string GetName();

	void SetName(string name);

	int GetId();

	void SetId(int id);

	bool AddCampaign(Campaign campaignObject);

	bool DeleteCampaign(int id);

	bool CommitAdvertisement(Ad ad, int campaignID);

	bool DeleteAdvertisement(int id, int campaignID);

	bool RenameAdvertisement(int id, int campaignID, string name);

	bool hasActiveCampaigns();

	void renameCampaign(int campaignID, string name);

	bool campaignExists(int id);

	int numberOfCampaigns();

	float GetTotalDeposit();

	vector<Campaign> GetAllCampaigns();

	vector<Ad> GetAllAdsForCampaign(int campaignID);
};
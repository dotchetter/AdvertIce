#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <ctime>
#include <random>
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
	Campaign(time_t fromDateTime, time_t toDateTime, int id, string name, float campaignCost);
	
	time_t GetFromDateTime();

	void SetFromDateTime(time_t fromDateTime);

	time_t GetToDateTime();

	void SetToDateTime(time_t toDateTime);

	int GetId();

	void SetId(int id);

	string GetName();

	void SetName(string name);

	float GetCampaignCost();

	void SetCampaignCost(float campaignCost);

	Ad GetRandomAd();

	bool IsActive();

	bool CommitAdvertisement(Ad ad);

	bool DeleteAdvertisement(int id);

	bool RenameAdvertisement(int id, string name);

	vector<Ad> GetAllAds();
};
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <ctime>
#include <random>
#include "Ad.h"

class Campaign
{
	std::string name;
	int id;
	time_t fromDateTime;
	time_t toDateTime;
	float campaignCost;
	std::vector<Ad> ads;

public:
	Campaign(time_t fromDateTime, time_t toDateTime, int id, std::string name, float campaignCost);
	
	time_t GetFromDateTime();

	void SetFromDateTime(time_t fromDateTime);

	time_t GetToDateTime();

	void SetToDateTime(time_t toDateTime);

	int GetId();

	void SetId(int id);

	std::string GetName();

	void SetName(std::string name);

	float GetCampaignCost();

	void SetCampaignCost(float campaignCost);

	Ad GetRandomAd();

	bool IsActive();

	bool CommitAdvertisement(Ad ad);

	bool DeleteAdvertisement(int id);

	bool RenameAdvertisement(int id, std::string name);

	std::vector<Ad> GetAllAds();
};
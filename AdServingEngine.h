#pragma once
#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>
#include "customer.h"

using namespace std;

class AdServingEngine
{
	vector<Customer> customerBase;

public:
	AdServingEngine()
	{
		//pass
	}

	void UpdateCustomerBase(vector<Customer> customerBase)
	{
		this->customerBase = customerBase;
	}

	Ad GetNextAd()
	{
		int random_customer = rand() % (customerBase.size());
		vector<Campaign> campaigns = customerBase[random_customer].GetAllCampaigns();

		int random_campaign = rand() % (campaigns.size());
		Campaign selected_campaign = campaigns[random_campaign];

		vector<Ad> ads = selected_campaign.GetAllAds();

		int random_ad = rand() % (ads.size());
		return ads[random_ad];
	}

	size_t GetNumberOfCustomers()
	{
		return customerBase.size();
	}
};
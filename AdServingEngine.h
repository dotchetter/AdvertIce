#pragma once
#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>
#include <ctime>
#include <map>
#include "customer.h"

using namespace std;

class AdServingEngine
{
	vector<Customer> customerBase;
	map<int, float> CustomerTotalDeposit;

public:

	void UpdateCustomerBase(vector<Customer> customerBase)
	{
		this->customerBase = customerBase;
	}

	Ad GetNextAd()
	{
		float allCustomersTotalDeposit = 0;
		float thisCustomerTotalDeposit = 0;
		int customerSelector;
		int campaignSelector;
		int selectedCustomerID;
		float selectedCustomerTotalDeposit;

		for (Customer i : customerBase) 
		{
			thisCustomerTotalDeposit = 0;
			for (Campaign c : i.GetAllCampaigns())
			{
				allCustomersTotalDeposit += c.GetCampaignCost();
				thisCustomerTotalDeposit += c.GetCampaignCost();
			}
			CustomerTotalDeposit.insert(make_pair(i.GetId(), thisCustomerTotalDeposit));
		}

		customerSelector = rand() % ((int)allCustomersTotalDeposit + 1);

		for (auto i = CustomerTotalDeposit.begin(); i != CustomerTotalDeposit.end(); i++)
		{
			customerSelector -= (int)i->second;
			if (customerSelector <= 0)
			{
				selectedCustomerID = i->first;
				selectedCustomerTotalDeposit = i->second;
				break;
			}
		}

		campaignSelector = rand() % ((int)selectedCustomerTotalDeposit + 1);

		for (Customer i : customerBase)
		{
			if (i.GetId() == selectedCustomerID)
			{
				for (Campaign c : i.GetAllCampaigns())
				{
					campaignSelector -= (int)c.GetCampaignCost();

					if (campaignSelector <= 0)
					{
						return c.GetRandomAd();
					}
				}
			}
		}
	}

	size_t GetNumberOfCustomers()
	{
		return customerBase.size();
	}
};
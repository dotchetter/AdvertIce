#pragma once
#include "AdServingEngine.h"

void AdServingEngine::UpdateCustomerBase(std::vector<Customer> customerBase)
{
	this->customerBase = customerBase;
}

Ad AdServingEngine::GetNextAd()
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
		if (!i.hasActiveCampaigns()) {
			continue;
		}

		for (Campaign c : i.GetAllCampaigns())
		{
			if (c.IsActive())
			{
				allCustomersTotalDeposit += c.GetCampaignCost();
				thisCustomerTotalDeposit += c.GetCampaignCost();
			}
		}
		CustomerTotalDeposit.insert(std::make_pair(i.GetId(), thisCustomerTotalDeposit));
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
				if (c.IsActive())
				{
					campaignSelector -= (int)c.GetCampaignCost();
				}

				if (campaignSelector <= 0 and c.IsActive())
				{
					return c.GetRandomAd();
				}
			}
		}
	}
}

size_t AdServingEngine::GetNumberOfCustomers()
{
	return customerBase.size();
}
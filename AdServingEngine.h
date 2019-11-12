#pragma once
#include <algorithm>
#include <random>
#include "customer.h"

using namespace std;

class AdServingEngine
{
	vector<Customer> customers;
	default_random_engine GetRandom;

	AdServingEngine()
	{
		// Constructor
	}

	vector<Campaign> GetAllValidCampaigns()
	{
		vector<Campaign> AllValidCampaigns;

		for (Customer customer : customers)
		{
			if (!customer.hasActiveCampaigns())
			{
				continue;
			}

			for (Campaign campaign : customer.GetAllActiveCampaigns()) // Method not ready just yet (customer.h)
			{
				AllValidCampaigns.push_back(campaign);
			}
		}
		return AllValidCampaigns;
	}

public:

	void getNextAd()
	{
		// Runtime - display ads and campaigns according probability regulated by cost.
		for (Customer customer : customers)
		{
			if (!customer.hasActiveCampaigns())
			{
				continue;
			}

			/*for (Campaign campaign : customer.GetAllCampaigns())
			{
				if ()
			}*/
		}
	}

	void AddCustomer(Customer customer)
	{
		customers.push_back(customer);
	}

	void DeleteCustomer(int id)
	{
		for (int i = 0; i < customers.size(); i++)
		{
			if (customers[i].GetId() == id)
			{
				customers.erase(customers.begin() + i);
			}
		}
	}

	void DisplayAllCustomers()
	{
		for (Customer i : customers)
		{
			string hasActive;

			switch (i.hasActiveCampaigns()) 
			{
			case 0:
				hasActive = "No";
				break;
			case 1:
				hasActive = "Yes";
				break;
			}

			cout << "Customer Name: " << i.GetName() << endl;
			cout << "Customer ID: " << i.GetId() << endl;
			cout << "Has active campaigns: " << hasActive << endl;
		}
	}
};
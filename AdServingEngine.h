#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include "customer.h"

using namespace std;

class AdServingEngine
{
	vector<Customer> customerBase;
	default_random_engine GetRandom;

	AdServingEngine(vector<Customer> customerBase)
	{
		this->customerBase = customerBase;
	}

public:
	Ad GetNextAd()
	{

	}
};


int main()
{
	Customer testcustomer = Customer("Kalles kaviar", 321587654);

}
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


};


int main()
{
	Customer* testcustomer = new Customer();
}
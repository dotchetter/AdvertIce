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

	void UpdateCustomerBase(vector<Customer> customerBase);

	Ad GetNextAd();

	size_t GetNumberOfCustomers();
};
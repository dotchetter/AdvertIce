#pragma once
#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>
#include <ctime>
#include <map>
#include "customer.h"

class AdServingEngine
{
	std::vector<Customer> customerBase;
	std::map<int, float> CustomerTotalDeposit;

public:

	void UpdateCustomerBase(std::vector<Customer> customerBase);

	Ad GetNextAd();

	size_t GetNumberOfCustomers();
};
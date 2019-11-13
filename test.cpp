#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include "customer.h"
#include "AdServingEngine.h"

using namespace std;

time_t makedate()
{
	int Year, Month, Day, Hour, Minute;
	struct tm tm = {0};
	bool validInput = true;

	cout << "Enter year: "; cin >> Year;
	cout << "Enter Month: "; cin >> Month;
	cout << "Enter Day: "; cin >> Day;
	cout << "Enter Hour: "; cin >> Hour;
	cout << "Enter Minute: "; cin >> Minute;
	
	tm.tm_year = Year - 1900;
	tm.tm_mon = Month - 1;
	tm.tm_mday = Day;
	tm.tm_hour = Hour;
	tm.tm_min = Minute;
	tm.tm_isdst = -1;

	if (Year <= 1970 || Month < 1 || Day < 1 || Hour < 1 || Minute < 0)
	{
		validInput = false;
	}
	else if (Month > 12 || Day > 31 || Hour > 23 || Minute > 59)
	{
		validInput = false;
	}

	if (!validInput)
	{
		return NULL;
	}
	return mktime(&tm);
}

int main()
{
	srand(time(NULL));

	cout << "Enter the start date for your campaign!" << endl;
	time_t begin = makedate();

	cout << "Enter the end date for your campaign!" << endl;
	time_t end = makedate();

	if (begin >= end)
	{
		cout << "The date scope entered is illogical." << endl;
	}

	Customer the_client = Customer("Foobar AB", 123);

	the_client.AddCampaign(Campaign(begin, end, 1234, "Christmas!", 500));
	the_client.AddCampaign(Campaign(begin, end, 12345, "New Year", 500));
	
	the_client.CommitAdvertisement(Ad("SALE!!", "theClient", 123456), 1234);
	the_client.CommitAdvertisement(Ad("SuperSale", "theClient", 123456789), 1234);

	the_client.CommitAdvertisement(Ad("New year craze, must buy!", "theClient", 123456), 12345);
	the_client.CommitAdvertisement(Ad("Are you feeling hungry?", "theClient", 123456789), 12345);

	Customer the_other_client = Customer("Foo bar AB", 111111);

	the_other_client.AddCampaign(Campaign(begin, end, 456, "Other client christmas!", 700));
	the_other_client.AddCampaign(Campaign(begin, end, 789, "Other clients new year", 600));
	
	the_other_client.CommitAdvertisement(Ad("SALE!!", "theOtherClient", 234565), 456);
	the_other_client.CommitAdvertisement(Ad("SuperDUPERSale", "theOtherClient", 35377), 456);

	the_other_client.CommitAdvertisement(Ad("New year never felt so good!", "theOtherClient", 3456345), 789);
	the_other_client.CommitAdvertisement(Ad("Are you feeling hungry?", "theOtherClient", 5677467), 789);

	vector<Customer> all_customers;

	all_customers.push_back(the_client);
	all_customers.push_back(the_other_client);

	AdServingEngine engine = AdServingEngine();
	engine.UpdateCustomerBase(all_customers);

	while (true)
	{
		Sleep(500);
		Ad newAd = engine.GetNextAd();
		cout << newAd.GetName() << endl << newAd.GetText() << endl << endl;
	}
}
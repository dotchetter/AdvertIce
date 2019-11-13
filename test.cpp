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
		cout << "Invalid entry, try again." << endl;
		return NULL;
	}
	return mktime(&tm);
}

int main()
{
	
	cout << "Enter the start date for your campaign!" << endl;
	time_t begin = makedate();

	cout << "Enter the end date for your campaign!" << endl;
	time_t end = makedate();

	if (begin >= end)
	{
		cout << "The date scope entered is illogical." << endl;
	}

	Customer the_client = Customer("Foobar AB", 123);

	the_client.AddCampaign(Campaign(begin, end, 1234, "Christmas!", 123455.0f));
	the_client.AddCampaign(Campaign(begin, end, 12345, "New Year", 10000.f));
	
	the_client.CommitAdvertisement(Ad("SALE!!", "Cheap presents that no one wanted", 123456), 1234);
	the_client.CommitAdvertisement(Ad("SuperSale", "30% off!", 123456789), 1234);

	the_client.CommitAdvertisement(Ad("New year craze, must buy!", "50% off for a limited time", 123456), 12345);
	the_client.CommitAdvertisement(Ad("Are you feeling hungry?", "Best potatoes in town!", 123456789), 12345);

	Customer the_other_client = Customer("Foo bar AB", 111111);

	the_other_client.AddCampaign(Campaign(begin, end, 456, "Other client christmas!", 123455.0f));
	the_other_client.AddCampaign(Campaign(begin, end, 789, "Other clients new year", 123455.0f));
	
	the_other_client.CommitAdvertisement(Ad("SALE!!", "We buy back old stuff!", 234565), 456);
	the_other_client.CommitAdvertisement(Ad("SuperDUPERSale", "90% off!!!!!", 35377), 456);

	the_other_client.CommitAdvertisement(Ad("New year never felt so good!", "75% off!!!", 3456345), 789);
	the_other_client.CommitAdvertisement(Ad("Are you feeling hungry?", "Best burgers in town!", 5677467), 789);

	vector<Customer> all_customers;

	all_customers.push_back(the_client);
	all_customers.push_back(the_other_client);

	AdServingEngine engine = AdServingEngine();
	engine.UpdateCustomerBase(all_customers);

	while (true)
	{
		Sleep(3000);
		Ad next = engine.GetNextAd();

		cout << next.GetName() << endl;
		cout << next.GetText() << endl;
		cout << "\n";
	}
}
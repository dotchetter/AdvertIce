#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include "customer.h"
using namespace std;

time_t makedate(int year, int month, int day, int hour, int minute)
{
	struct tm tm = { 0 };
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;
	tm.tm_isdst = -1;
	return mktime(&tm);
}

int main()
{
	int startYear, startMonth, startDay, startHour, startMinute;
	int endYear, endMonth, endDay, endHour, endMinute;

	cout << "Start Year: "; cin >> startYear;
	cout << "Start Month: "; cin >> startMonth;
	cout << "Start Day: "; cin >> startDay;
	cout << "Start Hour: "; cin >> startHour;
	cout << "Start Minute: "; cin >> startMinute;

	cout << "End year: "; cin >> endYear;
	cout << "End month: "; cin >> endMonth;
	cout << "End day: "; cin >> endDay;
	cout << "End hour: "; cin >> endHour;
	cout << "End minute: "; cin >> endMinute;

	time_t begin = makedate(startYear, startMonth, startDay, startHour, startMinute);
	time_t end = makedate(endYear, endMonth, endDay, endHour, endMinute);

	// Skapa en kund
	Customer the_client("Foobar AB", 123);

	// Skapa en kampanj
	Campaign c(begin, end, 00000, "Julrea!", 3000.0f);
	
	// Lägg till reklamen i kampanjen
	c.CommitAdvertisement(Ad("Rea", "Blinkar", 123, AdType::BLINK));
	c.CommitAdvertisement(Ad("Stektfläsk", "Statiskt", 123));

	// Lägg till kampanjen till kunden
	the_client.AddCampaign(c);

	// Printa ut alla Campaigns
	for (Campaign i : the_client.GetAllCampaigns())
	{
		cout << "Kampanjens namn: \n" << i.GetName() << endl;

	}

	cout << "Kunden har aktiva kampanjer: " << the_client.hasActiveCampaigns() << endl;
}
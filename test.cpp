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
	Customer *the_client = new Customer("Foobar AB", 123);

	// Skapa en kampanj
	Campaign *the_campaign = new Campaign(begin, end, 1234, "kampanjnamn", 123455.0f);

	// Skapa en reklam
	Ad *the_first_ad = new Ad("First ad", "Reklamtext", 6464564, AdType::PLAINTEXT);

	// Skapa en till reklam
	Ad* the_second_ad = new Ad("Second ad", "Reklamtext", 6468564, AdType::PLAINTEXT);

	// Lägg till kampanjen i kunden
	the_client->AddCampaign(*the_campaign);

	// Lägg till reklamen i kampanjen
	the_client->CommitAdvertisement(*the_first_ad, 1234);
	
	// Hur många reklamer finns
	cout << "Det finns nu " << the_client->GetAllAdsForCampaign(1234).size() << "reklamer i kampanjen" << endl;
	
	// Lägg till reklamen i kampanjen
	the_client->CommitAdvertisement(*the_second_ad, 1234);

	// Hur många reklamer finns
	cout << "Det finns nu " << the_client->GetAllAdsForCampaign(1234).size() << "reklamer i kampanjen" << endl;
}
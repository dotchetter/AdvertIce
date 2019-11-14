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

int GetIndexOfCustomer(vector<Customer> &AllCustomers, int id)
{
	for (int i = 0; i < AllCustomers.size(); i++)
	{
		if (AllCustomers[i].GetId() == id)
		{
			return i;
		}
	} return -1;
}

void AddCustomer(vector<Customer> &AllCustomers)
{
	string customerName;
	int customerID;

	cout << "Enter customer name: ";
	cin >> customerName;
	cout << "Enter customer ID: ";
	cin >> customerID;

	AllCustomers.push_back(Customer(customerName, customerID));
	cout << endl << endl;
}

void ListAllCampaignsForCustomer(vector<Customer> &AllCustomers, int indexForCustomer)
{
	cout << endl << endl;
	cout << " --- All Campaigns for customer " << AllCustomers[indexForCustomer].GetName() << endl << endl;
	cout << " --- <Name>\t\t<ID> --- " << endl << endl;

	for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
	{
		cout << " --- " << c.GetName() << "\t\t" << c.GetId() << " --- " << endl;
	}
	cout << endl << endl;
}

void AdvertisementMenu(vector<Customer> &AllCustomers, int indexForCustomer)
{
	int selection;
	int campaignIdBuf;
	AdType adtypeBuf;
	string advertisementName;
	string advertisementText;
	int adTypeSelection;
	int advertisementId;

	if (AllCustomers[indexForCustomer].GetAllCampaigns().size() < 1)
	{
		cout << "You cannot create or edit an Advertisement prior to creating a campaign." << endl;
		return;
	}
	cout << "[1] List all ads" << endl;
	cout << "[2] Create Ad" << endl;
	cout << "[3] Delete Ad" << endl;
	cout << "[4] Back" << endl;
	cout << endl << "-> "; cin >> selection;

	ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);
	switch (selection)
	{
	case 1:
		for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
		{
			for (Ad a : AllCustomers[indexForCustomer].GetAllAdsForCampaign(c.GetId()))
			{
				cout << "All ads for customers all campaigns:" << endl << "<< Name >> \t <<Text>> \t <<ID>>" << endl;
				cout << a.GetName() << "\t" << a.GetText() << "\t" << a.GetId() << endl;
			}
		}
		cout << endl << endl; 
		break;
	case 2:
		cout << "Enter campaign ID for the advertisement: " << endl << " -> "; cin >> campaignIdBuf;
		
		if (!AllCustomers[indexForCustomer].campaignExists(campaignIdBuf)){
			cout << "The campaign you searched for was not found." << endl;
			return;
		}
		
		cout << " -- Advertisement name: " << endl << " -> "; cin >> advertisementName;
		cout << " -- Advertisement text: " << endl << " -> "; cin >> advertisementText;
		cout << " -- Advertisement ID: " << endl << " -> "; cin >> advertisementId;
		cout << " --> This option comes in three flavors. Select with 1-3 and hit enter." << endl;
		cout << "1. Blinking" << endl << "2. Static, plain text" << endl << "3. Scrolling" << endl;
		cout << " -> "; cin >> adTypeSelection;

		switch (adTypeSelection)
		{
		case 1:
			adtypeBuf = AdType::BLINK;
			break;
		case 2:
			adtypeBuf = AdType::PLAINTEXT;
			break;
		case 3:
			adtypeBuf = AdType::SCROLL;
			break;
		default:

			return;
		}
		AllCustomers[indexForCustomer].CommitAdvertisement(
			Ad(advertisementName, advertisementText, advertisementId, adtypeBuf), campaignIdBuf);
		break;
	case 3:
		cout << "Enter Id for the ad to delete: " << endl; cout << " -> "; cin >> advertisementId;
		
		for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
		{
			for (Ad a : c.GetAllAds())
			{
				if (a.GetId() == advertisementId)
				{
					c.DeleteAdvertisement(advertisementId);
				}
			}
		}
		break;
	case 4:
		break;
	}
}

void ListAllCustomers(vector<Customer> &AllCustomers)
{
	cout << endl << " -------- All customers: -------- " << endl;
	cout << " --- <Name>\t\t<ID> --- " << endl << endl;

	for (Customer c : AllCustomers)
	{
		cout << " --- " << c.GetName() << "\t\t" << c.GetId() << " --- " << endl;
	}
	cout << endl << endl;
}

void EditCustomer(vector<Customer> &AllCustomers)
{
	int indexForCustomer = 0;
	int customerIdBuf;
	int selection;
	int idBuf;
	string newNameBuf;
	string campaignNameBuf;
	float campaignCostBuf = 0;
	time_t begin;
	time_t end;

	cout << "Enter the ID for the customer" << endl; cout << " -> "; cin >> customerIdBuf;
	indexForCustomer = GetIndexOfCustomer(AllCustomers, customerIdBuf);

	if (indexForCustomer == -1)
	{
		cout << "The customer you searched for was not found. " << endl;
		return;
	}

	cout << "[1] Edit Name" << endl;
	cout << "[2] Delete customer" << endl;
	cout << "[3] Add campaign" << endl;
	cout << "[4] Delete campaign" << endl;
	cout << "[5] List all campaigns" << endl;
	cout << "[6] Advertisement menu" << endl;
	cout << " -> "; cin >> selection;

	switch (selection)
	{
	case 1:
		cout << "Enter the new name for customer " <<
			AllCustomers[indexForCustomer].GetName() <<
			endl; cout << " -> "; cin >> newNameBuf;
		AllCustomers[indexForCustomer].SetName(newNameBuf);
		break;
	case 2:
		AllCustomers.erase(AllCustomers.begin() + indexForCustomer);
		cout << "Customer deleted." << endl;
		break;
	case 3:
		cout << "Enter campaign name: ";
		cout << endl << "-> "; cin >> campaignNameBuf;

		cout << "Enter campaign ID: ";
		cout << endl << "-> "; cin >> idBuf;

		cout << "Enter campaign investment: ";
		cout << endl << "-> "; cin >> campaignCostBuf;

		cout << "Enter Year, Month, Day for the beginning of this campaign: " << endl;
		begin = makedate();

		cout << "Enter Year, Month, Day for the end of this campaign: " << endl;
		end = makedate();

		AllCustomers[indexForCustomer].AddCampaign(
			Campaign(begin, end, idBuf, campaignNameBuf, campaignCostBuf));
		break;
	case 4:
		cout << "Enter campaign ID: ";
		cout << endl << "-> "; cin >> idBuf;
		AllCustomers[indexForCustomer].DeleteCampaign(idBuf);
		break;
	case 5:
		ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);
		break;
	case 6:
		AdvertisementMenu(AllCustomers, indexForCustomer);
		break;
	}
}

int MainMenu()
{
	int selection;

	cout << "[1] Add customer" << endl;
	cout << "[2] Edit customer" << endl;
	cout << "[3] List all customers" << endl;
	cout << "[4] Enter runtime" << endl;
	cout << "[5] Exit" << endl;
	cout << endl << "-> "; cin >> selection;
	
	return selection;
}

int main()
{
	srand(time(NULL));

	AdServingEngine engine = AdServingEngine();
	vector<Customer>AllCustomers;
	int selection;

	while (true)
	{
		selection = MainMenu();
		switch (selection)
		{
		case 1:
			AddCustomer(AllCustomers);
			break;
		case 2:
			EditCustomer(AllCustomers);
			break;
		case 3:
			if (AllCustomers.size() < 1)
			{
				cout << "There are no stored customers in the system." << endl << endl;
				break;
			}
			ListAllCustomers(AllCustomers);
			break;
		case 4:
			engine.UpdateCustomerBase(AllCustomers);
			while (true)
			{
				Ad newAd = engine.GetNextAd();
				cout << endl << endl << newAd.GetName() << endl << newAd.GetText();
				Sleep(1000);
			}
			break;
		case 5:
			break;
		}
	}	
}


void WorkingModel()
{
	/*srand(time(NULL));

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
	}*/
}
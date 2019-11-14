#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include "customer.h"
#include "AdServingEngine.h"
#include "IdGenerator.h"

using namespace std;

time_t makedate()
{
	int Year, Month, Day, Hour, Minute;
	struct tm tm = {0};
	bool validInput = true;

	cout << endl << "Enter Month: " << endl << endl << " -> "; cin >> Month;
	cout << endl << "Enter Day: " << endl << endl << " -> "; cin >> Day;
	cout << endl << "Enter Hour: " << endl << endl << " -> "; cin >> Hour;
	cout << endl << "Enter Minute: " << endl << endl << " -> "; cin >> Minute;
	cout << endl;
	
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

void AddCustomer(vector<Customer> &AllCustomers, IdGenerator &idGenerator)
{
	string customerName;
	int customerID;

	cout << endl << "Enter customer name: " << endl << endl << " -> ";
	getline(cin >> ws,customerName);
	cout << endl << "Enter customer ID: " << endl << endl << " -> ";
	cin >> customerID;

	AllCustomers.push_back(Customer(customerName, idGenerator.Get()));
	cout << endl << "Customer added successfully. " << endl << endl;
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

void AdvertisementMenu(vector<Customer> &AllCustomers, int indexForCustomer, IdGenerator &idGenerator)
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
	cout << endl << " -> "; cin >> selection;

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
		
		cout << " -- Advertisement name: " << endl << " -> "; getline(cin >> ws, advertisementName);;
		cout << " -- Advertisement text: " << endl << " -> "; getline(cin >> ws, advertisementText);;
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
			Ad(advertisementName, advertisementText, idGenerator.Get(), adtypeBuf), campaignIdBuf);
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
	string idRepresentation;
	const int headerLength = 22;
	int totalLength;
	int remainingWhitespace;

	cout << endl << " -------- All customers: -------- " << endl; // 34 ch
	cout << " --- <Name> ------------ <ID> --- " << endl << endl;

	for (Customer c : AllCustomers)
	{
		idRepresentation = to_string(c.GetId());
		totalLength = c.GetName().length() + idRepresentation.length();
		remainingWhitespace = (headerLength - totalLength);
		cout << "    " << c.GetName();
		for (int i = 0; i < remainingWhitespace; i++)
		{
			cout << " ";
		}
		cout << " " << c.GetId() << endl;
	}
	cout << endl << endl;
}

void EditCustomer(vector<Customer> &AllCustomers, IdGenerator &idGenerator)
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

	cout << endl << "Enter the ID for the customer:" << endl << endl; cout << " -> "; cin >> customerIdBuf;
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
	cout << endl << " -> "; cin >> selection;

	switch (selection)
	{
	case 1:
		cout << endl << "Enter the new name for customer [ " <<
			AllCustomers[indexForCustomer].GetName() << " ] :" << endl <<
			endl; cout << " -> "; getline(cin >> ws, newNameBuf);
		AllCustomers[indexForCustomer].SetName(newNameBuf);
		break;
	case 2:
		AllCustomers.erase(AllCustomers.begin() + indexForCustomer);
		cout << endl <<  "Customer deleted." << endl << endl;
		break;
	case 3:
		cout << endl << "Enter campaign name: " << endl;
		cout << endl << "-> "; getline(cin >> ws, campaignNameBuf);;

		cout << endl << "Enter campaign investment: " << endl;
		cout << endl << " -> "; cin >> campaignCostBuf;

		cout << endl << "Campaign start date :" << endl;
		begin = makedate();

		cout << "Campaign end date :" << endl;
		end = makedate();

		AllCustomers[indexForCustomer].AddCampaign(
			Campaign(begin, end, idGenerator.Get(), campaignNameBuf, campaignCostBuf));
		break;
	case 4:
		cout << "Enter campaign ID: ";
		cout << endl << " -> "; cin >> idBuf;
		AllCustomers[indexForCustomer].DeleteCampaign(idBuf);
		break;
	case 5:
		ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);
		break;
	case 6:
		AdvertisementMenu(AllCustomers, indexForCustomer, idGenerator);
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
	cout << endl << " -> "; cin >> selection;
	
	return selection;
}

int main()
{
	srand(time(NULL));

	AdServingEngine engine = AdServingEngine();
	IdGenerator idGenerator = IdGenerator();
	vector<Customer>AllCustomers;
	int selection;
	int adAmount = 0;

	while (true)
	{
		selection = MainMenu();
		switch (selection)
		{
		case 1:
			AddCustomer(AllCustomers, idGenerator);
			break;
		case 2:
			EditCustomer(AllCustomers, idGenerator);
			break;
		case 3:
			if (AllCustomers.size() < 1)
			{
				cout << endl << "-> There are no stored customers in the system." << endl << endl;
				break;
			}
			ListAllCustomers(AllCustomers);
			break;
		case 4:
			for (Customer c : AllCustomers)
			{
				for (Campaign i : c.GetAllCampaigns())
				{
					adAmount += i.GetAllAds().size();
				}
			}

			if (AllCustomers.size() < 1 or adAmount == 0)
			{
				cout << endl << "-> There are no stored customers, or no ads in the system." << endl << endl;
				break;
			}
			cout << ">>> Entering runtime. Ads will be displayed in a weighted randomized pattern. <<<" << endl;
			cout << ">>> To exit, hit and hold the ESC key. <<<" << endl;
			engine.UpdateCustomerBase(AllCustomers);
			while (true)
			{
				if (GetKeyState(VK_ESCAPE) & 0x8000)
				{
					break;
				}
				Ad newAd = engine.GetNextAd();
				cout << endl << endl << newAd.GetName() << endl << newAd.GetText();
				Sleep(1000);
			}
			break;
		case 5:
			exit(0);
		}
	}	
}



void WorkingModel()
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

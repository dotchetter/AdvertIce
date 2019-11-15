#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include "customer.h"
#include "AdServingEngine.h"
#include "IdGenerator.h",

using namespace std;

time_t makedate()
{
	int Year, Month, Day, Hour, Minute;
	struct tm tm = {0};
	bool validInput = true;

	cout << endl << endl;
	cout << " -> Enter year: ";
	cin >> Year;
	cout << " -> Enter Month: ";
	cin >> Month;
	cout << " -> Enter Day: ";
	cin >> Day; 
	cout << " -> Enter Hour: ";
	cin >> Hour;
	cout << " -> Enter Minute: ";
	cin >> Minute; 
	cout << endl << endl;

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
	cout << endl << " -> You are here: [Main menu > Add Customer]" << endl << endl;

	string customerName;
	int customerID;

	cout << " -> Enter customer name: " << endl << " -> ";
	getline(cin >> ws,customerName);

	AllCustomers.push_back(Customer(customerName, idGenerator.Get()));
	cout << " -> Customer added successfully. " << endl << endl;
}

void ListAllCampaignsForCustomer(vector<Customer> &AllCustomers, int indexForCustomer)
{
	string idRepresentation;
	const int headerLength = 22;
	int totalLength;
	int remainingWhitespace;

	cout << endl << " --- All Campaigns for customer " << 
		AllCustomers[indexForCustomer].GetName() << " --- " << endl;
	cout << " --- <Name> ------------ <ID> --- " << endl << endl;

	for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
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

void AdvertisementMenu(vector<Customer> &AllCustomers, int indexForCustomer, IdGenerator &idGenerator)
{
	int idBuf;
	int selection;
	int campaignIdBuf;
	AdType adtypeBuf;
	string advertisementName;
	string advertisementText;
	string nameBuf;
	int adTypeSelection;
	int advertisementId;

	string idRepresentation;
	const int headerLength = 20;
	int totalLength;
	int remainingWhitespace;

	cout << endl << " -> You are here: [Main menu > Edit Customer > Advertisement menu]" 
		<< endl << endl;

	if (AllCustomers[indexForCustomer].GetAllCampaigns().size() < 1)
	{
		cout << " -> There are no campaigns for this customer, thus no ads." << endl;
		cout << " -> Start by creating a campaign, then add advertisements to it." << endl;
		return;
	}
	while (true)
	{
		cout << "[1] List all Ads" << endl;
		cout << "[2] Create Ad" << endl;
		cout << "[3] Rename Ad" << endl;
		cout << "[4] Delete Ad" << endl;
		cout << "[5] Back" << endl;
		cout << endl << " -> "; cin >> selection;

		if (!cin)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << " -> Invalid entry - only digits allowed." << endl;
			break;
		}

		ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);

		switch (selection)
		{
		case 1:
			for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
			{
				cout << " --- Campaign: " << c.GetName() << "  --------" << endl;
				cout << endl << " --------  All ads:  --------- " << endl;
				cout << " --- <Name> --------- <ID> --- " << endl << endl;
				
				for (Ad a : AllCustomers[indexForCustomer].GetAllAdsForCampaign(c.GetId()))
				{
					idRepresentation = to_string(c.GetId());
					totalLength = c.GetName().length() + idRepresentation.length();
					remainingWhitespace = (headerLength - totalLength);
					cout << "    " << a.GetName();

					for (int i = 0; i < remainingWhitespace; i++)
					{
						cout << " ";
					}
					cout << " " << a.GetId() << endl;
				cout << endl << endl;
				}
			}
			cout << endl << endl;
			break;

		case 2:
			cout << "Enter campaign ID for the advertisement: " << endl << " -> "; 
			cin >> campaignIdBuf;

			if (!AllCustomers[indexForCustomer].campaignExists(campaignIdBuf)) {
				cout << "The campaign you searched for was not found." << endl;
				return;
			}
			else if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				break;
			}

			cout << " -> Advertisement name: " << endl << " -> "; getline(cin >> ws, advertisementName);;
			cout << " -> Advertisement text: " << endl << " -> "; getline(cin >> ws, advertisementText);;
			cout << " -> This option comes in three flavors. Select with 1-3 and hit enter." << endl << endl;
			cout << "[1] Blinking" << endl;
			cout << "[2] Static, plain text" << endl;
			cout << "[3] Scrolling" << endl << endl;
			cout << " -> "; cin >> adTypeSelection;

			if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				return;
			}

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
			cout << " -> Enter campaign ID for the advertisement: "
				<< endl << " -> "; cin >> campaignIdBuf;
			cout << " -> Enter ad ID: ";
			cout << endl << " -> "; cin >> idBuf;

			if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				break;
			}

			cout << " -> Enter new name for the advertisement: " << endl;
			cout << " -> "; getline(cin >> ws, nameBuf);
			AllCustomers[indexForCustomer].RenameAdvertisement(idBuf, campaignIdBuf, nameBuf);
			break;

		case 4:
			cout << " -> Enter campaign ID for the advertisement: " 
				<< endl << " -> "; cin >> campaignIdBuf;
			cout << " -> Enter ID for the advertisement to delete: " 
				<< endl; cout << " -> "; cin >> advertisementId;

			if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				break;
			}

			AllCustomers[indexForCustomer].DeleteAdvertisement(advertisementId, campaignIdBuf);
			break;

		case 5:
			return;
		}
	}
}

void ListAllCustomers(vector<Customer> &AllCustomers)
{
	string idRepresentation;
	const int headerLength = 14;
	int totalLength;
	int remainingWhitespace;

	cout << endl << " -------- All customers: -------- " << endl;
	cout << " --- <Name> --- <ID> --- <Deposit> ---" << endl << endl;

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
		cout << " " << c.GetId();
		for (int i = 0; i < remainingWhitespace; i++)
		{
			cout << " ";
		}
		cout << " " << c.GetTotalDeposit() << endl;

	}
	cout << endl << endl;
}

void EditCustomer(vector<Customer> &AllCustomers, IdGenerator &idGenerator)
{
	int indexForCustomer = 0;
	int customerIdBuf = 0;
	int selection;
	int idBuf;
	string newNameBuf;
	string campaignNameBuf;
	float campaignCostBuf = 0;
	time_t begin;
	time_t end;

	while (true)
	{
		cout << endl << " -> You are here: [Main menu > Edit Customer]" << endl << endl;
		
		if (customerIdBuf == 0)
		{
			cout << " -> Enter the ID for the customer" << endl;
			cout << " -> "; cin >> customerIdBuf;
		}

		indexForCustomer = GetIndexOfCustomer(AllCustomers, customerIdBuf);

		if (indexForCustomer == -1)
		{
			cout << " -> The customer you searched for was not found." << endl;
			break;
		}
		else
		{
			cout << " -> Selected customer: " << AllCustomers[indexForCustomer].GetName() << endl << endl;
		}

		cout << "[1] Edit Name" << endl;
		cout << "[2] Delete customer" << endl;
		cout << "[3] Add campaign" << endl;
		cout << "[4] Delete campaign" << endl;
		cout << "[5] Rename campaign" << endl;
		cout << "[6] List all campaigns" << endl;
		cout << "[7] Advertisement menu" << endl;
		cout << "[8] Back" << endl;

		cout << " -> "; cin >> selection;

		if (!cin)
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << " -> Invalid entry - only digits allowed." << endl;
			break;
		}
	
		switch (selection)
		{
		case 1:
			cout << " -> Enter the new name for customer " <<
				AllCustomers[indexForCustomer].GetName() <<
				endl; cout << " -> "; getline(cin >> ws, newNameBuf);;
			AllCustomers[indexForCustomer].SetName(newNameBuf);
			break;

		case 2:
			AllCustomers.erase(AllCustomers.begin() + indexForCustomer);
			cout << " -> Customer deleted: Going back to main menu." << endl;
			return;

		case 3:
			cout << " -> Enter campaign name: ";
			cout << endl << " -> "; getline(cin >> ws, campaignNameBuf);

			cout << " -> Enter campaign investment: ";
			cout << endl << " -> "; cin >> campaignCostBuf;

			cout << " -> Enter Year, Month, Day for the beginning of this campaign: " << endl;
			begin = makedate();

			cout << " -> Enter Year, Month, Day for the end of this campaign: " << endl;
			end = makedate();

			if (begin == NULL or end == NULL or begin > end)
			{
				cout << endl << " -> Warning: Illogical dates entered, try again." << endl;
				break;
			}

			AllCustomers[indexForCustomer].AddCampaign(
				Campaign(begin, end, idGenerator.Get(), campaignNameBuf, campaignCostBuf));
			cout << " -> Campaign added successfully." << endl << endl;
			break;

		case 4:
			cout << " -> Enter campaign ID: ";
			cout << endl << " -> "; cin >> idBuf;

			if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				break;
			}

			if (AllCustomers[indexForCustomer].DeleteCampaign(idBuf))
			{
				cout << " -> Campaign deleted successfully." << endl;
			}
			else
			{
				cout << " -> An error occured deleting this campaign. Did you enter a valid id?" << endl;
			}
			break;
		case 5:
			cout << " -> Enter campaign ID: ";
			cout << endl << " -> "; cin >> idBuf;

			if (!cin)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << " -> Invalid entry - only digits allowed." << endl;
				break;
			}

			cout << " -> Enter campaign name: ";
			cout << endl << " -> "; getline(cin >> ws, campaignNameBuf);
			AllCustomers[indexForCustomer].renameCampaign(idBuf, campaignNameBuf);
			break;

		case 6:
			ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);
			break;

		case 7:
			AdvertisementMenu(AllCustomers, indexForCustomer, idGenerator);
			break;
		case 8:
			return;
		}
	}
}

int MainMenu()
{
	int selection;
	cout << endl << " -> You are here: [Main menu]" << endl << endl;
	
	if (!cin)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << " -> Invalid entry - only digits allowed." << endl;
		return -1;
	}

	cout << "[1] Add customer" << endl;
	cout << "[2] Edit customer" << endl;
	cout << "[3] List all customers" << endl;
	cout << "[4] Enter runtime" << endl;
	cout << "[5] Exit" << endl; cout << endl << " -> "; cin >> selection;
	
	return selection;
}

int main()
{
	srand(time(NULL));
	
	char ent;
	AdServingEngine engine = AdServingEngine();
	IdGenerator idGenerator = IdGenerator();
	vector<Customer>AllCustomers;
	int selection;
	int adAmount = 0;
	string outbuf;
	string whitespace = " ";

	cout << endl;
	cout << "\t\t\t\t ******************* Advertice *******************" << endl;
	cout << "\t\t\t\t * All-in-one campaign and advertisement system  *" << endl;
	cout << "\t\t\t\t *************************************************" << endl;
	cout << endl;

	Sleep(3000);
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
				cout << endl << " -> There are no stored customers in the system." << endl << endl;
				break;
			}
			ListAllCustomers(AllCustomers);
			break;

		case 4:
			for (Customer c : AllCustomers)
			{
				if (c.hasActiveCampaigns())
				{
					for (Campaign i : c.GetAllCampaigns())
					{
						adAmount += i.GetAllAds().size();
					}
				}				
			}

			if (AllCustomers.size() < 1 or adAmount == 0)
			{
				cout << endl << " -> There are no stored customers, no valid campaigns or no ads in the system." << endl << endl;
				break;
			}

			cout << " -> Hit enter to start runtime. Ads will be displayed in a weighted randomized pattern." << endl;
			cout << " -> To exit, hit and hold the ESC key." << endl;
			cin >> ent;

			engine.UpdateCustomerBase(AllCustomers);
			while (true)
			{
				if (GetKeyState(VK_ESCAPE) & 0x8000)
				{
					break;
				}

				Ad newAd = engine.GetNextAd();
				system("cls");

				switch (newAd.GetType())
				{
				case AdType::BLINK:

					for (int i = 0; i < 10; i++)
					{
						cout << newAd.GetText();
						Sleep(500);
						system("cls");
						Sleep(500);
					}
				case AdType::SCROLL:
					outbuf = newAd.GetText();

					for (int i = 0; i < 100; i++)
					{
						outbuf.insert(0, whitespace);
						cout << outbuf;
						Sleep(15);
						system("cls");
					}
				case AdType::PLAINTEXT:
					cout << newAd.GetText() << endl;
				}
			}
			break;
		case 5:
			exit(0);
		}
	}	
}
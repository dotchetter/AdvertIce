#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include "customer.h"
#include "AdServingEngine.h"
#include "IdGenerator.h"

time_t makedate()
{
	int Year, Month, Day, Hour, Minute;
	struct tm tm = {0};
	bool validInput = true;

	std::cout << std::endl << std::endl;
	std::cout << " -> Enter year: ";
	std::cin >> Year;
	std::cout << " -> Enter Month: ";
	std::cin >> Month;
	std::cout << " -> Enter Day: ";
	std::cin >> Day; 
	std::cout << " -> Enter Hour: ";
	std::cin >> Hour;
	std::cout << " -> Enter Minute: ";
	std::cin >> Minute; 
	std::cout << std::endl << std::endl;

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

int GetIndexOfCustomer(std::vector<Customer> &AllCustomers, int id)
{
	for (int i = 0; i < AllCustomers.size(); i++)
	{
		if (AllCustomers[i].GetId() == id)
		{
			return i;
		}
	} return -1;
}

void AddCustomer(std::vector<Customer> &AllCustomers, IdGenerator &idGenerator)
{
	std::cout << std::endl << " -> You are here: [Main menu > Add Customer]" << std::endl << std::endl;

	std::string customerName;
	int customerID;

	std::cout << " -> Enter customer name: " << std::endl << " -> ";
	getline(std::cin >> std::ws,customerName);

	AllCustomers.push_back(Customer(customerName, idGenerator.Get()));
	std::cout << " -> Customer added successfully. " << std::endl << std::endl;
}

void ListAllCampaignsForCustomer(std::vector<Customer> &AllCustomers, int indexForCustomer)
{
	std::string idRepresentation;
	const int headerLength = 22;
	int totalLength;
	int remainingWhitespace;

	std::cout << std::endl << " --- All Campaigns for customer " << 
		AllCustomers[indexForCustomer].GetName() << " --- " << std::endl;
	std::cout << " --- <Name> ------------ <ID> --- " << std::endl << std::endl;

	for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
	{
		idRepresentation =std::to_string(c.GetId());
		totalLength = c.GetName().length() + idRepresentation.length();
		remainingWhitespace = (headerLength - totalLength);
		std::cout << "    " << c.GetName();
		for (int i = 0; i < remainingWhitespace; i++)
		{
			std::cout << " ";
		}
		std::cout << " " << c.GetId() << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void AdvertisementMenu(std::vector<Customer> &AllCustomers, int indexForCustomer, IdGenerator &idGenerator)
{
	int idBuf;
	int selection;
	int campaignIdBuf;
	AdType adtypeBuf;
	std::string advertisementName;
	std::string advertisementText;
	std::string nameBuf;
	int adTypeSelection;
	int advertisementId;

	std::string idRepresentation;
	const int headerLength = 20;
	int totalLength;
	int remainingWhitespace;

	std::cout << std::endl << " -> You are here: [Main menu > Edit Customer > Advertisement menu]" 
		<< std::endl << std::endl;

	if (AllCustomers[indexForCustomer].GetAllCampaigns().size() < 1)
	{
		std::cout << " -> There are no campaigns for this customer, thus no ads." << std::endl;
		std::cout << " -> Start by creating a campaign, then add advertisements to it." << std::endl;
		return;
	}
	while (true)
	{
		std::cout << "[1] List all Ads" << std::endl;
		std::cout << "[2] Create Ad" << std::endl;
		std::cout << "[3] Rename Ad" << std::endl;
		std::cout << "[4] Delete Ad" << std::endl;
		std::cout << "[5] Back" << std::endl;
		std::cout << std::endl << " -> "; std::cin >> selection;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << " -> Invalid entry - only digits allowed." << std::endl;
			break;
		}

		ListAllCampaignsForCustomer(AllCustomers, indexForCustomer);

		switch (selection)
		{
		case 1:
			for (Campaign c : AllCustomers[indexForCustomer].GetAllCampaigns())
			{
				std::cout << " --- Campaign: " << c.GetName() << "  --------" << std::endl;
				std::cout << std::endl << " --------  All ads:  --------- " << std::endl;
				std::cout << " --- <Name> --------- <ID> --- " << std::endl << std::endl;
				
				for (Ad a : AllCustomers[indexForCustomer].GetAllAdsForCampaign(c.GetId()))
				{
					idRepresentation =std:: to_string(c.GetId());
					totalLength = c.GetName().length() + idRepresentation.length();
					remainingWhitespace = (headerLength - totalLength);
					std::cout << "    " << a.GetName();

					for (int i = 0; i < remainingWhitespace; i++)
					{
						std::cout << " ";
					}
					std::cout << " " << a.GetId() << std::endl;
				std::cout << std::endl << std::endl;
				}
			}
			std::cout << std::endl << std::endl;
			break;

		case 2:
			std::cout << "Enter campaign ID for the advertisement: " << std::endl << " -> ";
			std::cin >> campaignIdBuf;

			if (!AllCustomers[indexForCustomer].campaignExists(campaignIdBuf)) {
				std::cout << "The campaign you searched for was not found." << std::endl;
				return;
			}
			else if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
				break;
			}

			std::cout << " -> Advertisement name: " << std::endl << " -> "; getline(std::cin >> std::ws, advertisementName);;
			std::cout << " -> Advertisement text: " << std::endl << " -> "; getline(std::cin >> std::ws, advertisementText);;
			std::cout << " -> This option comes in three flavors. Select with 1-3 and hit enter." << std::endl << std::endl;
			std::cout << "[1] Blinking" << std::endl;
			std::cout << "[2] Static, plain text" << std::endl;
			std::cout << "[3] Scrolling" << std::endl << std::endl;
			std::cout << " -> "; std::cin >> adTypeSelection;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
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
			std::cout << " -> Enter campaign ID for the advertisement: "
				<< std::endl << " -> "; std::cin >> campaignIdBuf;
			std::cout << " -> Enter ad ID: ";
			std::cout << std::endl << " -> "; std::cin >> idBuf;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
				break;
			}

			std::cout << " -> Enter new name for the advertisement: " << std::endl;
			std::cout << " -> "; getline(std::cin >> std::ws, nameBuf);
			AllCustomers[indexForCustomer].RenameAdvertisement(idBuf, campaignIdBuf, nameBuf);
			break;

		case 4:
			std::cout << " -> Enter campaign ID for the advertisement: " 
				<< std::endl << " -> "; std::cin >> campaignIdBuf;
			std::cout << " -> Enter ID for the advertisement to delete: " 
				<< std::endl; std::cout << " -> "; std::cin >> advertisementId;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
				break;
			}

			AllCustomers[indexForCustomer].DeleteAdvertisement(advertisementId, campaignIdBuf);
			break;

		case 5:
			return;
		}
	}
}

void ListAllCustomers(std::vector<Customer> &AllCustomers)
{
	std::string idRepresentation;
	const int headerLength = 14;
	int totalLength;
	int remainingWhitespace;

	std::cout << std::endl << " -------- All customers: -------- " << std::endl;
	std::cout << " --- <Name> --- <ID> --- <Deposit> ---" << std::endl << std::endl;

	for (Customer c : AllCustomers)
	{
		idRepresentation = std::to_string(c.GetId());
		totalLength = c.GetName().length() + idRepresentation.length();
		remainingWhitespace = (headerLength - totalLength);
		std::cout << "    " << c.GetName();
		for (int i = 0; i < remainingWhitespace; i++)
		{
			std::cout << " ";
		}
		std::cout << " " << c.GetId();
		for (int i = 0; i < remainingWhitespace; i++)
		{
			std::cout << " ";
		}
		std::cout << " " << c.GetTotalDeposit() << std::endl;

	}
	std::cout << std::endl << std::endl;
}

void EditCustomer(std::vector<Customer> &AllCustomers, IdGenerator &idGenerator)
{
	int indexForCustomer = 0;
	int customerIdBuf = 0;
	int selection;
	int idBuf;
	std::string newNameBuf;
	std::string campaignNameBuf;
	float campaignCostBuf = 0;
	time_t begin;
	time_t end;

	while (true)
	{
		std::cout << std::endl << " -> You are here: [Main menu > Edit Customer]" << std::endl << std::endl;
		
		if (customerIdBuf == 0)
		{
			std::cout << " -> Enter the ID for the customer" << std::endl;
			std::cout << " -> "; std::cin >> customerIdBuf;
		}

		indexForCustomer = GetIndexOfCustomer(AllCustomers, customerIdBuf);

		if (indexForCustomer == -1)
		{
			std::cout << " -> The customer you searched for was not found." << std::endl;
			break;
		}
		else
		{
			std::cout << " -> Selected customer: " << AllCustomers[indexForCustomer].GetName() << std::endl << std::endl;
		}

		std::cout << "[1] Edit Name" << std::endl;
		std::cout << "[2] Delete customer" << std::endl;
		std::cout << "[3] Add campaign" << std::endl;
		std::cout << "[4] Delete campaign" << std::endl;
		std::cout << "[5] Rename campaign" << std::endl;
		std::cout << "[6] List all campaigns" << std::endl;
		std::cout << "[7] Advertisement menu" << std::endl;
		std::cout << "[8] Back" << std::endl;

		std::cout << " -> "; std::cin >> selection;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << " -> Invalid entry - only digits allowed." << std::endl;
			break;
		}

		switch (selection)
		{
		case 1:
			std::cout << " -> Enter the new name for customer " <<
				AllCustomers[indexForCustomer].GetName() <<
				std::endl; std::cout << " -> "; std::getline(std::cin >> std::ws, newNameBuf);;
			AllCustomers[indexForCustomer].SetName(newNameBuf);
			break;

		case 2:
			AllCustomers.erase(AllCustomers.begin() + indexForCustomer);
			std::cout << " -> Customer deleted: Going back to main menu." << std::endl;
			return;

		case 3:
			std::cout << " -> Enter campaign name: ";
			std::cout << std::endl << " -> "; getline(std::cin >> std::ws, campaignNameBuf);

			std::cout << " -> Enter campaign investment: ";
			std::cout << std::endl << " -> "; std::cin >> campaignCostBuf;

			std::cout << " -> Enter Year, Month, Day for the beginning of this campaign: " << std::endl;
			begin = makedate();

			std::cout << " -> Enter Year, Month, Day for the end of this campaign: " << std::endl;
			end = makedate();

			if (begin == NULL or end == NULL or begin > end)
			{
				std::cout << std::endl << " -> Warning: Illogical dates entered, try again." << std::endl;
				break;
			}

			AllCustomers[indexForCustomer].AddCampaign(
				Campaign(begin, end, idGenerator.Get(), campaignNameBuf, campaignCostBuf));
			std::cout << " -> Campaign added successfully." << std::endl << std::endl;
			break;

		case 4:
			std::cout << " -> Enter campaign ID: ";
			std::cout << std::endl << " -> "; std::cin >> idBuf;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
				break;
			}

			if (AllCustomers[indexForCustomer].DeleteCampaign(idBuf))
			{
				std::cout << " -> Campaign deleted successfully." << std::endl;
			}
			else
			{
				std::cout << " -> An error occured deleting this campaign. Did you enter a valid id?" << std::endl;
			}
			break;
		case 5:
			std::cout << " -> Enter campaign ID: ";
			std::cout << std::endl << " -> "; std::cin >> idBuf;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << " -> Invalid entry - only digits allowed." << std::endl;
				break;
			}

			std::cout << " -> Enter campaign name: ";
			std::cout << std::endl << " -> "; getline(std::cin >> std::ws, campaignNameBuf);
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
	std::cout << std::endl << " -> You are here: [Main menu]" << std::endl << std::endl;
	
	if (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << " -> Invalid entry - only digits allowed." << std::endl;
		return -1;
	}

	std::cout << "[1] Add customer" << std::endl;
	std::cout << "[2] Edit customer" << std::endl;
	std::cout << "[3] List all customers" << std::endl;
	std::cout << "[4] Enter runtime" << std::endl;
	std::cout << "[5] Exit" << std::endl; std::cout << std::endl << " -> "; std::cin >> selection;
	
	return selection;
}

int main()
{
	srand(time(NULL));
	
	char ent;
	AdServingEngine engine = AdServingEngine();
	IdGenerator idGenerator = IdGenerator();
	std::vector<Customer>AllCustomers;
	int selection;
	int adAmount = 0;
	std::string outbuf;
	std::string whitespace = " ";

	std::cout << std::endl;
	std::cout << "\t\t\t\t ******************* Advertice *******************" << std::endl;
	std::cout << "\t\t\t\t * All-in-one campaign and advertisement system  *" << std::endl;
	std::cout << "\t\t\t\t *************************************************" << std::endl;
	std::cout << std::endl;

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
				std::cout << std::endl << " -> There are no stored customers in the system." << std::endl << std::endl;
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
				std::cout << std::endl << " -> There are no stored customers, no valid campaigns or no ads in the system." << std::endl << std::endl;
				break;
			}

			std::cout << " -> Hit enter to start runtime. Ads will be displayed in a weighted randomized pattern." << std::endl;
			std::cout << " -> To exit, hit and hold the ESC key." << std::endl;
			std::cin >> ent;

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
						std::cout << newAd.GetText();
						Sleep(500);
						system("cls");
						Sleep(500);
					}
				case AdType::SCROLL:
					outbuf = newAd.GetText();

					for (int i = 0; i < 100; i++)
					{
						outbuf.insert(0, whitespace);
						std::cout << outbuf;
						Sleep(15);
						system("cls");
					}
				case AdType::PLAINTEXT:
					std::cout << newAd.GetText() << std::endl;
					Sleep(3000);
				}
			}
			break;
		case 5:
			exit(0);
		}
	}	
}
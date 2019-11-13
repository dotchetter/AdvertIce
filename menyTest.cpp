#include <string>
#include <ctime>
#include <iomanip>
#include <cstdio>
#include <Windows.h>
#include "customer.h"
#include "AdServingEngine.h"

using namespace std;

void AddCustomer(vector<Customer>& allCustomers)
{
	string customerName;
	int customerID;

	cout << "Provide customer name: " << endl;
	cin >> customerName;

	cout << "Provide customer ID: " << endl;
	cin >> customerID;

	Customer customer(customerName, customerID);

	allCustomers.push_back(customer);

	cout << "Customer " << customer.GetName() << " with ID: " << customer.GetId() << " created." << endl;
	cout << allCustomers.size() << endl;

}


void EditCustomer(vector<Customer> allCustomers)
{
	int customerID;
	int menuSelection;
	int selectedCustomer;
	cout << "Enter customer ID: ";
	cin >> customerID;

	for (int i = 0; i < allCustomers.size(); i++)
	{
		if (allCustomers[i].GetId == customerID)
		{
			selectedCustomer = i;
		}
	}

	cout << "[1] - Create new campaign";
	cout << "[2] - Edit existing campaign";
	cout << "[3] - Deleta existing campaign";

	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		cout << "Enter the start date for your campaign!" << endl;
		time_t begin = makedate();

		cout << "Enter the end date for your campaign!" << endl;
		time_t end = makedate();

		if (begin >= end)
		{
			cout << "The date scope entered is illogical." << endl;
		}

		int campaignID;
		float campaignCost;
		string campaignText;

		cout << "Enter campaign id: ";
		cin >> campaignID;

		cout << "Enter campaign text: ";
		cin >> campaignText;

		cout << "Enter campaign cost: ";
		cin >> campaignCost;

		allCustomers[selectedCustomer].AddCampaign(Campaign(begin, end, campaignID, campaignText, campaignCost));
		cout << "Campaign " << campaignText << " created.";

		break;

		/*case 2:
			EditExistingCampaign();
			break;
		case 3:
			DeleteExistingCampaign();
		default:
			break;*/
	}
}

void EnterRuntime()

{}

void ListAllCustomers()
{}

void MainLoop()
{
	vector<Customer> all_customers;

	while (true)

	{
		int menuSelection;

		cout << "[1] - Create customer" << endl;
		cout << "[2] - Edit customer" << endl;
		cout << "[3] - List all customers" << endl;
		cout << "[4] - Enter runtime" << endl;
		cout << "[5] - Exit program" << endl;

		cin >> menuSelection;

		switch (menuSelection)
		{
		case 1:
			AddCustomer(all_customers);
			break;
		case 2:
			EditCustomer(all_customers);
			break;
			/*case 3:
				EnterRuntime();
				break;
			case 4:
				ListAllCustomers();
				break;
			case 5:
				cout << "Press any key to continue.";
				return;
			default:
				cout << "Invalid choice";
				break;*/
		}
	}
}


time_t makedate()
{
	int Year, Month, Day, Hour, Minute;
	struct tm tm = { 0 };
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
	MainLoop();


}
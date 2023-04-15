/*
Names: Brendan Zientek
Date: 05/08/2022
Problem Statement: Design a structure to hold customer records which contain
				   customer's name, address, city, state, zip, phone number,
				   account balance, and date of last payment. The program should
				   allow the user to enter a new record into the file, search a
				   particular customer and display the information, delete a customer's
				   record, change a customer's record, and display the contents of all the
				   customers on file.
*/

//============ Preprocessor directive ============
#include <iostream>		// cout object
#include <iomanip>		// manage format of output 
#include <string>		// reading string of characters
#include <vector>		// compile file called vector
using namespace std;

//============ Structure Delcaration =======
struct CustomerRecords
{
	string name,		//Store's Customer's first and last Name
		address,		//Store's Customer's address
		city,			//Store's Customer's city in which they live in
		state,			//Store's Customer's state in which they live in
		zip,			//Store's Customer's zip code
		phoneNum,		//Store's Customer's phone number
		lastPayDate;	//Store's Customer's last date of payment

	double accBalance = 0.0;	//Store's Customer's total account balance
};

//=============== ProtoTypes ===============
void menu(vector<CustomerRecords>& records);	//Prototype menu function to repeatedly call while program is running

//=============== Linear Search ============
int linearSearch(vector<CustomerRecords>& records, string searchName)
{
	bool found = false;		//Set flag to false
	int index = 0;			//Store's vector's index 
	int position = -1;		//Store's index number where name was found in the vector

	while (index < records.size() && !found)
	{
		if (records[index].name == searchName)	//If the value is found
		{
			found = true;		//If found set the flag to true
			position = index;	//Record the value's subscript
		}
		index++;	//Go to the next element
	}
	if (position != -1)
	{
		return position;	//If name was found position will return the index where it was found in the vector
	}
	else
	{
		cout << searchName << " is not found in customer records" << endl;	//Input Validation
		menu(records);	//Set the user back to main menu if the name is not found in records
	}
}

//========== User Input Name on Record ============
string getName()
{
	string searchName;	//The name to search for
	cout << "Enter the Name of the Customer: ";
	getline(cin, searchName);
	return searchName;	//Return the name inputted by user
}

//================ Input Record ================
void insert(vector<CustomerRecords>& records)
{

	records.push_back(CustomerRecords());		//Increase the size of the CustomerRecords structure records object vector by 1

	cout << "\n\n========= Record Creation =========\n";
	cout << "Please Insert Customer's\n" << endl;
	cout << "Name: ";
	getline(cin, records[records.size() - 1].name);		//Store's the name inputted by user in name variable in the CustomerRecords structure records object
	cout << "Address: ";
	getline(cin, records[records.size() - 1].address);	//Store's the address inputted by user in address variable in the CustomerRecords structure records object
	cout << "City: ";
	getline(cin, records[records.size() - 1].city);		//Store's the city inputted by user in the city variable in the CustomerRecords structure records object
	cout << "State: ";
	getline(cin, records[records.size() - 1].state);	//Store's the state inputted by user in the state variable in the CustomerRecords structure records object
	cout << "Zip: ";
	getline(cin, records[records.size() - 1].zip);		//Store's the zip inputted by user in the zip variable in the CustomerRecords structure records object
	cout << "Phone Number: ";
	getline(cin, records[records.size() - 1].phoneNum);	//Store's the phone number inputted by user in the phoneNum variable in the CustomerRecords structure records object
	cout << "Last Pay Day: ";
	getline(cin, records[records.size() - 1].lastPayDate);	//Store's the last date of paymentinputted by user in the lastPayDate variable in CustomerRecords structure records object
	cout << "Account Balance: ";
	cin >> records[records.size() - 1].accBalance;		//Store's the account balance inputted by user in the accBalance variable in CustomerRecords structure records object

	//Input validation : User input can NOT be less than 0
	while (records[records.size() - 1].accBalance < 0)
	{
		cout << "\nAccount Balance can NOT be a negative number.\n"
			<< "Please input a positive account balance\n\n$";
		cin >> records[records.size() - 1].accBalance;			// Store the user's proper account balance inputted by user
		cout << endl;
	}

	cout << "\n========= Record has been Created =========\n\n";
	cin.ignore();	//Ignore input so it doesn't get inputted for choice when going to menu function
	menu(records);	//Calling menu function
}

//================ Search Record ================
void search(vector<CustomerRecords>& records)
{
	cout << "\n\n========= Search Record =========\n\n";
	string searchName = getName();						//Calling function to get the name user wants to search
	int position = linearSearch(records, searchName);	//Calling function to get the index where the name is in the vector

	cout << "\n" << setw(50) << " " << searchName << " Information: \n\n";	//Move the user inputted name to display on top and towards the middle of the information header   
	cout << right << "Name" << setw(27) << "Address" << setw(23) << "City" << setw(19) << "State" << setw(12) << "Zip" << setw(17) << "Phone Number" << setw(17) << "Last Pay Date" << setw(19) << "Account Balance\n";	//Display header

	//Display Player's stats
	cout << left << setw(19) << records[position].name << setw(30) << records[position].address << setw(19) << records[position].city
		<< setw(13) << records[position].state << setw(9) << records[position].zip << setw(17) << records[position].phoneNum
		<< setw(20) << records[position].lastPayDate << records[position].accBalance << endl;

	cout << "\n========= End of Search Record =========\n\n";
	menu(records);		//Send user to menu after displaying the information 
}

//================ Delete Record ================
void deleteRec(vector<CustomerRecords>& records)
{
	cout << "\n\n========= Delete Customer Record =========\n\n";
	string searchName = getName();						//Calling function to get the name user wants to search
	int position = linearSearch(records, searchName);	//Calling function to get the index where the name is in the vector

	cout << "Deleting " << searchName << " record..." << endl;
	records.erase(records.begin() + position);		//Erases all information stored in the vector at the index found at the name inputted by the user

	cout << "\n========= End of Delete Customer Record =========\n\n";
	menu(records);		//Send user to menu after erasing info stored at vector index  
}

//================ Edit Record ================
void change(vector<CustomerRecords>& records)
{
	cout << "\n\n========= Customer Record Change =========\n\n";
	string searchName = getName();						//Calling function to get the name user wants to search
	int position = linearSearch(records, searchName);	//Calling function to get the index where the name is in the vector

	string userInfoChange;	//Store's what variable the user would like to change
	cout << "Which Info Would You Like to Change?" << endl;
	cout << "Enter Either 'Name', 'Address', 'City', 'State', 'Zip', 'Phone', 'PayDate', 'AccBalance'" << endl;
	cin >> userInfoChange;
	cin.ignore();	//Ignore input so it doesnt get stored in other string variables

	if (userInfoChange == "Name")			//If the user types 'Name'
	{
		cout << "Enter the new Name \n";
		getline(cin, records[position].name);	//Store's changed aame inputted by the user
	}
	else if (userInfoChange == "Address")	//If the user types 'Address'
	{
		cout << "Enter the address \n";
		getline(cin, records[position].address);	//Store's changed address inputted by the user
	}
	else if (userInfoChange == "City")		//If the user types 'City'
	{
		cout << "Enter the new City \n";
		getline(cin, records[position].city);	//Store's changed City inputted by the user
	}
	else if (userInfoChange == "State")		//If the user types 'State'
	{
		cout << "Enter the new State \n";
		getline(cin, records[position].state);	//Store's changed state inputted by the user
	}
	else if (userInfoChange == "Zip")		//If the user types 'Zip'
	{
		cout << "Enter the new Zip \n";
		getline(cin, records[position].zip);	//Store's changed zip code inputted by the user
	}
	else if (userInfoChange == "Phone")		//If the user types 'Phone'
	{
		cout << "Enter the new Phone Number \n";
		getline(cin, records[position].phoneNum);	//Store's changed phone number inputted by the user
	}
	else if (userInfoChange == "PayDate")	//If the user types 'PayDate'
	{
		cout << "Enter the new Last Pay Date \n";
		getline(cin, records[position].lastPayDate);	//Store's changed last date of payment inputted by the user
	}
	else if (userInfoChange == "AccBalance")	//If the user types 'AccBalance'
	{
		cout << "Enter the new Account Balance \n";
		cin >> records[position].accBalance;	//Store's changed account balance inputted by the user

		while (records[position].accBalance < 0)	//Input Validation if user inputs negative account balance
		{
			cout << "\nAccount Balance can NOT be a negative number.\n"
				<< "Please input a positive account balance\n\n$";
			cin >> records[position].accBalance;			// Store the user's proper account balance inputted by user
			cout << endl;
		}
	}
	else
	{
		cout << "\n" << userInfoChange << " is not an option\n";		//Input Validation if the user inputs an invalid option
		cout << "\n========= End of Customer Record Change =========\n\n";
		menu(records);	//Sends user back to the menu if the inputs is to change something not there
	}
	cout << "\n========= End of Customer Record Change =========\n\n";
	menu(records);	//Sends user back to menu after the change to the record is changed
}

//========== Display All Records ============
void display(vector<CustomerRecords>& records)
{
	cout << right << "\nName" << setw(27) << "Address" << setw(23) << "City" << setw(19) << "State" << setw(12) << "Zip" << setw(17) << "Phone Number" << setw(17) << "Last Pay Date" << setw(19) << "Account Balance\n";	//Display header
	for (int r = 0; r < records.size(); r++)
	{
		cout << left << setw(19) << records[r].name << setw(30) << records[r].address << setw(19) << records[r].city
			<< setw(13) << records[r].state << setw(9) << records[r].zip << setw(17) << records[r].phoneNum
			<< setw(20) << records[r].lastPayDate << records[r].accBalance << endl;
	}
	cout << "\n\n";
	menu(records);	//Calls menu function
}

//================ Main Menu ================
void menu(vector<CustomerRecords>& records)
{
	string choice;	//Store's the choice made by user in the menu
	cout << "=========== Menu ===========\n";
	cout << "1 | Enter New Customer Record\n";
	cout << "2 | Display Customer Record\n";
	cout << "3 | Delete Customer Record\n";
	cout << "4 | Change Customer Record\n";
	cout << "5 | Display All Customers\n";
	cout << "============================\n";
	getline(cin, choice);

	while (choice > "5" || choice < "1")	//Input validation if the user inputs anything other than a number higher than 5 or lower than 1
	{
		cout << "\nInput Validation Only Numbers 1-5" << endl;
		getline(cin, choice);
		cout << "\n";
	}

	if (choice == "1")	//If the user inputs 1 to insert a new record calls the insert function 
	{
		insert(records);
	}
	else if (choice == "2")	//If the user inputs 2 to display a record calls the search function	
	{
		search(records);
	}
	else if (choice == "3")	//If the user inputs 3 to delete a record calls the deleteRec function
	{
		deleteRec(records);
	}
	else if (choice == "4")	//If the user inputs 4 to change a record calls the change function
	{
		change(records);
	}
	else if (choice == "5")	//If the user inputs 5 to display all records calls the display function
	{
		display(records);
	}
}

//================ Main ================
int main()
{
	vector<CustomerRecords> records;	//Delecaration of CustomerRecords object vector records   
	menu(records);	//Call menu function
}
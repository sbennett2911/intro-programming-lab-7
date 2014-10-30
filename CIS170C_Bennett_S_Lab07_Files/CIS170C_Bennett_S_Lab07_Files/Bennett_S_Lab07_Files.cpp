/*Developer: Steven Bennett
	Assignment: Week 7 Lab 7 I/O Files
	Date: April 19, 2013 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

void menu(void);
void writeData(void);
void readData(void);
string * split(string, char);

const char FileName[] = "TestAddress.txt";
const char delimiter = ',';

int main()
{
	cout << "Welcome to Address Book.\n" << endl;
	menu();
	return 0;
}

void menu(void)
{
//allow user to choose to append records, display records or exit the program
	char choice;
	do
	{
		cout << "(A)ppend Records, (S)how Records, (E)xit" << endl;
		cout << "Enter Selection: ";
		cin >> choice;
		cin.ignore();
		cout << endl;
		switch (choice)
		{
			case 'A': case 'a':
				writeData();
				break;
			case 'S': case 's':
				readData();
				break;
			case 'E': case 'e':
				cout << "Good-Bye" << endl;
				break;
			default:
				cout << "Invalid Selection" << endl;
				break;
		}
		cout << endl;
	} while (choice != 'E' && choice != 'e'); 	
}


void writeData(void)
{
//write the Address Infor to a file
	//output message notifying user of what menu they are using
	
	cout << "Append Records\n" << endl;
	
	ofstream TestAddressFile; //instatiate file output object
	TestAddressFile.open("TestAddress.txt", ios::app) ; //creates file TestAddress.txt
	if (TestAddressFile.is_open())
	{
		//variable declaration
		string name = " ";
		string street = " ";
		string city = " ";
		string state = " ";
		string zipCode = " ";
		char selection = ' ';

		do//loop to allow user to enter numerous address records
		{
			cout << "Name...........";
			getline(cin, name);
			cout << "Street.........";
			getline(cin, street);
			cout << "City...........";
			getline(cin, city);
			cout << "State..........";
			getline(cin, state);
			cout << "Zip Code.......";
			getline(cin, zipCode);
			TestAddressFile << name << delimiter;
			TestAddressFile << street << delimiter;
			TestAddressFile << city << delimiter;
			TestAddressFile << state << delimiter;
			TestAddressFile << zipCode << endl;

			cout << "\nEnter another record? (Y/N) ";
			cin >> selection;
			cin.ignore();
			cout << endl;
		} while (selection == 'Y' || selection == 'y');

		TestAddressFile.close(); //close file
	}
	else
		cout << "File not opened" << endl;
}

void readData(void)
{
//read data from a file
	ifstream TestAddressFile("TestAddress.txt", ios::in);
	if (TestAddressFile.is_open())
	{
		string recBreaks = "";
		recBreaks.assign(20, '-');

		int recordCount = 1;
		cout << "Address Records" << endl;

		//read the first record
		string buffer;
		getline(TestAddressFile, buffer, '\n');
			while (!TestAddressFile.eof())
			{
				string *theFields = split(buffer, delimiter); //call to split() to separate fields in CSV file.

				//display line records
				cout << recBreaks << endl;
				cout << "Record #" << recordCount << endl;
				cout << "Name........." << theFields[0] << endl;
				cout << "Street......." << theFields[1] << endl;
				cout << "City........." << theFields[2] << endl;
				cout << "State........" << theFields[3] << endl;
				cout << "ZipCode......" << theFields[4] << endl;
				recordCount++;
				getline(TestAddressFile, buffer, '\n');
			}
		cout << recBreaks << endl;
		TestAddressFile.close();
	}
	else
		cout << "Error: could not open file:" << endl;
}


string *split(string theLine, char theDelimiter)
{
	/*break theLine into fields and save the fields to an array.
	//Each field will occupy one element in a character array.
	//theLine is a string with fields separated with theDelimiter character.
	//Assumes the last field in the string is terminated with a newline.
	//Usage: string *theFields = split(lineBuffer, ',');*/

	/*determine how many splits there will be so we can size our array*/
	int splitCount = 0;
	for(int i = 0; i < theLine.size(); i++)
	{
		if(theLine[i] == theDelimiter)
			splitCount++;
	}
	splitCount++; /*addone more to the count because there is not an ending comma*/

	/*create an array to hold the fields*/
	string * theFieldArray;
	theFieldArray = new string[splitCount];

	/*split the string into seperate fields*/
	string theField ="";
	int commaCount = 0 ;

	for(int i = 0; i < theLine.size(); i++)
	{
		/*read each character and look for the delimiter*/
		if(theLine[i] != theDelimiter)
		{
			theField += theLine[i];//build the field
		}
		else
		{
			theFieldArray[commaCount] = theField; //save the field to the array
			theField = "";
			commaCount++;
		}
	}

	theFieldArray[commaCount] = theField; /*the last field is not marked with a comma.*/

	return theFieldArray;
}//end split


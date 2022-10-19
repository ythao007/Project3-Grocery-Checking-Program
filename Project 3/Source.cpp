/*
Author: Yeng Thao
Date 10/12/2022
Assignment: Project 3
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip> // For setw()
#include <fstream> // For reading files

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Validates user choice
bool validateUserChoice(int value, int min, int max) {
	/*
	If the value is less than or equal to min
	Or greater than or eqaul to max, return true
	*/
	if ((value >= min) || (value <= max)) {
		return true;
	}
	// Otherwise, return false
	else {
		return false;
	}

	return false;
}


// Displays the Main Menu
void displayMenu() {
	// Changes the font color to green with a black background
	system("Color 0A");

	// Sets "Main Menu" in the middle
	cout << setw(30) << "MAIN MENU" << endl;
	cout << endl;
	cout << "1 - List of all items purchased and its frequency" << endl;
	cout << "2 - Frequency of a specific item" << endl;
	cout << "3 - Histogram list of all items purchased and its frequency" << endl;
	cout << "4 - Exit Program" << endl;
	cout << endl;
}

void inventoryItemsHistogram() {
	/*
	Writes the output to frequency.dat file
	Calls the CallProcedure method from Source.cpp
	Uses the output method from the PythonCode.py in the CallProcedure method
	*/
	cout << endl;
	cout << "WRITE OUTPUT TO frequency.dat" << endl;
	CallProcedure("output");

	// Read the frequency.dat file, and create the histogram using C++

	// Create new file object for reading
	ifstream fileIn;

	// Open a file to perform read operation using file object
	fileIn.open("frequency.dat");

	// Checks if file failed to open
	if (!fileIn.is_open()) {
		cout << "The file failed to open." << endl;
	}

	// Checks that the file did not fail to open
	if (!fileIn.fail()) {
		// To store data contents from the file
		string itemName;
		int itemFrequency;

		// Special caharacter for histogram
		char c = '*';

		// Reads from the file and points data contents to respective variable
		while (fileIn >> itemName >> itemFrequency) {
			cout << itemName << " ";

			/*
			For loop to loop through the frequency and replacing the integer with
			the numeric amount of a special character
			*/
			for (unsigned int i = 0; i < itemFrequency; i++) {
				cout << c;
			}

			cout << endl;
		}
	}

	// Closes the file
	fileIn.close();
}

// Main function for compiling and running program
void main()
{
	// Varibles for user inputs
	int userInput;
	string userItem;

	// Displays the Main Menu
	displayMenu();

	// Get user input
	cin >> userInput;

	// While loop to loop through menu choices
	while (validateUserChoice(userInput, 1, 4) == true) {
		// Switch case for Main Menu options using userInput
		switch (userInput) {
			/*
			Menu option 1
			List of all items and its frequency
			Uses the CallProcedure method from Soucre.cpp
			Uses the determineInventory method from PythonCode.py
			*/
		case 1:
			cout << endl;
			cout << "TOTAL INVENTORY" << endl;
			CallProcedure("determineInventory");
			cout << endl;
			break;

			/*
			Menu option 2
			Outputs a specifc item and its frequency
			Uses the callIntFunc(string, string) method from Source.cpp
			Uses the determineFrequency method from PythonCode.py
			*/
		case 2:
			//Gets user item
			cout << endl;
			cout << "Enter an item you'd like to see the frequency of:" << endl;
			cin >> userItem;

			// Capitalizes the first letter of the string
			userItem[0] = toupper(userItem[0]);

			cout << endl;
			cout << userItem << " occur " << callIntFunc("determineFrequency", userItem) 
				<< " times" << endl;
			cout << endl;
			break;

			/*
			Menu option 3
			Outputs the histogram list of all items and it's frequency
			Uses the inventoryItemsHistogram() method from Source.cpp
			*/
		case 3:
			cout << endl;
			inventoryItemsHistogram();
			cout << endl;
			break;

			/*
			Menu option 4
			Exits the Program
			*/
		case 4:
			exit(0);
			break;

			// Default to handle exception
		default:
			cout << endl;
			cout << "Invalid input. Please enter a number between 1 - 4" << endl;
			cout << endl;
			break;
		}

		// Displays the menu again
		displayMenu();

		// Gets user input to validate again
		cin >> userInput;
	}
}

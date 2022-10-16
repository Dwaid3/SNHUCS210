
/*

Project 3 Corner Grocer
By: David Waid

*/

#define NOMINMAX
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <limits>
#include <array>
#include <fstream>
#include <stdlib.h>
#include <iomanip>


using namespace std;

int userChoice = 0;
string itemToCheck;
int* userChoicePtr = &userChoice;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


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
void callPyFunc(string pName)
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
int callPyFunc(string proc, string param)
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
	if (param == "q")
	{
		cout << "cleaning up. Goodbye.";
		//printf("Result is %d\n", _PyLong_AsInt(presult));
		Py_DECREF(pValue);
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);
		// Finish the Python Interpreter
		Py_Finalize();
		delete[] procname;
	}
	else {
		// clean 
		delete[] procname;
	}

	return _PyLong_AsInt(presult);
}






void printMenu()
{
	//These will hold old necessary values for the menu functionality
	string line;
	string item;
	int total;
	string options[] = { "Show list of items purchased and the amount of times said item was purchased " , "Find out how many times the items you choose was purchased" ,"Display a histogram of items purchased and the amount of times said item was purchased", "Exit" };
	//This will class let us open the file and read from it
	ifstream fileStream("freq.dat");


	//This will loop until the 
	while (userChoice != 4)
	{
		//This will print menu for user to select function
		cout << "Choose an Option:" << endl;

		for (int i = 0; i < 4; ++i)
		{
			cout << i + 1 << ": " << options[i] << endl;

		}

		//This will print the options
		cin >> userChoice;
		while (std::cin.fail() || userChoice < 0 || userChoice > 4)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter 1-4: ";
			//This will catch invalid input
			cin >> userChoice;

		}


		//This switch statments will choose functions or exit program based on userChoice
		switch (userChoice)
		{
		case 1:
			callPyFunc("listOfItems");
			break;
		case 2:

			cout << "Choose the item that you want to check the quantity bought: ";
			cin >> itemToCheck;
			while (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad entry.  Enter a valid entry: ";
				//This will catch invalid input
				cin >> itemToCheck;

			}
			callPyFunc("quantityBought", itemToCheck);
			break;
		case 3:
			
			callPyFunc("createHistogram");

			cout << setw(20) << left << "ITEM" << setw(55) << right << "TOTAL BOUGHT" << endl;
			cout << string(75, '-') << endl;
			//This class will allow us to change output color

			while (getline(fileStream, line)) {
				
				item = line;
				getline(fileStream, line);
				total = stoi(line);
				cout << setw(20) << left << item;
				
				SetConsoleTextAttribute(hConsole, 1);
				cout << setw(55) << right << string(total, '*') << endl;
				SetConsoleTextAttribute(hConsole, 15);
				
			}
			cout << endl;

			break;

		case 4:
			callPyFunc("Cleaning up", "q");
			break;
		}


	}
	
}

void main()
{
	printMenu();
}
/* GroceryTracking is a class that read sa text file of grocery purchases and display results depending on choice of the user
   Starting code provided by Professor Noss.
   @author Anthony Minunni
   @date 4/18/2021 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

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


void main()
{

	bool run = true; //boolean that will be used in while loop
	int choice = 0; //int that will be used for user numerical inputs

	while (run) {
		string answer; //string for try-except block to test user input
		string next; //string used whereever "enter any key to continue" prompt appears

		cout << "1: Show how many of every item appears" << endl;
		cout << "2: Search for a particular item" << endl;
		cout << "3: Display a histogram of the items" << endl;
		cout << "4: Exit" << endl;
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

		//try-catch block in event user's input cannot be converted to int
		try {
			getline(cin, answer);
			choice = stoi(answer);
		}
		catch (exception e) {
			answer = "null";
			choice = 0;
			cout << "Choice could not be computed. Try again." << endl;
			cout << "Press enter to continue." << endl;
			getline(cin, next);
			cin.clear();
		}

		//if statement to see if user entered int that is not a valid option of 1 - 4
		if (choice != 0) {
			if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
				cout << "Not a valid option. Try again." << endl;
				cout << "Press enter to continue" << endl;
				getline(cin, next);
				cin.clear();
			}
		}

		//switch statement for valid user options
		switch (choice) {
		//case 1 calls the Python method "TotalItems"
		case 1:
			CallProcedure("TotalItems");
			cout << "Results are in frequency.dat" << endl;
			cout << "Press enter to continue" << endl;
			getline(cin, next);
			cin.clear();
			break;
		//case 2 asks for additional user input then calls the Python method "FindItem"
		case 2:
			cout << "What would you like to find?" << endl;
			getline(cin, answer);
			cout << "Number of " << answer << " bought: " << callIntFunc("FindItem", answer) << endl;
			cout << "Press enter to continue" << endl;
			getline(cin, next);
			cin.clear();
			break;
		//case 3 calls the Python method "Histogram"
		case 3:
			CallProcedure("Histogram");
			cout << "Press enter to continue" << endl;
			getline(cin, next);
			cin.clear();
			break;
		//case 4 exits the program
		case 4:
			cout << "Goodbye!" << endl;
			run = false;
			break;
		}
	}

}
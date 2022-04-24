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
	PyRun_SimpleString("import sys");                                  //                  Added per advice from stack overflow
	PyRun_SimpleString("sys.path.append(\".\")");                      //                  Added per advice from stack overflow

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
	PyRun_SimpleString("import sys");                                  //                  Added per advice from stack overflow
	PyRun_SimpleString("sys.path.append(\".\")");                      //                  Added per advice from stack overflow

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
	PyRun_SimpleString("import sys");                                  //                  Added per advice from stack overflow
	PyRun_SimpleString("sys.path.append(\".\")");                      //                  Added per advice from stack overflow

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



//CallProcedure("printsomething");
//cout << callIntFunc("PrintMe", "House") <<
//cout << callIntFunc("SquareValue", 2);

int uin = 0; //user menu choice
int NumItem = 0; //number of the item purchased
string Item = " "; //item name
bool looper = true; // while loop control
int i = 0; //for loop control

void main()
{
	while (looper == true) { //main while loop

		//display menu
		cout << "Please select an option." << endl;
		cout << "1: Display total sales." << endl;
		cout << "2: Display sales of a specific item." << endl;
		cout << "3: Graph total sales." << endl;
		cout << "4: Exit." << endl << endl;

		cin >> uin; //user selection
		cout << endl;

		if (uin == 1) {
			CallProcedure("makeList");  //makeList call
			cout << endl;
			cout << endl;

		} //end 1

		else if (uin == 2) {
			cout << "Please enter the desired item." << endl; //get item input
			cin >> Item;
			NumItem = callIntFunc("countItem", Item); // countItem call
			cout << NumItem << " " << Item << " sold."; //item output
			cout << endl;
			cout << endl;


		} //end 2

		else if (uin == 3) {
			CallProcedure("makeGraph");  // makeGraph call
			cout << endl;
			cout << endl;
		}// end 3

		else if (uin == 4) {
			looper = false; // breaks while loop
			break;
		} // end 4

		else {
			cout << "Please enter a valid repsonse." << endl; // validation check
		} // end else


	}//end while

	cout << "Goodbye." << endl; //end text
} // end main
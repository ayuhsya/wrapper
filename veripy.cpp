#include <Python.h>
#include "include/NBioAPI.h"
#include <string.h>
#include <iostream>

// Functions to be called from Python
NBioAPI_HANDLE g_hBSP;
NBioAPI_DEVICE_ID m_DeviceID;
NBioAPI_RETURN ret;

static PyObject* py_veripy(PyObject* self, PyObject* args){
	const char *text_stream1;
	const char *text_stream2;
	if(!PyArg_ParseTuple(args, "ss", &text_stream1, &text_stream2)){
		std::cout << "Unable to fetch arguments.\n";
		return 0;
	}
	if ( NBioAPI_Init(&g_hBSP) != NBioAPIERROR_NONE ){
		std::cout<<"Init Failed";
		return 0;
	}
	// Uncomment to print arguments
	//printf("\n%s\n\n%s",text_stream1,text_stream2);

	NBioAPI_BOOL result;
	NBioAPI_INPUT_FIR storedFIR1, storedFIR2;

	NBioAPI_FIR_TEXTENCODE g_storedTextFIR1, g_storedTextFIR2; // Set input FIR.
	g_storedTextFIR1.IsWideChar = NBioAPI_FALSE;			// It depends on application
	int length = strlen(text_stream1);
	g_storedTextFIR1.TextFIR = new NBioAPI_CHAR [length + 1];
	memcpy(g_storedTextFIR1.TextFIR, text_stream1, length + 1);

	storedFIR1.Form = NBioAPI_FIR_FORM_TEXTENCODE; // stored FIR
	storedFIR1.InputFIR.TextFIR = &g_storedTextFIR1;

	// Read input stream and convert into FIR(fir2)
	g_storedTextFIR2.IsWideChar = NBioAPI_FALSE;			// It depends on application
	length = strlen(text_stream2);
	g_storedTextFIR2.TextFIR = new NBioAPI_CHAR [length + 1];
	memcpy(g_storedTextFIR2.TextFIR, text_stream2, length + 1);

	storedFIR2.Form = NBioAPI_FIR_FORM_TEXTENCODE; // stored FIR
	storedFIR2.InputFIR.TextFIR = &g_storedTextFIR2;
	
	ret = NBioAPI_VerifyMatch( // Matching use with stored FIR
	g_hBSP,		// Handle of NBioBSP module
	&storedFIR1,	// stored FIR
	&storedFIR2,	// input FIR for matching
	&result,	// Result of matching
	NULL	// Payload
	);
	if ( result == NBioAPI_TRUE){
		return Py_BuildValue("i", 1); // Matched successfully
	}
	else{
		return Py_BuildValue("i", 0);
	}
}

// Bind Python function names to our C functions
static PyMethodDef veripy_methods[] = {
	//{"myFunction", py_myFunction, METH_VARARGS},
	{"veripy", py_veripy, METH_VARARGS},
	{NULL, NULL}
};

// Python calls this to let us initialize our module
extern "C" void initveripy(){
	(void) Py_InitModule("veripy", veripy_methods);
}
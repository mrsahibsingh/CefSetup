#include "ClientV8ExtensionHandler.h"
#include <atlstr.h>

ClientV8ExtensionHandler::ClientV8ExtensionHandler(CefRefPtr<CefApp> app)
{
	this->app = app;
}

bool ClientV8ExtensionHandler::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval, CefString &exception)
{

	if (name == "printSomething")
	{
		MessageBox(NULL, "HELLO", "HELLO", NULL);
		return true;
	}

	return false;
}
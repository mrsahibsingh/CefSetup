
#include "ClientApp.h"
#include "ClientHandler.h"
#include "ClientV8ExtensionHandler.h"

SimpleApp::SimpleApp()
{

}

void SimpleApp::OnWebKitInitialized()
{
	std::string app_code =
		"var test;"
		"if (!test)"
		"  test = {};"
		"(function() {"
		""
		"})();";
	CefRegisterExtension("v8/app", app_code, new ClientV8ExtensionHandler(this));
}


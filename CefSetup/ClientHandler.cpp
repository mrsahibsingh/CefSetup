
#include "ClientHandler.h"
#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

SimpleHandler::SimpleHandler()
{

}


bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	return false;
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	if (!m_Browser.get()) {
		// We need to keep the main child window, but not popup windows
		m_Browser = browser;
		m_BrowserHwnd = browser->GetHost()->GetWindowHandle();
	}
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (m_BrowserHwnd == browser->GetHost()->GetWindowHandle()) {
		// Free the browser pointer so that the browser can be destroyed
		m_Browser = NULL;
	}
}
//Defining OnBeforeContextmenu Function Defined in CefContextMenuHandler
void SimpleHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
	// Clears the menu open on right mouse click. Returns true on success.
	model->Clear();
}

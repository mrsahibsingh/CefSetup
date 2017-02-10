// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"
#include "include/cef_render_process_handler.h"
#include "include/cef_client.h"
#include "include/cef_v8.h"
#include "include/cef_browser.h"
#include <list>

class SimpleHandler : public CefClient, public CefDisplayHandler, public CefLifeSpanHandler, public CefLoadHandler, public CefContextMenuHandler
{
public:
	SimpleHandler();
	CefRefPtr<CefBrowser> GetBrowser()
	{
		return m_Browser;
	}

	CefWindowHandle GetBrowserHwnd()
	{
		return m_BrowserHwnd;
	}

	// CefClient methods
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}
	//Disable Right-Click
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() OVERRIDE
	{
		return this;
	}


	// Virutal on CefLifeSpanHandler
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	//Overriding OnBeforeContextmenu Function Defined in CefContextMenuHandler
	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) OVERRIDE;

protected:
	// The child browser window
	CefRefPtr<CefBrowser> m_Browser;

	// The child browser window handle
	CefWindowHandle m_BrowserHwnd;

	CefContextMenuHandler *mnuHandler;

	// /
	// Macro that provides a reference counting implementation for classes extending
	// CefBase.
	// /
	IMPLEMENT_REFCOUNTING(SimpleHandler);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

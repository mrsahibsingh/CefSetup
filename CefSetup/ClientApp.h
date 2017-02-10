// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"
#include "include/cef_client.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp,
	public CefRenderProcessHandler {
public:
	SimpleApp();

	// CefApp methods:
	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	// CefBrowserProcessHandler methods:
	void OnWebKitInitialized() OVERRIDE;
	IMPLEMENT_REFCOUNTING(SimpleApp);

};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

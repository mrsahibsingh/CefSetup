
#include <windows.h>
#include "ClientApp.h"
#include "ClientHandler.h"
#include "include/cef_sandbox_win.h"

std::string GetApplicationDir()
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR   wpath[MAX_PATH];
	GetModuleFileNameW(hModule, wpath, MAX_PATH);
	std::wstring wide(wpath);
	std::string path(wide.begin(), wide.end());
	path = path.substr(0, path.find_last_of("\\/"));
	return path;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{

	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
ATOM RegisterWndClass(HINSTANCE hInstance, LPCSTR lpszWndClassName)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = lpszWndClassName;
	return RegisterClassEx(&wcex);
}
SimpleHandler *g_handler = 0;
HWND RegisterWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND hwnd;
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Test";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowEx(WS_EX_LAYERED,
		"Test", "Test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	return hwnd;
}

LRESULT CALLBACK MessageWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}
HWND CreateMessageWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc = {
		0
	};

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = MessageWndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "ClientMessageWindow";
	RegisterClassEx(&wc);
	return CreateWindow("ClientMessageWindow", 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, hInstance, 0);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {


	CefMainArgs main_args(hInstance);

	CefRefPtr<SimpleApp> app(new SimpleApp);

	// Execute the secondary process, if any.
	int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
	if (exit_code >= 0) {
		exit(exit_code);
	}

	// Register the window class.
	HWND hwnd = RegisterWindow(hInstance, nCmdShow);

	if (hwnd != NULL)
	{
		MSG  msg;
		SetLayeredWindowAttributes(hwnd, 0,
			(255 * 100) / 100, LWA_ALPHA);

		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);
	}
	//--------------------------------------------------


	//--------------------------------------------------
	RECT rect;
	GetClientRect(hwnd, &rect);

	CefSettings settings;
	CefInitialize(main_args, settings, app.get(), NULL);
	CefWindowInfo        info;
	CefBrowserSettings   b_settings;
	CefRefPtr<CefClient> client(new SimpleHandler);
	g_handler = (SimpleHandler *)client.get();
	std::string path = "https://www.google.co.in/";


	CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

	if (command_line->HasSwitch("url")) {
		path = command_line->GetSwitchValue("url");
	}

	info.SetAsChild(hwnd, rect);
	CefBrowserHost::CreateBrowser(info, client.get(), path, b_settings, NULL);
	int result = 0;

	if (!settings.multi_threaded_message_loop) {
		// Run the CEF message loop. This function will block until the application
		// recieves a WM_QUIT message.
		CefRunMessageLoop();
	}
	else {
		// Create a hidden window for message processing.
		HWND hMessageWnd = CreateMessageWindow(hInstance);
		MSG  msg;

		// Run the application message loop.
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DestroyWindow(hMessageWnd);
		hMessageWnd = NULL;
		result = static_cast<int> (msg.wParam);
	}
	CefShutdown();
	return result;

}

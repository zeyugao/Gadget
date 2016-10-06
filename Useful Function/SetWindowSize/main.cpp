void SetWindowSize(HWND &hWnd,int nWidth,int nHeight)
{

	//hWnd = CreateWindowExW(0, szWindowClass, L"设置", WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),0, 0, nWidth, nHeight, hWndParent, nullptr, hInst, nullptr);
	
	RECT WindowRect, ClientRect;
	GetWindowRect(hWnd, &WindowRect);
	GetClientRect(hWnd, &ClientRect);

	nWidth += (WindowRect.right - WindowRect.left) - (ClientRect.right - ClientRect.left);
	nHeight += (WindowRect.bottom - WindowRect.top) - (ClientRect.bottom - ClientRect.top);

	int nX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
	int nY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;
	SetWindowPos(hWnd, nullptr, nX, nY, nWidth, nHeight, 0);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}
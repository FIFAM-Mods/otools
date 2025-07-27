#pragma once
#include "..\WinInclude.h"

struct IDirect3D9;
struct IDirect3DDevice9;

class D3DDevice {
	IDirect3D9 *mDirect3D = nullptr;
	IDirect3DDevice9 *mDevice = nullptr;
    HWND mWindowHandle = NULL;
    WNDCLASSEXW mWindowClass = {};
    bool mCreatedWindow = false;
public:
	D3DDevice(HWND hWnd);
    D3DDevice();
	~D3DDevice();
    void Create(HWND hwnd);
	IDirect3DDevice9 *Interface();
};

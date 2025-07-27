#include "D3DDevice.h"
#include "..\D3DInclude.h"
#include <stdexcept>

using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return DefWindowProcW(hWnd, msg, wParam, lParam); };

void D3DDevice::Create(HWND hWnd) {
	mDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!mDirect3D)
		throw runtime_error("D3DDevice: failed to create direct3d");
	static D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	IDirect3DDevice9 *device = nullptr;
	auto devResult = mDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mDevice);
	if (FAILED(devResult)) {
		mDirect3D->Release();
		mDirect3D = nullptr;
		static char errMsg[512];
		sprintf(errMsg, "D3DDevice: failed to create direct3d device (Error %X)", devResult);
		throw runtime_error(errMsg);
	}
}

D3DDevice::D3DDevice() {
    static char errMsg[512];
    ZeroMemory(&mWindowClass, sizeof(mWindowClass));
    mWindowClass.cbSize = sizeof(WNDCLASSEXW);
    mWindowClass.style = CS_CLASSDC;
    mWindowClass.hInstance = 0;
    mWindowClass.lpszClassName = L"D3DDeviceWindow";
    mWindowClass.lpfnWndProc = WndProc;
    auto classResult = RegisterClassExW(&mWindowClass);
    if (classResult == 0) {
        sprintf(errMsg, "D3DDevice::D3DDevice(): Failed to register Window Class (%X / %d)", GetLastError(), GetLastError());
		throw runtime_error(errMsg);
    }
    mWindowHandle = CreateWindowExW(0, L"D3DDeviceWindow", L"D3DDevice", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, 0, 0, 0, 0);
    if (mWindowHandle == NULL) {
        sprintf(errMsg, "D3DDevice::D3DDevice(): Failed to create Window (%X / %d)", GetLastError(), GetLastError());
        throw runtime_error(errMsg);
    }
    mCreatedWindow = true;
    Create(mWindowHandle);
}

D3DDevice::D3DDevice(HWND hWnd) {
    Create(hWnd);
}

D3DDevice::~D3DDevice() {
	if (mDevice)
		mDevice->Release();
	if (mDirect3D)
		mDirect3D->Release();
    if (mCreatedWindow) {
        DestroyWindow(mWindowHandle);
        UnregisterClassW(L"D3DDeviceWindow", mWindowClass.hInstance);
    }
}

IDirect3DDevice9 * D3DDevice::Interface() { return mDevice; }

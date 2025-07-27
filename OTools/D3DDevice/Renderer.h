#pragma once
#include "..\WinInclude.h"
#include "..\D3DInclude.h"
#include "D3DDevice.h"

class Renderer {
	IDirect3DDevice9 *mDevice = nullptr;
    IDirect3DSurface9 *mRT = nullptr;
    bool mAvailable = false;
public:
    struct Vertex {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float rwh = 1.0f;
        D3DCOLOR color = 0;
    };
    Renderer(D3DDevice *device, int w, int h);
	~Renderer();
    bool Available();
    IDirect3DDevice9 *Device();
    bool Begin();
    bool End();
    bool SaveRT(wchar_t const *path, D3DXIMAGE_FILEFORMAT ff = D3DXIFF_PNG);
    bool RenderTriangles(unsigned int numIndices, unsigned int *indices, Vertex *vertices, unsigned int numVertices);
};

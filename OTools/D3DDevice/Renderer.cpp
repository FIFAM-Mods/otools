#include "Renderer.h"

Renderer::Renderer(D3DDevice *device, int w, int h) {
    mDevice = device->Interface();
    auto sampling = D3DMULTISAMPLE_NONE;
    if (!FAILED(mDevice->CreateRenderTarget(w, h, D3DFMT_A8R8G8B8, sampling, sampling, FALSE, &mRT, NULL))) {
        if (FAILED(mDevice->SetRenderTarget(0, mRT))) {
            mRT->Release();
            mRT = nullptr;
        }
        else
            mAvailable = true;
    }
}

bool Renderer::Available() {
    return mAvailable;
}

IDirect3DDevice9 *Renderer::Device() {
    return mDevice;
}

bool Renderer::Begin() {
    if (FAILED(mDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 255)))
        return false;
    if (FAILED(mDevice->BeginScene()))
        return false;
    return true;
}

bool Renderer::End() {
    if (FAILED(mDevice->EndScene()))
        return false;
    return true;
}

bool Renderer::SaveRT(wchar_t const *path, D3DXIMAGE_FILEFORMAT ff) {
    if (mRT) {
        if (FAILED(D3DXSaveSurfaceToFileW(path, ff, mRT, NULL, NULL)))
            return false;
        return true;
    }
    return false;
}

bool Renderer::RenderTriangles(unsigned int numIndices, unsigned int *indices, Vertex *vertices, unsigned int numVertices) {
    LPDIRECT3DINDEXBUFFER9 indexBuffer = nullptr;
    mDevice->CreateIndexBuffer(numIndices * sizeof(UINT), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &indexBuffer, NULL);
    UINT *pIndexData = nullptr;
    indexBuffer->Lock(0, 0, (void **)&pIndexData, 0);
    CopyMemory(pIndexData, indices, numIndices * sizeof(UINT));
    indexBuffer->Unlock();
    mDevice->SetIndices(indexBuffer);
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer = nullptr;
    mDevice->CreateVertexBuffer(numVertices * sizeof(Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
    Vertex *pVertexData = nullptr;
    vertexBuffer->Lock(0, numVertices * sizeof(Vertex), (void **)&pVertexData, 0);
    CopyMemory(pVertexData, vertices, numVertices * sizeof(Vertex));
    mDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
    mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    mDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numIndices / 3);
    indexBuffer->Release();
    vertexBuffer->Release();
    return true;
}

Renderer::~Renderer() {
    if (mRT)
        mRT->Release();
}

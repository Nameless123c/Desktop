#include "pch.h"
#include "FileService.h"
#include "ChangeFormat.h"

CImage* FileService::LoadImageFromFile(const std::string& path) {
    CImage* pImage = new CImage();
    CA2W wPath(path.c_str(), CP_UTF8);

    HRESULT hr = pImage->Load(wPath);
    if (FAILED(hr)) {
        delete pImage;
        return nullptr;
    }

    return pImage;
}
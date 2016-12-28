// ToAcroPDF2.cpp : CToAcroPDF2 の実装
#include "stdafx.h"
#include "ToAcroPDF2.h"


// CToAcroPDF2

LRESULT CToAcroPDF2::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (m_hWndCD == NULL)
		return 0;

	RECT clientRect = {0};
	GetClientRect(&clientRect);
	HWND hwndPDF = GetDlgItem(IDC_PDF1);
	if (hwndPDF != NULL) {
		::MoveWindow(hwndPDF, 0, 0, clientRect.right, clientRect.bottom, true);
	}

	return 0;
}

static LPCWSTR TRY_QUEUED_SRC = L"c312a127-c910-4ca2-8288-ce8d59c542c1";

void CToAcroPDF2::Setsrc(LPCWSTR pcwSrc) {
	if (pcwSrc == TRY_QUEUED_SRC) {
		if (m_hWndCD == NULL) {
			return;
		}
		pcwSrc = queuedSrc;
		queuedSrc.Empty();
	}
	else {
		if (m_hWndCD == NULL) {
			queuedSrc = pcwSrc;
			return;
		}
	}
	HRESULT hr;
	CComPtr<IDispatch> pDisp;
	if (SUCCEEDED(hr = GetDlgControl(IDC_PDF1, IID_IDispatch, reinterpret_cast<void **>(&pDisp)))) {
		CComVariant srcProp = pcwSrc;
		if (SUCCEEDED(hr = pDisp.PutPropertyByName(L"src", &srcProp))) {
			return;
		}
	}
}

bool CToAcroPDF2::LoadFromMoniker(LPBC pibc, LPMONIKER pMonikerDL) {
	HRESULT hr;

	bool ok = false;

	if (pMonikerDL != NULL) {
		if (!ok) {
			// ファイル名が出た→Setsrc
			// URLが出た→今は何もしない
			LPOLESTR lpcw = NULL;
			if (SUCCEEDED(hr = pMonikerDL->GetDisplayName(pibc, NULL, &lpcw))) {
				WCHAR wcfp[1000] = {0};
				DWORD cchfp = 256;
				if (!ok && UrlIsFileUrl(lpcw)) {
					if (SUCCEEDED(hr = PathCreateFromUrl(lpcw, wcfp, &cchfp, NULL))) {
						Setsrc(wcfp);
						ok = true;
					}
				}
				if (!ok && PathIsURL(lpcw)) {

				}
				CoTaskMemFree(lpcw);
			}
		}
		if (!ok) {
			// URL等のモニカ読み込み(asynchronous moniker)
			CComPtr<IBindCtx> pibcAsync;
			if (SUCCEEDED(hr = CreateAsyncBindCtx(0, this, NULL, &pibcAsync))) {
				CComPtr<IStream> pSt;
				hr = pMonikerDL->BindToStorage(pibcAsync, NULL, IID_IStream, reinterpret_cast<void **>(&pSt));
				if (hr == S_OK) {
					if (LoadSyncSt(pSt)) {
						ok = true;
					}
				}
				else if (hr == MK_S_ASYNCHRONOUS) {
					isAsyncDownload = true;
					curPos = maxPos = 0;
					statusText.Empty();
					pStreamAsync.Release();
					ok = true;
				}
			}
		}
		if (!ok) {
			// URL等のモニカ読み込み(not asynchronous moniker)
			CComPtr<IStream> pSt;
			if (SUCCEEDED(hr = pMonikerDL->BindToStorage(pibc, NULL, IID_IStream, reinterpret_cast<void **>(&pSt)))) {
				if (LoadSyncSt(pSt)) {
					return true;
				}
			}
		}
		if (ok) {
			return true;
		}
	}
	return false;
}

bool CToAcroPDF2::LoadSyncSt(LPSTREAM pStream) {
	if (loaded) {
		return false;
	}
	GUID tmpId = {0};
	CoCreateGuid(&tmpId);

	TCHAR fileName[MAX_PATH] = {0};
	_stprintf_s(fileName, _T("%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X.pdf")
		, 0U +tmpId.Data1
		, 0U +tmpId.Data2
		, 0U +tmpId.Data3
		, 0U +tmpId.Data4[0]
		, 0U +tmpId.Data4[1]
		, 0U +tmpId.Data4[2]
		, 0U +tmpId.Data4[3]
		, 0U +tmpId.Data4[4]
		, 0U +tmpId.Data4[5]
		, 0U +tmpId.Data4[6]
		, 0U +tmpId.Data4[7]
		);

	TCHAR tempPath[MAX_PATH] = {0};
	GetTempPath(MAX_PATH, tempPath);
	PathAppend(tempPath, fileName);

	if (tempFilePath.Length() != 0) {
		ATLVERIFY(DeleteFile(tempFilePath));
		tempFilePath.Empty();
	}

	tempFilePath = tempPath;

	HRESULT hr;
	HANDLE hFile = CreateFile(tempPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE && hFile != NULL) {
		BYTE buffer[4096];
		bool ok = true;
		while (true) {
			ULONG cbRead = 0;
			if (FAILED(hr = pStream->Read(buffer, sizeof(buffer), &cbRead))) {
				ok = false;
				break;
			}
			if (cbRead == 0) {
				break;
			}
			DWORD cbWritten = 0;
			if (!WriteFile(hFile, buffer, cbRead, &cbWritten, NULL)) {
				ok = false;
				break;
			}
		}
		CloseHandle(hFile);

		if (ok) {
			Setsrc(tempFilePath);
		}
	}
	loaded = true;
	return true;
}

LRESULT CToAcroPDF2::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Setsrc(TRY_QUEUED_SRC);
	return TRUE;
}

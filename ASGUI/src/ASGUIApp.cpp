#include "ASGUIApp.hpp"
#include "ASCore.hpp"
#include "CMainFrame.hpp"
#include <atlimage.h>

CASGUIApp theApp;

static const int FRAME_WIDTH = 640;
static const int FRAME_HEIGHT = 480;
unsigned char* g_frameBuffer = nullptr;
CImage g_image;

BOOL CASGUIApp::InitInstance() {
    CWinApp::InitInstance();

    // 윈도우 생성
    CMainFrame* pFrame = new CMainFrame();
    m_pMainWnd = pFrame;
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    // 카메라 초기화
    if (!InitCamera()) {
        AfxMessageBox(_T("웹캠 초기화 실패"));
        return FALSE;
    }

    // 버퍼와 이미지 초기화
    g_frameBuffer = new unsigned char[FRAME_WIDTH * FRAME_HEIGHT * 3];
    g_image.Create(FRAME_WIDTH, FRAME_HEIGHT, 24);

    // 타이머 시작 (윈도우에 바인딩됨)
    pFrame->SetTimer(1, 30, nullptr);

    return TRUE;  // 메시지 루프 시작
}

int CASGUIApp::ExitInstance() {
    if (m_pMainWnd)
        m_pMainWnd->KillTimer(1);

    ReleaseCamera();

    if (g_frameBuffer)
        delete[] g_frameBuffer;
    g_image.Destroy();

    return CWinApp::ExitInstance();
}

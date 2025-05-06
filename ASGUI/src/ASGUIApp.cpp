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

    // ������ ����
    CMainFrame* pFrame = new CMainFrame();
    m_pMainWnd = pFrame;
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    // ī�޶� �ʱ�ȭ
    if (!InitCamera()) {
        AfxMessageBox(_T("��ķ �ʱ�ȭ ����"));
        return FALSE;
    }

    // ���ۿ� �̹��� �ʱ�ȭ
    g_frameBuffer = new unsigned char[FRAME_WIDTH * FRAME_HEIGHT * 3];
    g_image.Create(FRAME_WIDTH, FRAME_HEIGHT, 24);

    // Ÿ�̸� ���� (�����쿡 ���ε���)
    pFrame->SetTimer(1, 30, nullptr);

    return TRUE;  // �޽��� ���� ����
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

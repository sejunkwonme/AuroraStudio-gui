#include "CMainFrame.hpp"
#include "ASCore.hpp"
#include <atlimage.h>

extern unsigned char* g_frameBuffer;
extern CImage g_image;
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_TIMER()
END_MESSAGE_MAP()

CMainFrame::CMainFrame() {
    Create(NULL, _T("Aurora Studio - Webcam Viewer"), WS_OVERLAPPEDWINDOW, CRect(100, 100, 800, 600));
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent != 1) return;

    if (GetFrameRGB(g_frameBuffer, FRAME_WIDTH, FRAME_HEIGHT)) {
        BYTE* dst = (BYTE*)g_image.GetBits();
        int pitch = g_image.GetPitch();
        for (int y = 0; y < FRAME_HEIGHT; ++y)
            memcpy(dst + y * pitch, g_frameBuffer + y * FRAME_WIDTH * 3, FRAME_WIDTH * 3);

        CClientDC dc(this);
        g_image.Draw(dc.m_hDC, 0, 0);
    }
}

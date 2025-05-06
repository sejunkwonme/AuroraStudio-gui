#pragma once
#include <afxwin.h>

class CMainFrame : public CFrameWnd {
public:
    CMainFrame();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    DECLARE_MESSAGE_MAP()
};

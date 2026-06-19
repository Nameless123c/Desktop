#include "pch.h"
#include "Main.h"
#include "afxdialogex.h"
#include "CFriendDlg.h"
#include "PaintService.h"
#include "CChatFriendDlg.h"
#include "FileService.h"


IMPLEMENT_DYNAMIC(CFriendDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CFriendDlg, CDialogEx)
	ON_WM_PAINT()
    ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_FRIEND_SUBMIT, &CFriendDlg::OnBnClickedBtnFriendSubmit)
END_MESSAGE_MAP()

CFriendDlg::CFriendDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRIEND_DIALOG, pParent)
{

}

CFriendDlg::~CFriendDlg()
{
}

void CFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_FRIEND_SUBMIT, m_btnNickName);
}

BOOL CFriendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    SetBackgroundColor(RGB(255, 255, 255));

	// btn NickName
	m_btnNickName.m_bDontUseWinXPTheme = TRUE;
	m_btnNickName.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_btnNickName.SetMouseCursorHand();
	m_btnNickName.m_bDrawFocus = FALSE;
	m_btnNickName.m_bTransparent = FALSE;
	m_btnNickName.SetFaceColor(RGB(28, 127, 217));
	m_btnNickName.SetTextColor(RGB(255, 255, 255));

	// tên
	m_fontTitle.CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Segoe UI Semibold"));

	GetDlgItem(IDC_STATIC_FRIEND_NICKNAME)->SetFont(&m_fontTitle);

    m_friendData.pAvatar = FileService::LoadImageFromFile(m_friendData.avatar);

    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FRIEND_NICKNAME);
    if (pEdit) {
        pEdit->SetCueBanner(_T("Nhập biệt danh..."));
    }

	return TRUE;
}

void CFriendDlg::OnPaint()
{
	CPaintDC dc(this);

    CWnd* pArea = GetDlgItem(IDC_STATIC_FRIEND_AVT);
    if (pArea) {
        CRect rectAvt;
        pArea->GetWindowRect(&rectAvt);
        ScreenToClient(&rectAvt);
        pArea->ShowWindow(SW_HIDE);

        PaintService::DrawAvatar(&dc, m_friendData.pAvatar,
            rectAvt.left, rectAvt.top,
            rectAvt.Width(), rectAvt.Height());
    }

    GetDlgItem(IDC_STATIC_FRIEND_NICKNAME)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_FRIEND_NICKNAME)->SetWindowText(CA2W(m_friendData.fullName.c_str(), CP_UTF8));

}

void CFriendDlg::OnBnClickedBtnFriendSubmit()
{
	CString nickName;
	GetDlgItemText(IDC_EDIT_FRIEND_NICKNAME, nickName);

	if (nickName == _T("")) {
		GetDlgItem(IDC_STATIC_FRIEND_ERROR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FRIEND_ERROR)->SetWindowTextW(_T("Bạn chưa nhập biệt danh cho đối phương!"));
	}
	else {

	}
}


HBRUSH CFriendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_FRIEND_NICKNAME) {
		pDC->SetTextColor(RGB(0, 0, 0));

		pDC->SetBkColor(RGB(235, 233, 239));

		static CBrush brush(RGB(235, 233, 239));
		return (HBRUSH)brush.GetSafeHandle();
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_FRIEND_ERROR) {
		pDC->SetTextColor(RGB(236, 70, 34));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	return hbr;
}


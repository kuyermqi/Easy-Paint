// PEN_Dialog.cpp: 实现文件
//

#include "stdafx.h"
#include "EasyPaint.h"
#include "PEN_Dialog.h"
#include "afxdialogex.h"


// PEN_Dialog 对话框

IMPLEMENT_DYNAMIC(PEN_Dialog, CDialogEx)

PEN_Dialog::PEN_Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEN_Dialog, pParent)
{
}

PEN_Dialog::~PEN_Dialog()
{
}

void PEN_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PEN_Dialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &PEN_Dialog::OnBnClickedOk)
END_MESSAGE_MAP()


// PEN_Dialog 消息处理程序

BOOL PEN_Dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Size = 3;
	CSliderCtrl* pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSliderCtrl->SetRange(1, 101);//设置范围
	pSliderCtrl->SetTicFreq(10);
	pSliderCtrl->SetPos(Size);

	return true;
}
void PEN_Dialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
	CSliderCtrl* pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	Size = pSliderCtrl->GetPos();
}

// PLG_Dialog.cpp: 实现文件
//

#include "stdafx.h"
#include "EasyPaint.h"
#include "PLG_Dialog.h"
#include "afxdialogex.h"


// PLG_Dialog 对话框

IMPLEMENT_DYNAMIC(PLG_Dialog, CDialogEx)

PLG_Dialog::PLG_Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLG_Dialog, pParent)
{
	
}

PLG_Dialog::~PLG_Dialog()
{
}

void PLG_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PLG_Dialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &PLG_Dialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &PLG_Dialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// PLG_Dialog 消息处理程序


void PLG_Dialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	comboxIndex = pComboBox->GetCurSel() + 3;
}


void PLG_Dialog::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL PLG_Dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化下拉列表内容
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	pComboBox->InsertString(0, L"3");
	pComboBox->InsertString(1, L"4");
	pComboBox->InsertString(2, L"5");
	pComboBox->InsertString(3, L"6");
	pComboBox->InsertString(4, L"7");
	pComboBox->InsertString(5, L"8");
	pComboBox->InsertString(6, L"9");
	pComboBox->InsertString(7, L"10");
	pComboBox->InsertString(8, L"11");
	pComboBox->InsertString(9, L"12");
	pComboBox->SetCurSel(0);

	return 0;
}

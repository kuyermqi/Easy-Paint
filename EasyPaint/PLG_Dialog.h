#pragma once


// PLG_Dialog 对话框

class PLG_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(PLG_Dialog)

public:
	PLG_Dialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PLG_Dialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLG_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	CComboBox plg_sides;
	int comboxIndex;
};

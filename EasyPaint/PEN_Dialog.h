#pragma once


// PEN_Dialog 对话框

class PEN_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(PEN_Dialog)

public:
	PEN_Dialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PEN_Dialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEN_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CSliderCtrl pen_size;
	int Size;
};

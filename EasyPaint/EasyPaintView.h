#pragma once

#include <vector>
#include <stack>
#include "MyShape.h"
#include "MyBrush.h"
#include "MyRect.h"
#include "MyEllipse.h"
#include "MyArc.h"
#include "MyPolygon.h"
#include "PLG_Dialog.h"
#include "PEN_Dialog.h"

using namespace std;

class CEasyPaintView : public CView
{
protected: // 仅从序列化创建
	CEasyPaintView();
	DECLARE_DYNCREATE(CEasyPaintView)

public:
	bool isLMouseDown;		//鼠标左键是否按下
	bool isNewShape;		//判断是否为新一次的绘图
	int plg_sides;			//多边形的边数
	int borderSize;			//边框大小
	int borderType;			//边框样式
	int commandCount;		//OnMouseMove操作的计数
	stack<int> command;		//计数的栈，撤回用
	stack<int> _command;	//计数的栈，重做用
	CPoint start;			//开始坐标
	CPoint end;				//结束坐标
	COLORREF m_clr;			//画笔颜色
	COLORREF m_clr_f;		//填充颜色
	enum tagMODE { BRS, RCT, ELP, LIN, ARC, PLG } mode;
	CEasyPaintDoc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CEasyPaintView();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void Mode_Pen();
	afx_msg void Mode_Rect();
	afx_msg void Mode_Ellipse();
	afx_msg void Color();
	afx_msg void OnUndo();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void Mode_Line();
	afx_msg void Mode_Arc();
	afx_msg void Mode_Polygon();
	afx_msg void FillColor();
	afx_msg void setPolygonSide();
	afx_msg void setPen();
	afx_msg void Redo();
};

#ifndef _DEBUG  // EasyPaintView.cpp 中的调试版本
inline CEasyPaintDoc* CEasyPaintView::GetDocument() const
   { return reinterpret_cast<CEasyPaintDoc*>(m_pDocument); }
#endif


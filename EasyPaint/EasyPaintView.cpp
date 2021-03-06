#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "EasyPaint.h"
#endif

#include "EasyPaintDoc.h"
#include "EasyPaintView.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CEasyPaintView, CView)

BEGIN_MESSAGE_MAP(CEasyPaintView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CEasyPaintView::Mode_Pen)
	ON_COMMAND(ID_32772, &CEasyPaintView::Mode_Rect)
	ON_COMMAND(ID_32773, &CEasyPaintView::Mode_Ellipse)
	ON_COMMAND(ID_32774, &CEasyPaintView::Color)
	ON_COMMAND(ID_EDIT_UNDO, &CEasyPaintView::OnUndo)
	ON_COMMAND(ID_32775, &CEasyPaintView::Mode_Line)
	ON_COMMAND(ID_32776, &CEasyPaintView::Mode_Arc)
	ON_COMMAND(ID_32777, &CEasyPaintView::Mode_Polygon)
	ON_COMMAND(ID_32780, &CEasyPaintView::FillColor)
	ON_COMMAND(ID_32781, &CEasyPaintView::setPolygonSide)
	ON_COMMAND(ID_32782, &CEasyPaintView::setPen)
	ON_COMMAND(ID_32784, &CEasyPaintView::Redo)
END_MESSAGE_MAP()

// CEasyPaintView 构造/析构
CEasyPaintView::CEasyPaintView()
{
	isLMouseDown = FALSE;
	isNewShape = TRUE;
	plg_sides = 3;
	commandCount = 0;
	mode = BRS;
	borderSize = 2;
	borderType = PS_SOLID;
	m_clr_f = RGB(255, 255, 255);
}

CEasyPaintView::~CEasyPaintView()
{
}

BOOL CEasyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

void CEasyPaintView::OnDraw(CDC* pDC)
{
	CEasyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	int count = pDoc->shapeArray.GetCount();
	if (count > 0)
	{
		MyShape *p = NULL;
		for (int i = 0; i < count; i++)
		{
			p = (MyShape*)pDoc->shapeArray[i];
			p->Draw(pDC);
		}
	}
}

// CEasyPaintView 诊断
#ifdef _DEBUG
void CEasyPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CEasyPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEasyPaintDoc* CEasyPaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEasyPaintDoc)));
	return (CEasyPaintDoc*)m_pDocument;
}
#endif //_DEBUG

//鼠标左键按下
void CEasyPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	isLMouseDown = TRUE;
	start = point;
}

//鼠标左键松开
void CEasyPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
	CEasyPaintDoc* pDoc = GetDocument();
	isLMouseDown = FALSE;
	isNewShape = TRUE;
	end = point;
	if (mode == BRS)
		command.push(commandCount);
	else
		command.push(1);
	commandCount = 0;
}

//当鼠标移动
void CEasyPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	if (isLMouseDown)
	{
		CEasyPaintDoc *pDoc = GetDocument();
		int count = pDoc->shapeArray.GetCount();
		int index = pDoc->shapeArray.GetUpperBound();

		if (mode == BRS)
		{
			MyBrush * p = new MyBrush(start, PS_SOLID, borderSize, m_clr);
			p->setEnd(point);
			pDoc->shapeArray.Add(p);
			start = point;
			commandCount++;
			Invalidate(false);
		}
		else if (mode == RCT) {
			CRect rct(start, point);
			MyRect * p = new MyRect(start, point, PS_SOLID, borderSize, m_clr, m_clr_f);
			if (isNewShape)
			{
				isNewShape = FALSE;
			}
			else if (count != 0 && !isNewShape) {
				pDoc->shapeArray.RemoveAt(count - 1);
			}
			pDoc->shapeArray.Add(p);
			Invalidate();
		}
		else if (mode == ELP) {
			CRect rct(start, point);
			MyEllipse * p = new MyEllipse(start, point, PS_SOLID, borderSize, m_clr, m_clr_f);
			if (isNewShape)
			{
				isNewShape = FALSE;
			}
			else if (count != 0 && !isNewShape) {
				pDoc->shapeArray.RemoveAt(count - 1);
			}
			pDoc->shapeArray.Add(p);
			Invalidate();
		}
		else if (mode == LIN) {
			MyBrush * p = new MyBrush(start, PS_SOLID, borderSize, m_clr);
			p->setEnd(point);
			if (isNewShape)
			{
				isNewShape = FALSE;
			}
			else if (count != 0 && !isNewShape) {
				pDoc->shapeArray.RemoveAt(count - 1);
			}
			pDoc->shapeArray.Add(p);
			Invalidate();
		}
		else if (mode == ARC) {
			CRect rct(start, point);
			MyArc * p = new MyArc(start, point, PS_SOLID, borderSize, m_clr);
			if (isNewShape)
			{
				isNewShape = FALSE;
			}
			else if (count != 0 && !isNewShape) {
				pDoc->shapeArray.RemoveAt(count - 1);
			}
			pDoc->shapeArray.Add(p);
			Invalidate();
		}
		else if (mode == PLG) {
			MyPolygon * p = new MyPolygon(plg_sides, start, point, PS_SOLID, borderSize, m_clr, m_clr_f);
			if (isNewShape)
			{
				isNewShape = FALSE;
			}
			else if (count != 0 && !isNewShape) {
				pDoc->shapeArray.RemoveAt(count - 1);
			}
			pDoc->shapeArray.Add(p);
			Invalidate();
		}
	}
}

//绘图模式更改
void CEasyPaintView::Mode_Pen()		{ mode = BRS; }
void CEasyPaintView::Mode_Rect()	{ mode = RCT; }
void CEasyPaintView::Mode_Ellipse() { mode = ELP; }
void CEasyPaintView::Mode_Line()	{ mode = LIN; }
void CEasyPaintView::Mode_Arc()		{ mode = ARC; }
void CEasyPaintView::Mode_Polygon() { mode = PLG; }

//颜色选择
void CEasyPaintView::Color()
{
	CColorDialog m_setClrDlg;
	m_setClrDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;		// CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
	m_setClrDlg.m_cc.rgbResult = m_clr;						//记录上次选择的颜色
	if (IDOK == m_setClrDlg.DoModal())
	{
		m_clr = m_setClrDlg.m_cc.rgbResult;					// 保存用户选择的颜色
	}
}

//填充颜色选择
void CEasyPaintView::FillColor()
{
	CColorDialog m_setClrDlg_f;
	m_setClrDlg_f.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;		// CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
	m_setClrDlg_f.m_cc.rgbResult = m_clr_f;						//记录上次选择的颜色
	if (IDOK == m_setClrDlg_f.DoModal())
	{
		m_clr_f = m_setClrDlg_f.m_cc.rgbResult;					// 保存用户选择的颜色
	}
}

//撤销
void CEasyPaintView::OnUndo()
{
	CEasyPaintDoc *pDoc = GetDocument();
	int count = pDoc->shapeArray.GetCount();
	if (count != 0) 
	{
		if (!command.empty())
		{
			for (int i = 0; i < command.top(); i++)
			{
				pDoc->_shapeArray.Add(pDoc->shapeArray[count - i - 1]);
				pDoc->shapeArray.RemoveAt(count - i - 1);
			}
			_command.push(command.top());
			command.pop();
		}
	}
	Invalidate();
}

//重做
void CEasyPaintView::Redo()
{
	CEasyPaintDoc *pDoc = GetDocument();
	int count = pDoc->_shapeArray.GetCount();
	if (count != 0)
	{
		if (!_command.empty())
		{
			for (int i = 0; i < _command.top(); i++)
			{
				pDoc->shapeArray.Add(pDoc->_shapeArray[count - i - 1]);
				pDoc->_shapeArray.RemoveAt(count - i - 1);
			}
			command.push(_command.top());
			_command.pop();
		}
	}
	Invalidate();
}


//设置多边形边数
void CEasyPaintView::setPolygonSide()
{
	PLG_Dialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		plg_sides = dlg.comboxIndex;
	}
}

//设置画笔大小
void CEasyPaintView::setPen()
{
	PEN_Dialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		borderSize = dlg.Size;
	}
}



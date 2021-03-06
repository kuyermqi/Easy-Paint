#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EasyPaint.h"
#endif

#include "EasyPaintDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEasyPaintDoc

IMPLEMENT_DYNCREATE(CEasyPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyPaintDoc, CDocument)
END_MESSAGE_MAP()


// CEasyPaintDoc 构造/析构

CEasyPaintDoc::CEasyPaintDoc()
{
	// TODO: 在此添加一次性构造代码

}

CEasyPaintDoc::~CEasyPaintDoc()
{
	int count = shapeArray.GetCount();
	if (count > 0)
	{
		MyShape *p = NULL;
		for (int i = 0; i < count; i++)
		{
			p = (MyShape*)shapeArray[i];
			delete p;
		}
	}
	shapeArray.RemoveAll();
}

BOOL CEasyPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

// CEasyPaintDoc 序列化

void CEasyPaintDoc::Serialize(CArchive& ar)
{
	shapeArray.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CEasyPaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CEasyPaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CEasyPaintDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEasyPaintDoc 诊断

#ifdef _DEBUG
void CEasyPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEasyPaintDoc 命令

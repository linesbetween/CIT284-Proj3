
// Project3View.cpp : implementation of the CProject3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project3.h"
#endif

#include "Project3Doc.h"
#include "Project3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject3View

IMPLEMENT_DYNCREATE(CProject3View, CView)

BEGIN_MESSAGE_MAP(CProject3View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CProject3View construction/destruction

CProject3View::CProject3View()
{
	// TODO: add construction code here

}

CProject3View::~CProject3View()
{
}

BOOL CProject3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject3View drawing

void CProject3View::OnDraw(CDC* /*pDC*/)
{
	CProject3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CProject3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProject3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProject3View diagnostics

#ifdef _DEBUG
void CProject3View::AssertValid() const
{
	CView::AssertValid();
}

void CProject3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject3Doc* CProject3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject3Doc)));
	return (CProject3Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject3View message handlers

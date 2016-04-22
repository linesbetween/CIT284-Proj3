// InventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project3.h"
#include "InventDlg.h"
#include "afxdialogex.h"


// InventDlg dialog

IMPLEMENT_DYNAMIC(InventDlg, CDialogEx)

InventDlg::InventDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(InventDlg::IDD, pParent)
{

}

InventDlg::InventDlg(LinkedList* stockList, CWnd* pParent)
	: CDialogEx(InventDlg::IDD, pParent){
	this->stockList = stockList;
	//stockList->resetPostion();
	//stockNumList.AddString(stockList->getFirst()->stockNum);
}

InventDlg::~InventDlg()
{
}

void InventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INVENT, listCtrlInvent);
}

BOOL InventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitListCtrlCols();
	InsertItems();

	return true;
}

void InventDlg::InitListCtrlCols()
{
	// Insert some columns
	CRect rect;
	listCtrlInvent.GetClientRect(&rect);
	int nColInterval = rect.Width() / 8;

	listCtrlInvent.InsertColumn(0, _T("Stock Number"), LVCFMT_LEFT, nColInterval * 2);
	listCtrlInvent.InsertColumn(1, _T("Quantity"), LVCFMT_LEFT, nColInterval);
	listCtrlInvent.InsertColumn(2, _T("Description"), LVCFMT_LEFT, nColInterval * 3);
	listCtrlInvent.InsertColumn(4, _T("Price per item"), LVCFMT_LEFT, nColInterval * 2);
}

void InventDlg::InsertItems(){
	// Delete the current contents
	listCtrlInvent.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	Node* pCurrent = NULL;
	CString str;
	int idx = 0;

	stockList->resetPostion();
	while (stockList->getPosition() != NULL){
		pCurrent = stockList->getAndMovePosition();
		// Insert the first item
		lvi.mask = LVIF_IMAGE | LVIF_TEXT;
		lvi.iItem = idx;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(pCurrent->stockNum);
		listCtrlInvent.InsertItem(&lvi);

		// Set subitem quantity
		str.Format(_T("%u"), pCurrent->quant);
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(str);
		listCtrlInvent.SetItem(&lvi);

		// Set subitem descript
		lvi.iSubItem = 2;
		lvi.pszText = (LPTSTR)(LPCTSTR)(pCurrent->descript);
		listCtrlInvent.SetItem(&lvi);

		// Set subitem price
		str.Format(_T("$ %.2f"), pCurrent->price);
		lvi.iSubItem = 3;
		lvi.pszText = (LPTSTR)(LPCTSTR)(str);
		listCtrlInvent.SetItem(&lvi);

		++idx;
	}

}


BEGIN_MESSAGE_MAP(InventDlg, CDialogEx)
END_MESSAGE_MAP()


// InventDlg message handlers

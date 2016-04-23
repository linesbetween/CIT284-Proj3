// CartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project3.h"
#include "CartDlg.h"
#include "afxdialogex.h"


// CartDlg dialog

IMPLEMENT_DYNAMIC(CartDlg, CDialogEx)

CartDlg::CartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CartDlg::IDD, pParent)
{

}

CartDlg::CartDlg(LinkedList* cartList, CWnd* pParent)
	: CDialogEx(CartDlg::IDD, pParent){
	this->cartList = cartList;
}

CartDlg::~CartDlg()
{
}

void CartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CART, listCtrlCart);
}

BOOL CartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitListCtrlCols();
	InsertItems();

	return true;
}

void CartDlg::InitListCtrlCols()
{
	// Insert some columns
	CRect rect;
	listCtrlCart.GetClientRect(&rect);
	int nColInterval = rect.Width() / 9;

	listCtrlCart.InsertColumn(0, _T("Stock Number"), LVCFMT_LEFT, nColInterval*2);
	listCtrlCart.InsertColumn(1, _T("Quantity"), LVCFMT_LEFT, nColInterval);
	listCtrlCart.InsertColumn(2, _T("Description"), LVCFMT_LEFT, nColInterval * 3);
	listCtrlCart.InsertColumn(3, _T("Price per item"), LVCFMT_LEFT, nColInterval * 2);
	listCtrlCart.InsertColumn(4, _T("Extension"), LVCFMT_LEFT, nColInterval);
}

void CartDlg:: InsertItems(){
	// Delete the current contents
	listCtrlCart.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	Node* pCurrent = NULL;
	CString str;
	int idx = 0;

	if (!cartList->isEmpty()){
		cartList->resetPostion();
		while (cartList->getPosition() != NULL){
			pCurrent = cartList->getAndMovePosition();
			// Insert the first item
			lvi.mask = LVIF_IMAGE | LVIF_TEXT;
			lvi.iItem = idx;
			lvi.iSubItem = 0;
			lvi.pszText = (LPTSTR)(LPCTSTR)(pCurrent->stockNum);
			listCtrlCart.InsertItem(&lvi);

			// Set subitem quantity
			str.Format(_T("%u"), pCurrent->quant);
			lvi.iSubItem = 1;
			lvi.pszText = (LPTSTR)(LPCTSTR)(str);
			listCtrlCart.SetItem(&lvi);

			// Set subitem descript
			lvi.iSubItem = 2;
			lvi.pszText = (LPTSTR)(LPCTSTR)(pCurrent->descript);
			listCtrlCart.SetItem(&lvi);

			// Set subitem price
			str.Format(_T("$ %.2f"), pCurrent->price);
			lvi.iSubItem = 3;
			lvi.pszText = (LPTSTR)(LPCTSTR)(str);
			listCtrlCart.SetItem(&lvi);

			// Set extension
			lvi.iSubItem = 4;
			lvi.pszText = (LPTSTR)(LPCTSTR)(pCurrent->extension);
			listCtrlCart.SetItem(&lvi);


			++idx;
		}
	}
}



BEGIN_MESSAGE_MAP(CartDlg, CDialogEx)
END_MESSAGE_MAP()


// CartDlg message handlers

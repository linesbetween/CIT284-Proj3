// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project3.h"
#include "AddDlg.h"
#include "afxdialogex.h"


// AddDlg dialog

IMPLEMENT_DYNAMIC(AddDlg, CDialogEx)

AddDlg::AddDlg(CWnd* pParent /*=NULL*/) : CDialogEx(AddDlg::IDD, pParent)
{

}

AddDlg::AddDlg(LinkedList* stockList, LinkedList* cartList, CWnd* pParent) : CDialogEx(AddDlg::IDD, pParent){
	stock= stockList;
	cart = cartList;
}

////AddDlg::AddDlg(CWnd* pParent /*=NULL*/) : CDialogEx(AddDlg::IDD, pParent)
//{
//
//}

AddDlg::~AddDlg()
{
}

void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STOCKNUM, stockNum);
	DDX_Control(pDX, IDC_EDIT_QUANT, quant);
	DDX_Control(pDX, IDC_EDIT_DESCRIPT, descript);
	DDX_Control(pDX, IDC_EDIT_PRICE, price);

	
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT_STOCKNUM, &AddDlg::OnEnChangeEditStocknum)
END_MESSAGE_MAP()


// AddDlg message handlers

BOOL AddDlg::PreTranslateMessage(LPMSG pMsg)
{
	if (WM_KEYDOWN == pMsg->message &&
		VK_RETURN == pMsg->wParam)
	{
		// process enter key pressing
		stockNum.GetWindowTextW(stockNumStr);
		//descript.SetWindowTextW(stockNumStr);
		
		Node* temp = stock->getNode(stockNumStr);
		if (temp != NULL){
			descriptStr = temp->descript;
			descript.SetWindowTextW(descriptStr);
			priceDbl = temp->price;
			priceStr.Format(_T("%.2f"), priceDbl);
			price.SetWindowTextW(priceStr);
			
		}
		else{
			descript.SetWindowTextW(_T("Not found"));
			price.SetWindowTextW(_T("Not found"));
		}
		
		return TRUE;
	}
	return FALSE;
}
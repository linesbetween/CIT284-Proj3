// RemoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Project3.h"
#include "RemoveDlg.h"
#include "afxdialogex.h"


// RemoveDlg dialog

IMPLEMENT_DYNAMIC(RemoveDlg, CDialogEx)

RemoveDlg::RemoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RemoveDlg::IDD, pParent)
{

}

RemoveDlg::RemoveDlg(LinkedList* stockList, LinkedList* cartList, CWnd* pParent) 
	: CDialogEx(RemoveDlg::IDD, pParent){
	this->stockList = stockList;
	this->cartList = cartList;
}

RemoveDlg::~RemoveDlg()
{
}

void RemoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STOCKNUM, comboStockNum);
	DDX_Control(pDX, IDC_COMBO_QUANT, comboQuant);
	DDX_Control(pDX, IDC_EDIT_DESCRIPT, editDescript);
	DDX_Control(pDX, IDC_EDIT_PRICE, editPrice);

	//initialize stock number list
	cartList->resetPostion();
	Node* pCurrent = NULL;
	while (cartList->getPosition() != NULL){
		pCurrent = cartList->getAndMovePosition();
		comboStockNum.AddString(pCurrent->stockNum);
	}
}


BEGIN_MESSAGE_MAP(RemoveDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_STOCKNUM, &RemoveDlg::OnCbnSelchangeComboStocknum)
	ON_CBN_SELCHANGE(IDC_COMBO_QUANT, &RemoveDlg::OnCbnSelchangeComboQuant)
	ON_BN_CLICKED(IDOK, &RemoveDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RemoveDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// RemoveDlg message handlers


void RemoveDlg::OnCbnSelchangeComboStocknum()
{
	idxStockNum = comboStockNum.GetCurSel();

	if (idxStockNum < 0){
		clearDescript();
		clearPrice();
		clearQuant();
		return;
	}
	else{
		// get input, display price & descript
		comboStockNum.GetLBText(idxStockNum, stockNumStr);
		Node* pSel = cartList->getNode(stockNumStr);
		quantInCartInt = pSel->quant;
		descriptStr = pSel->descript;
		editDescript.SetWindowTextW(descriptStr);
		priceDbl = pSel->price;
		priceStr.Format(_T("%.2f"), priceDbl);
		editPrice.SetWindowTextW(priceStr);

		//initialize quant  list
		CString str;
		for (int i = 1; i <= quantInCartInt; ++i){
			str.Format(_T("%d"), i);
			comboQuant.AddString(str);
		}
	}
		
}


void RemoveDlg::OnCbnSelchangeComboQuant()
{

	idxQuant = comboQuant.GetCurSel();

	if (idxStockNum <= -1){ //if item is not seletect yet
		AfxMessageBox(_T("You must choose item first"));
		clearQuant();
		return;
	}
	else {
		comboQuant.GetLBText(idxQuant, quantStr);
		quantInt = _ttoi(quantStr);
	}

}


void RemoveDlg::OnBnClickedOk()
{

	if (stockNumStr.IsEmpty() || quantInt == 0){
		AfxMessageBox(_T("All fiels must be filled"));
		clearStockNum();
		clearQuant();
		clearDescript();
		clearPrice();
	}
	else{
		Node* pRemoved = cartList->getNode(stockNumStr);
		Node* pFromStock = stockList->getNode(stockNumStr);

		if (quantInt == quantInCartInt)
			cartList->deleteNode(stockNumStr);
		else
			pRemoved->quant -= quantInt;
		pFromStock->quant += quantInt;
		AfxMessageBox(_T("Removed from cart"));

		//TODO delete item when quant == 0

		clearStockNum();
		clearQuant();
		clearDescript();
		clearPrice();
		
		//CDialogEx::OnOK();
	}
}



void RemoveDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	clearStockNum();
	clearQuant();
	clearDescript();
	clearPrice();
	CDialogEx::OnCancel();
}

void RemoveDlg::clearStockNum(){
	idxStockNum = -1;
	comboStockNum.SetCurSel(-1);
	stockNumStr = _T("");
}

void RemoveDlg::clearQuant(){
	idxQuant = -1;
	comboQuant.SetCurSel(-1);
	quantInt = 0;
	quantStr = _T("0");
}

void RemoveDlg::clearDescript(){
	editDescript.SetWindowTextW(_T(""));
	descriptStr = _T("");
}

void RemoveDlg::clearPrice(){
	editPrice.SetWindowTextW(_T(""));
	priceStr = _T("");
	priceDbl = 0;
}

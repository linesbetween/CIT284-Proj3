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
	quantInt = 0;
	priceDbl = 0;
	billAmount = 0;
}

RemoveDlg::RemoveDlg(LinkedList* stockList, LinkedList* cartList, CWnd* pParent) 
	: CDialogEx(RemoveDlg::IDD, pParent){
	this->stockList = stockList;
	this->cartList = cartList;
	quantInt = 0;
	priceDbl = 0;
	billAmount = 0;
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
	DDX_Control(pDX, IDC_EDIT_EXTENSION, editExtension);

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
		clearExtension();
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
		extensionStr = pSel->extension;
		editExtension.SetWindowTextW(extensionStr);

		//initialize quant  list
		clearQuant();
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
		MessageBox(_T("All fiels must be filled"), _T("Remove cart"), MB_ICONERROR);
		clearStockNum();
		clearQuant();
		clearDescript();
		clearPrice();
		clearExtension();
	}
	else{
		Node* pRemoved = cartList->getNode(stockNumStr);
		Node* pFromStock = stockList->getNode(stockNumStr);

		pRemoved->quant -= quantInt;
		if (pRemoved->quant == 0){ //TODO delete item.
			cartList->deleteNode(stockNumStr);
			cartList->printList();
			//TODO reload comboStockNum
			cartList->resetPostion();
			//comboStockNum.ResetContent();
			//comboStockNum.AddString(_T("Place holder")); //works
			
			Node* pCurrent = NULL;
			while (cartList->getPosition() != NULL){
				pCurrent = cartList->getAndMovePosition();
				comboStockNum.AddString(pCurrent->stockNum);
			}
			
		}
			 
		pFromStock->quant += quantInt;
		calcuBill();
		CString billAmountStr, billReducedStr;
		billAmountStr.Format(_T("%.2f"), billAmount);
		billReducedStr.Format(_T("%.2f"), pRemoved->price*quantInt);
		MessageBox(_T("Item " + stockNumStr + " Removed from cart \n" +
			"Reduced from Bill: " + billReducedStr + "\n" +
			"Current Bill: " + billAmountStr)
			, _T("Remove"),			MB_ICONINFORMATION);

		//TODO delete item when quant == 0

		clearStockNum();
		clearQuant();
		clearDescript();
		clearPrice();
		clearExtension();
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

void RemoveDlg::calcuBill(){
	Node* pCurrent = NULL;
	billAmount = 0;
	cartList->resetPostion();
	while (cartList->getPosition() != NULL){
		pCurrent = cartList->getAndMovePosition();
		billAmount += pCurrent->price * pCurrent->quant;
	}
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
	comboQuant.ResetContent();
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

void RemoveDlg::clearExtension(){
	editExtension.SetWindowTextW(_T(""));
	extensionStr = _T("");
}


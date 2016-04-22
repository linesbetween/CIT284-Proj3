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
	DDX_Control(pDX, IDC_COMBO_STOCKNUM, comboStockList);

	stock->resetPostion();
	Node* pCurrent = NULL;
	while (stock->getPosition() != NULL){
		pCurrent = stock->getAndMovePosition();
		comboStockList.AddString(pCurrent->stockNum);
	}
	DDX_Control(pDX, IDC_COMBO_QUANT, comboQuant);
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT_STOCKNUM, &AddDlg::OnEnChangeEditStocknum)
	ON_CBN_SELCHANGE(IDC_COMBO_STOCKNUM, &AddDlg::OnCbnSelchangeComboStocknum)
	ON_EN_UPDATE(IDC_EDIT_QUANT, &AddDlg::OnEnUpdateEditQuant)
	ON_BN_CLICKED(ID_BTN_ADD, &AddDlg::OnBnClickedBtnAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_QUANT, &AddDlg::OnCbnSelchangeComboQuant)
	ON_BN_CLICKED(IDCANCEL, &AddDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddDlg message handlers

void AddDlg::OnCbnSelchangeComboStocknum()
{
	idxStockNum = comboStockList.GetCurSel();

	if (idxStockNum < 0){
		clearDescript();
		clearPrice();
		clearQuant();
		return;
	}
	else{
		comboStockList.GetLBText(idxStockNum, stockNumStr);
		Node* pSel = stock->getNode(stockNumStr);
		quantInStockInt = pSel->quant;
		descriptStr = pSel->descript;
		descript.SetWindowTextW(descriptStr);
		priceDbl = pSel->price;
		priceStr.Format(_T("%.2f"), priceDbl);
		price.SetWindowTextW(priceStr);

		clearQuantCombo();

		CString str;
		for (int i = 1; i <= quantInStockInt; ++i){
			str.Format(_T("%d"), i);
			comboQuant.AddString(str);
		}
	}
}


void AddDlg::OnCbnSelchangeComboQuant()
{
	idxQuant = comboQuant.GetCurSel();

	if (idxStockNum <= -1){ //if item is not seletect yet
		AfxMessageBox(_T("You must choose item first"));
		clearQuantCombo();
		return;
	}
	else {
		comboQuant.GetLBText(idxQuant, quantStr);
		quantInt = _ttoi(quantStr);
	}
}


void AddDlg::OnBnClickedBtnAdd() //TODO< when quant == 0, quantcombo 
{
	//check empty field
	if (stockNumStr.IsEmpty() || quantInt == 0){
		AfxMessageBox(_T("All fiels must be filled"));
		clearStockListCombo();
		clearQuantCombo();
		clearDescript();
		clearPrice();
		
	}
	else{
		if (cart->getNode(stockNumStr) == NULL){
			cart->insertNode(stockNumStr, quantInt, descriptStr, priceDbl);
		}
		else{
			cart->getNode(stockNumStr)->quant += quantInt;
		}

		Node* pAdded = stock->getNode(stockNumStr);
		pAdded->quant -= quantInt;
		AfxMessageBox(_T("Added to cart"));
		
		clearStockListCombo();
		clearQuantCombo();
		clearDescript();
		clearPrice();
	}
}

void AddDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void AddDlg::clearStockListCombo(){
	idxStockNum = -1;
	comboStockList.SetCurSel(-1);
	stockNumStr = _T("");
}

void AddDlg::clearQuantCombo(){
	idxQuant = -1;
	comboQuant.SetCurSel(-1);
	quantInt = 0;
	quantStr = _T("0");
}

void AddDlg::clearDescript(){
	descript.SetWindowTextW(_T(""));
	descriptStr = _T("");
}

void AddDlg::clearPrice(){
	price.SetWindowTextW(_T(""));
	priceStr = _T("");
	priceDbl = 0;
}



///////////////////////////////unused part

void AddDlg::OnEnUpdateEditQuant()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	CString quantStr;
	if (idxStockNum <= -1){ //if item is not seletect yet
		AfxMessageBox(_T("You must choose item first"));
		clearQuant();
		return;
	}
	else {
		quant.GetWindowTextW(quantStr);
		quantInt = _ttoi(quantStr);

		if (quantInt >= quantInStockInt){
			AfxMessageBox(_T("Can't add more than %u"), quantInStockInt);
			quantInt = 0;
			quant.SetWindowTextW(_T(""));
		}
	}
}


BOOL AddDlg::PreTranslateMessage(LPMSG pMsg)  // Handle Enter key in editStockNum
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


void AddDlg::clearQuant(){
	quant.SetWindowTextW(_T(""));
	quantStr = _T("");
	quantInt = 0;
}



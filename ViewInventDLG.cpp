// ViewInventDLG.cpp : implementation file
//

#include "stdafx.h"
#include "Project3.h"
#include "ViewInventDLG.h"
#include "afxdialogex.h"


// ViewInventDLG dialog

IMPLEMENT_DYNAMIC(ViewInventDLG, CDialogEx)

ViewInventDLG::ViewInventDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ViewInventDLG::IDD, pParent)
{
}

ViewInventDLG::ViewInventDLG(LinkedList* stockList, CWnd* pParent /*=NULL*/)
	: CDialogEx(ViewInventDLG::IDD, pParent){
	stock = stockList;
	//stockList->resetPostion();
	//stockNumList.AddString(stockList->getFirst()->stockNum);
}

ViewInventDLG::~ViewInventDLG()
{
}

void ViewInventDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCKNUM, stockNumList);
	DDX_Control(pDX, IDC_LIST_QUANT, quantList);
	DDX_Control(pDX, IDC_LIST_DESCRIPT, descriptList);
	DDX_Control(pDX, IDC_LIST_PRICE, priceList);

	CString str;
	UINT num;
	stock->resetPostion();
	Node* pCurrent = NULL; 
	while (stock->getPosition() != NULL){
		pCurrent = stock->getAndMovePosition();
		stockNumList.AddString(pCurrent->stockNum);
		str.Format(_T("%u"), pCurrent->quant);
		quantList.AddString(str);
		descriptList.AddString(pCurrent->descript);
		str.Format(_T("%.2f"), pCurrent->price);
		priceList.AddString(str);
	}

}


BEGIN_MESSAGE_MAP(ViewInventDLG, CDialogEx)
END_MESSAGE_MAP()


// ViewInventDLG message handlers

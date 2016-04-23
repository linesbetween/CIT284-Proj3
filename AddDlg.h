#include "LinkedList.h"
#pragma once
#include "afxwin.h"

// AddDlg dialog

class AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddDlg)

public:
	AddDlg(CWnd* pParent = NULL);   // standard constructor
	AddDlg(LinkedList* stockList, LinkedList* cartList, CWnd* pParent = NULL);
	virtual ~AddDlg();
	BOOL PreTranslateMessage(LPMSG pMgs);

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	LinkedList* stock;
	LinkedList* cart;
	CEdit stockNum;
	CEdit quant;
	CEdit descript;
	CEdit price;

	CString stockNumStr, descriptStr, quantStr, priceStr;
	UINT quantInt;
	DOUBLE priceDbl;
	afx_msg void OnEnChangeEditStocknum();
};

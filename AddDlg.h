#include "LinkedList.h"
#pragma once
#include "afxwin.h"

// AddDlg dialog

class AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddDlg)

private:
	void clearStockListCombo();
	void clearQuantCombo();
	void clearQuant();
	void clearDescript();
	void clearPrice();
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
private:
	LinkedList* stock;
	LinkedList* cart;
	CString stockNumStr, descriptStr, quantStr, priceStr;
	UINT quantInt = 0, quantInStockInt;
	DOUBLE priceDbl = 0;
	int idxStockNum, idxQuant;

public:
	CEdit stockNum;
	CEdit quant;
	CEdit descript;
	CEdit price;
	CComboBox comboStockList;
	CComboBox comboQuant;
	
	afx_msg void OnEnChangeEditStocknum();
	afx_msg void OnCbnSelchangeComboStocknum();
	afx_msg void OnEnUpdateEditQuant();
	afx_msg void OnBnClickedBtnAdd();	
	afx_msg void OnCbnSelchangeComboQuant();
	afx_msg void OnBnClickedCancel();
};

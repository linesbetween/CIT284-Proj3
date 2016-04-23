#pragma once
#include "afxwin.h"
#include "LinkedList.h"

// RemoveDlg dialog

class RemoveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RemoveDlg)

private:
	void clearDescript();
	void clearPrice();
	void clearQuant();
	void clearStockNum();
	void clearExtension();

public:
	RemoveDlg(CWnd* pParent = NULL);   // standard constructor
	RemoveDlg(LinkedList* stockList, LinkedList* cartList, CWnd* pParent = NULL);
	virtual ~RemoveDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_REMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


	////////////////////Data fields
private:

	LinkedList* stockList;
	LinkedList* cartList;
	CString stockNumStr, descriptStr, quantStr, priceStr, extensionStr;
	UINT quantInt = 0, quantInCartInt;
	DOUBLE priceDbl = 0;
	int idxStockNum, idxQuant;

public:
	CComboBox comboStockNum;
	CComboBox comboQuant;
	CEdit editDescript;
	CEdit editPrice;
	CEdit editExtension;

	afx_msg void OnCbnSelchangeComboStocknum();
	afx_msg void OnCbnSelchangeComboQuant();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

};

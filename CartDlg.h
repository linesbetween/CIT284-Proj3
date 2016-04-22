#pragma once
#include "LinkedList.h"
#include "afxcmn.h"

// CartDlg dialog

class CartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CartDlg)

private:
	LinkedList* cartList;

protected:
	CListCtrl listCtrlCart;

public:
	CartDlg(CWnd* pParent = NULL);   // standard constructor
	CartDlg(LinkedList* cartList, CWnd* pParent = NULL);
	virtual ~CartDlg();
	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitListCtrlCols();
	void InsertItems();

	DECLARE_MESSAGE_MAP()
public:
	
};

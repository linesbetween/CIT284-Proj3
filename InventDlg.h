#pragma once
#include "LinkedList.h"
#include "afxwin.h"
#include "afxcmn.h"


// InventDlg dialog

class InventDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InventDlg)

public:
	InventDlg(CWnd* pParent = NULL);   // standard constructor
	InventDlg(LinkedList* stockList, CWnd* pParent = NULL);
	virtual ~InventDlg();
	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_INVENT };

private:
	LinkedList* stockList;
	CListCtrl listCtrlInvent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitListCtrlCols();
	void InsertItems();

	DECLARE_MESSAGE_MAP()
public:
	
};

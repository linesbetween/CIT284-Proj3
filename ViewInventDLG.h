
#include "LinkedList.h"
#pragma once
#include "afxwin.h"

// ViewInventDLG dialog

class ViewInventDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ViewInventDLG)

public:
	ViewInventDLG(CWnd* pParent = NULL);   // standard constructor
	ViewInventDLG(LinkedList* stockList, CWnd* pParent = NULL);
	virtual ~ViewInventDLG();

// Dialog Data
	enum { IDD = IDD_DIALOG_INVENTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	LinkedList *stock;
	CListBox stockNumList;
	CListBox quantList;
	CListBox descriptList;
	CListBox priceList;
};

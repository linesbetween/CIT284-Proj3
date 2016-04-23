#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <conio.h>
#include <afx.h>
using namespace std;

/////////////////////////////////Node
class Node {
public:
	CString stockNum, descript;
	UINT quant;
	DOUBLE price;
	Node *pNext;

	Node(CString stockNum, int quant, CString descript, double price){
		this->quant = quant;
		this->price = price;
		this->stockNum = stockNum;
		this->descript = descript;
		pNext = NULL;
	}

	void printNode(){
		cout << "Stock Num: " << stockNum << ", Quant: " << quant << ", Price: " << price <<"\n";
	}

};

//////////////////////////// List
class LinkedList{
private:
	Node *pFirst;
	Node *pPosition;

public:

	LinkedList() {
		pFirst = NULL;
	}

	bool isEmpty(){
		return pFirst == NULL;
	}


	void insertNode(CString stockNum, int quant, CString descript, double price){
		Node* pNewNode = new Node(stockNum, quant, descript, price);
		cout << "\ninserting node "; pNewNode->printNode(); cout << endl;
		Node* pCurrent = pFirst;
		Node* pPrev = pFirst;
		//Node* pVeryFirst = pFirst;

		if (pCurrent == NULL) {//list in empty
			pFirst = pNewNode;
			cout << "    List is empty, insert first node \n";
		}
		else if (pNewNode->stockNum.Compare(pFirst->stockNum) < 0){
			cout << "    inserting in front \n";
			pNewNode->pNext = pFirst;//insert in front
			pFirst = pNewNode;
			cout << "    inserted in front \n";
		}
		else{
			while (pCurrent != NULL && pCurrent->stockNum.Compare(pNewNode->stockNum)<0){
				pPrev = pCurrent;
				pCurrent = pCurrent->pNext;
				cout << "    move forward \n";
			}

			/*
			if (pCurrent->stockNum.compare(pFirst->stockNum) < 0){
			cout << "    inserting in front \n";
			pNewNode->pNext = pFirst;//insert in front
			pFirst = pNewNode;
			cout << "    inserted in front \n";
			}

			else*/{ //insert in end or middle
				cout << "    inserting in middle or end\n";
				pPrev->pNext = pNewNode;
				if (pCurrent != NULL){
					pNewNode->pNext = pCurrent;
					cout << "    Inserted in the middle \n";
				}
				else{
					cout << "    Inserted in the last \n";
				}
			}
		}
		cout << "node inserted \n";
	}

	Node* getNode(CString stockNum){
		Node* pCurrent = pFirst;
//		cout << "Searching list \n";
		if (pCurrent == NULL) {//list in empty
//			cout << "    List is empty \n";
			return NULL;
		}
		else{
			while (pCurrent != NULL && pCurrent->stockNum != stockNum){
				pCurrent = pCurrent->pNext;
//				cout << "    move forward \n";
			}
		}

		if (pCurrent == NULL) {//list in empty
//			cout << "    NOT found \n";
			return NULL;
		}
		else{
//			cout << "    Found \n";
			return pCurrent;
		}
	}

	void deleteNode(CString stockNum){
		Node* pCurrent = pFirst;
		Node* pPrev = pFirst;

		cout << "Searching list \n";
		if (pCurrent == NULL) {//list in empty
			cout << "    List is empty \n";
		}
		else{
			while (pCurrent != NULL && pCurrent->stockNum != stockNum){
				pPrev = pCurrent;
				pCurrent = pCurrent->pNext;
				cout << "    move forward \n";
			}
		}

		if (pCurrent == NULL) {//list in empty
			cout << "    NOT found \n";
		}
		else{
			cout << "    Found \n";
			pPrev->pNext = pCurrent->pNext;
			cout << "    Deleted \n";
		}
	}


	Node* getPosition(){
		return pPosition;
	}

	void resetPostion(){
		pPosition = pFirst;
	}

	Node* getAndMovePosition(){
		Node *pPrev = pPosition;
		//if (pPosition->pNext)
			pPosition = pPosition->pNext;
		return pPrev;
	}


	/*
	void insertFirst(CString stockNum, int quant, CString descript, double price){
		Node* pNewNode = new Node(stockNum, quant, descript, price);
		pNewNode->pNext = pFirst;
		pFirst = pNewNode;
	}*/

	
	Node* getFirst(){
		return pFirst;
	}
	

	/*
	void removeFirst(){
		Node* pTemp = pFirst; //why
		pFirst = pFirst->pNext;
		delete pTemp; //why
	}
	*/
	void printList(){
		cout << "List: \n";
		Node* pCurrent = pFirst;
		while (pCurrent != NULL){
			pCurrent->printNode();
			pCurrent = pCurrent->pNext;
		}
		cout << endl;
	}

};

#endif
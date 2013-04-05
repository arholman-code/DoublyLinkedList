/*********************************************************************************
Andrew Holman
This is my own work.
**********************************************************************************

**********************************************************************************
Program #7
The following will merge two linked lists into a single sorted linked list.
That is, it will perform a "merge sort" on the two.
*********************************************************************************/

#include <fstream>
#include <iostream>
#include "d_dnode.h"
#include "d_node.h"
#include "d_nodel.h"
using namespace std;

void merge (dnode<double> *A, dnode<double> *B);

int main ()
{	
	int sz1, sz2;
	double new_val;
	ifstream fin;
	dnode<double> *listA = new dnode<double>;
	dnode<double> *listB = new dnode<double>;

	fin.open("lnkList.in");

	if (!fin)
	{
		cout << "File not found!\n";
		exit(1);
	}

	fin >> sz1 >> sz2;

	dnode<double> *curr = listA -> next;

	for (int i = 0; i < sz1; i++)
	{
		curr = listA -> next;
		fin >> new_val;
		for (int j = 0; j < i; j++)
			if (curr -> nodeValue < new_val)
				curr = curr -> next;
		insert(curr, new_val);
	}

	cout << "List 1 before merge:\n";
	writeDLinkedList(listA);
	cout << endl;

	for (int i = 0; i < sz2; i++)
	{
		curr = listB -> next;
		fin >> new_val;
		for (int j = 0; j < i; j++)
			if (curr -> nodeValue < new_val)
				curr = curr -> next;
		insert(curr, new_val);
	}
	cout << "List 2 before merge:\n";
	writeDLinkedList(listB);
	cout << "\n\n";

	merge(listA, listB);
	
	cout << "List 1 after merge:\n";
	writeDLinkedList(listA);

	cout << "\n\nList 2 after merge:\n";
	writeDLinkedList(listB);
	cout << "\n";

	fin.close();

	return 0;
}

void merge (dnode<double> *A, dnode<double> *B)
{ 
	dnode<double> *pA = A -> next;
	dnode<double> *pB = B -> next;

	while (pA != A && pB != B) 
	{
		if (pA -> nodeValue < pB -> nodeValue) 
			pA = pA -> next;
		else 
		{
			dnode<double>* holder = pB;
			pB = pB -> next;
			holder -> prev -> next = holder -> next;
			holder -> next -> prev = holder -> prev;
			holder -> prev = pA -> prev;
			holder -> next = pA;
			pA -> prev -> next = holder;
			pA -> prev = holder;
		}
	}
  
	if (pB != B) 
	{
		A -> prev -> next = B -> next;
		B -> next -> prev = A -> prev;
		B -> prev -> next = A;
		A -> prev = B -> prev;
	}
  
	B -> next = B -> prev = B;
}


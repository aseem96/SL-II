/*
 * heapsort.h
 *
 *  Created on: 21-Apr-2015
 *      Author: aseem
 */

#include <iostream>
#include <stdio.h>

#define MAX 20

using namespace std;

struct node {
	node *left,*right;
	char data;
	int freq;
};

void max_heap(node* a[],int i,int n) {
	int j;
	node *temp;
	temp = a[i];
	j = 2*i;
	while(j <= n)
	{
		if(j < n && a[j+1]->freq > a[j]->freq)
			j++;
		if(temp->freq > a[j]->freq)
			break;
		else if(temp->freq <= a[j]->freq)
		{
			a[j/2] = a[j];
			j = 2*j;
		}
	}
	a[j/2] = temp;
	return;
}

void heapify(node* a[],int n) {
	int i;
	for(i = n/2;i >= 1;i--)
		max_heap(a,i,n);
}

void heapsort(node* a[],int n) {
	int i;
	node* temp;
	for(i = n;i >= 2;i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		max_heap(a,1,i-1);
	}
}
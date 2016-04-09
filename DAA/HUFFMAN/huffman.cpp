#include <iostream>
#include <iomanip>
#include "heapsort.h"

#define MAX 20

using namespace std;

int shift(node* x, node* nodes[],int n) {
	for(int i = n;i > 0;i--) 
		nodes[i+1] = nodes[i];
	nodes[1] = x;
	return (n+1);
}

bool check(int a, int b) {
	return (a >= b)?true:false;
}

int remove(node* a[],int index,int n) {
	for(int i = index; i <= n; ++i)
    	a[i] = a[i+1];
    return n-1;
}

void inorder(node *t) {
	if(t) {
		inorder(t->left);
		cout << t->freq << " ";
		inorder(t->right);
	}
}

void decode(node* t, string s) {
	int i = 0;
	int l = s.length();
	while(i < l) {
		node *temp = t;
		while(temp->data == '@') {
			if(s[i] == '1')
				temp = temp->right;
			else
				temp = temp->left;
			++i;
		}
		cout << temp->data;
	}
	cout << "\n";
	return;
}

node* create_huffman_tree(node* nodes[],int n) {
	node *t;
	while(n != 1) {
		t = new node;
		t->data = '@';
		if(check(nodes[2]->freq,nodes[1]->freq)) {
			t->left = nodes[1];
			t->right = nodes[2];
		}
		else {
			t->right = nodes[1];
			t->left = nodes[2];
		}
		t->freq = nodes[1]->freq + nodes[2]->freq;
		n = remove(nodes,1,n);
		n = remove(nodes,1,n);
		n = shift(t,nodes,n);
		heapify(nodes,n);
		heapsort(nodes,n);
	}
	cout << "\nRoot = " << nodes[1]->freq << "\n";
	return nodes[1];
}

void printArr(int arr[], int n) {
    int i;
    for (i = 1; i <= n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int isLeaf(node* root) {
    return !(root->left) && !(root->right);
}

void printCodes(node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        cout << root->data << " -> ";
        printArr(arr, top-1);
    }
}

int main(void) {
	int n;
	node *root, *t;
	string s = "";
	cout << "ENTER NUMBER OF CHARACTERS : ";
	cin >> n;
	node* nodes[n];
	cout << "ENTER CHARACTER AND FREQUENCY : \n";
	for(int i = 1;i <= n;i++) {
		t = new node; 
		cin >> t->data >> t->freq;
		t->left = t->right = NULL;
		nodes[i] = t;
	}
	heapify(nodes,n);
	heapsort(nodes,n);
	cout << "\nCHAR\tFREQUENCY\n";
	for(int i = 1;i <= n;i++)
		cout << nodes[i]->data << "\t" << nodes[i]->freq << "\n";
	root = create_huffman_tree(nodes,n);
	cout << "\n";
	inorder(root);
	cout << "\n\n";
	cout << "CODES\n\n";
	int arr[MAX], top = 1;
   	printCodes(root, arr, top);
	cout << "\n";
	cout << "ENTER THE STRING TO DECODE : ";
	cin >> s;
	cout << "\nDECODED STRING : ";
	decode(root,s);
	cout << "\n";
}
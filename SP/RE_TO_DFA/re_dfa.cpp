/*
 * re_dfa.cpp
 *
 *  Created on: 21-Dec-2015
 *  Author: Aseem Raina, TE9, 3957
 *  Problem Statement:
 *  	Write a program to to convert Regular Expression to DFA.
 		Input is taken as postfix expression.
 		1. Take input as postfix and create expression tree
 		2. Calculate position, nullable, followpos, lastpos
 		3. Convert to state table and then to DFA
 */

#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

// define node structure
struct treenode {
	char data;
	int pos;
	bool nullable;
	int fpos[20];
	int lpos[20];
	treenode *left, *right;
}*root;

// define followpos structure
struct followpos {
	char ch;
	int follow[10];
};

char postfix[50];								// take postfix expression as input
followpos folltable[10];						// array of structure for storing followpos of nodes
int state[10][10],dfa[30],c,df,sym[10];			// for DFA construction

// to search array 'a' for element 'n'
int search(int n,int a[]) {
	for(int i = 1;i <= a[0];i++)
		if(a[i] == n)
			return i;
	return -1;
}

// append array 'b' at the end of array 'a'
void arr_app(int a[],int b[]) {	
	int c = a[0];
	for(int i = 1;i <= b[0];i++) {
		if(search(b[i],a) == -1)
			a[++c] = b[i];
	}
	a[0] = c;
}

// copy array 'b' to array 'a'
void arr_cpy(int a[],int b[]) {
	for(int i = 0;i <= b[0];i++)
		a[i] = b[i];
}

// find union of array 'a' and array 'b' and store it in array 'c'
void union1(int a[],int b[],int c[]) {	
	int c1 = a[0];
	for(int i = 1;i <= a[0];i++)
		c[i] = a[i];
	for(int i = 1;i <= b[0];i++) {
		if(search(b[i],a) == -1)
			c[++c1] = b[i];
	}
	c[0]=c1;
}

// display attributes of treenode
void display_node(treenode *t) {
	cout << t->data << "\t" << t->pos << "\t\t" << t->nullable << "\t\t";
	for(int i = 1;i <= t->fpos[0];i++)
		cout << t->fpos[i] << " ";
	cout << "\t\t";
	for(int i = 1;i <= t->lpos[0];i++)
		cout << t->lpos[i] << " ";
	cout << "\n";
}

// traverse the syntax tree
void traverse(treenode *t) {
	if(t == NULL)
		return;
	traverse(t->left);
	display_node(t);
	traverse(t->right);
}

// compute the follow pos for treenodes
void follow(treenode *t) {
	if(t->data == '*') {	
		for(int i = 1;i <= t->lpos[0];i++)
	    	arr_app(folltable[t->lpos[i]].follow,t->fpos);
	}
	else if(t->data=='.') {	
		for(int i = 1;i <= t->left->lpos[0];i++)
	    	arr_app(folltable[t->left->lpos[i]].follow,t->right->fpos);
	}
}

// construct the syntax tree from postfix expression
void create_syntax_tree() {	
	int i = 0;
	char x;
	stack<treenode *> st;
	treenode *t1, *t2;
	while(postfix[i] != '\0') {	
		x = postfix[i++];
		treenode *t = new treenode;
		if(isalpha(x) || isdigit(x) || x=='#') {				// if character is symbol
			t->data = x;
			t->pos = c;
			t->nullable = false;
			t->fpos[0] = 1;
			t->fpos[1] = c;
			folltable[c].ch = t->data;
			t->lpos[0] = 1;
			t->lpos[1] = c++;
			t->left = t->right = NULL;
			st.push(t);
			if(search((int)t->data,sym) == -1) {				// if not already present, store in symbol table
				sym[sym[0]+1]=t->data;
				sym[0]++;
			}
		}
		else if(x == '.') {										// if character is concat '.' operator
			t->data = x;
			t->pos = 0;
			t1 = st.top();
			st.pop();
			t2 = st.top();
			st.pop();
			t->right = t1;
            t->left = t2;
			t->nullable = t->left->nullable && t->right->nullable;
			if(t->left->nullable == true)
				union1(t->left->fpos,t->right->fpos,t->fpos);
			else
				arr_cpy(t->fpos,t->left->fpos);
			if(t->right->nullable)
				union1(t->left->lpos,t->right->lpos,t->lpos);
			else
				arr_cpy(t->lpos,t->right->lpos);
			follow(t);
			st.push(t);
		}
		else if(x == '|') {										// if character is or '|' operator 
			t->data = '|';
			t->pos = 0;
			t1 = st.top();
			st.pop();
			t2 = st.top();
			st.pop();
			t->right = t1;
            t->left = t2;
			t->nullable = t->left->nullable || t->right->nullable;
			union1(t->left->fpos,t->right->fpos,t->fpos);
			union1(t->left->lpos,t->right->lpos,t->lpos);
			st.push(t);
		}
		else if(x == '*') {										// if character is unary '*' operator
			t->data = '*';
			t->pos = 0;
			t->right = NULL;
			t1 = st.top();
			st.pop();
			t->left = t1;
			t->nullable = true;
			arr_cpy(t->fpos,t->left->fpos);
			arr_cpy(t->lpos,t->left->lpos);
			follow(t);
			st.push(t);
		}
	}
	root = st.top();											// top of tree is root
	st.pop();
	sym[0]--;
}

// display followpos for each node
void display_follow() {	
	cout<<"\nFOLLOWPOS TABLE\n\n";
	cout << "Position\tNode\tFollowpos\n"; 
	for(int i = 1;i < c;i++) {	
		cout << i << "\t\t" << folltable[i].ch << "\t";
		for(int j = 1;j <= folltable[i].follow[0];j++)
			cout << folltable[i].follow[j] << " ";
		cout << "\n";
	}
	cout << "\n";
}

// check if DFA state already exists
int check(int temp[],int nos) {	
	int i,j = 0;
	for(i = 0;i < nos;i++) {	
	    if(temp[0] == state[i][0]) {	
	    	for(j = 01;j <= temp[0];j++) {
	    		if(temp[j] != state[i][j])
	    			break;
	     	}
	    	if(j == (temp[0]+1))
	    		return i;
	    }
	}
	return -1;
}

// create DFA from followpos table
void dfa_build() {
	int k = 0,temp[10];
	temp[0] = 0;
	int nos = 1;
	int m;
	arr_cpy(state[0],folltable[1].follow);
	while(true) {	
		for(int i = 1;i <= sym[0];i++) {
			for(int j = 1;j <= state[k][0];j++) {
				if(folltable[state[k][j]].ch == (char)sym[i])
					arr_app(temp,folltable[state[k][j]].follow);
			}
			m = check(temp,nos);
			if(m == -1) {	
				arr_app(state[nos++],temp);
				m = nos-1;
			}
			dfa[df++] = m;
			temp[0] = 0;
		}
		if(k == nos-1)
		    break;
		k++;
	}
	cout<<"\nSTATES\n";
	for(int j = 0;j < nos;j++) {	
		cout << "\n"<<(char)(j+65) << ": ";
		for(int l = 1;l <= state[j][0];l++)
			cout << state[j][l]<<" ";
	}
	cout << "\n";
}

// display the final DFA
void display_dfa() {
	int i,j,k;
	cout << "\nDFA TRANSITION TABLE \n\n ";
	for(i = 01;i <= sym[0];i++)
		cout << "\t" << (char)(sym[i]);
	cout << "\n";
	for(j = 0;j < (df/sym[0]);j++) {
		cout << "\n" << (char)(j+65) << "\t";
	    for(k = j*sym[0];k < (j*sym[0])+sym[0];k++)
	    	cout << (char)(dfa[k]+65) << "\t";
	}
	cout << "\n";
}

// main driver function for the above program
int main(void) {
	//char postfix[50];
	string p;
	cout << "Enter postfix expression : ";
	cin >> postfix;
	cout << "Postfix expression entered : " << postfix << "\n";
	cout << "\n";
	p = postfix;
	int i = 0;
	c = 1;
	df = 0;
	sym[0] = 0;
	while(i < p.length()) {   
		postfix[i] = p[i];
		i++;
	}
	postfix[i] = '#';
	postfix[i+1] = '.';
	postfix[i+2] = '\0';
	root = NULL;
	i = 0;
	while(i < 10) {	
		folltable[i].follow[0] = 0;
		state[i++][0] = 0;
	}
	create_syntax_tree();
	cout << "\nINORDER \n\n";
	cout << "Node\tPosition\tNullable\tFpos\t\tLpos\n";
	traverse(root);
	cout << "\n";
	display_follow();
	dfa_build();
	display_dfa();	
}




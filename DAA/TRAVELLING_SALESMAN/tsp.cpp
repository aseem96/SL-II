/*
 * tsp.cpp
 *
 *  Created on: 30-Mar-2016
 *  Author: Aseem Raina, TE9, 3957
 *  Problem Statement:
 *  	Write a program to solve Travelling Salesman Problem using Branch and Bound approach.
 */

#include <iostream>
#include <iomanip>
#define INF 99

using namespace std;

int visited[10],n,cost[10],l=0;
static int node_no = 1;
int tsp_cost[10][10];

// Display final path
void display_path() {
    cout << "THE PATH OF THE TOUR IS : ";
    for(int i = 0;i < n;i++)
		cout << visited[i] + 1 << " -> ";
	cout << "1\n";
	cout << "MINIMUM COST OF THE TOUR IS : " << cost[l-1] << "\n";
}

// find min in row
int find_row_min(int b[][10],int r) {
	int min = INF;
	for(int j = 0;j < n;j++) {
		if(b[r][j] < min)
			min = b[r][j];
	}
	if(min == INF)
		min = 0;
   return min;
}

// find min in column
int find_col_min(int b[][10],int c)
{
	int min = INF;
	for(int i = 0;i < n;i++) {
		if(b[i][c] < min)
			min = b[i][c];
	}
	if(min == INF)
		min = 0;
	return min;
}

//to reduce matrix
int reduced_matrix(int b[10][10]) {
	int reduced_sum = 0,min;
	//row reduction
	for(int i = 0;i < n;i++) {
		min = find_row_min(b,i);
		reduced_sum += min;
		for(int j = 0;j < n;j++) {
			if(b[i][j] != INF)
				b[i][j] -= min;
		}
	}
	// column reduction
	for(int i = 0;i < n;i++) {
		min = find_col_min(b,i);
		reduced_sum += min;
		for(int j = 0;j < n;j++) {
			if(b[j][i] != INF)
				b[j][i] -= min;
		}
	}
	cout << "REDUCED MATRIX FOR CITY " << node_no++ << " : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << setw(3) << b[i][j];
		cout << "\n";
	}
	return reduced_sum;
}

// finding min  value
int min1(int temp[][2],int q) {
	int small = 999,j;
	for(int i = 0;i < q;i++) {
		if(temp[i][1] < small) {
			small = temp[i][1];
			j = i;
		}
	}
	return j;
}

// to check visited nodes
int check_visited(int k) {
	for(int i = 0;i < l;i++) {
		if(visited[i] == k)
			return 1;
	}
	return 0;
}

// matrix reduction for branch as per bound (condition)
void dynamic_reduction() {
	int temp[10][2],q,p,m[10][10],sum=0;
	while(l < n) {
		q = 0;
		for(int i = 0;i < n;i++) {
			p = check_visited(i);
			if(p == 0)
				temp[q++][0] = i;
		}
		for(int i = 0;i < q;i++) {
			//copy full reduced matrix a to matrix m for dynamic reduction;
			for(int k = 0;k < n;k++) {
				for(int j = 0;j < n;j++)
					m[k][j] = tsp_cost[k][j];
			}
			for(int k = 0;k < l;k++) {
				for(int j = 0;j < n;j++)
					m[visited[k]][j] = INF; 	// make row infinity for visited city
			}
			for(int k = 1;k < l;k++) {
				for(int j = 0;j < n;j++) {
					m[j][visited[k]] = INF; 	// make col infinity  for next visited city
				}
			}
			for(int j = 0;j < n;j++) 			// make col infinity for the city to be visited
				m[j][temp[i][0]] = INF;
 
			for(int j = 0;j < n;j++) {			// make m[j][i] infinity  for i to j path
				if(visited[j+1] != -1)
					m[visited[j+1]][0] = INF;
			}

			m[temp[i][0]][0] = INF;
			sum = reduced_matrix(m);
			temp[i][1] = cost[l-1] + sum + tsp_cost[visited[l-1]][temp[i][0]];
			cout << "COST OF NODE NO. " << node_no-1 << " : "<< temp[i][1] << "\n";
		}
		p = min1(temp,q);         				//find minimum cost node as E-node
		visited[l] = temp[p][0];
		cost[l++] = temp[p][1];
		cout << "MINIMUM COST CITY IS " << temp[p][0]+1 << " AND ITS COST IS "<< temp[p][1] << "\n";
	}
}

int main(void) {
	cout << "ENTER NUMBER OF CITIES : \n";
	cin >> n;
	cout << "ENTER COST MATRIX (99 FOR INF): \n";
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			cin >> tsp_cost[i][j];
	cout << "COST MATRIX\n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << setw(3) << tsp_cost[i][j];
		cout << "\n";
	}
	visited[l] = 0;
	cost[l++] = reduced_matrix(tsp_cost);
	dynamic_reduction();
	display_path();
	cout << "\n";
}

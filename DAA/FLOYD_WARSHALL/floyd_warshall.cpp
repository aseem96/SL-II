/*
 * floyd_warshall.cpp
 *
 *  Created on: 23-Feb-2016
 *      Author: aseem
 */

#include <iostream>
#include <iomanip>
#define INF 999
#define MAX 100

using namespace std;

int graph[MAX][MAX];
int closure[MAX][MAX];
int dist[MAX][MAX];	
int n;

void printSolution(int dist[][MAX]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << setw(4) << "INF";
            else
                cout << setw(4) << dist[i][j];
        }
        cout << "\n";
    }
}

void fwarshall(int graph[][MAX]) {
	int i,j,k;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			dist[i][j] = graph[i][j];
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++) {
			for(int k = 0;k < n;k++) {
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
				closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
			}
		}
	}
}

int main(void) {
	cout << "ENTER NUMBER OF VERTICES : ";
	cin >> n;
	cout << "ENTER DISTANCE MATRIX (999 for no edge or infinite) : ";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++) {
			cin >> graph[i][j];
			if(graph[i][j] != INF)
				closure[i][j] = 1;
			else
				closure[i][j] = 0;
		}
	}
	cout << "\n";
	cout << "THE INITIAL CLOSURE MATRIX IS : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << setw(4) << closure[i][j];
		cout << "\n";
	}
	fwarshall(graph);
	cout << "THE DISTANCE MATRIX IS : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << setw(4) << graph[i][j];
		cout << "\n";
	}
	cout << "THE TRANSITIVE CLOSURE MATRIX IS : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++)
			cout << setw(4) << closure[i][j];
		cout << "\n";
	}
	cout << "THE SHORTEST DISTANCE MATRIX IS : \n";
	printSolution(dist);
}

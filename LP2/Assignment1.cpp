/*
LP 2
Group A
Assignment 1

Name: Swaraj Sachin Gosavi
Roll no: 31328
Batch: L3

ASSINGMENT NO. 1
TITLE: Depth first search algorithm and Breadth First Search algorithm

PROBLEM STATEMENT / DEFINITION:
Implement depth first search algorithm and Breadth First Search
algorithm, Use an undirected graph and develop a recursive algorithm
for searching all the vertices of a graph or tree data structure.

OBJECTIVE: 
1. To traverse and search the node in DFS and BFS manner

OUTCOME: The student will be able to
1. Learn depth first search algorithm
2. Learn breadth first search algorithm
*/

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <unistd.h>
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void printMatrix(vector<vector<char>> const &mat);

bool isSafe(vector<vector<char>> const &mat, int x, int y, int target) {
    return (x >= 0 && x < mat.size()) && (y >= 0 && y < mat.size()) && mat[x][y] == target;
}

void floodFillBFS(vector<vector<char>> &mat, int x, int y, char replacement) {

    if (mat.size() == 0) {
        return;
    }

    queue<pair<int, int>> q;
    q.push({x, y});

    char target = mat[x][y];

    if (target == replacement) {
        return;
    }

    while (!q.empty()) {

        pair<int, int> node = q.front();
        q.pop();

        int x = node.first, y = node.second;

        if (mat[x][y] != replacement) {
            mat[x][y] = replacement;
            printMatrix(mat);
            sleep(1);
        }

        for (int k=0; k < 8; k++) {
            if (isSafe(mat, x + row[k], y + col[k], target)) {
                q.push({x + row[k], y+ col[k]});
            }
        }

    }
}

void floodFillDFS(vector<vector<char>> &mat, int x, int y, char replacement) {

    if (mat.size() == 0) {
        return;
    }

    char target = mat[x][y];

    if (target == replacement) {
        return;
    }

    mat[x][y] = replacement;
    printMatrix(mat);
    sleep(1);

    for (int k=0; k < 8; k++) {
        if (isSafe(mat, x + row[k], y + col[k], target)) {
            floodFillDFS(mat, x + row[k], y + col[k], replacement);
        }
    }

}

void printMatrix(vector<vector<char>> const &mat) {
    cout << endl;
    for (int i=0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            switch (mat[i][j]) {
                case 'R':
                    cout << RED;
                    break;
                case 'Y':
                    cout << YELLOW;
                    break;
                case 'G':
                    cout << GREEN;
                    break;
                case 'W':
                    cout << WHITE;
                    break;
                case 'B':
                    cout << BLUE;
                    break;
                case 'X':
                    cout << MAGENTA;
                    break;
                case 'O':
                    cout << CYAN;
                    break;
                default:
                    cout << RESET;
            }
            cout << setw(3) << mat[i][j] << RESET;
        }
        cout << endl;   
    }
    cout << endl;
}

int main() {

    while (true) {
        cout << "\nFloodFill Using BFS & DFS\n";
        vector<vector<char>> mat = 
        {
            { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
            { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
            { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
            { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
            { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
            { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
            { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
            { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
            { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
            { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
        };

        int x = 3, y = 9;

        char replacement = 'O';

        printMatrix(mat);

        int choice;
        cout << "\n\nMenu\nChoose Search Type\n"
            << "1. BFS \n"
            << "2. DFS \n"
            << "0. Exit \n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n\nBFS\n";
                floodFillBFS(mat, x, y, replacement);
                printMatrix(mat);
                break;
            case 2:
                cout << "\n\nDFS\n";
                floodFillDFS(mat, x, y, replacement);
                printMatrix(mat);
                break;
            case 0:
                cout << "Exiting\nThank You!!!\n\n";
                return 0;
            default:
                cout << "Enter valid choice";
                break;
        }
    }

    return 0;
}
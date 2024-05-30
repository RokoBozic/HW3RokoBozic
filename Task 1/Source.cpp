#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

const int R_Max = 20;
const int C_Max = 40;

void clearScreen() {
    cout << "\x1B[2J\x1B[H";
}

void plotPoint(int row, int col, int RowA, int ColA, int RowB, int ColB, bool reachedB) {
    clearScreen();
    for (int i = 1; i <= R_Max; i++) {
        for (int j = 1; j <= C_Max; j++) {
            if (i == RowA && j == ColA) {
                cout << "A";
            }
            else if (i == RowB && j == ColB && !reachedB) {
                cout << "B";
            }
            else if (i == row && j == col) {
                cout << "*";
            }
            else {
                cout << "-";
            }
        }
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}

int main() {
    int RowA, ColA, RowB, ColB;

    cout << "row A: ";
    cin >> RowA;

    cout << "column A: ";
    cin >> ColA;

    cout << "row B: ";
    cin >> RowB;

    cout << "column B: ";
    cin >> ColB;

    if (RowA < 1 || RowA > R_Max || ColA < 1 || ColA > C_Max ||
        RowB < 1 || RowB > R_Max || ColB < 1 || ColB > C_Max) {
        cerr << "Invalid input" << endl;
        return 1;
    }

    int row = RowA;
    int col = ColA;
    bool reachedB = false;

    while (col != ColB) {
        plotPoint(row, col, RowA, ColA, RowB, ColB, reachedB);

        if (col < ColB) {
            col++;
        }
        else {
            col--;
        }
    }

    while (row != RowB) {
        plotPoint(row, col, RowA, ColA, RowB, ColB, reachedB);

        if (row < RowB) {
            row++;
        }
        else {
            row--;
        }
    }

    reachedB = true;
    plotPoint(RowB, ColB, RowA, ColA, RowB, ColB, reachedB);

    return 0;
}
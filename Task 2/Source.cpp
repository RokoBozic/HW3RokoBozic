#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

const int R_Max = 20;
const int C_Max = 40;
const int INF = 1e9;

void clearScreen() {
    cout << "\x1B[2J\x1B[H";
}

void plotPoint(int row, int col, const vector<pair<int, int>>& walls, int RowA, int ColA, int RowB, int ColB, bool reachedB) {
    clearScreen();
    for (int i = 1; i <= R_Max; i++) {
        for (int j = 1; j <= C_Max; j++) {
            bool isWall = false;
            for (const auto& wall : walls) {
                if (i == wall.first && j == wall.second) {
                    isWall = true;
                    break;
                }
            }
            if (i == RowA && j == ColA) {
                cout << "A";
            }
            else if (i == RowB && j == ColB && !reachedB) {
                cout << "B";
            }
            else if (i == row && j == col) {
                cout << "*";
            }
            else if (isWall) {
                cout << "X";
            }
            else {
                cout << "-";
            }
        }
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}

bool isValid(int row, int col, const vector<pair<int, int>>& walls) {
    if (row < 1 || row > R_Max || col < 1 || col > C_Max) return false;
    for (const auto& wall : walls) {
        if (row == wall.first && col == wall.second) return false;
    }
    return true;
}

vector<pair<int, int>> dijkstra(int RowA, int ColA, int RowB, int ColB, const vector<pair<int, int>>& walls) {
    vector<vector<int>> dist(R_Max + 1, vector<int>(C_Max + 1, INF));
    vector<vector<pair<int, int>>> parent(R_Max + 1, vector<pair<int, int>>(C_Max + 1, { -1, -1 }));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    pq.push({ 0, {RowA, ColA} });
    dist[RowA][ColA] = 0;

    while (!pq.empty()) {
        int d = pq.top().first;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();

        if (r == RowB && c == ColB) break;

        for (const auto& dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;
            if (isValid(nr, nc, walls) && d + 1 < dist[nr][nc]) {
                dist[nr][nc] = d + 1;
                parent[nr][nc] = { r, c };
                pq.push({ dist[nr][nc], {nr, nc} });
            }
        }
    }

    vector<pair<int, int>> path;
    for (pair<int, int> at = { RowB, ColB }; at != make_pair(-1, -1); at = parent[at.first][at.second]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
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

    vector<pair<int, int>> walls = { {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10} };

    vector<pair<int, int>> path = dijkstra(RowA, ColA, RowB, ColB, walls);

    if (path.size() == 1 && path[0] == make_pair(RowB, ColB)) {
        cerr << "No path found" << endl;
        return 1;
    }

    bool reachedB = false;
    for (const auto& point : path) {
        if (point == make_pair(RowB, ColB)) {
            reachedB = true;
        }
        plotPoint(point.first, point.second, walls, RowA, ColA, RowB, ColB, reachedB);
    }

    return 0;
}
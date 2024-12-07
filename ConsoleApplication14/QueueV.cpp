#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// ��������� ��� �������� ���������
struct Point {
    int x, y;
};

bool isValid(int x, int y, int n, const vector<vector<int>>& labyrinth, vector<vector<bool>>& visited) {
    return (x >= 0 && x < n && y >= 0 && y < n && labyrinth[x][y] == 0 && !visited[x][y]);
}

void writeLabyrinth(const string& filename, const vector<vector<int>>& labyrinth) {
    ofstream file(filename);
    for (const auto& row : labyrinth) {
        for (int cell : row) {
            file << (cell == 0 ? '0' : cell == 1 ? '1' : '*');
        }
        file << endl;
    }
}

int main() {
    ifstream inputFile("labyrinth.txt");
    if (!inputFile.is_open()) {
        cerr << "�� ������� ������� ���� labyrinth.txt" << endl;
        return 1;
    }

    int n;
    inputFile >> n; // ������ ������� ���������
    vector<vector<int>> labyrinth(n, vector<int>(n));

    // ������ ���������
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> labyrinth[i][j];
        }
    }

    inputFile.close();

    int startX, startY;
    cout << "������� ��������� ������� x: ";
    cin >> startX;
    cout << "������� ��������� ������� y: ";
    cin >> startY;

    // �������� �� ������������ ��������� �������
    if (startX < 0 || startX >= n || startY < 0 || startY >= n || labyrinth[startX][startY] == 1) {
        cerr << "������������ ��������� �������." << endl;
        return 1;
    }

    queue<Point> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // ����������� ��������: �����, ����, �����, ������
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    q.push({ startX, startY });
    visited[startX][startY] = true;

    Point exitPoint = { -1, -1 }; // ���������� ��� �������� ��������� ������

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // �������� �� �����
        if (current.x == 0 || current.x == n - 1 || current.y == 0 || current.y == n - 1) {
            exitPoint = current;
            break; // ������ �����
        }

        // �������� ���� �����������
        for (auto& dir : directions) {
            int newX = current.x + dir[0];
            int newY = current.y + dir[1];

            if (isValid(newX, newY, n, labyrinth, visited)) {
                visited[newX][newY] = true;
                q.push({ newX, newY });
            }
        }
    }

    // ������� ���� � ���������
    if (exitPoint.x != -1 && exitPoint.y != -1) {
        Point current = exitPoint;

        // ������� ���� �� ������ �� ������
        while (!(current.x == startX && current.y == startY)) {
            labyrinth[current.x][current.y] = '*';
            bool foundPrevious = false;

            for (auto& dir : directions) {
                int prevX = current.x + dir[0];
                int prevY = current.y + dir[1];

                if (prevX >= 0 && prevX < n && prevY >= 0 && prevY < n && visited[prevX][prevY]) {
                    current = { prevX, prevY };
                    foundPrevious = true;
                    break;
                }
            }

            if (!foundPrevious) break; // ���� �� ����� ���������� ������
        }

        // ������� ��������� �������
        labyrinth[startX][startY] = '*';
    }

    writeLabyrinth("exit_labyrinth.txt", labyrinth);

    cout << "���� � ������ ������� � ����� exit_labyrinth.txt." << endl;

    return 0;
}
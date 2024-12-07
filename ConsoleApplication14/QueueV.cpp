#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Структура для хранения координат
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
        cerr << "Не удалось открыть файл labyrinth.txt" << endl;
        return 1;
    }

    int n;
    inputFile >> n; // Чтение размера лабиринта
    vector<vector<int>> labyrinth(n, vector<int>(n));

    // Чтение лабиринта
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> labyrinth[i][j];
        }
    }

    inputFile.close();

    int startX, startY;
    cout << "Введите начальную позицию x: ";
    cin >> startX;
    cout << "Введите начальную позицию y: ";
    cin >> startY;

    // Проверка на корректность начальной позиции
    if (startX < 0 || startX >= n || startY < 0 || startY >= n || labyrinth[startX][startY] == 1) {
        cerr << "Некорректная начальная позиция." << endl;
        return 1;
    }

    queue<Point> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // Направления движения: вверх, вниз, влево, вправо
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    q.push({ startX, startY });
    visited[startX][startY] = true;

    Point exitPoint = { -1, -1 }; // Переменная для хранения координат выхода

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // Проверка на выход
        if (current.x == 0 || current.x == n - 1 || current.y == 0 || current.y == n - 1) {
            exitPoint = current;
            break; // Найден выход
        }

        // Проверка всех направлений
        for (auto& dir : directions) {
            int newX = current.x + dir[0];
            int newY = current.y + dir[1];

            if (isValid(newX, newY, n, labyrinth, visited)) {
                visited[newX][newY] = true;
                q.push({ newX, newY });
            }
        }
    }

    // Отметка пути в лабиринте
    if (exitPoint.x != -1 && exitPoint.y != -1) {
        Point current = exitPoint;

        // Отметим путь от выхода до начала
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

            if (!foundPrevious) break; // Если не нашли предыдущую клетку
        }

        // Отметим стартовую позицию
        labyrinth[startX][startY] = '*';
    }

    writeLabyrinth("exit_labyrinth.txt", labyrinth);

    cout << "Путь к выходу отмечен в файле exit_labyrinth.txt." << endl;

    return 0;
}
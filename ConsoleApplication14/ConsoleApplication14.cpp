#include <iostream>
#include <fstream>
#include <vector>
#include "StackZV.h"
#include <Windows.h>
using namespace std;

// Структура для хранения координат


bool isValid(int x, int y, int n, char** labyrinth, bool** visited) {
    return (x >= 0 && x < n && y >= 0 && y < n && labyrinth[x][y] == '0' && !visited[x][y]);
}

void writeLabyrinth(const string& filename, const vector<vector<char>>& labyrinth) {
    ofstream file(filename);
    for (const auto& row : labyrinth) {
        for (char cell : row) {
            file << cell << " ";
        }
        file << endl;
    }
}
void input_labyrinth(char**& labyrinth, int& size) {
    ifstream inputFile("labyrinth.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл labyrinth.txt" << endl;
    }

    int n;
    inputFile >> n; // Чтение размера лабиринта
    size = n;

    char** maze = new char* [n];
    for (int i{}; i < n; ++i)
        maze[i] = new char[n];
    for (int i{}; i < n; ++i)
        for (int j{}; j < n; ++j)
            inputFile >> maze[i][j];
    labyrinth = maze;

    inputFile.close();
}
void print_labyrinth(char** labyrinth, int n) {
    for (int i{}; i < n; ++i) {
        for (int j{}; j < n; ++j)
            std::cout << labyrinth[i][j] << " ";
        std::cout << '\n';
    }
}
void enter_start_position(char** labyrinth, int n, int& x, int& y) {
    do {
        std::cout << "Введите координаты начала (x, y), которые являются проходом в лабиринте: \n";
        std::cin >> x >> y;
    } while (x < 0 || x >= n || y < 0 || y >= n || labyrinth[x][y] == '1');
}
void create_array_visited(bool**& labyrinth, int n) {
    bool** visited = new bool* [n];
    for (int i{}; i < n; ++i)
        visited[i] = new bool[n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            visited[i][j] = false;
    labyrinth = visited;
}

int main() {
    SetConsoleOutputCP(1251);
    try {
        char** maze;
        int n;
        input_labyrinth(maze, n);
        print_labyrinth(maze, n);

        int startX, startY;
        enter_start_position(maze, n, startX, startY);

        StackZV<std::pair<int, int>> s;
        bool** visited;
        create_array_visited(visited, n);
       

        s.push({ startX, startY });

        // Направления движения: вверх, вниз, влево, вправо
        int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        while (!s.empty()) {
            std::pair<int, int> current = s.top();
            s.pop();

            if (current.first == 0 || current.first == n - 1 || current.second == 0 || current.second == n - 1) {
                path.push_back(current);
                break; // Найден выход
            }

            if (!visited[current.first][current.second]) {
                visited[current.first][current.second] = true;
                path.push_back(current);

                // Проверка всех направлений
                for (auto& dir : directions) {
                    int newX = current.first + dir[0];
                    int newY = current.second + dir[1];

                    if (isValid(newX, newY, n, maze, visited)) {
                        s.push({ newX, newY });
                    }
                }
            }
        }
        for (const auto& p : path) {
            labyrinth[p.x][p.y] = '*';
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    

    

    
    stack<Point> s;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<Point> path;

    s.push({ startX, startY });

    // Направления движения: вверх, вниз, влево, вправо
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!s.empty()) {
        Point current = s.top();
        s.pop();

        if (current.x == 0 || current.x == n - 1 || current.y == 0 || current.y == n - 1) {
            path.push_back(current);
            break; // Найден выход
        }

        if (!visited[current.x][current.y]) {
            visited[current.x][current.y] = true;
            path.push_back(current);

            // Проверка всех направлений
            for (auto& dir : directions) {
                int newX = current.x + dir[0];
                int newY = current.y + dir[1];

                if (isValid(newX, newY, n, labyrinth, visited)) {
                    s.push({ newX, newY });
                }
            }
        }
    }

    // Отметка пути в лабиринте
    

    writeLabyrinth("exit_labyrinth.txt", labyrinth);

    cout << "Путь к выходу отмечен в файле exit_labyrinth.txt." << endl;

    return 0;
}
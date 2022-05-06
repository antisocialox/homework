#include <iostream>
#include <vector>

using namespace std;

struct stack{
    int inf;
    stack* next;
};

struct queue{
    int inf;
    queue* next;
};

// ввод графа
void input(vector <vector <int>>& gr) {
    int x, y;
    for (int i = 0; i < gr.size(); ++i) {
        cin >> x >> y;
        gr[x].push_back(y);
    }
}

// Дан ориентированный граф. Вывести на экран все вершины, не смежные с данной.
void task1() {
    int n, X; // Х - данная вершина
    cin >> n;
    vector <vector <int>> gr(n);
    input(gr);
    cin >> X;
    vector <bool> vert(n, true); // вершины, не смежные с данной - true
    // убираю вершины, следующие из Х
    for (int i = 0; i < gr[X].size(); ++i) {
        vert[gr[X][i]] = false;
    }
    // убираю вершины, из которых следует Х
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < gr[i].size(); ++j) {
            if (gr[i][j] == X) {
                vert[i] = false;
                break;
            }
        }
    }
    // вывод
    for (int i = 0; i < n; ++i) {
        if (vert[i])
            cout << i << " ";
    }
    cout << endl;
}
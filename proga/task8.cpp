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

void push(stack*& h, int x) {
    stack* tmp = new stack;
    tmp->inf = x;
    tmp->next = h;
    h = tmp;
}

int pop(stack*& h) {
    stack* tmp = h;
    int x = tmp->inf;
    h = h->next;
    delete tmp;
    return x;
}

void push(queue*& h, queue*& t, int x) {
    queue* tmp = new queue;
    tmp->inf = x;
    tmp->next = nullptr;
    if (!h && !t) {
        h = t = tmp;
    }
    else {
        t->next = tmp;
        t = tmp;
    }
}

int pop(queue*& h, queue*& t) {
    queue* tmp = h;
    h = h->next;
    int x = tmp->inf;
    if (!h)
        t = nullptr;
    delete tmp;
    return x;
}

// ввод ориентированного графа
void inputOriented(vector <vector <int>>& gr) {
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
    inputOriented(gr);
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

// Дан ориентированный граф. Вставить в граф ребро, соединяющее вершины A и B.
void task2() {
    int n, A, B;
    cin >> n;
    vector <vector <int>> gr(n);
    inputOriented(gr);

}
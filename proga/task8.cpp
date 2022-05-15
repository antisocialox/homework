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

void dfs(vector <vector <int>> gr, int x, vector <int> res) {
    stack* h = nullptr;
    vector <int> used(gr.size());
    used[x] = 1;
    res.push_back(x);
    push(h, x);
    while(h) {
        int inf = h->inf;
        bool flag = false;
        int i;
        for (i = 0; i < gr[inf].size(); ++i) {
            if (!used[gr[inf][i]]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            used[gr[inf][i]] = 1;
            res.push_back(gr[inf][i]);
            push(h, gr[inf][i]);
        }
        else
            pop(h);
    }
}

void bfs(vector <vector <int>> gr, int x, vector <int> res) {
    queue* h = nullptr;
    queue* t = nullptr;
    vector <int> used(gr.size());
    used[x] = 1;
    res.push_back(x);
    push(h, t, x);
    while (h) {
        int inf = pop(h, t);
        for (int i = 0; i < gr[inf].size(); ++i) {
            if (!used[gr[inf][i]]) {
                used[gr[inf][i]] = 1;
                res.push_back(gr[inf][i]);
                push(h, t, gr[inf][i]);
            }
        }
    }
}

// ввод ориентированного графа
void inputOriented(vector <vector <int>>& gr) {
    int n, x, y; // n - кол-во связей
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        gr[x].push_back(y);
    }
}

// ввод неориентированного графа
void inputUnoriented(vector <vector <int>>& gr) {
    int n, x, y; // n - кол-во связей
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
}

// Дан ориентированный граф. Вывести на экран все вершины, не смежные с данной.
void task1() {
    int m, X; // m - кол-во вершин, Х - данная вершина
    cin >> m;
    vector <vector <int>> gr(m);
    inputOriented(gr);
    cin >> X;
    vector <bool> vert(m, true); // вершины, не смежные с данной - true
    // убираю вершины, следующие из Х
    for (int i = 0; i < gr[X].size(); ++i) {
        vert[gr[X][i]] = false;
    }
    // убираю вершины, из которых следует Х
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < gr[i].size(); ++j) {
            if (gr[i][j] == X) {
                vert[i] = false;
                break;
            }
        }
    }
    // вывод
    for (int i = 0; i < m; ++i) {
        if (vert[i])
            cout << i << " ";
    }
    cout << endl;
}

// Дан ориентированный граф. Вставить в граф ребро, соединяющее вершины A и B.
void task2() {
    int m, A, B;
    cin >> m;
    vector <vector <int>> gr(m);
    inputOriented(gr);
    gr[A].push_back(B); // добавил ребро А -> В
    vector <int> res; //результат обхода в глубину
    // прохожу по всем узлам графа, пока не найду тот, из которого можно попасть во все вершины (res.size() == m), чтобы вывести полный обход в глубину
    for (int i = 0; i < m; ++i) {
        dfs(gr, i, res);
        if (res.size() == m)
            break;
        res.clear();
    }
    // вывод
    for (auto i : res)
        cout << i << " ";
    cout << endl;
}

// Дан неориентированный граф. Подсчитать степень каждой вершины.
void task3() {
    setlocale(LC_ALL, "rus");
    int m;
    cin >> m;
    vector <vector <int>> gr(m);
    inputUnoriented(gr);
    for (int i = 0; i < m; ++i) {
        cout << "\tСтепень вершины " << i << " равна " << gr[i].size() << endl;
    }
}

// Дан неориентированный граф. Определить содержит ли он циклы. Если да, то вывести их.
void task4() {
    int m;
    cin >> m;
    vector <vector <int>> gr(m);
    inputUnoriented(gr);
    
}
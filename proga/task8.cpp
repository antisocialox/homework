#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct stack{
    int inf;
    stack* next;
};

struct queue{
    int inf;
    queue* next;
};

vector <vector <int>> cycles;
set <vector <int>> sort_cycles;

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

void add_cycles(int start, int end, vector <int> pred) {
    int cur = end;
    vector <int> tmp, sort_tmp;
    while (cur != start) {
        tmp.push_back(cur);
        cur = pred[cur];
    }
    tmp.push_back(start);
    sort_tmp = tmp;
    sort(sort_tmp.begin(), sort_tmp.end());
    if (!sort_cycles.count(sort_tmp)) { 
        reverse(tmp.begin(), tmp.end());
        cycles.push_back(tmp);
        sort_cycles.insert(sort_tmp);
    }
}

void cycle_search(int cur, vector <vector <int>> gr, vector <int>& used, vector <int>& pred) {
    used[cur] = 1;
    for (int i = 0; i < gr[cur].size(); ++i) {
        if (pred[gr[cur][i]] == cur)
            continue;
        else if (used[gr[cur][i]] == 0) {
            pred[gr[cur][i]] = cur;
            cycle_search(gr[cur][i], gr, used, pred);
        }
        else if (used[gr[cur][i]] == 1) {
            add_cycles(gr[cur][i], cur, pred);
        }
    }
    used[cur] = 0;
}

int dfs_with_search_of_dist(int A, int B, vector <vector <int>> gr) {
    int dist = gr.size(), tmpdist = 1;
    stack* h = nullptr;
    vector <int> used(gr.size());
    used[A] = 1;
    push(h, A);
    while (h) {
        int inf = h->inf;
        bool flag = false;
        int i;
        for (i = 0; i < gr[inf].size(); ++i) {
            if (gr[inf][i] == B) {
                dist = min(dist, tmpdist);
                break;
            }
            else if (!used[gr[inf][i]]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            used[gr[inf][i]] = 1;
            push(h, gr[inf][i]);
            tmpdist++;
        }
        else {
            pop(h);
            tmpdist--;
        }
    }
    return dist;
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
    setlocale(LC_ALL, "rus");
    int m;
    cin >> m;
    vector <vector <int>> gr(m);
    inputUnoriented(gr);
    vector <int> used(m);
    vector <int> pred(m, -1);
    for (int i = 0; i < m; ++i) {
        cycle_search(i, gr, used, pred);
    }
    if (cycles.size() == 0)
        cout << "Граф не содержит циклов." << endl;
    else {
        cout << "Граф содержит циклы: " << endl;
        for (auto i : cycles) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
}

// Дан невзвешенный граф неориентированный граф. Найти кратчайший путь между вершинами A и В.
void task5() {
    int m, A, B;
    cin >> m;
    vector <vector <int>> gr(m);
    inputUnoriented(gr);
    cin >> A >> B;
    cout << dfs_with_search_of_dist(A, B, gr) << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "\nЗадание 1.\nВведите кол-во вершин графа, кол-во ребер графа и соединенные вершины:\n";
    task1();
    cout << "\nЗадание 2.\nВведите кол-во вершин графа, кол-во ребер графа, соединенные вершины и вершины А и В:\n";
    task2();
    cout << "\nЗадание 3.\nВведите кол-во вершин графа, кол-во ребер графа и соединенные вершины:\n";
    task3();
    cout << "\nЗадание 4.\nВведите кол-во вершин графа, кол-во ребер графа и соединенные вершины:\n";
    task4();
    cout << "\nЗадание 5.\nВведите кол-во вершин графа, кол-во ребер графа, соединенные вершины и вершины А и В:\n";
    task5();
    return 0;
}
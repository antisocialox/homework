#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// вектор из двух точе с его координатами
struct vect{
    int v1, v2;
};

bool cross(vect forward, vect back) {
    return  (forward.v1 * back.v2 - forward.v2 * back.v1 >= 0);
}

// создание вектора с началом в данной точке и концом в следующей, либо предыдущей
vect mkvect(pair <int, int> current, pair <int, int> next_or_prev) {
    vect v;
    v.v1 = next_or_prev.first - current.first;
    v.v2 = next_or_prev.second - current.second;
    return v;
}

// нахождение точек верхней/нижней огибающей
void envelope(vector <pair <int, int>> ps, vector <pair <int, int>>& res) {
    int len = res.size(); // кол-во уже найденных точек в векторе res (чтобы они не учитывались при нахождении новых точек)
    int cnt = len; // кол-во найденных точек в текущий момент
    for (int i = 0; i < ps.size(); ++i) {
        // если в данной огибающей найдено 2 и более точек, нахожу векторное произведение векторов из средней точки в предыдущую и слудующую для последних трех точек, чтобы исключить среднюю точку, если она не входит в оболочку
        while (cnt >= len + 2 && cross(mkvect(res[cnt - 1], res[cnt - 2]), mkvect(res[cnt - 1], ps[i]))) {
            res.pop_back();
            cnt--;
        }
        res.push_back(ps[i]);
        cnt++;
    }
    // удаляю последнюю в данной огибающей точку, т.к. она является первой точкой в другой огибающей
    res.pop_back();
}

int main() {
    int n;
    cin >> n;
    vector <pair <int, int>> ps(n);
    for (int i = 0; i < n; i++)
        cin >> ps[i].first >> ps[i].second;
    sort(ps.begin(), ps.end());
    vector <pair <int, int>> res;
    envelope(ps, res); // нахожу нижнюю огибающую
    reverse(ps.begin(), ps.end());
    envelope(ps, res); // нахожу верхнюю огибающую
    for (auto i : res)
        cout << '(' << i.first << ", " << i.second << ") ";
    cout << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct point{
    int x, y;
};

struct vect{
    int v1, v2;
};

bool cross(vect forward, vect back) {
    return  (forward.v1 * back.v2 - forward.v2 * back.v1 <= 0);
}

vect mkvect(point current, point next_or_prev) {
    vect v;
    v.v1 = next_or_prev.x - current.x;
    v.v2 = next_or_prev.y - current.y;
    return v;
}

int main() {
    int n;
    cin >> n;
    vector <point> ps(n);
    for (int i = 0; i < n; i++)
        cin >> ps[i].x >> ps[i].y;
    sort(ps.begin(), ps.end());
    vector <point> res;
    return 0;
}
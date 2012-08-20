/**
 * OJ: Caribbean Online Judge
 * Problem: 1532 - Blackholes
 * Status: Accepted (3rd time)
 * URL: http://coj.uci.cu/24h/problem.xhtml?abb=1532
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 60

typedef struct {
    int x, y, z;
} point_t;

typedef struct {
    point_t s, e;
    int t, d;
} blackhole_t;

int t, n;
point_t s, d;
blackhole_t bhs[MAXN];

size_t distance(point_t a, point_t b) {
    int dx = a.x - b.x,
        dy = a.y - b.y,
        dz = a.z - b.z;
    return (size_t)ceil(sqrt(dx * dx + dy * dy + dz * dz));
}

int solve() {
    int i, j, k;
    int l, nt;
    int t[MAXN], t2[MAXN];
    int m[MAXN];
    size_t dis[MAXN][MAXN];
    int ans = INT_MAX;

    for (i = 0; i <= n; ++i)
        t[i] = INT_MAX;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            dis[i][j] = distance(bhs[i].e, bhs[j].s);

    for (i = 0; i < n; ++i) {
        for (j = 0; j <= n; ++j) {
            t2[j] = INT_MIN;
            m[j] = 0;
        }
        t2[i] = bhs[i].t;
        m[i] = 0;
        for (j = 0; j < n; ++j) {
            l = n;
            for (k = 0; k < n; ++k)
                if (!m[k] && t2[k] > t2[l])
                    l = k;
            if (l == n) break;
            for (k = 0; k < n; ++k) {
                if (m[k]) continue;
                nt = t2[l] - dis[k][l] - bhs[k].d;
                if (nt >= bhs[k].t && nt > t2[k])
                    t2[k] = nt;
            }
            m[l] = 1;
        }
        for (j = 0; j < n; ++j) {
            if (t2[j] == INT_MIN)
                continue;
            nt = t2[j] - dis[i][j] - bhs[i].d;
            if (t2[i] < nt)
                t2[i] = nt;
        }
        if (t2[i] > bhs[i].t)
            t[i] = bhs[i].t;
    }

    for (i = 0; i < n; ++i)
        m[i] = 0;
    for (i = 0; i < n; ++i) {
        nt = distance(s, bhs[i].s);
        if (nt < bhs[i].t)
            nt = bhs[i].t;
        if (t[i] > nt)
            t[i] = nt;
    }
    for (i = 0; i < n; ++i) {
        l = n;
        for (j = 0; j < n; ++j)
            if (!m[j] && t[j] < t[l])
                l = j;
        m[l] = 1;
        for (j = 0; j < n; ++j) {
            if (m[j]) continue;
            nt = t[l] + bhs[l].d + dis[l][j];
            if (nt < bhs[j].t)
                nt = bhs[j].t;
            if (t[j] > nt)
                t[j] = nt;
        }
    }
    ans = distance(s, d);
    for (i = 0; i < n; ++i) {
        nt = t[i] + bhs[i].d + distance(bhs[i].e, d);
        if (ans > nt)
            ans = nt;
    }

    return ans;
}

int main() {
    int i, j;

    scanf("%d", &t);
    for (i = 0; i < t; ++i) {
        scanf("%d%d%d", &s.x, &s.y, &s.z);
        scanf("%d%d%d", &d.x, &d.y, &d.z);
        scanf("%d", &n);
        for (j = 0; j < n; ++j) {
            blackhole_t *b = &bhs[j];
            scanf("%d%d%d", &b->s.x, &b->s.y, &b->s.z);
            scanf("%d%d%d", &b->e.x, &b->e.y, &b->e.z);
            scanf("%d%d", &b->t, &b->d);
        }
        printf("%d\n", solve());
    }

    return 0;
}

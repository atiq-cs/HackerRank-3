#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <cassert>
#include <climits>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long LL;

#define maxn 75005
/*
 * Suffix Array da algorithm
 */
struct SuffixArray {

	int wa[maxn], wb[maxn], wv[maxn], ws[maxn];

	int cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}

	void da(int *r, int *sa, int n, int m) {
		int i, j, p, *x = wa, *y = wb, *t;
		for (i = 0; i < m; i++) ws[i] = 0;
		for (i = 0; i < n; i++) ws[x[i] = r[i]]++;
		for (i = 1; i < m; i++) ws[i] += ws[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
		for (j = 1, p = 1; p < n; j *= 2, m = p) {
			for (p = 0, i = n - j; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			for (i = 0; i < n; i++) wv[i] = x[y[i]];
			for (i = 0; i < m; i++) ws[i] = 0;
			for (i = 0; i < n; i++) ws[wv[i]]++;
			for (i = 1; i < m; i++) ws[i] += ws[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
			for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
		}
			return;
	}

	int rank[maxn], height[maxn];

	void calheight(int *r, int *sa, int n) {
		int i, j, k = 0;
		for (i = 1; i <= n; i++) rank[sa[i]] = i;
		for (i = 0; i < n; height[rank[i++]] = k)
			for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
		return;
	}
	
	int RMQ[maxn];
	int mm[maxn];
	int best[20][maxn];

	void initRMQ(int n) {
		int i, j, a, b;
		for (mm[0] = -1, i = 1; i <= n; i++)
			mm[i] = (((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1]);
		for (i = 1; i <= n; i++)
			best[0][i] = i;
		for (i = 1; i <= mm[n]; i++)
			for (j = 1; j <= n + 1 - (1 << i); j++) {
				a = best[i - 1][j];
				b = best[i - 1][j + (1 << (i - 1))];
				if (RMQ[a] < RMQ[b]) best[i][j] = a;
				else best[i][j] = b;
			}
		return;
	}

	int askRMQ(int a, int b) {
		int t;
		t = mm[b - a + 1]; b -= (1 << t) - 1;
		a = best[t][a]; b = best[t][b];
		return RMQ[a] < RMQ[b] ? a : b;
	}

	int lcp(int a, int b) {
		int t;
		a = rank[a]; b = rank[b];
		if (a > b) {
			t = a; a = b; b = t;
		}
		return (height[askRMQ(a + 1, b)]);
	}

}SA;

char s[maxn];
int r[maxn], sa[maxn];
int n, q;

int main() {
	scanf("%d%d", &n, &q);
	scanf("%s", s);
	while (q--) {
		int p; char ch;
		scanf("%d %c\n", &p, &ch);
		p--;
		s[p] = ch;
		memset(r, 0, sizeof(r));
		memset(sa, 0, sizeof(sa));
		for (int i = 0; i < n; i++)
			r[i] = s[i];
		r[n] = 0;
		SA.da(r, sa, n + 1, 128);
		SA.calheight(r, sa, n);
		long long ret = (long long)n * (n + 1) / 2;
		for (int i = 1; i <= n; i++)
			ret -= SA.height[i];
		cout << ret << endl;
	}
	return 0;
}



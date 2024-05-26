#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int inf = 0x7f7f7f7f;
const long long infll = 0x7f7f7f7f7f7f7f7fll;

template <class T>
class MaximumFlow
{
public:
	static const int maxn = 1000;

	class Edge
	{
	public:
		int u, v;
		T c, f;

		Edge(void) : u(0), v(0), c(0), f(0)
		{

		}

		Edge(const int & u, const int & v, const T & c, const T & f) : u(u), v(v), c(c), f(f)
		{

		}
	};

	int n;
	int s, t;
	vector<Edge> edges;
	vector<int> Eid[maxn];
	int d[maxn];
	bool vis[maxn];
	int cur[maxn];

	void resize(const int & n)
	{
		edges.clear();
		for (int i = 0; i < this->n; i++)
			Eid[i].clear();
		this->n = n;
	}

	void add_edge(const int & u, const int & v, const T & c)
	{
		edges.push_back(Edge(u, v, c, 0));
		Eid[u].push_back(edges.size() - 1);
		edges.push_back(Edge(v, u, 0, 0));
		Eid[v].push_back(edges.size() - 1);
	}

	bool bfs(void)
	{
		queue<int> que;
		memset(vis, false, sizeof vis[0] * n);
		d[s] = 0;
		vis[s] = true;
		for (que.push(s); !que.empty(); que.pop())
		{
			int u = que.front();
			for (const auto & id : Eid[u])
			{
				const Edge & e = edges[id];
				if (!vis[e.v] && e.f < e.c)
				{
					vis[e.v] = true;
					d[e.v] = d[u] + 1;
					que.push(e.v);
				}
			}
		}
		return vis[t];
	}

	T dfs(const int & u, T f)
	{
		if (u == t || f == 0)
			return f;
		else
		{
			T flw, ans = 0;
			for (; cur[u] < Eid[u].size(); cur[u]++)
			{
				Edge & e = edges[Eid[u][cur[u]]];
				if (d[e.v] == d[u] + 1 && (flw = dfs(e.v, min(f, e.c - e.f))) > 0)
				{
					e.f += flw;
					edges[Eid[u][cur[u]] ^ 1].f -= flw;
					ans += flw;
					f -= flw;
				}
				if (f == 0)
					break;
			}
			return ans;
		}
	}

	T maximum_flow(const int & s, const int & t)
	{
		T ans = 0;
		this->s = s;
		this->t = t;
		for (; bfs(); )
		{
			memset(cur, 0, sizeof cur[0] * n);
			ans += dfs(s, inf);
		}
		return ans;
	}
};

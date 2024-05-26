class MaxFlowEdge
{
private:
protected:
public:
	int u;
	int v;
	int c;
	int f;

	MaxFlowEdge(void);
	MaxFlowEdge(int, int, int, int);
};

MaxFlowEdge::MaxFlowEdge(void) : u(0), v(0), c(0), f(0)
{

}

MaxFlowEdge::MaxFlowEdge(int u, int v, int c, int f) : u(u), v(v), c(c), f(f)
{

}

int n;
int dpt, g, stp;
int m;
int x[maxn];
int r;
int sz;
vector<MaxFlowEdge> edges;
vector<int> Eid[maxsz];
int a[maxsz];
int d[maxsz];
int p[maxsz];

void initialize(void)
{
	int i;

	edges.clear();
	for(i=0 ; i<sz ; ++i)
		Eid[i].clear();
	sz = 0;
}

void add_edge(int u, int v, int c)
{
	edges.push_back(MaxFlowEdge(u, v, c, 0));
	Eid[u].push_back(edges.size()-1);
	edges.push_back(MaxFlowEdge(v, u, 0, 0));
	Eid[v].push_back(edges.size()-1);
}

int maximum_flow(int s, int t)
{
	int i;
	int u;
	int ans;
	MaxFlowEdge * e;
	queue<int> que;

	ans = 0;
	for( ; ; )
	{
		d[s] = 0;
		memset(a, 0, sizeof(a[0])*sz);
		a[s] = inf;
		for( ; !que.empty() ; que.pop());
		for(que.push(s) ; !que.empty() ; que.pop())
		{
			u = que.front();

			for(i=0 ; i<Eid[u].size() ; ++i)
			{
				e = &edges[Eid[u][i]];

				if(a[e->v]==0 && e->c>e->f)
				{
					a[e->v] = min(a[u], e->c-e->f);
					d[e->v] = d[u]+1;
					p[e->v] = Eid[u][i];
					que.push(e->v);
				}
			}

			if(a[t] != 0)
				break;
		}

		if(a[t] == 0)
			break;
		
		for(u=t ; u!=s ; u=edges[p[u]].u)
		{
			edges[p[u]].f += a[t];
			edges[p[u]^1].f -= a[t];
		}

		ans += a[t]*max(0, stp-d[t]+3);
	}

	return ans;
}
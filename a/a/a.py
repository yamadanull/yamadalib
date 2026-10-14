N=int(input())
g=[[] for _ in range(N)]
for c_,p in enumerate(list(map(int,input().split()))):
	c=c_+1
	g[p].append(c)

ans=[1]*N
def dfs(u):
	for v in g[u]:ans[u]+=dfs(v)
	return ans[u]

dfs(0)
for a in ans:print(a)

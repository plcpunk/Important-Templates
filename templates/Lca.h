#include <vector>
#include <cmath>

class Lca {

    std::vector<int> *adj;
    vector<int> E;
    vector<int> H;
    vector<int> L;
    int **M;
    int size;

    void euler_tour(int v,int level)
    {
        E.push_back(v);
        L.push_back(level);
        H.at(v-1)=E.size()-1;
        for(int i=0;i<adj[v].size();i++)
        {
            int j = adj[v].at(i);
            if(H.at(j-1)==-1)
            {
                euler_tour(j,level+1);
		        E.push_back(v);
        	    L.push_back(level);
            }
        }
    }

    void process()
    {
	  	int n=L.size();
	  	M = new int*[n+9];
      	for(int i=0;i<n;i++)
      		M[i] = new int[(int)log2(n)+9];
      	int i, j;
      	for (i=0;i<n;i++)
        	M[i][0] = i;
      	for (j = 1; 1 << j <= n; j++)
        	for (i = 0; i + (1 << j) - 1 < n; i++)
            	if (L.at(M[i][j - 1]) < L.at(M[i + (1 << (j - 1))][j - 1]))
                	M[i][j] = M[i][j - 1];
              	else
                  	M[i][j] = M[i + (1 << (j - 1))][j - 1];
    }

    int rmq(int i, int j) 
    {
        int k =log2(j - i + 1);
        if (L.at(M[i][k]) <= L.at(M[j-(1 << k)+1][k]))
            return M[i][k];
        else
            return M[j -(1 << k)+1][k];
    }

    public:

    Lca(int n)
    {
        size=n;
        adj = new std::vector<int>[size+9];
    }

    void addEdge(int u,int v)
    {
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    void initialize(int r)
    {
        for(int i=1;i<=size;i++)
            H.push_back(-1);
        euler_tour(r,0);
        process();
    }

    void initialize()
    {
        for(int i=0;i<size;i++)
            H.push_back(-1);
        euler_tour(1,0);
        process();
    }

    int lca(int u,int v)
    {
        int x = H.at(u-1),y=H.at(v-1);
        if(y<x)
            swap(x,y);
        return E.at(rmq(x,y));
    }

    int level(int v)
    {
        return L.at(H.at(v-1));
    }
};
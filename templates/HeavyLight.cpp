#include <iostream>
#include <cstdio>
#include <vector>
#define pii pair<int,int>
#define mk_pii make_pair
using namespace std;

class HeavyLight {

    pii *adj;
    int *subTreeSize;
    int *parent;
    int size;
    int root;

    public:

    HeavyLight(int vertex, int n)
    {
        root = vertex;
        size = n;
        adj = new vector<pii>[n+9];
    }

    void addEdge(int u,int v,int w)
    {
        adj[u].push_back(mk_pii(v,w));
        adj[v].push_back(mk_pii(u,w));
    }


};
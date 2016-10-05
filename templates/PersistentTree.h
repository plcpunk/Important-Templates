#include <vector>

template <class T> class PersistentTree {
    struct node {
        T info;
        node *left;
        node *right;
        node(T val) {
            info = val;
            right = NULL;
            left = NULL;
        }
    };

    vector <node*> tree;
    vector <node*> lazy;

    int size;

    node* initNode() 
    {
        return new node(identity_element());
    }

    void construct_tree_helper(T* arr,int l,int r,node *cur,node *lazyCur)
    {
		if(l==r)
		{
			cur->info = arr[l];
			return;
		}
        cur->left = initNode();
        cur->right = initNode();
        lazyCur->left = initNode();
        lazyCur->right = initNode();
		int mid = l + (r-l)/2;
		construct_tree_helper(arr,l,mid,cur->left,lazyCur->left);
		construct_tree_helper(arr,mid+1,r,cur->right,lazyCur->right);
		cur->info = combine(cur->left->info,cur->right->info);
    }

    void update_helper(int l, int r, T val, int x, int y, node *cur, node *lazyCur, node *newCur, node *newLazyCur)
    {
        int mid = x + (y-x)/2;
		if(l==x && r==y)
		{
			newLazyCur->info = update_combine(lazyCur->info,val);
			newCur->info = update_combine(cur->info,val);
            newLazyCur->left = lazyCur->left;
            newLazyCur->right = lazyCur->right;
            newCur->left = cur->left;
            newCur->right = cur->right;
            return;
		}
		if(r<=mid)
		{
            newCur->left = initNode();
            newLazyCur->left = initNode();
			update_helper(l,r,val,x,mid,cur->left,lazyCur->left,newCur->left,newLazyCur->left);
            newCur->right = cur->right;
            newLazyCur->right = lazyCur->right;
		}
		else if(l>mid)
		{
            newCur->right = initNode();
            newLazyCur->right = initNode();
			update_helper(l,r,val,mid+1,y,cur->right,lazyCur->right,newCur->right,newLazyCur->right);
            newCur->left = cur->left;
            newLazyCur->left = lazyCur->left;
		}
		else
		{
            newCur->left = initNode();
            newLazyCur->left = initNode();
            newCur->right = initNode();
            newLazyCur->right = initNode();   
			update_helper(l,mid,val,x,mid,cur->left,lazyCur->left,newCur->left,newLazyCur->left);
			update_helper(mid+1,r,val,mid+1,y,cur->right,lazyCur->right,newCur->right,newLazyCur->right);
		}
        newCur->info = combine(newCur->left->info,newCur->right->info);
        newLazyCur->info = lazyCur->info;
		newCur->info = update_combine(newCur->info,newLazyCur->info);
    }

	T query_helper(int l,int r,T lazyVal,int x,int y,node* cur,node* lazyCur)
	{
		int mid = x + (y-x)/2;
		if(l==x && r==y)
		{
				return update_combine(lazyVal,cur->info);
		}
		else if(r<=mid)
		{
			return query_helper(l,r,update_combine(lazyVal,lazyCur->info),x,mid,cur->left,lazyCur->left);
		}
		else if(l>mid)
		{
			return query_helper(l,r,update_combine(lazyVal,lazyCur->info),mid+1,y,cur->right,lazyCur->right);
		}
		else
		{
			T result1 = query_helper(l,mid,update_combine(lazyVal,lazyCur->info),x,mid,cur->left,lazyCur->left);
			T result2 = query_helper(mid+1,r,update_combine(lazyVal,lazyCur->info),mid+1,y,cur->right,lazyCur->right);
			return combine(result1,result2);
		}
	}

    public:

	virtual T combine(T x,T y) = 0;

	virtual T update_combine(T x, T y) = 0;

	virtual T identity_element() = 0;

	void construct_tree(T *arr,int n)
	{
		if(n<=0)
			return;
		size = n;
		node *root = initNode();
        node *lazyRoot = initNode();
		construct_tree_helper(arr,0,size-1,root,lazyRoot);
        tree.push_back(root);
        lazy.push_back(lazyRoot);
	}

    void update(int l,int r,T val)
    {
        if(l>r || l<0 || l>size || r<0 || r>size)
			return;
        node *newRoot = initNode();
        node *newLazyRoot = initNode();    
        update_helper(l,r,val,0,size-1,tree.at(tree.size()-1),lazy.at(lazy.size()-1),newRoot,newLazyRoot);
        tree.push_back(newRoot);
        lazy.push_back(newLazyRoot);
    }

    T query(int l,int r,int index)
    {
        if(l>r || l<0 || l>size || r<0 || r>size)
			return identity_element();
        return query_helper(l,r,identity_element(),0,size-1,tree.at(index),lazy.at(index));
    }

    T query_current(int l,int r)
    {
        return query(l,r,tree.size()-1);
    }

};
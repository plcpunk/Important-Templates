
template <class T> class SegmentTree {

	T *tree;
	T *lazy;
	int size;

	void construct_tree_helper(T *arr,int l,int r,int index)
	{
		lazy[index] = identity_element();
		if(l==r)
		{
			tree[index] = arr[l];
			return;
		}
		int mid = l + (r-l)/2;
		construct_tree_helper(arr,l,mid,2*index+1);
		construct_tree_helper(arr,mid+1,r,2*index+2);
		tree[index] = combine(tree[2*index+1],tree[2*index+2]);
	}

	T update_helper(int l,int r,T val,int x,int y,int index)
	{
		int mid = x + (y-x)/2;
		if(l==x && r==y)
		{
			lazy[index] = update_combine(lazy[index],val);
			tree[index] = update_combine(tree[index],val);
			return tree[index];
		}
		if(r<=mid)
		{
			T result = update_helper(l,r,val,x,mid,2*index+1);
			tree[index] = combine(result,tree[2*index+2]);
		}
		else if(l>mid)
		{
			T result = update_helper(l,r,val,mid+1,y,2*index+2);
			tree[index] = combine(tree[2*index+1],result);
		}
		else
		{
			update_helper(l,mid,val,x,mid,2*index+1);
			update_helper(mid+1,r,val,mid+1,y,2*index+2);
			tree[index] = combine(tree[2*index+1],tree[2*index+2]);
		}
		tree[index] = update_combine(tree[index],lazy[index]);
		return tree[index];
	}

	T query_helper(int l,int r,T lazyVal,int x,int y,int index)
	{
		int mid = x + (y-x)/2;
		if(l==x && r==y)
		{
				return update_combine(lazyVal,tree[index]);
		}
		else if(r<=mid)
		{
			return query_helper(l,r,update_combine(lazyVal,lazy[index]),x,mid,2*index+1);
		}
		else if(l>mid)
		{
			return query_helper(l,r,update_combine(lazyVal,lazy[index]),mid+1,y,2*index+2);
		}
		else
		{
			T result1 = query_helper(l,mid,update_combine(lazyVal,lazy[index]),x,mid,2*index+1);
			T result2 = query_helper(mid+1,r,update_combine(lazyVal,lazy[index]),mid+1,y,2*index+2);
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
		tree = new T[4*size+9];
		lazy = new T[4*size+9];
		construct_tree_helper(arr,0,size-1,0);
	}

	void update(int l,int r,T val)
	{
		if(l>r || l<0 || l>size || r<0 || r>size)
			return;
		update_helper(l,r,val,0,size-1,0);
	}

	T query(int l,int r)
	{
		if(l>r || l<0 || l>size || r<0 || r>size)
			return identity_element();
		return query_helper(l,r,identity_element(),0,size-1,0);
	}

};
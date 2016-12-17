#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#include "templates/SegmentTree.h"

struct segment {
	long long firstNum;
	long long lastNum;
	int size;
	int maxWidth;
	int firstWidth;
	bool firstType;
	int lastWidth;
	bool lastType;
	segment()
	{
		firstNum = 0 = lastNum = 0 = size = 0 = lastWidth = firstWidth = maxWidth = 0;
		firstType = lastType = false;
	}
	segment(long long a, long long b, int c, int d, int e,bool f, int g,bool h)
	{
		firstNum = a;lastNum = b;size = c;maxWidth = d,firstWidth = e;firstType = f;
		lastWidth = g;lastType = h;
	}
};

class Custom_SegmentTree: public SegmentTree<segment>
{
	public:

	segment combine(segment x,segment y)
	{
		int firstWidth = x.firstWidth;
		bool firstType = x.firstType;
		int lastWidth = y.lastWidth;
		bool lastType = y.lastType;
		int maxWidth = max(x.maxWidth,y.maxWidth);
		int firstNum = x.firstNum;
		int lastNum = y.lastNum;
		int size = x.size + y.size;
		if(x.lastNum > y.firstNum)
		{
			int newWidth = x.lastWidth + (y.firstType)?1:y.firstWidth;
			if(x.lastWidth==x.size)
				firstWidth = newWidth;
			if(y.firstWidth==y.size && !y.firstType)
				lastWidth = newWidth;
			if(y.size==1)
				lastType = false;
			if(x.size==1)
				firstType = false;	
		}
		if(x.lastNum < y.firstNum)
		{

		}
		return new segment(firstNum, lastNum, size,
		maxWidth, firstWidth, firstType, lastWidth, lastType);
	}

	segment update_combine(segment x,segment y)
	{
		
	}

	segment identity_element()
	{
		return new segment();
	}

} tree;

void solve_input()
{

}

int main()
{
	solve_input();
	return 0;
}
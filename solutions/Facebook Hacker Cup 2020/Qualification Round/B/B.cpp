#include <iostream>
using namespace std;

int main() {
	int t,n;
	cin>>t;
	for(int testCase=1;testCase<=t;testCase++) {
		cin>>n;
		int balance = 0;
		for(int i=0;i<n;i++) {
			char ch;
			cin>>ch;
			if(ch=='A') balance++;
			else balance--;
		}
		cout<<"Case #"<<testCase<<": ";
		if(balance==1 || balance==-1) cout<<'Y'<<endl;
		else cout<<'N'<<endl;
	}
	return 0;
}

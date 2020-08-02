#include <iostream>
using namespace std;

int main() {
	int t,n;
	char arr[59][59];
	cin>>t;
	for(int testCase=1;testCase<=t;testCase++) {
		cin>>n;
		string I, O;
		cin>>I>>O;
		for(int i=0;i<n;i++) {
			arr[i][i]='Y';
			bool disconnect = false;
			for(int j=i+1;j<n;j++) {
				disconnect = disconnect || I[j]=='N' || O[j-1]=='N';
				if(disconnect) arr[i][j]='N';
				else arr[i][j]='Y';
			}
			disconnect = false;
			for(int j=i-1;j>=0;j--) {
				disconnect = disconnect || I[j]=='N' || O[j+1]=='N';
				if(disconnect) arr[i][j]='N';
				else arr[i][j]='Y';
			}
		}
		cout<<"Case #"<<testCase<<": "<<endl;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cout<<arr[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}

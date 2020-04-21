#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=100;
char A[N],B[N];
int dp[N][N];
int main(){
	gets(A+1);
	gets(B+1);
	int lenA=strlen(A+1);
	int lenB=strlen(B+1);
	for(register int i=1;i<=lenA;++i){
		for(register int j=1;j<=lenB;++j){
			if(A[i]==B[j])dp[i][j]=dp[i-1][j-1]+1;
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
	}
	printf("%d\n",dp[lenA][lenB]);
}

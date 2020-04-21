#include<stdio.h>
#include<string.h>
const int maxn=1010;
char s[maxn];
int dp[maxn][maxn];
int main(){
	gets(s);
	int len=strlen(s),ans=1;
	for(register int i=0;i<len-1;++i){
		dp[i][i]=1;
		if(s[i]==s[i+1])dp[i][i+1]=1,ans=2;
	}
	for(register int l=3;l<=len;++l){
		for(register int i=0;i+l-1<len;++i){
			int j=i+l-1;
			if(s[i]==s[j]&&dp[i+1][j-1]==1){
				dp[i][j]=1;
				ans=l;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

#include<stdio.h>
int f[10],n;
void dfs(int pre,int pos,int sum){
	if(sum==n&&pos>1){
		for(int i=0;i<pos-1;++i){
			printf("%d+",f[i]);
		}
		printf("%d\n",f[pos-1]);
		return ;
	}
	for(register int i=pre;i<=n-sum;++i){
		f[pos]=i;
		//printf("%d %d\n",pos,f[pos]);
		dfs(i,pos+1,sum+i);
	}
}
int main(){
	scanf("%d",&n);
	dfs(1,0,0);
	return 0;
} 

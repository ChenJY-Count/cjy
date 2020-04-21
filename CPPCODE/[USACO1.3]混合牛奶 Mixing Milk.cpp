#include<stdio.h>
int a[5005];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++){
		int p,t;
		scanf("%d %d",&p,&t);
		a[p]+=t;
	}
	int i=0,money=0;
	while(n){
		if(a[i]){
			if(a[i]<=n){
				n-=a[i];
				money+=i*a[i];
			}
			else{
				
				money+=i*n;
				n=0;
			}
		}
		i++;
	}
	printf("%d\n",money);
	return 0;
}

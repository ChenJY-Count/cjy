#include<stdio.h>
#define ll long long int
int inv[3000003];
int main(){
	int n,p; 
	scanf("%d %d",&n,&p);
	inv[1]=1;
	puts("1");
	for(register int i=2;i<=n;++i){
		inv[i]=(ll)(p-p/i)*inv[p%i]%p;
		printf("%d\n",inv[i]);
	}
	return 0;
}

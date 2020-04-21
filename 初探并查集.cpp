#include<stdio.h>
int f[1001],n,m,sum;

void init(){
    for(int i=1;i<=n;i++)
        f[i]=i;
}

int getf(int v){
    if(f[v] == v)
        return v;
    else{
        f[v]=getf(f[v]); //v的直系boss是f[v]，如果值不一样，继续寻找f[v]的boss，一直递归调用
        return f[v];
    }
}

void merge(int v,int u){
    int t1,t2;
    t1=getf(v);
    t2=getf(u);
    if(t1 != t2){
        f[t2]=t1;
    }
    return;
}
int main(){
	int x,y;
	scanf("%d %d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		scanf("%d %d",&x,&y);
		merge(x,y); 
	}
	for(int i=1;i<=n;i++){
		if(f[i]==i)sum++;
	}
	printf("%d\n",sum);
	return 0;
}
/*
11 10
1 2
3 4
5 2
4 6
2 6
7 11
8 7
9 7
9 11
1 6
*/ 

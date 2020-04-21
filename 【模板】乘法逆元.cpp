#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x;
}
void exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return ;
	}
	exgcd(b,a%b,x,y);
	int temp=x;
	x=y;
	y=temp-a/b*y;
	return ;
}

int inverse(int a,int m){
	int x,y;
	exgcd(a,m,x,y);
	return (x%m+m)%m;
}
int main(){
	int n,p;
	n=read(),p=read();
	for(register int i=1;i<=n;i++){
		printf("%d\n",inverse(i,p));
	}
	return 0;
}

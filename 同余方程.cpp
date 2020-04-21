#include<cstdio> 
void exGcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return ;
	}
	exGcd(b,a%b,y,x),y-=a/b*x;
}
int main(){
	int a,b,x,y;
	scanf("%d %d",&a,&b);
	exGcd(a,b,x,y);
	printf("%d\n",(x%b+b)%b);
	return 0;
}

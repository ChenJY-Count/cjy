#include<stdio.h>
#define ll long long int
ll gcd(ll a,ll b){
	return !b?a:gcd(b,a%b);
} 
int main(){
	ll a,b,c;
	scanf("%lld %lld %lld",&a,&b,&c);
	a=a/gcd(a,b)*b;
	a=a/gcd(a,c)*c;
	printf("%lld\n",a);
	return 0;
}

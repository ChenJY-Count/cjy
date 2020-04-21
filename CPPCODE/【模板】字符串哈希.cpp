#include<cstdio>
#include<cstring>
#include<algorithm>
#define ull unsigned long long int
ull p=233;
using namespace std;
int hashfunc(char s[]){
	int len=strlen(s);
	ull h=0;
	for(register int i=0;i<len;++i){
		/*if(s[i]>='0'&&s[i]<='9'){
			h=(h*p+s[i]-'0')%mod;
		}
		else if(s[i]>='A'&&s[i]<='Z'){
			h=(h*p+s[i]-'A'+10)%mod;
		}
		else{
			h=(h*p+s[i]-'a'+36)%mod;
		}*/
		h=h*p+(ull)s[i];
	}
	return (int)h;
}
int a[10001];
int main(){
	int n;
	char s[1501];
	scanf("%d",&n);
	for(register int i=0;i<n;++i){
		scanf("%s",s);
		a[i]=hashfunc(s);
		//printf("%d\n",a[i]);
	}
	sort(a,a+n);
	printf("%d\n",unique(a,a+n)-a);
	return 0;
}

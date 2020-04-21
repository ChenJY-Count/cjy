#include <iostream>
#include <cstring>
using namespace std;
const int max_len = 200;
struct bign{
    int d[410];
    int len;
    int fuhao;
    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
        fuhao=0;
    }
};

//将整数转化成bign
bign change(char str[]){
    bign a;
    a.len = strlen(str);
    if(str[0]=='-') {
		a.fuhao=1;
	}
    for (int i = 0; i < a.len; i++){
        a.d[i] = str[a.len - i - 1] - '0'; //逆着赋值
        if(a.fuhao==1&&i==a.len-2)break;
    }
    if(a.fuhao==1)a.len-=1;
    return a;
}

//高精度A * B
bign mul(bign a, bign b){
    bign c;
    for (int i = 0; i < a.len; i++){
        for (int j = 0; j < b.len; j++){
            c.d[i + j] += a.d[i] * b.d[j];
        }
    }
    for (int i = 0; i < a.len + b.len; i++){
        int temp = c.d[i];
        if (temp >= 10){
            c.d[i] = temp % 10;
            c.d[i + 1] += temp / 10;
        }
    }
    c.len = a.len + b.len;
    while (c.len > 1 && c.d[c.len - 1] == 0){
        c.len--;
    }
    if(a.fuhao+b.fuhao==1)c.fuhao=1;
    return c;
}
void print(bign n){
	if(n.fuhao==1)printf("-");
    for (int i = n.len - 1; i >= 0; i--){
        printf("%d", n.d[i]);
    }
    printf("\n");
}
int main(){
    char str1[210], str2[210];
    scanf("%s", str1);
    scanf("%s", str2);
    bign a = change(str1);
    bign b = change(str2);
    bign c = mul(a, b);
    print(c);
    return 0;
}


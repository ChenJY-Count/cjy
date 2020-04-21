#include<bits/stdc++.h>
using namespace std;
struct node{
	string yuan;
	string bian;
}a[8];
struct x{
	string s;
	int step;
	x(){
		s="";
		step=0;
	}
};
int n;
string s1,sn;

int judge(string &a,node b,int f){
	int e=a.find(b.yuan,f);
	if(e!=string::npos){
		return e;
	}
	else return -1;
}
string y(string a,node b,int pos){
	return a.replace(pos,b.yuan.length(),b.bian);
}
int judge1(string &a,node b,int f){
	int e=a.find(b.bian,f);
	if(e!=string::npos){
		return e;
	}
	else return -1;
}
string y1(string a,node b,int pos){
	return a.replace(pos,b.bian.length(),b.yuan);
}
unordered_map<string,int>color,inq;
int bfs(){
	if(s1==sn)return 0;
	queue<x>q1,q2;
	inq[s1]=0;
	x t1;
	t1.s=s1;
	q1.push(t1);
	color[s1]=1;
	inq[sn]=1;
	x tn;
	tn.s=sn;
	q2.push(tn);
	color[sn]=2;
	int step1=0,step2=0,flag=1;
	while(!q1.empty()&&!q2.empty()){
		if(flag){
			//if(++step1+step2>10)break;
				x s2=q1.front();
				q1.pop();
			if(inq[s2.s]+step2==10)break;
			for(int i=0;i<n;i++){
				int pos=judge(s2.s,a[i],0);
				if(pos==-1)continue;
				string s3=y(s2.s,a[i],pos);
					while(pos!=-1){
						if(inq[s3]){
							if(color[s2.s]+color[s3]==3){
								//cout<<inq[s2.s]<<" 1 "<<inq[s3]<<" "<<step2<<endl<<endl<<endl;
								return inq[s2.s]+inq[s3];
							}
							pos=judge(s2.s,a[i],pos+1);
							if(pos==-1)break;
							s3=y(s2.s,a[i],pos);
							continue;
						}
					inq[s3]=inq[s2.s]+1;
					color[s3]=color[s2.s];
					x t3;
					t3.s=s3;
					t3.step=s2.step+1;
					step1=t3.step;
					q1.push(t3);
					pos=judge(s2.s,a[i],pos+1);
					if(pos==-1)break;
					s3=y(s2.s,a[i],pos);
				}
			}
			flag=0;
		}
		else{
			//if(++step2+step1>10)break;
				x s2=q2.front();
				q2.pop();
				if(inq[s2.s]+step1>10)break;
			//	if(s2.step==5)break;
			for(int i=0;i<n;i++){
				int pos=judge1(s2.s,a[i],0);
				if(pos==-1)continue;
				string s3=y1(s2.s,a[i],pos);
					while(pos!=-1){
						if(inq[s3]){
							if(color[s2.s]+color[s3]==3){
								//cout<<inq[s2.s]<<" 2 "<<inq[s3]<<" "<<step1<<endl<<endl<<endl;
								return inq[s2.s]+inq[s3];
							}
							pos=judge1(s2.s,a[i],pos+1);
							if(pos==-1)break;
							s3=y1(s2.s,a[i],pos);
							continue;
						}
					inq[s3]=inq[s2.s]+1;
					color[s3]=color[s2.s];
					x t3;
					t3.s=s3;
					t3.step=s2.step+1;
					step2=t3.step;
					q2.push(t3);
					pos=judge1(s2.s,a[i],pos+1);
					if(pos==-1)break;
					s3=y1(s2.s,a[i],pos);
				}
			}
			flag=1;
		}
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string c,d;
	cin>>s1>>sn;
	while(cin>>c>>d){
		a[n].yuan=c;
		a[n].bian=d;
		n++;
	}
	//for(int i=0;i<n;i++)cout<<a[i].yuan<<" "<<a[i].bian<<endl;
	int t=bfs();
	if(t!=-1)cout<<t<<endl;
	else cout<<"NO ANSWER!"<<endl;
}

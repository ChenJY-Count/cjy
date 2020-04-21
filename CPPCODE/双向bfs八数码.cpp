#include <iostream>
#include <algorithm>
#include <queue> 
#include <unordered_map>
using namespace std;
const int END = 123804765;

unordered_map <int, int> state; //状态为1表示q1扩展的，状态为2表示q2扩展的 如果出现两个状态相加为3说明找到路径 
unordered_map <int, int> ans;
queue <int> q1, q2; //q1从前搜，q2从后搜 
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int cnt, mat[3][3], zx, zy;

inline int toInt() { //将数字转为矩阵
	int now = 0;
	for(int i = 0; i < 3; i++) 
		for(int j = 0; j < 3; j++)
			now = now * 10 + mat[i][j];
	return now;
}
inline void toMatrix(int s) { //将矩阵转为数字
	int div = 100000000;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++) {
			mat[i][j] = (s / div) % 10;
			if(!mat[i][j]) zx = i, zy = j;
			div /= 10;
		}
	}
}

void dbfs(int s) {
	if(s == END) return; 
	bool flag;
	state[s] = 1, state[END] = 2;
	ans[s] = 0, ans[END] = 1; 
	q1.push(s), q2.push(END);
	while(!q1.empty() && !q2.empty()) {
		flag = false;
		int t;
		if(q1.size() > q2.size()) {
			t = q2.front(), q2.pop();
		}else {
			t = q1.front(), q1.pop();
			flag = true;
		}
		toMatrix(t);
		for(int i = 0; i < 4; i++) {
			int num;
			int nx = dx[i] + zx;
			int ny = dy[i] + zy;
			if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
				swap(mat[zx][zy], mat[nx][ny]);
				num = toInt();
				if(!ans.count(num)) {  //当前状态未被扩展过
					ans[num] = ans[t] + 1;
					state[num] = state[t]; //更新状态
					cout<<ans[t]<<" "<<ans[num]<<endl;
					if(flag) q1.push(num);
					else q2.push(num);
				}else if(state[t] + state[num] == 3){ //搜索范围重叠，出现答案 
					cnt = ans[t] + ans[num];
					return;
				}
				swap(mat[zx][zy], mat[nx][ny]);
			} 
		}
	}
}

int main() {
	int n;
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n;
	dbfs(n);	
	cout << cnt << endl;
	return 0;
} 


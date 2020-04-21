//无向图的邻接多重表
//广度优先搜索的实现
//求两个顶点之间一条路径长度最短的路径
#include <iostream>
#include <stack>
#include <list>
#include <queue>
using namespace std;
#define MAX_VERTEX_NUM 20
enum VisitIf {unvisited, visited};
VisitIf visit[MAX_VERTEX_NUM];
class EBox {
public:
	VisitIf mark; //访问标记
	int ivex, jvex; //该边依附的两个顶点位置
	EBox *ilink, *jlink; //分别指向依附这两个顶点的下一条边
};

class VexBox {
public:
	string data;
	EBox *firstedge; //指向第一条依附该顶点的边
};

class AMLGraph {
public:
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum; //无向图的当前顶点数和边数
};

struct Node {
	Node *next;
	Node *front;
	int data;
};

int LocateVex(VexBox adj[], int num, string v) {
	for (int i = 0; i < num; i++) {
		if (adj[i].data == v) {
			return i;
		}
	}
}

void CreateGraph(AMLGraph *G) {
	cout << "请输入顶点数和边数: " << endl;
	cin >> G->vexnum >> G->edgenum;
	cout << "请输入顶点: " << endl;
	for (int i = 0; i < G->vexnum; i++) {
		cin >> G->adjmulist[i].data;
		G->adjmulist[i].firstedge = NULL;
	}
	for (int i = 0; i < G->edgenum; i++) {
		cout << "请输入边的两个顶点: " << endl;
		string v1, v2;
		cin >> v1 >> v2;
		int i1 = LocateVex(G->adjmulist, G->vexnum, v1);
		int i2 = LocateVex(G->adjmulist, G->vexnum, v2);
		//cout << i1 << "...." << i2 << endl;
		EBox *p = new EBox;
		p->mark = unvisited;
		p->ivex = i1;
		p->jvex = i2;
		p->ilink = G->adjmulist[i1].firstedge;
		p->jlink = G->adjmulist[i2].firstedge;
		G->adjmulist[i1].firstedge = p;
		G->adjmulist[i2].firstedge = p;
	}
}

int FirstAdjVex(AMLGraph G, int v) {
	if (G.adjmulist[v].firstedge) {
		if (G.adjmulist[v].firstedge->ivex == v) {
			return G.adjmulist[v].firstedge->jvex;
		}
		else {
			return G.adjmulist[v].firstedge->ivex;
		}
	}
	else return -1;
}
//v是G中的某个顶点，w是v的邻接顶点
//返回v的(相对于w的)下一个邻接顶点。若w是v的最后一个邻接点，则返回空

int NextAdjVex(AMLGraph G, int v, int w) {
	EBox *p = G.adjmulist[v].firstedge;
	while (p) {
		if (p->ivex == v && p->jvex != w) p = p->ilink;
		else if (p->ivex != w && p->jvex == v) p = p->jlink;
		else break;
	}
	if (p && p->ivex == v && p->jvex == w) {
		p = p->ilink;
		if (p&&p->ivex == v) return p->jvex;
		else if (p&&p->jvex == v) return p->ivex;
	}
	if (p && p->ivex == w && p->jvex == v) {
		p = p->jlink;
		if (p&&p->ivex == v) return p->jvex;
		else if (p&&p->jvex == v) return p->ivex;
	}
	return -1;
}

void BFSTraverse(AMLGraph G) {
	queue<int> a;
	int cnt=0;
	for(int i = 0; i < G.vexnum; ++i) {
		visit[i] = unvisited;
	}
	for(int i = 0; i < G.vexnum; ++i) {
		if (visit[i] == unvisited) {
			cout << "连通图" <<++cnt<<":"<< endl;
			a.push(i);
			visit[i] = visited;
			cout << G.adjmulist[i].data << endl;
			while (!a.empty()) {
				int v = a.front();
				a.pop();
				for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
					if (visit[w] == unvisited) {
						a.push(w);
						cout << G.adjmulist[w].data << endl;
						visit[w] = visited;
					}
				}
			}
			cout<<endl;
		}
	}
}

int BFSPath(AMLGraph G, string v1, string v2) {
	if (v1 == v2) {
		cout << v1 << endl;
		return 0;
	}
	int i1 = LocateVex(G.adjmulist, G.vexnum, v1);
	int i2 = LocateVex(G.adjmulist, G.vexnum, v2);
	//int num = 0;
	Node *head;
	Node *rear;
	head = NULL;
	rear = NULL;
	for(int i = 0; i < G.vexnum; ++i) {
		visit[i] = unvisited;
	}
	visit[i1] = visited;
	Node *temp = new Node;
	temp->data = i1;
	temp->front = NULL;
	temp->next = NULL;
	head = rear = temp;
	stack<string> a;
	while (head) {
		int v = head->data;
		for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
			if (visit[w] == unvisited) {
				Node *temp0 = new Node;
				temp0->data = w;
				temp0->front = head;
				temp0->next = NULL;
				rear->next = temp0;
				rear = temp0;
				visit[w] = visited;
				if (rear->data == i2) {
					Node *p = rear;
					while(p) {
						a.push(G.adjmulist[p->data].data);
						p = p->front;
					}
					cout << a.top();
					a.pop();
					while (!a.empty()) {
						cout << "->" << a.top();
						a.pop();
					}
					cout << endl;
					return 1;
				}
			}
		}
		head = head->next;
	}
	cout << "There is no path" << endl;
	return 0;
}

void PrintGraph(AMLGraph G) {
    EBox *p;
    cout<<"打印出图中所有边"<<endl; 
    for(int i = 0; i < G.vexnum; ++i) {
        p = G.adjmulist[i].firstedge;
        while(p != NULL) {
            if(p->ivex == i) {   //判断相等才能知道连接上的是ivex还是jvex;
            	cout <<  G.adjmulist[p->ivex].data << "------" << G.adjmulist[p->jvex].data << endl;
                p = p->ilink;
            }
            else if(p->jvex == i){
               	cout <<  G.adjmulist[p->jvex].data << "------" << G.adjmulist[p->ivex].data << endl;
                p = p->jlink;
            }
        }
    }
    cout<<endl;
}
int main () {
	AMLGraph g;
	CreateGraph(&g);
	PrintGraph(g);
	BFSTraverse(g);
	int finish=0;
	while (!finish) {
		string v1, v2;
		cout << "请输入你想查询的两点: " << endl;
		cin >> v1 >> v2;
		BFSPath(g, v1, v2);
		cout<< "是否结束？是:1;否:0 "<<endl;
		cin>>finish;
	}
	return 0;
}


/** 邻接表广度优先遍历 **/
#include<iostream>
#include<cstdio>  
#include<cstdlib>
#include<cstring>
#define MaxVex 255 
#define TRUE 1
#define FALSE 0
using namespace std;
typedef string VertexType;  //顶点类型
typedef int Bool;
Bool visited[MaxVex];  //全局数组,记录图中节点访问状态
int pre[MaxVex];
typedef struct EdgeNode { //边表节点  
    int adjvex;    //该邻接点在顶点数组中的下标  
    struct EdgeNode *next;   //链域 指向下一个邻接点  
}EdgeNode;

typedef struct VertexNode { //头节点
   	VertexType data;  //顶点信息
    EdgeNode *firstedge;  //边表头指针(指向第一条依附于该顶点的弧的指针) 
}VertexNode,AdjList[MaxVex]; //顶点数组(结构体数组)   

typedef struct Graph{  
    AdjList adjList;  
    int numVertexes,numEdges;  //图中当前的结点数以及边数  
}Graph,*GraphAdjList;

int i1,i2;
/** 队列定义及相关操作(广度遍历会用到此循环队列) **/
typedef struct LoopQueue{ 
    int data[MaxVex];
    int front,rear;
}LoopQueue,*Queue; //队列结构

void initQueue(Queue Q){
    Q->front=Q->rear=0;
}

Bool QueueEmpty(Queue Q){
    if(Q->front == Q->rear){
        return TRUE;
    }else{
        return FALSE;
    }
}

Bool QueueFull(Queue Q){
    if((Q->rear+1)%MaxVex == Q->front){
        return TRUE;
    }else{
        return FALSE;
    }
}

/**
 * 队尾插入元素
 */
void EnQueue(Queue Q,int e){
    if(!QueueFull(Q)){
        Q->data[Q->rear] = e;
        Q->rear = (Q->rear+1)%MaxVex;
    }
}

/**
 * 队头删除元素
 */
void DeQueue(Queue Q,int *e){
    if(!QueueEmpty(Q)){
        *e = Q->data[Q->front];  
        Q->front = (Q->front+1)%MaxVex;
    }
}
/*************************************************/
/**
 * 建立图的邻接表结构(无向图)
 */
int LocateVex(AdjList adj, int num, string v) {
	for (int i = 0; i < num; i++) {
		if (adj[i].data == v) {
			return i;
		}
	}
}
void CreateALGraph(GraphAdjList G){
    int i, j, k;  
    printf("输入图的结点数以及边数: ");  
    //scanf("%d%d",&G->numVertexes,&G->numEdges);
	cin>>G->numVertexes>>G->numEdges;
    printf("===========================\n");
    printf("输入各个顶点的数据:\n");  
    for (i=0; i<G->numVertexes; ++i){  
        cin>>G->adjList[i].data;
        G->adjList[i].firstedge = NULL;   
    }
    
    printf("===========================\n");
    for (k=0; k<G->numEdges; ++k){
        printf("输入边的信息（两个顶点）: \n");
        //scanf("%d%d",&i,&j);
		string s1,s2;
		cin>>s1>>s2;
		i=LocateVex(G->adjList,G->numVertexes,s1);
		j=LocateVex(G->adjList,G->numVertexes,s2);
        EdgeNode *ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = j;
        ptrEdgeNode->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = ptrEdgeNode;

        ptrEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
        ptrEdgeNode->adjvex = i;
        ptrEdgeNode->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = ptrEdgeNode;
    }
}


void PrintPath(AdjList adj,int i){
	if(i!=i1)PrintPath(adj,pre[i]),cout<<"->"<<adj[i].data;
	else cout<<adj[i].data;
}

void BFSTraverse(GraphAdjList G,string s1,string s2){
	if (s1 == s2) {
		cout << s1 << endl;
		return ;
	}	 
    i1=LocateVex(G->adjList,G->numVertexes,s1);
	i2=LocateVex(G->adjList,G->numVertexes,s2);
    Queue Q = (Queue)malloc(sizeof(LoopQueue));  
	memset(pre,0,sizeof(pre));
    for (int i=0; i<G->numVertexes; ++i){  
        visited[i] = FALSE; 
    } 
    initQueue(Q);  
   
    visited[i1] = TRUE;   
    EnQueue(Q, i1);  
	int j;
    while (!QueueEmpty(Q)){
    	DeQueue(Q, &j);  
        EdgeNode *p = G->adjList[j].firstedge;
        while (p){  
            if (!visited[p->adjvex]){
            	if(p->adjvex==i2){
            		pre[i2]=j;
					PrintPath(G->adjList,i2);
					printf("\n");
					return;
				} 
                visited[p->adjvex] = TRUE;  
            	EnQueue(Q, p->adjvex); 
            	pre[p->adjvex]=j;
            }  
            p = p->next;  
    	}
	}  
    cout << "There is no path" << endl;
    return ;
}



/**
 * 程序入口
 */
int main(){
    Graph G;  
    CreateALGraph(&G);
    int finish=0;
	while (!finish) {
		string v1, v2;
		cout << "请输入你想查询的两点: " << endl;
		cin >> v1 >> v2;
		BFSTraverse(&G, v1, v2);
		cout<< "是否结束？是:1;否:0 "<<endl;
		cin>>finish;
	}
    return 0;
}

/** �ڽӱ������ȱ��� **/
#include<iostream>
#include<cstdio>  
#include<cstdlib>
#include<cstring>
#define MaxVex 255 
#define TRUE 1
#define FALSE 0
using namespace std;
typedef string VertexType;  //��������
typedef int Bool;
Bool visited[MaxVex];  //ȫ������,��¼ͼ�нڵ����״̬
int pre[MaxVex];
typedef struct EdgeNode { //�߱�ڵ�  
    int adjvex;    //���ڽӵ��ڶ��������е��±�  
    struct EdgeNode *next;   //���� ָ����һ���ڽӵ�  
}EdgeNode;

typedef struct VertexNode { //ͷ�ڵ�
   	VertexType data;  //������Ϣ
    EdgeNode *firstedge;  //�߱�ͷָ��(ָ���һ�������ڸö���Ļ���ָ��) 
}VertexNode,AdjList[MaxVex]; //��������(�ṹ������)   

typedef struct Graph{  
    AdjList adjList;  
    int numVertexes,numEdges;  //ͼ�е�ǰ�Ľ�����Լ�����  
}Graph,*GraphAdjList;

int i1,i2;
/** ���ж��弰��ز���(��ȱ������õ���ѭ������) **/
typedef struct LoopQueue{ 
    int data[MaxVex];
    int front,rear;
}LoopQueue,*Queue; //���нṹ

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
 * ��β����Ԫ��
 */
void EnQueue(Queue Q,int e){
    if(!QueueFull(Q)){
        Q->data[Q->rear] = e;
        Q->rear = (Q->rear+1)%MaxVex;
    }
}

/**
 * ��ͷɾ��Ԫ��
 */
void DeQueue(Queue Q,int *e){
    if(!QueueEmpty(Q)){
        *e = Q->data[Q->front];  
        Q->front = (Q->front+1)%MaxVex;
    }
}
/*************************************************/
/**
 * ����ͼ���ڽӱ�ṹ(����ͼ)
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
    printf("����ͼ�Ľ�����Լ�����: ");  
    //scanf("%d%d",&G->numVertexes,&G->numEdges);
	cin>>G->numVertexes>>G->numEdges;
    printf("===========================\n");
    printf("����������������:\n");  
    for (i=0; i<G->numVertexes; ++i){  
        cin>>G->adjList[i].data;
        G->adjList[i].firstedge = NULL;   
    }
    
    printf("===========================\n");
    for (k=0; k<G->numEdges; ++k){
        printf("����ߵ���Ϣ���������㣩: \n");
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
 * �������
 */
int main(){
    Graph G;  
    CreateALGraph(&G);
    int finish=0;
	while (!finish) {
		string v1, v2;
		cout << "�����������ѯ������: " << endl;
		cin >> v1 >> v2;
		BFSTraverse(&G, v1, v2);
		cout<< "�Ƿ��������:1;��:0 "<<endl;
		cin>>finish;
	}
    return 0;
}

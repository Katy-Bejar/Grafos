#include <iostream>
#include <stdlib.h>
#define MVNum 100
using namespace std;

typedef struct ArcNode{
    int vertAd;          
    struct ArcNode* sigPos; 
}ArcNode;

typedef struct VNode{
    char data;
    ArcNode* firstarc; 
}VNode, AdjList[MVNum];

typedef struct{
    AdjList vertices;
    int vexnum;
    int arcnum;
}ALGraph;

typedef struct QNode{
    int data;
    struct QNode* next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int LocateVex(ALGraph& G, char NodeInfo)
{
    int flag = 0;
    for (int i = 0; i < G.vexnum; i++){
        if (G.vertices[i].data == NodeInfo){
            flag = i;
            return i;
            break;
        }
    }
    if (flag)
        return flag;
    else
        exit(errno);
}

void CreateUDG(ALGraph& G)
{
    cout << " Ingrese el número correspondiente de vértices y aristas (separados por espacios): "  << endl;
    cin >> G.vexnum >> G.arcnum;

    cout << G.vexnum << " Ingresar del vértice (separada por espacios): "<< endl;
    for (int i = 0; i < G.vexnum; i++){
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
    }

    for (int i = 0; i < G.arcnum; i++){
        char v1, v2; 
        cout <<" Por favor ingrese la información de los dos vértices del borde (separados por espacios): "  << i ;
        cin >> v1 >> v2;

        int idx_v1 = LocateVex(G, v1);
        int idx_v2 = LocateVex(G, v2);

        ArcNode* p1 = new ArcNode; 
        p1->vertAd = idx_v2; 
        p1->sigPos = G.vertices[idx_v1].firstarc;
        G.vertices[idx_v1].firstarc = p1;

        ArcNode* p2 = new ArcNode;
        p2->vertAd = idx_v1; 
        p2->sigPos = G.vertices[idx_v2].firstarc;
        G.vertices[idx_v2].firstarc = p2;
    }
}

void TraverseAdjList(ALGraph& G)
{
    for (int i = 0; i < G.vexnum; i++){
        cout << "【" << G.vertices[i].data << "】→";
        ArcNode* tmp = G.vertices[i].firstarc;

        while (tmp){
            cout<<"["<<tmp->vertAd<<"]";
            tmp=tmp->sigPos;
            if (tmp)
                cout << "→";
        }
        putchar(10);
    }
}

int visisted_D[MVNum] = { 0 }; 
void DFS_AL(ALGraph& G, int v)
{
    cout <<"("<< G.vertices[v].data <<")";
    visisted_D[v] = 1;
    ArcNode *tmp = G.vertices[v].firstarc;

    while (tmp){
        int w = tmp->vertAd;
        if (visisted_D[w] == 0){
            DFS_AL(G, w);
        }
        tmp = tmp->sigPos;
    }
}

int visisted_B[MVNum] = { 0 }; 

void InitQuenue(LinkQueue& Q)
{
    Q.rear = new QNode;
    Q.front = Q.rear;
    Q.front->next = nullptr;
}

void EnQuenue(LinkQueue& Q,int v)
{
    QNode* cur = new QNode;
    cur->data = v;
    cur->next = nullptr;
    Q.rear->next = cur;
    Q.rear = cur;
}

void DeQuenue(LinkQueue& Q, int &u)
{
    QNode* tmp = Q.front->next;
    Q.front->next = tmp->next;
    u = tmp->data;
    if (Q.rear == tmp){
        Q.rear = Q.front;
    }
    delete tmp;
}

int PrimerVert(ALGraph& G, int u)
{
    int w = G.vertices[u].firstarc->vertAd;
    return w;
}

int SigVert(ALGraph& G, int u, int w)
{
    ArcNode *tmp = G.vertices[u].firstarc;
    while (tmp->vertAd != w){
        tmp = tmp->sigPos;
    }
    if (tmp->sigPos)
        return tmp->sigPos->vertAd;
    else 
        return -1;
    delete tmp;
}
void BFS_AL(ALGraph& G, int v)
{
    cout << "(" << G.vertices[v].data << ")";
    visisted_B[v] = 1;
    LinkQueue Q;
    InitQuenue(Q);
    EnQuenue(Q,v);
    int u = v; 
    while (Q.rear != Q.front){
        DeQuenue(Q, u);
        for (int w = PrimerVert(G, u); w >= 0; w = SigVert(G, u, w)){
            if (!visisted_B[w]){
                cout << "(" << G.vertices[w].data << ")";
                visisted_B[w] = 1;
                EnQuenue(Q, w);
            }
        }
    }
}

int main(){
    ALGraph G;

    CreateUDG(G); 
    TraverseAdjList(G);
    cout << " Qué vértice inicia el recorrido en profundidad primero: ";
    int v;
    cin >> v;
    cout << "DFS：";
    DFS_AL(G, v-1);
    putchar(10);
    cout << " ¿Qué vértice es el recorrido primero en amplitud: " ;
    cin >> v;
    cout << "BFS：";
    BFS_AL(G, v - 1);
    putchar(10);
}
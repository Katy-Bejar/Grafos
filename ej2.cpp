#include <iostream>

using namespace std;

struct Node{
    int index;
    string value;
    Node* next;
};


struct Edge{
    int startIndex;
    int endIndex;
};


class DirectedGraph
{
public:
    Node** headNode;

    Node* insertNewNode(int index, string value, Node* node)
    {
        Node* newNode = new Node;
        newNode->index = index;
        newNode->value = value;
        newNode->next = node;
        return newNode;
    }

    DirectedGraph(Node nodes[], Edge edges[], int numberOfEdges, int numberOfNodes)
    {
        headNode = new Node*[numberOfNodes]();
        for (int i = 0; i < numberOfEdges; i++){
            int startIndex = edges[i].startIndex;
            int endIndex = edges[i].endIndex;
            string value = nodes[endIndex].value;
            Node* newNode = insertNewNode(endIndex, value, headNode[startIndex]);
            headNode[startIndex] = newNode;
        }
    }
};


void writeAdjacencyList(Node* node, int i)
{
    cout << "Nodo " << (i + 1) << ": ";
    while (node != nullptr)
    {
        cout << "(" << node->index << ", " << node->value << ") ";
        node = node->next;
    }
    cout << endl;
}


int main()
{

    Node nodes[] = { {0,"A"}, {1,"B"}, {2,"C"}, {3,"D"}, {4,"E"},{5,"F"} ,{6,"G"} ,{7,"H"} ,{8,"I"}  };
    Edge edges[] = { {0,1},{0,2},{1,4},{2,3},{3,1},{4,3},{5,3},{6,2},{1,7},{4,8},{6,8} };
    int numberOfNodes = sizeof(nodes); 
    int numberOfEdges = sizeof(edges) / sizeof(edges[0]); 
    DirectedGraph directedGraph(nodes, edges, numberOfEdges, numberOfNodes); 
    for (int i = 0; i < numberOfNodes; i++){
        Node* headNode = directedGraph.headNode[i];
        writeAdjacencyList(headNode, i);
    }
}
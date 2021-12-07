#include <iostream>
#include <list>
#include <ostream>
using namespace std;
 
template<class V,class E>
class Vertex;

template<class V,class E>
class Edge
{
    public:
        E                   m_Dato;
        Vertex<V,E> *       m_pVertes;
    public:
        Edge(E d,  Vertex<V,E> * p=0)
        {
           m_Dato = d;
           m_pVertes =p;
        }
        Edge(){};  
};

template<class V,class E>
class Vertex
{
    public:
        V                   m_Dato;
        list< Edge <V,E> >  m_Aristas;
    public:
        Vertex(V d)
        {
           m_Dato = d;
        }
        Vertex(){};  
};


template<class V, class E>
class Grafo
{
    private:
        list<Vertex<V,E>> m_grafo;
    public:
        Grafo(){};
        Vertex<V,E> *  find_Vertex(V v)
        {
            Vertex<V,E> * p;
            
            return p;
        }

        void Insert_Vertex(V dato)
        {
              m_grafo.push_back(Vertex<V,E>(dato));
        }

        void Insert_Arista(V v1, V v2, E Ar)
        {
               Vertex<V,E> * p = find_Vertex(v1);
               Vertex<V,E> * q = find_Vertex(v2);
               
               if( p && q)
                   p->m_Aristas.push_back(Edge<V,E>(Ar,q));
               
        }
        void Floyd(int* M[], int n)
        {
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    for(int k = 0; k < n; k++){
                        if(M[i][j] || (M[i][j] && M[k][j])){
                            M[i][j] = 1;
                        }
                    }
                }
            }
        }
        void Warshall(int* M[], int n)
        {
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    for(int k = 0; k < n; k++){
                        M[i][j] = min(M[i][j] || (M[i][j] && M[k][j]));
                    }
                }
            }
        }    
};
 

int main()
{
    Grafo<string, int> G;
    Insert_Vertex("Arequipa");
    Insert_Vertex("Lima");
    Insert_Vertex("Cuzco");
    Insert_Vertex("Puno");
    Insert_Vertex("Ica");

    Insert_Arista("Arequipa","Cuzco",250);
    Insert_Arista("Arequipa","Puno",200);
    G.Insert_Arista("Lima","Ica",100);
    G.Insert_Arista("Lima","Arequipa",160);
    return 1;
}
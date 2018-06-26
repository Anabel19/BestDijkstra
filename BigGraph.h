#ifndef BIGGRAPH_H
#define BIGGRAPH_H

#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include <QPoint>
#include "grapho.h"

using namespace std;

class CBigGraph : public CGraph<QPointF, int> {
public:
    //void receiveNodes(int&, string);
    //void receiveEdges(int&, string);

    void receiveNodes(int );
    void receiveEdges(int , int numero = 2);

    bool dijkstra(Node* inicio, Node* final, list<Node*> &ruta);
//    CityGraph(){
//    }

//    ~CityGraph(){

//    }
};

//DIJKSTRA

extern CBigGraph::Node* FINAL;
extern CBigGraph::Node* ACTUAL;
//-------------------
/*
inline void CBigGraph::receiveNodes(int& i, string line){
    vector<int> x;
    vector<int> y;

    int space=line.find(' ');
    x.push_back(stoi(line.substr(0,space)));
    y.push_back(stoi(line.substr(space)));

    for(uint i=0; i < y.size(); i++){
        InsNode(QPoint(x[i],y[i]));
    }
    i++;
}


inline void CBigGraph::receiveEdges(int& i, string line){
    int dist;

    auto distanciaCuad = [](Node *a, Node *b) {
        return pow(a->value.x() - b->value.x(), 2) +
               pow(a->value.y() - b->value.y(), 2);
    };
    int space=line.find(' ');
    int ini= stoi(line.substr(0,space));
    int fin= stoi(line.substr(space));
        dist= distanciaCuad(mnodes[ini], mnodes[fin]);
        InsEdge(mnodes[ini], mnodes[fin], dist,0);
}
*/
inline void CBigGraph::receiveNodes(int numero){
    vector<int> xs;
    vector<int> ys;
    srand(unsigned(time(0)));


    for(int i= 0; i < numero; i++){
        int rndm = rand()% 20 ;
        for(int j = 0; j < rndm; j++)
            xs.push_back(i);
        ys.push_back(i);
    }

    auto randomFun =[] (int i) { return rand()%i;};
    random_shuffle(xs.begin(), xs.end(), randomFun);
    random_shuffle(ys.begin(), ys.end(), randomFun);

    for(uint i=0; i < ys.size(); i++){
        InsNode(QPoint(xs[i],ys[i]));
    }
}

inline void CBigGraph::receiveEdges(int radio, int numero){
    int contador = 0;
    int dist;

    auto distanciaCuad = [](Node *a, Node *b) {
        return pow(a->value.x() - b->value.x(), 2) +
               pow(a->value.y() - b->value.y(), 2);
    };

    for (uint i = 0; i < mnodes.size(); i++) {
        contador = 0;
        for (uint j = 0; (contador <= numero) && (j < mnodes.size()); j++) {
            if (i != j){
                dist = distanciaCuad(mnodes[i], mnodes[j]);
                if (dist <= radio) {
                    InsEdge(mnodes[i], mnodes[j], dist, 0);// PONER EL 0 EN RANDOM!!
                    contador++;
                }
            }
        }
    }
}

//DIJKSTRA

inline int distancia(CBigGraph::Node* a , CBigGraph::Node* b) {
    return pow(a->value.x() - b->value.x(), 2) + pow(a->value.y() - b->value.y(), 2);
}



inline bool MenorDestino(CBigGraph::Edge* &a, CBigGraph::Edge * &b) {
    //Rutina necesaria para sort de lista de Edge* Menor distancia euclid a nodo destino
    int dist_a, dist_b;

    CBigGraph::Node* nodo_a = (a->enodo[0] != ACTUAL) ? a->enodo[0] : a->enodo[1];
    CBigGraph::Node* nodo_b = (b->enodo[0] != ACTUAL) ? b->enodo[0] : b->enodo[1];

    dist_a = distancia(nodo_a, FINAL);
    dist_b = distancia(nodo_b, FINAL);

    if (dist_a < dist_b) {
        return true;
    }
    return false;
}

inline bool CBigGraph::dijkstra(Node* A, Node* B, list<Node*> &ruta) {
    Node* actual = A;
    //list<Node*> ruta;
    ruta.push_back(A);
    FINAL = B;

    int i = 0; //iteracion de busqueda
               //inicio->d_visitado = true;
    A->d_dist = 0;

    while (actual != B) {
        ACTUAL = actual;
        if (!actual->d_visitado) {
            actual->d_visitado = true;
            actual->EdgeNod.sort(MenorDestino);
            //actual->edges.sort();
        }
        //list<Edge*> busqueda; // busqueda de la menor arista no usada
        Node* next = nullptr; //siguiente nodo en la ruta
        list<Edge*>::iterator it = actual->EdgeNod.begin();

        while (it != actual->EdgeNod.end()) {
            if (!(*it)->utilizado) {
                //actualizar distancia a origen
                Node* check = ((*it)->enodo[0] != actual) ? (*it)->enodo[0] : (*it)->enodo[1];
                if (!check->d_visitado) {
                    if (!next) {// next es nullpointer aun no asignado
                        next = check;
                    }
                    if (check->d_dist < 0 || check->d_dist > actual->d_dist + (*it)->value) {
                        check->d_dist = actual->d_dist + (*it)->value;
                        check->nodo_ant = actual;
                    }

                }
                cout << "";
            }
            it++;
        }
        if (next)
        {
            actual = next;
            ruta.push_back(actual);
            //i++;// TODO si no existe next debemos corregir la ruta
        }
        else
        {
            if (ruta.size() > 1)
            {
                ruta.pop_back();
                actual = ruta.back();
                //i++;
            }
            else
            {
                return false;
            }
        }
        //i++;
    }

    return true;
}

#endif //BIGGRAPH_H

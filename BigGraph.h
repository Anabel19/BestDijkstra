#ifndef CITYGRAPH_H
#define CITYGRAPH_H

#include "graph.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <QPoint>
using namespace std;


class CityGraph : public Graph<QPointF, int> {
public:
    void generadorNodos(int numero);
    void generadorNodesCuad(int numero);
    void generadorEdges(int radio, int numero = 2);
    void borrarNodes(int x1, int y1, int x2, int y2);
    void borrarNodes(QPoint *top, QPoint *bot);

    //bool dijkstra(Node * inicio, Node * final, vector<Node*> &ruta);
    bool dijkstra(Node* inicio, Node* final, list<Node*> &ruta);
//    CityGraph(){
//    }

//    ~CityGraph(){

//    }
};

//DIJKSTRA

extern CityGraph::Node* FINAL;
extern CityGraph::Node* ACTUAL;
//-------------------

inline void CityGraph::generadorNodos(int numero){
    vector<int> xs;
    vector<int> ys;
    srand(unsigned(time(0)));


    for(int i= 0; i < numero; i++){
        int rndm = rand()% 5 ;
        for(int j = 0; j < rndm; j++)
            xs.push_back(i);
        ys.push_back(i);
    }

    auto randomFun =[] (int i) { return rand()%i;};
    random_shuffle(xs.begin(), xs.end(), randomFun);
    random_shuffle(ys.begin(), ys.end(), randomFun);

    for(uint i=0; i < ys.size(); i++){
        insNode(QPoint(xs[i],ys[i]));
    }
}

inline void CityGraph::generadorNodesCuad(int numero){
    for(int i = 5; i < numero*5; i+=5){
        for(int j = 5; j < numero*5; j+=5){
            insNode(QPoint(i,j));
        }
    }
}


inline void CityGraph::generadorEdges(int radio, int numero){
    int contador = 0;
    int dist;

    auto distanciaCuad = [](Node *a, Node *b) {
        return pow(a->data.x() - b->data.x(), 2) +
               pow(a->data.y() - b->data.y(), 2);
    };

    for (uint i = 0; i < nodes.size(); i++) {
        contador = 0;
        for (uint j = 0; (contador <= numero) and (j < nodes.size()); j++) {
            if (i != j){
                dist = distanciaCuad(nodes[i], nodes[j]);
                if (dist <= radio) {
                    insEdge(nodes[i], nodes[j], dist, 0);// PONER EL 0 EN RANDOM!!
                    contador++;
                }
            }
        }
    }
}

inline void CityGraph::borrarNodes(int x1, int y1, int x2, int y2){
    for(vecIt it = nodes.begin(); it != nodes.end();){
        if((*it)->data.x() >= x1 and (*it)->data.x() <= x2 and
           (*it)->data.y() >= y1 and (*it)->data.y() <= y2){
            remNode(it);
        }
        else it++;
    }

}

inline void CityGraph::borrarNodes(QPoint *top, QPoint *bot){
    int x1, y1, x2, y2;
    if(top->x() <= bot->x()){
        x1 = top->x();
        x2 = bot->x();
    }
    else {
        x1 = bot->x();
        x2 = top->x();
        //Para imprimir correctamente el rectángulo:
        top->setX(x1);
        bot->setX(x2);
    }
    if(top->y() <= bot->y()){
        y1 = top->y();
        y2 = bot->y();
    }
    else {
        y1 = bot->y();
        y2 = top->y();
        //Para imprimir correctamente el rectángulo:
        top->setY(y1);
        bot->setY(y2);
    }

    for(vecIt it = nodes.begin(); it != nodes.end();){
        if((*it)->data.x() >= x1 and (*it)->data.x() <= x2 and
           (*it)->data.y() >= y1 and (*it)->data.y() <= y2){
            remNode(it);
        }
        else it++;
    }

}

//inline void CityGraph::dijkstra(Node *inicio, Node *final, vector<Node*> &ruta){

//}

//DIJKSTRA

inline int distancia(CityGraph::Node* a , CityGraph::Node* b) {
    return pow(a->data.x() - b->data.x(), 2) + pow(a->data.y() - b->data.y(), 2);
}


inline bool Menor(CityGraph::Edge* &a, CityGraph::Edge * &b) {
    //Rutina necesaria para sort de lista de Edge*
    if (a->data < b->data) {
        return true;
    }
    return false;
}

inline bool MenorDestino(CityGraph::Edge* &a, CityGraph::Edge * &b) {
    //Rutina necesaria para sort de lista de Edge* Menor distancia euclid a nodo destino
    int dist_a, dist_b;

    CityGraph::Node* nodo_a = (a->nodes[0] != ACTUAL) ? a->nodes[0] : a->nodes[1];
    CityGraph::Node* nodo_b = (b->nodes[0] != ACTUAL) ? b->nodes[0] : b->nodes[1];

    dist_a = distancia(nodo_a, FINAL);
    dist_b = distancia(nodo_b, FINAL);

    if (dist_a < dist_b) {
        return true;
    }
    return false;
}

inline bool CityGraph::dijkstra(Node* inicio, Node* final, list<Node*> &ruta) {
    Node* actual = inicio;
    //list<Node*> ruta;
    ruta.push_back(inicio);
    FINAL = final;

    int i = 0; //iteracion de busqueda
               //inicio->d_visitado = true;
    inicio->d_dist = 0;

    while (actual != final) {
        ACTUAL = actual;
        if (!actual->d_visitado) {
            actual->d_visitado = true;
            actual->edges.sort(MenorDestino);
            //actual->edges.sort();
        }
        //list<Edge*> busqueda; // busqueda de la menor arista no usada
        Node* next = nullptr; //siguiente nodo en la ruta
        list<Edge*>::iterator it = actual->edges.begin();

        while (it != actual->edges.end()) {
            if (!(*it)->utilizado) {
                //actualizar distancia a origen
                Node* check = ((*it)->nodes[0] != actual) ? (*it)->nodes[0] : (*it)->nodes[1];
                if (!check->d_visitado) {
                    if (!next) {// next es nullpointer aun no asignado
                        next = check;
                    }
                    if (check->d_dist < 0 || check->d_dist > actual->d_dist + (*it)->data) {
                        check->d_dist = actual->d_dist + (*it)->data;
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

#endif //CITYGRAPH_H
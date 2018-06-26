#ifndef GRAPHSHOW_H
#define GRAPHSHOW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <iostream>
#include "BigGraph.h"
#include "drawnode.h"
#include <QDebug>

class CGraphShow: public QGraphicsView{
    Q_OBJECT
    public:
    CBigGraph * graph;
    QGraphicsScene *scene;
    QPoint * delete1;
    QPoint * delete2;
    DrawNode * fnode; //start node
    DrawNode * enode; //end node

    CGraphShow (QWidget *parent): QGraphicsView(parent)  {
        setGeometry(10,0,parent->width(),parent->height());
        scene = new QGraphicsScene(this);
        setScene(scene);
        graph = nullptr;
        delete1 = delete2 = nullptr;
        fnode = enode = nullptr;

    }
    /*
    void generateGraph(){
        if(!graph) delete graph;
        graph = new CBigGraph;

        //ifstream finput;
        string line;
        int num;
        QFile finput("graphics/nodes_20_graph_3.dat");
        finput.open(QIODevice::ReadOnly);
        int i=0;
        while(!finput.eof()){
            getline(finput, line);
            qDebug() << "--"<<line;
            if((strstr(line.c_str(),"POINTS")) || (strstr(line.c_str(),"EDGES")))
                if(strstr(line.c_str(),"POINTS")){ num=stoi(line.substr(6));}
            else{
                if(i<num){
                    graph->receiveNodes(i, line);}
                else graph->receiveEdges(i, line);
            }

        }
        finput.close();

    }

*/
    void generateGraph(){
        if(!graph) delete graph;
        graph = new CBigGraph;

        int numNodes = 500;
        int radioEdges = 4*numNodes;


        graph->receiveNodes(numNodes);
        graph->receiveEdges(radioEdges);
        qDebug() << "insercion terminada";
    }

    bool printGraph(){
        if(!graph) return 0;
        QPen pen(Qt::black, 1);

        for (uint i = 0; i < graph->mnodes.size(); i++){
            auto it = graph->mnodes[i]->EdgeNod.begin();
            for(uint j = 0; j < graph->mnodes[i]->EdgeNod.size(); j++){
                scene->addLine(QLine((*it)->enodo[0]->value.toPoint(),(*it)->enodo[1]->value.toPoint()),pen);
                it++;
            }
        }

        for (uint i = 0; i < graph->mnodes.size(); i++){
            DrawNode* tmp = new DrawNode(graph->mnodes[i]);
            scene->addItem(tmp);
        }
        return 1;
    }

    void mousePressEvent(QMouseEvent *event){
        QPointF mousePoint = mapToScene(event->pos());
        QGraphicsItem* ptr = itemAt(mousePoint.toPoint());
        if(ptr) qDebug() << "PTR" << ptr ;
        DrawNode* pp = dynamic_cast<DrawNode*>(ptr);

        if(event->button()== Qt::LeftButton){
            if(pp){
                qDebug() << "XY NODO: "<<pp->point.x() << ", " << pp->point.y();
                qDebug() << "PTR NODO:" << pp->realNode;
                if(!fnode){
                    fnode = pp;
                }
                else{
                        enode = pp;

                        list<CBigGraph::Node*> ruta;
                        graph->dijkstra(fnode->realNode,enode->realNode, ruta);

                        scene->clear();

                        printGraph();
                        drawRoute(ruta);
                        update();

                        fnode = enode = nullptr;
                    }
            }
        }
    }

    //DIJKSTRA
    void drawRoute(list<CBigGraph:: Node*> rout){
        if(rout.empty()) return;
        list<CBigGraph::Node*>::iterator it, itt;
        it=itt=rout.begin();
        QPen pencil(Qt::green, 2);
        for(itt++; itt!= rout.end();itt++){
            scene->addLine((*it)->value.x(), (*it)->value.y(),(*itt)->value.x(), (*itt)->value.y(), pencil);
            it=itt;
        }

    }
};

#endif // GRAPHSHOW_H

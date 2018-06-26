#ifndef GRAPHO_H
#define GRAPHO_H
#include<list>
#include<vector>

using namespace std;
template<class G>
class CNode
{
	public:
    typedef class G::Edge Edge;//typename because is a dependent scope
	typedef typename G::n_ N;
	//typedef class G::Node N;
	N value;
	list<Edge*> EdgeNod;
	
	CNode(N date){
		this->value=date;
	}
	
	void RemEdgeN(CNode <G> *tmp){
        for (typename list<Edge*>::iterator it= EdgeNod.begin(); it != EdgeNod.end(); it++){//lista de aristas del nodo inicio
			for (typename list<Edge*>::iterator itt= tmp->EdgeNod.begin(); itt != tmp->EdgeNod.end(); itt++){//lista de aristas del nodo fin	
				if(*it == *itt){cout<<"here"<<*it<<*itt<<endl;
					 EdgeNod.remove(*it);
					 tmp->EdgeNod.remove(*itt);
					 
					 delete *it;
					return;
				}
			}	
		}
    }
	
	void RemEdges(){
        Edge *tmp;
        while(!EdgeNod.empty()){
            tmp = EdgeNod.front();
            ((tmp->enodo[0])->EdgeNod).remove(tmp);
            ((tmp->enodo[1])->EdgeNod).remove(tmp);
            delete tmp;
        }
    }
	~CNode(){};
};

template<class G>
class CEdge
{
	public:
	typedef typename G::Node Node;
	typedef typename G::e_ E;
	//typedef typename G::Edge E;
	E value;
	Node *enodo[2]; //Node extremos
	bool mdir; //0[bidireccional] 1[unidireccional]
	CEdge(E date, bool dir){
		this->value=date;
		this->mdir=dir;
		enodo[0]=enodo[1]=nullptr;
	}
	~CEdge(){};
};

//template<class T, class C>
template<class N, class E>
class CGraph
{
	public:
	typedef CGraph<N,E>  self;
	typedef CNode<self>  Node;
	typedef CEdge<self>  Edge;
	typedef N n_;
	typedef E e_;
	vector<Node*> mnodes;
	
	//para no repetir código
	bool findN(N d, unsigned &id){
		for(id=0;id < mnodes.size();id++){
			if(mnodes[id]->value==d)  return 1;
		}			
		return 0;
	}
	
	bool InsNode(N date){
		Node* new_node= new Node(date);
		mnodes.push_back(new_node);
		//prob necesitamos ya ir calculando cant de node
		return 1;	
	}

	bool InsEdge(N a, N b, E dato, bool dir){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) return 0;			
			Edge* new_edge= new Edge(dato,dir);
			mnodes[ia]->EdgeNod.push_back(new_edge);
			mnodes[ib]->EdgeNod.push_back(new_edge);
			new_edge->enodo[0]= mnodes[ia]; 	new_edge->enodo[1]= mnodes[ib];
		//prob necesitamos ya ir calculando cant de edges
		return 1;
	}

	bool RemEdge(N a, N b){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) {cout<<"no hay nodos[extremos]"<<endl; return 0;}
		mnodes[ia]->RemEdgeN(mnodes[ib]);
		return 1;
	}
	
	bool RemNode(N date){
		unsigned idate;
		if(!findN(date,idate)) return 0;
		
		mnodes[idate]->RemEdges();
		delete mnodes[idate];
		mnodes->erase(mnodes.begin()+idate);
		//mnodes.erase(mnodes.begin()+idate);
		return 1;
	}
	
	void printGraph(){
		for(int i=0; i<mnodes.size(); i++) {//ingreso al vector de nodos del grafo
			Node *temp_node = mnodes[i]; // cada nodo
			cout<<temp_node->value;// etiqueta-valor de cada nodo

			for (typename list<Edge*>::iterator it= temp_node->EdgeNod.begin(); it != temp_node->EdgeNod.end(); ++it){
				//recorrer la lista de punteros a aristas del nodo
				if(temp_node->value != (*it)->enodo[1]->value){
					cout<<" ---> "<< (*it)->value<<"("<<((*it)->enodo[1])->value<<")";
					cout<<endl;
				}
			}
			cout<<"\n";
		}
	}

};
#endif //GRAPHO_H

/*
#ifndef GRAPHO_H
#define GRAPHO_H
#include<list>
#include<vector>

using namespace std;
template<class G>
class Node
{
	public:
    typedef class G::Edge Edge;//typename because is a dependent scope
	typedef typename G::n_ N;
	//typedef class G::Node N;
	N value;
	list<Edge*> EdgeNod;
	
	Node(N date){
		this->value=date;
	}
	
	void RemEdges(){
        Edge *tmp;
        while(!EdgeNod.empty()){
            tmp = EdgeNod.front();
            ((tmp->enodo[0])->EdgeNod).remove(tmp);
            ((tmp->enodo[1])->EdgeNod).remove(tmp);
            delete tmp;
        }
    }
	~Node(){};
};

template<class G>
class Edge
{
	public:
	typedef typename G::Node Node;
	typedef typename G::e_ E;
	//typedef typename G::Edge E;
	E value;
	Node *enodo[2]; //Node extremos
	bool mdir; //0[bidireccional] 1[unidireccional]
	Edge(E date, bool dir){
		this->value=date;
		this->mdir=dir;
		enodo[0]=enodo[1]=nullptr;
	}
	~Edge(){};
};

//template<class T, class C>
template<class N, class E>
class CGraph
{
	public:
	typedef CGraph<N,E>  self;
	typedef Node<self>  Node;
	typedef Edge<self>  Edge;
	typedef N n_;
	typedef E e_;
	vector<Node*> mnodes;
	
	//para no repetir código
	bool findN(N d, unsigned &id){
		for(id=0;id < mnodes.size();id++){
			if(mnodes[id]->value==d)  return 1;
		}			
		return 0;
	}
	
	bool InsNode(N date){
		Node* new_node= new Node(date);
		mnodes.push_back(new_node);
		//prob necesitamos ya ir calculando cant de node
		return 1;	
	}

	bool InsEdge(N a, N b, E dato, bool dir){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) return 0;			
			Edge* new_edge= new Edge(dato,dir);
			mnodes[ia]->EdgeNod.push_back(new_edge);
			mnodes[ib]->EdgeNod.push_back(new_edge);
			new_edge->enodo[0]= mnodes[ia]; 	new_edge->enodo[1]= mnodes[ib];
		//prob necesitamos ya ir calculando cant de edges
		return 1;
	}

	bool RemEdge(N a, N b, E dato){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) {cout<<"no hay nodos[extremos]"<<endl; return 0;}
		
		for (typename list<Edge*>::iterator it=mnodes[ia]->EdgeNod.begin(); it != mnodes[ia]->EdgeNod.end(); ++it){
			 if((*it)->enodo[1] == mnodes[ib]){ cout<<"ent"<<(*it)->enodo[1]->value<<"  "<<mnodes[ib]->value<<endl;
			     mnodes[ia]->EdgeNod.erase(it);
				 delete *it;}
				//mnodes[ia]->EdgeNod.remove(*it);
			
		}
	
		for(typename list<Edge*>::iterator it=mnodes[ib]->EdgeNod.begin(); it != mnodes[ib]->EdgeNod.end(); ++it){
			if((*it)->enodo[0] == mnodes[ia]){
				mnodes[ib]->EdgeNod.erase(it);
				delete *it;}
				
				//mnodes[ib]->EdgeNod.remove(*it);
		} 
		//Edge *delette;
		return 1;
	}
	
	bool RemNode(N date){
		unsigned idate;
		if(!findN(date,idate)) return false;
		
		mnodes[idate]->RemEdges();
		delete mnodes[idate];
		mnodes->erase(mnodes.begin()+idate);
		//mnodes.erase(mnodes.begin()+idate);
		return 1;
	}
	void printGraph(){
		for(int i=0; i<mnodes.size(); i++) {//ingreso al vector de nodos del grafo
			Node *temp_node = mnodes[i]; // cada nodo
			cout<<temp_node->value;// etiqueta-valor de cada nodo

			for (typename list<Edge*>::iterator it= temp_node->EdgeNod.begin(); it != temp_node->EdgeNod.end(); ++it){
				//recorrer la lista de punteros a aristas del nodo
				if(temp_node->value != (*it)->enodo[1]->value){
					cout<<" ---> "<< (*it)->value<<"("<<((*it)->enodo[1])->value<<")";
					cout<<endl;
				}
			}
			cout<<"\n";
		}
	}
	/*
	void printGraph(){
	  Node *tmp,*auxi;
	  Edge *m;

	  for(int i=0;i<mnodes.size();i++)
		{  cout<<"nodo:"<<mnodes[i]->value<<" "<<endl;
		   tmp=mnodes[i];
		  for(int j=0;j<mnodes[i]->EdgeNod.size();j++)
			  {  cout<<"aristas:"<<(tmp->EdgeNod.begin()+j)->value<<" ";}
			  cout<<endl;

		}
	  for(int i=0;i<mnodes.size();i++)
		{auxi=mnodes[i];
		  for(int j=0;j<mnodes[i]->EdgeNod.size();j++)
			{ m=mnodes[i]->EdgeNod[j];
			  if(m->mdir==1)
				{cout<<"de"<<"("<<m->enodo[0]->value<<") "<<"<-"<<m->value<<"->"<<" a "<<"("<<m->enodo[1]->value<<")"<<endl;}
			  else
				{cout<<"de"<<"("<<m->enodo[0]->value<<") "<<"-"<<m->value<<"->"<<" a "<<"("<<m->enodo[1]->value<<")"<<endl;}
			}
		}	
	}*/
/*	
};
#endif //GRAPHO_H
*/
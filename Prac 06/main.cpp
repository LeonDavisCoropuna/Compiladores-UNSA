#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;
/*clases*/
class Nodo;
class Arista;
class AFN;

class NodoAFD;
class AristaAFD;
class AFD;

class Arista
{
public:
    int caracter_destino; // indica la letra / caracter de destino
    Nodo *destino;        // indica el nodo destino
};

class Nodo
{
public:
    int id;
    bool aceptacion = 0; //si es estado final
    vector<Arista *> salidas; //aristas
    //busca las transicion epsilon
    void buscar(int s, set<Nodo *> &pila) 
    {
        for (auto i : salidas)
        {
            if (i->caracter_destino == s)
            {
                pila.insert(i->destino);
                i->destino->buscar(s, pila);
            }
        }
    }
    void E_claus(int s, set<Nodo *>&pila){
        //pila.insert(this);
        buscar(s,pila);
    }
    //aristas de un nodo
    void findSalidas(int s, set<Nodo *>&pila){
        for(auto i : salidas){
            if(i->caracter_destino == s){
                pila.insert(i->destino);
            }
        }
    }

    Nodo() {}
    Nodo(int _id)
    {
        id = _id;
    }
    //muestra las transiciones del nodo 
    void printSalidas(){
        for(auto i:salidas){
            cout<<id<<" "<<i->caracter_destino<<" "<<i->destino->id<<endl;
        }
    }
};

class AFN
{
public:
    int numEstados;
    int numEstadosAceptacion;
    int numEntradas;
    int numTransiciones;
    vector<int> estados;
    vector<int> entradas;
    vector<Nodo *> nodos; // vector de nodos

    void cargar_txt(string file_name)
    {
        int t = 0;
        string line;
        ifstream archivo(file_name);
        while (getline(archivo, line))
        {
            if (t == 0)
            {
                numEstados = (stoi(line));
                t++;
            }
            else if (t == 1)
            {
                stringstream ss(line);
                int numero;
                while (ss >> numero)
                {
                    Nodo *q = new Nodo(numero);
                    nodos.push_back(q);
                }
                t++;
            }
            else if (t == 2)
            {
                numEstadosAceptacion = stoi(line);
                t++;
            }
            else if (t == 3)
            {

                stringstream ss(line);
                int numero;
                while (ss >> numero)
                {
                    for (auto i : nodos)
                    {
                        if (i->id == numero)
                        {
                            i->aceptacion = 1;
                        }
                    }
                }
                t++;
            }
            else if(t == 4){
                numEntradas = stoi(line);
                t++;
            }
            else if(t == 5){
                stringstream ss(line);
                int numero;
                while (ss >> numero)
                {
                    entradas.push_back(numero);
                }
                //entradas.push_back(-1);
                t++;
            }
            else if(t== 6){
                numTransiciones = stoi(line);
                t++;
            }
            else{
                Arista * p = new Arista;
                stringstream ss(line); //obtiene los numeros de un string
                int idNodo,caracter,idNododes;
                ss>>idNodo; ss>>caracter;ss>>idNododes;
                for(auto i:nodos){
                    if(i->id == idNodo){
                        p->caracter_destino = caracter;
                        for(auto j:nodos){
                            if(j->id == idNododes){
                                p->destino = j;
                                break;
                            }
                        }
                        i->salidas.push_back(p);
                        break;
                    }
                }
                t++;
            }
        }
    }
    void printAFD(){
        for(auto i:nodos){
            i->printSalidas();
        }
    }
};
class AristaAFD{
    public:
    int caracter_destino;
    NodoAFD * destino;
};
class NodoAFD{
    public:
        int id;
        bool marca = 0; //indica si el nodo esta marcado
        bool aceptacion=0;
        set<Nodo *> lista;
        vector<AristaAFD *> salidas;
};

class AFD{
    public:
    vector<NodoAFD *> nodos;
    vector<AristaAFD *> salidasAFD;
    vector<int> entradas;
    int numEstadosAceptacion=0;
    int numTransiciones=0;
    bool existeNodo(set<Nodo *> afd,NodoAFD *&p){
        int temp = 0;
        for(auto i : nodos){
            bool sonIguales = std::equal(i->lista.begin(), i->lista.end(), afd.begin(), afd.end());
            if(sonIguales){
                temp = 1;p = i;break;
            }
        }
        return temp;
    }
    AFD(){}
};

void TranformarAFD_AFN(AFN &afn,AFD &afd){
    //se inicializa el afd con el estado inicial
    set<Nodo *> temp3;
    temp3.insert(afn.nodos[0]);
    NodoAFD *q = new NodoAFD;
    q->id = 0;
    q->lista.insert(afn.nodos[0]);
    afn.nodos[0]->E_claus(-1,q->lista);
    afd.nodos.push_back(q);
    int todoMarcado = 1;
    //mientras todos los nodos no esten marcados entonces...
    while(todoMarcado){
        set<Nodo *> aux; //almacena las salidas desde un nodo
        set<Nodo *> aux2; //almacena los elementos del nodoAFD
        todoMarcado = 0;
        for(auto itnodos :afd.nodos){
            if(itnodos->marca == 0){
                todoMarcado = 1;
                for(auto itAlfabeto : afn.entradas){
                    for(auto itNodo : itnodos->lista){
                        itNodo->findSalidas(itAlfabeto,aux);
                        for(auto i : aux){
                            aux2.insert(i);
                            i->E_claus(-1,aux2);
                        }
                    }
                    NodoAFD *q;
                    AristaAFD *a = new AristaAFD;
                    a->caracter_destino = itAlfabeto;
                    //verifica si existe el nodoAFD para crearlo o solo cambiar el puntero del arista
                    if(!afd.existeNodo(aux2,q)){  
                        q = new NodoAFD;
                        auto inicio = afd.nodos.begin();
                        auto final = afd.nodos.end();
                        q->id = std::distance(inicio, final);
                        for(auto k : aux2)
                            if(k->aceptacion){ q->aceptacion = 1;++afd.numEstadosAceptacion;}
                        q->lista = aux2;
                        afd.nodos.push_back(q);
                    }

                    a->destino = q;
                    itnodos->salidas.push_back(a);
                    afd.numTransiciones++;
                    //vacia ambos std::set (conjuntos)
                    aux.clear();
                    aux2.clear();
                }
            }
            itnodos->marca = 1;
        }
    }
}

template <class T>

class GeneratePNG{
    public:
    T automata;
    GeneratePNG(const T & _automata){
        automata = _automata;
    }
    void generarPNG(string image_name){
        ofstream os(image_name);
        os<<"digraph finite_state_machine {"<<endl;
        os<<"fontname=\"Helvetica,Arial,sans-serif\""<<endl;
        os<<"node [fontname=\"Helvetica,Arial,sans-serif\"]"<<endl;
        os<<"edge [fontname=\"Helvetica,Arial,sans-serif\"]"<<endl;
        os<<"rankdir=LR;"<<endl;
        if(automata.numEstadosAceptacion>0){
            os<<"node [shape = doublecircle]; ";
            for(auto i: automata.nodos){
                if(i->aceptacion){
                    os<<i->id<<" ";
                }
            }
            os<<";"<<endl;
        }
        os<<"node [shape = circle];"<<endl;
        for(auto itNodos : automata.nodos){
            for(auto itAristas : itNodos->salidas){
                os<< itNodos->id<<" -> "<<itAristas->destino->id<<"[label = \""<<itAristas->caracter_destino<<"\"];"<<endl;

            }
        }
        os<<"}"<<endl;
        string comand = "dot -Tpng "+image_name+" -o "+image_name.substr(0,image_name.size()-4) +".png";
        system(comand.c_str());
    }
};

int main()
{ 
    AFN afn;
    AFD afd;
    
    string entrada,salida,entradaGrafica,salidaGrafica;
    cout<<"Archivo entrada AFN: ";getline(cin,entrada);
    cout<<"Nombre del archivo grafica AFN: ";getline(cin,entradaGrafica);
    cout<<"Archivo salida AFD: ";getline(cin,salida);
    cout<<"Nombre del archivo grafica AFD: ";getline(cin,salidaGrafica);
    
    afn.cargar_txt(entrada);
    TranformarAFD_AFN(afn,afd);
    GeneratePNG<AFN> g1(afn);
    GeneratePNG<AFD> g2(afd);
    g1.generarPNG(entradaGrafica);
    g2.generarPNG(salidaGrafica);


    cout<<"Estados"<<endl;
    cout<<afd.nodos.size()<<endl;
    for(int i=0;i<afd.nodos.size();i++){
        cout<<afd.nodos[i]->id<<" = { ";
        for(auto h : afd.nodos[i]->lista){
            cout<<h->id<<" ";
        }
        cout<<"}"<<endl;
    }

    cout<<"Estados de aceptacion: "<<endl;
    cout<<afd.numEstadosAceptacion<<endl;
    for(auto i:afd.nodos){
        if(i->aceptacion){
            cout<<i->id<<" ";
        }
    }
    cout<<endl;
    cout<<"Entradas"<<endl;
    cout<<afn.entradas.size()<<endl;
    for(auto i:afn.entradas){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"Transiciones de Estados (x,y,z)"<<endl;
    cout<<afd.numTransiciones<<endl;
    for(int i=0;i<afd.nodos.size();i++){
        for(auto h : afd.nodos[i]->salidas){
            cout<< afd.nodos[i]->id<<" "<<h->caracter_destino<<" "<<h->destino->id<<endl;
        }
    }
}
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//simulacion de un grafo
class Nodo; 
class Arista;

class Arista
{
public:
    string letra_origen; //indica la letra / caracter de origen
    Nodo *destino; //indica el nodo destino
};
class Nodo
{
public:
    int id; //id del nodo
    bool aceptacion = 0; //indica si el nodo es un estado de aceptacion
    vector<Arista *> salidas; //salidas del nodo

    //funcion que indica si la cadena es reconocida por el AFD
    void reconocer(string cadena)
    {
        if (cadena.size() > 0)
                cout << cadena << endl; //imprime paso a paso el procesor de reconocimiento
        if (cadena.size() > 0)
        {

            string destino = cadena.substr(0, 1); //extrae el primer caracter de la cadena 
            Nodo *q;
            for (int i = 0; i < salidas.size(); i++) //recorre las posibles salidas del nodo
            {
                if (salidas[i]->letra_origen == destino) //una vez ubicada
                {
                    q = salidas[i]->destino; //se dirige al destino
                }
            }
            string aux = cadena.substr(1, cadena.size());//se le setea la cadena para que 
            //no se tome el primer caracter
            q->reconocer(aux); //llama a la funcion del nodo destino y se ejecuta nuevamente reconocer()
        }
        else
        {
            // si la longitud de cadena es 0
            if (aceptacion) //se verifica si este nodo es un estado de aceptacion
                cout << "El AFD reconoce la cadena" << endl;
            else
                cout << "El AFD NO reconoce la cadena" << endl;
        }
    }
};

class AFD
{
public:
    int num_nodos; //numero de nodos
    int idNodoInicio; //estado inicial
    vector<Nodo *> nodos; //vector de nodos
    vector<string> alfabeto; //contiene el alfabeto
    string cadena; //el string a reconocer
    void cargar_txt(string file_name)
    {
        string line;
        ifstream archivo(file_name);
        int t = 0;
        while (getline(archivo, line))
        {
            if (t == 0)
            {
                //en la 1ra del file
                //setea el nro de nodos 
                //crea n nodos en el vector
                num_nodos = (stoi(line));
                for (int i = 0; i < num_nodos; i++)
                {
                    Nodo *b = new Nodo;
                    b->id = i;
                    nodos.push_back(b);
                }
            }
            else if (t == 1)
            {
                //en la 2da del file
                //se pushea el alfabeto
                string aux = "";
                for (int i = 0; i < line.size() + 1; i++)
                {
                    if (line[i] == ',' || line[i] == '\0'){
                        alfabeto.push_back(aux);
                        aux= "";
                    }
                    else
                        aux += line[i];
                }
            }
            else if (t == 2)
            {   //en la 3ra del file
                //se indica el estado inicial
                idNodoInicio = stoi(line);
            }
            else if (t == 3)
            {
                //de la 4ta fila se establecen los estados finales
                string aux = "";
                for (int i = 0; i < line.size() + 1; i++)
                {
                    if (line[i] == ',' || line[i] == '\0')
                    {
                        nodos[stoi(aux)]->aceptacion = 1; 
                        aux = "";

                    }
                    else
                    {
                        aux += line[i];
                    }
                }
            }
            else
            {
                //de la 5ta fila en adelante
                //se conocen las transiciones y se pushean a los vectores
                Arista *c = new Arista;
                int idNodo;
                string aux = "";
                for (int i = 0; i < line.size() + 1; i++)
                {
                    if (line[i] == ',')
                    {
                        idNodo = stoi(aux);
                        aux = "";
                    }
                    else if (line[i] == '>')
                    {
                        int t = 0;
                        for(int i=0;i<alfabeto.size();i++){
                            if(alfabeto[i] == aux){
                                t = 1;
                                break;
                            }
                        }
                        if(t){
                            c->letra_origen = aux;
                            aux = "";
                        }
                        else{
                            //si la transicion es incorrecta entonces: 
                            throw runtime_error("AFD NO valido");
                        }
                    }
                    else if (line[i] == '\0')
                    {
                        c->destino = nodos[stoi(aux)];
                        aux = "";
                    }
                    else
                    {
                        aux += line[i];
                    }
                }
                nodos[idNodo]->salidas.push_back(c);
            }
            t++;
        }
    }
    void reconocer_cadena(string cadena)
    {
        nodos[idNodoInicio]->reconocer(cadena);
    }
    AFD() {}
};

int main()
{
    AFD a;
    a.cargar_txt("afd3.txt"); //nombre del file
    a.reconocer_cadena("bbabbabaab");

    return 0;
}
#include <iostream>
#include <fstream>
using namespace std;

void desplazar(string word, int desplazamiento, ostream &os){
   for(auto i : word){
       if(i == ' ') os<<i; //el espacio no se toma en cuenta
       else {
           int des = int(i) + desplazamiento;
           char con = des;
           os<<con;
       }
   }
   os<<endl;
}

int main(){

    string archivo_entrada, archivo_salida, accion;
    int desplazamiento;

    cout<<"Archivo entrada: ";
    getline(cin,archivo_entrada);

    cout<<"Desplazamiento: ";
    cin>>desplazamiento; cin.ignore();

    cout<<"Archivo salida: ";
    getline(cin,archivo_salida);

    cout<<"Accion: ";
    getline(cin,accion);

    ifstream entrada(archivo_entrada + ".txt");
    ofstream salida(archivo_salida + ".txt");

    //si quiero descifrar el desplazamiento tiene que ser negativo
    if(accion == "descifrar") desplazamiento *= -1;
    
    string linea;
    while(getline(entrada,linea)){
       desplazar(linea,desplazamiento,salida);
    }

    return 0;
}

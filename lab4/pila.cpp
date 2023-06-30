#include <iostream>
#include <stack>
using namespace std;
void leer_cadena(stack<int> &pila,string cadena){
    string aux="";
    for(auto i : cadena){
        if(i != ' '){
            if(i == '+'){
                int temp = pila.top();
                pila.pop();
                int temp2 = pila.top(); 
                pila.pop();
                pila.push(temp2+temp);
                aux = "";
            }
            else if(i == '-'){
                int temp = pila.top();
                pila.pop();
                int temp2 = pila.top(); 
                pila.pop();
                pila.push(temp2-temp);
                aux = "";

            }
            else if(i == '*'){
                int temp = pila.top();
                pila.pop();
                int temp2 = pila.top(); 
                pila.pop();
                pila.push(temp2*temp);
                aux = "";
            }
            else if(i == '/'){
                int temp = pila.top();
                pila.pop();
                int temp2 = pila.top(); 
                pila.pop();
                pila.push(temp2/temp);
                aux = "";

            }
            else{
                aux += i;
            }
        } else{
            if(aux.size()>0)
                pila.push(stoi(aux));
            aux = "";
        }
    }
}
int main()
{
    string cadena="";
    cout<<"Texto: ";
    getline(cin,cadena);
    stack <int> pila;
    leer_cadena(pila,cadena);
    cout<<"Resultado: "<<pila.top()<<endl;
    return 0;
}
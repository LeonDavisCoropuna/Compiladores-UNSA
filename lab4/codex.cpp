//intente con el codigo de clase, pero con los parentesis dobles o mas 
//((Exp)) me ocurren errores
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;
#include <regex>

std::string obtenerParteAritmetica(const std::string& cadena) {
    std::regex patron("[0-9+\\-*/ ]+"); // Patrón para encontrar números, operadores y espacios en blanco
    std::smatch coincidencia;

    if (std::regex_search(cadena, coincidencia, patron)) {
        return coincidencia.str();
    } else {
        return ""; // Si no se encuentra ninguna coincidencia, devuelve una cadena vacía
    }
}

bool esOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// A mayor número, la operación es más prioritaria
float getPrioridad(char operador)
{
    if (operador == '+' || operador == '-')
        return 1;
    else if (operador == '*' || operador == '/')
        return 2;
    return 0;
}

string convertirInfijaAPostfija(const string &expresion)
{
    string postfija;
    stack<char> pila;

    for (char c : expresion)
    {
        if (isspace(c))
            continue; // Ignorar espacios en blanco

        if (isalnum(c))
        {
            postfija += c; // Agregar operandos directamente a la salida
        }
        else if (esOperador(c))
        {
            while (!pila.empty() && esOperador(pila.top()) && getPrioridad(pila.top()) >= getPrioridad(c))
            {
                postfija += ' ';
                postfija += pila.top();
                pila.pop();
            }
            postfija += ' ';
            pila.push(c);
        }
        else if (c == '(')
        {
            pila.push(c);
        }
        else if (c == ')')
        {
            while (!pila.empty() && pila.top() != '(')
            {
                postfija += ' ';
                postfija += pila.top();
                pila.pop();
            }
            pila.pop(); // Eliminar el paréntesis izquierdo de la pila
        }
    }

    // Vaciar la pila al final
    while (!pila.empty())
    {
        postfija += ' ';
        postfija += pila.top();
        pila.pop();
    }

    return postfija;
}

float resultado_postfija(string cadena)
{
    stack<float> pila;
    string aux = "";
    for (auto i : cadena)
    {
        if (i != ' ')
        {
            if (i == '+')
            {
                float temp = pila.top();
                pila.pop();
                float temp2 = pila.top();
                pila.pop();
                pila.push(temp2 + temp);
                aux = "";
            }
            else if (i == '-')
            {
                float temp = pila.top();
                pila.pop();
                float temp2 = pila.top();
                pila.pop();
                pila.push(temp2 - temp);
                aux = "";
            }
            else if (i == '*')
            {
                float temp = pila.top();
                pila.pop();
                float temp2 = pila.top();
                pila.pop();
                pila.push(temp2 * temp);
                aux = "";
            }
            else if (i == '/')
            {
                float temp = pila.top();
                pila.pop();
                float temp2 = pila.top();
                pila.pop();
                pila.push(temp2 / temp);
                aux = "";
            }
            else
            {
                aux += i;
            }
        }
        else
        {
            if (aux.size() > 0)
                pila.push(stoi(aux));
            aux = "";
        }
    }
    return pila.top();
}

int main()
{
    string texto;
    cout << "Nombre del .txt: ";
    getline(cin, texto);
    ifstream archivo(texto, ios::in);
    string expresion,exp;
    getline(archivo, expresion);
    if (expresion != "INICIO")
        return 0;
    while (getline(archivo, expresion))
    {
        exp = obtenerParteAritmetica(expresion);
        cout<<exp<<endl;
        expresion.erase(std::remove_if(texto.begin(), texto.end(), ::isspace), texto.end());
        if(expresion == "FIN") return 0;
        cout << "Expresion infija: " << expresion << endl;
        string postfija = convertirInfijaAPostfija(expresion);
        cout << "Expresion postfija: " << postfija << endl;
        float resultado = resultado_postfija(postfija);
        cout << "Resultado postfija: " << resultado << endl<<endl;
    }

    cout<<"Archivo leido correctamente"<<endl;
    return 0;
}

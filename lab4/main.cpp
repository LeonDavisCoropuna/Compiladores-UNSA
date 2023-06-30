#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#define MAS '+'
#define MENOS '-'
#define NUM 256
#define FIN -1
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

char lexema[80];
int tok;
string cadena="";
void parea(int);
void error();
void Resto();
void Term();
void Exp();
int scanner();

void Exp()
{
    if (tok == NUM)
    {
        Term();
        Resto();
    }
    else error();
}

void Resto()
{
    if (tok == MAS)
    {
        parea(MAS);
        Term();
        printf("+");
        cadena += "+ ";
        Resto();
    }
    else if (tok == MENOS) 
    {
        parea(MENOS);
        Term();
        printf("-");
        cadena += "- ";

        Resto();
    }
}

void Term()
{
    if (tok == NUM)
    {
        printf("%s", lexema);
        cadena += string(lexema) + " ";
        parea(NUM);
    }
    else
        error();
}

void error()
{
    printf("Error de sintaxis.");
}

void parea(int t)
{
    if (tok == t)
        tok = scanner();
    else 
        error();
}

int scanner()
{
    int c, i;
    do 
        c = getchar();
    while (c == '0');
    if (c == '\n')
        return FIN;
    if (c == MAS || c == MENOS)
        return c;
    if (isdigit(c))
    {
        i = 0;
        do 
        {
            lexema[i++] = c;
            c = getchar();
        }
        while (isdigit(c));
        lexema[i] = 0;
        ungetc(c, stdin);
        return NUM;
    }
    return 0;
}

int main() 
{
    tok = scanner();
    Exp();
}
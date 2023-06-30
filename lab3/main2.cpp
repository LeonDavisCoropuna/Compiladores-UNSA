#include <iostream>
#include <fstream>
#define ARRAY_SIZE_PR 13
#define PALABRAS_RESERVADAS                                                                                              \
    {                                                                                                                    \
        "int", "float", "double", "bool", "char", "string", "class", "struct", "return", "if", "else", "main", "include" \
    }

#define ARRAY_SIZE_SO 5
#define SIMBOLOS_OPERACION       \
    {                            \
        "+", "-", "*", "/", "**" \
    }
#define ARRAY_SIZE_OPERACION_LOGICA 7
#define SIMBOLOS_OPERACION_LOGICA             \
    {                                         \
        "<", ">", "<=", ">=", "=", "==", "!=" \
    }
#define ARRAY_SIZE_SI 7
#define SIMBOLOS_SINTAXIS                 \
    {                                     \
        ",", ";", "'", "(", ")", "[", "]" \
    }

#define COMENTAR_LINEA "//"
#define COMENTAR_BLOQUE \
    {                   \
        "/*", "*/"      \
    }

using namespace std;
//ascii para caracteres especiales
bool isCaracterEspecial(char caracter)
{
    int le = int(caracter);
    if ((le >= 33 && le <= 47) || (le >= 58 && le <= 64) || (le >= 58 && le <= 96) || (le >= 123))
        return 1;
    return 0;
}
//ascii para numeros
bool isNumero(char caracter)
{
    int le = int(caracter);
    if (le >= 48 && le <= 57)
        return 1;
    return 0;
}
//ascii para letras en general
bool isWord(char caracter)
{
    int le = int(caracter);
    if ((le >= 65 && le <= 91) || (le >= 97 && le <= 122))
        return 1;
    return 0;
}
void separador(string word) //el parametro es una palabra unica a la cual se le asignara un token 
{
    string num = "", palabra = ""; // buffer para numeros y palabras
    for (int i = 0; i < word.size(); i++) 
    {
        if (isCaracterEspecial(word[i])) //verifica que word[i] es un caracter
        {
            //como se encontro un caracter, significa que el buffer esta lleno con algo
            //a ese buffer se le asigna un token
            if (num.size() > 0) //si la longitud de num es mayor que 0 entonces el buffer de numeros tiene algo
            {
                cout << "token = NUM [" << num << "]" << endl;
                num = ""; // se reinicia el buffer de numeros
            }
            if (palabra.size() > 0)
            {
                //se crea este for para saber si es una palabra reservada
                for (int k = 0; k < ARRAY_SIZE_PR; k++)
                {
                    const char *pr[ARRAY_SIZE_PR] = PALABRAS_RESERVADAS;
                    if (pr[k] == palabra)
                    {
                        cout << "token = PALABRA_RESERVADA [" << palabra << "]" << endl;
                    }
                }
                palabra = ""; // se reinicia el buffer de palabras
            }
            //si no es ni numero ni palabra entonces: 
            if (i + 1 < word.size())
            {
                //puede ocurrir que un cacter especial tenga longitud 2 como: >= , != , etc
                if (isCaracterEspecial(word[i + 1]))
                {
                    int x = 0;//indica si es una operacion
                    string q = string(1, word[i]) + string(1, word[i + 1]); //concatenar 2 char
                    // se verifica que q sea alguna operacion (+,-,*,/,**)
                    const char *ce[ARRAY_SIZE_SO] = SIMBOLOS_OPERACION;
                    for (int k = 0; k < ARRAY_SIZE_SO; k++)
                    {
                        if (ce[k] == q)
                        {
                            x = 1; 
                        }
                    }
                    
                    if (x)
                    {
                        cout << "token = OPERACION [" << q << "]" << endl;
                    }
                    //si no es una operacion entonces: 
                    else 
                    {
                        //indica si es un simbolo de operacion logica (<=,>=,etc)
                        int x = 0;
                        const char *sop[ARRAY_SIZE_OPERACION_LOGICA] = SIMBOLOS_OPERACION_LOGICA;
                        string q = string(1, word[i]) + string(1, word[i + 1]);
                        for (int k = 0; k < ARRAY_SIZE_OPERACION_LOGICA; k++)
                        {
                            if (sop[k] == q)
                            {
                                x = 1;
                            }
                        }
                        if (x)
                        {
                            cout << "token = SIMBOLO OPERACION LOGICA [" << word[i] << word[i + 1] << "]" << endl;
                        }
                        else
                        {
                            cout << "token = SIMBOLO SINTAXIS [" << word[i] << word[i + 1] << "]" << endl;
                        }
                        
                    }
                    i++;
                }
            }
            //tambien solo puede ser un caracter especial de longitud 1
            else
            {
                int x = 0;//indica si es un simbolo normal
                const char *ce[ARRAY_SIZE_SO] = SIMBOLOS_OPERACION;
                for (int k = 0; k < ARRAY_SIZE_SO; k++)
                {
                    if (ce[k] == string(1, word[i]))
                    {
                        //si es una simbolo de operacion 
                        x = 1;
                    }
                }
                
                if (x)
                {
                    cout << "token = OPERACION [" << word[i] << "] " << endl;
                }
                else
                {
                    //si no es un simbolo de operacion normal, puede ser un simbolo 
                    //de operacion logica
                    int x = 0;
                    string q = string(1, word[i]);
                    const char *ce[ARRAY_SIZE_OPERACION_LOGICA] = SIMBOLOS_OPERACION_LOGICA;
                    for (int k = 0; k < ARRAY_SIZE_OPERACION_LOGICA; k++)
                    {
                        if (ce[k] == q)
                        {
                            //si es un simbolo de operacion logica
                            x = 1;
                        }
                    }
                    
                    if (x)
                    {
                        cout << "token = SIMBOLO OPERACION LOGICA [" << word[i] << word[i + 1] << "]" << endl;
                    }
                    else
                    {
                        //si este no pertenece a ninguno de estos, quiere decir que el simbolo
                        //pertenece a la sintaxis del programa: ; , () , [] , etc
                        cout << "token = SIMBOLO SINTANXIS [" << word[i] << "] " << endl;
                    }
                }
            }
        }
        if (isNumero(word[i]))
        {
            num += word[i];
            if (palabra.size() > 0)
            {
                cout << "token = ID [" << palabra << "]" << endl;
                palabra = "";
            }
        }
        if (isWord(word[i]))
        {
            palabra += word[i];
            //nuevamente,si el buffer de numeros tiene algo se muestra
            if (num.size() > 0)
            {
                cout << "token = NUM [" << num << "]" << endl;
                num = "";
            }
        }
    }
    if (num.size() == word.size())
        cout << "token = NUM [" << num << "]" << endl;
    else if (palabra.size() == word.size())
    {
        int t = 0;
        for (int k = 0; k < ARRAY_SIZE_PR; k++)
        {
            //verifica si es una palabra reservada o no
            const char *pr[ARRAY_SIZE_PR] = PALABRAS_RESERVADAS;
            if (pr[k] == palabra)
            {
                t = 1;
            }
        }
        if (t)
        {
            cout << "token = PALABRA_RESERVADA [" << palabra << "]" << endl;
        }
        else
        {
            cout << "token = ID [" << palabra << "]" << endl;
        }
    }
}
int main()
{
    string linea; //buffer de lectura para el txt
    ifstream archivo("archivo.txt"); 
    int comentario_bloque = 0; //controlador de /* y */
    while (getline(archivo, linea)) //recorre linea a linea el archivo
    {
        linea += " "; // debido a la construccion de mi algoritmo, necesito añadir un valor mas
        string aux; //sirve para concatenar lo leido
        for (auto k : linea) //recorre la linea
        {
            if (k != ' ') //si no es espacio vacio
                aux += k; //aux se concatena 
            else //si se encuentra un vacio, significa que se encontro una palabra
            {
                if (aux.size() > 0) //si es un espacio vacio no cuenta
                {
                    if (comentario_bloque) //si es verdadero se tiene que buscar /*
                    // para que el analizador lexico siga funcionando
                    {
                        if (linea.substr(0, 2) == "*/") //si se encuentra entonces el analizador continua
                        {
                            comentario_bloque = 0; //esta comentado? NO
                        }
                    }
                    else
                    {
                        if (linea.substr(0, 2) == "/*")//si se eneuntra esto significa que empieza un bloque
                        //de comentarios
                        {
                            comentario_bloque = 1; //esta comentado? SI
                        }
                        else
                        {
                            if (!(linea.substr(0, 2) == "//")) //el ultimo paso es ver si la linea esta comentada
                            {
                                separador(aux);  //inicia la funcion principal
                            }
                        }
                    }
                    aux = ""; //se reinicia el buffer
                }
            }
        }
    }
    return 0;
}
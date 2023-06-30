#include <iostream>
#include <fstream>

using namespace std;

bool isCaracterEspecial(char caracter){
    int le = int(caracter);
    if((le >= 33 && le <= 47) || (le >= 58 && le <= 64) || (le >= 58 && le <= 96) || (le >= 123)) return 1;
    return 0;
}
bool isNumero(char caracter){
    int le = int(caracter);
    if(le >= 48 && le <= 57) return 1;
    return 0;
}
bool isWord(char caracter){
    int le = int(caracter);
    if((le >= 65 && le <= 91) || (le >= 97 && le <= 122)) return 1;
    return 0;
}
void separador(string word){
    string num = "", palabra="";
    for(int i = 0 ; i < word.size() ;i++){
        if(isCaracterEspecial(word[i])){ 
            if(num.size() > 0) {
                cout<<"["<<num<<"] -> numero" <<endl;
                num = "";
            }
            if(palabra.size() > 0) {
                cout<<"["<<palabra<<"] -> palabra" <<endl;
                palabra = "";
            }
            cout<<"["<<word[i]<<"] -> caracter especial" <<endl;
        }
        if(isNumero(word[i])){
            num += word[i];
            if(palabra.size() > 0) {
                cout<<"["<<palabra<<"] -> palabra" <<endl;
                palabra = "";
            }
        }
        if(isWord(word[i])){
            palabra += word[i];
            if(num.size() > 0) {
                cout<<"["<<num<<"] -> numero" <<endl;
                num = "";
            }
        }
    }
    if(num.size() == word.size()) cout<<"["<<num<<"] -> numero" <<endl;
    else if(palabra.size() == word.size())cout<<"["<<palabra<<"] -> palabra" <<endl;
}
int main(){
    string linea;
    ifstream archivo("archivo.txt");
    while(getline(archivo,linea)){
        linea += " ";
        string aux;
        for(auto k : linea){
            if(k != ' ') aux += k;
            else{
                if(aux.size() > 0){
                    separador(aux);
                    aux = "";
                }
            }
        }
    }
    return 0;
}
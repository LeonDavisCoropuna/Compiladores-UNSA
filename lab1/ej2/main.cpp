#include <iostream>
#include <fstream>

using namespace std;

int main(){
   ifstream archivo("archivo.txt");
   string line;
   while(getline(archivo,line)){
       for(auto i : line){
           cout<<i<<endl;
       }
   }
}

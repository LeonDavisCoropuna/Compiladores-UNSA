#include <iostream>
#include <fstream>


using namespace std;
int main(){
   string inst = "int temp;";
   //cout<<"Ingrese una instruccion: ";
   //cin>>inst;
  
   for(auto i : inst){
       cout<<i<<endl;
   }
   return 0;
}

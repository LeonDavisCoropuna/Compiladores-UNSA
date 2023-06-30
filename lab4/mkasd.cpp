#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Objeto {
    int peso;
    int beneficio;
};

bool compararRelacionBeneficioPeso(const Objeto& obj1, const Objeto& obj2) {
    double relacion1 = static_cast<double>(obj1.beneficio) / obj1.peso;
    double relacion2 = static_cast<double>(obj2.beneficio) / obj2.peso;
    return relacion1 > relacion2;
}

int Mochila01(vector<Objeto>& objetos, int capacidad) {
    sort(objetos.begin(), objetos.end(), compararRelacionBeneficioPeso);

    int numObjetos = objetos.size();
    vector<vector<int>> dp(numObjetos + 1, vector<int>(capacidad + 1, 0));

    for (int i = 1; i <= numObjetos; i++) {
        for (int j = 1; j <= capacidad; j++) {
            if (objetos[i - 1].peso <= j) {
                dp[i][j] = max(objetos[i - 1].beneficio + dp[i - 1][j - objetos[i - 1].peso], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[numObjetos][capacidad];
}

int main() {
    vector<Objeto> objetos = {
        { 10, 60 },
        { 20, 100 },
        { 30, 120 }
    };

    int capacidadMochila = 50;

    int beneficioOptimo = Mochila01(objetos, capacidadMochila);

    cout << "El beneficio máximo obtenido en la mochila es: " << beneficioOptimo << endl;

    return 0;
}

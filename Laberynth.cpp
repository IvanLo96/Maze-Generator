#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
int filas, columnas;
bool encontrado = false;
bool despejado = false;
string personaje;

enum Celda {
    PARED,
    CAMINO,
    CAMINO_SOLUCION
};

class Laberinto {
    public:
        int filas;
        int columnas;
        vector<vector<Celda>> grid;

        // Inicializar el laberinto con todas las celdas como paredes
        Laberinto(int filas, int columnas) : filas(filas), columnas(columnas) {
            grid.assign(filas, vector<Celda>(columnas, Celda::PARED));
        }

        void imprimir() {
            // Imprimir fila superior del borde
            for (int j = 0; j < columnas + 2; j++) {
                
                cout << "⬛";
            }
            cout << endl;

            for (int i = 0; i < filas; i++) {
                // Imprimir columna izquierda del borde
                cout << "⬛";

                for (int j = 0; j < columnas; j++) {
                    if (i == 0 && j == 0) {
                        cout << "E "; // Marcador de entrada
                    } else if (i == filas - 1 && j == columnas - 1) {
                        cout << "S "; // Marcador de salida
                    } else if (grid[i][j] == Celda::PARED) {
                        cout << "⬜";
                    } else if (grid[i][j] == Celda::CAMINO_SOLUCION){

                        if (personaje == "1"){ cout<<"🐧";} 
                        else if (personaje == "2"){ cout<<"👣";}
                        else { cout<<"🐧";}
                        
                    } 
                    else {

                        cout<<"  ";      
                    }    
                }

                // Imprimir columna derecha del borde
                cout << "⬛" << endl;
            }

            // Imprimir fila inferior del borde
            for (int j = 0; j < columnas + 2; j++) {
                cout << "⬛";
            }
            cout << endl;
        }

        void generarCaminoAleatorio(int x, int y) {
            grid[x][y] = CAMINO;

            // Definir las posibles direcciones a explorar.
            vector<pair<int, int>> direcciones = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            random_shuffle(direcciones.begin(), direcciones.end());

            for (int i = 0; i < direcciones.size(); i++) {
                int newX = x + direcciones[i].first * 2;
                int newY = y + direcciones[i].second * 2;

                if (newX >= 0 && newX < filas && newY >= 0 && newY < columnas && grid[newX][newY] == Celda::PARED) {   // Si la celda vecina es una pared (no visitada)
                    grid[x + direcciones[i].first][y + direcciones[i].second] = Celda::CAMINO;
                    generarCaminoAleatorio(newX, newY);
                }
            }
            }


        void despejarSalida(int x, int y) 
        {
        
            if (x <= filas-2 && y <= columnas- 2) {
            despejado = true;
            }

            grid[x][y] = CAMINO;

            vector<pair<int, int>> direcciones = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            random_shuffle(direcciones.begin(), direcciones.end());

            for (int i = 0; i < direcciones.size(); i++) {
                int newX = x + direcciones[i].first;
                int newY = y + direcciones[i].second;

                if (newX >= 0 && newX < filas && newY >= 0 && newY < columnas && grid[newX][newY] == Celda::PARED && despejado == false ) {  
                    despejarSalida(newX, newY);
                
                }
            }

        }

        void generar() 
        {
            generarCaminoAleatorio(0, 0);
            despejarSalida(filas - 1, columnas - 1); 
        }



        void buscarSolucion(int x, int y) 
        {
            
            if (x == filas - 1 && y == columnas - 1) {
                encontrado = true;
                
            }

            grid[x][y] = CAMINO_SOLUCION;
            vector<pair<int, int>> direcciones = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

            for (int i = 0; i < direcciones.size(); i++) {
                int newX = x + direcciones[i].first;
                int newY = y + direcciones[i].second;

                if (newX >= 0 && newX < filas && newY >= 0 && newY < columnas && !encontrado && grid[newX][newY] == CAMINO) {
                    buscarSolucion(newX, newY);
                }
            }   
        }
};



int main() {
    
    cout << "Cuantas filas deseas que posea el laberinto? : "; cin >> filas;
    cout << "Cuantas columnas deseas que posea el laberinto? : "; cin >> columnas;

    Laberinto laberinto(filas, columnas);
    laberinto.generar();
    cout<<endl<<"Laberinto Generado: "<<endl<<endl;
    laberinto.imprimir();
    
    laberinto.buscarSolucion(0,0);
    cout<<endl<<endl<<"Antes de mostrarte la solución, elige un personaje ==>(🐧 : 1, 👣 : 2) : ";cin>>personaje;
    cout<<endl<<endl<<"Solución: "<<endl<<endl;
    laberinto.imprimir();
    cout<<endl;

}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

#include "lib/matriz.h"
#include "lib/problema.h"

/*
   + Tres ficheros, uno para cada matriz (adyacencia, costos y heurística)

   + Fichero de valores Heurísticos:

      Es una matriz con estimaciones de las distancias.
      Matriz heurística

      4
      0 1 2 2
      pesos pesos pesos estimados




   + Los vértices de cada nivel de un árbol van ordenados segun su número, para mantener el orden de las búsquedas.

   + Debe preguntar al user los vértices inicial y final.
   + Como salida => El salido encontrado (con cada búsqueda) y cuantos nodos se han explorado.
*/

using namespace std;

int main (){
    while (1){
        system("clear");
        cout << "(Para salir introduzca un número negativo como nodo inicial)" << endl;
        int inicio, final;
        cout << "Nodo de inicio: ";
        cin >> inicio;
        if (inicio < 0)
            return 0;
        cout << "Nodo final: ";
        cin >> final;

        Problema* prob = new Problema(inicio, final);
        Solucion* sol = prob->BPA();
        if (sol != NULL)
            cout << "Búsqueda Primero en Anchura" << endl << *sol << endl;

        sol = prob->BPP();
        if (sol != NULL)
            cout << endl << "Búsqueda Primero en Profundidad" << endl << *sol << endl;

        sol = prob->BAE();
        if (sol != NULL)
            cout << endl << "Búsqueda A*" << endl << *sol << endl;

        cout << endl << "Pulse enter para continuar" << endl;
        cin.ignore().get();
    }
   return 0;
}


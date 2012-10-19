/*
 * Inteligencia Artificial - Práctica 2: Algoritmos de búsqueda
 *
 * AUTOR: Fernando González López-Peñalver (alu3177)
 * EMAIL: alu0100256543@ull.edu.es
 *
 * Fecha de entrega: 18 - Octubre - 2012
 *
 * Descripción:
 *      Se obtienen los datos desde tres ficheros (matriz de adyacencia,
 *      matriz de costos y matriz de evaluaciones heurísticas) para
 *      ejecutar tres algoritmos de búsqueda:
 *          - Búsqueda Primero en Amplitud      (no informada)
 *          - Búsqueda Primero en Profundidad   (no informada)
 *          - Búsqueda A*                       (infomada)
 */

#include "lib/problema.h"

int main (){
    while (1){
        system("clear");
        cout << "(Para salir introduzca un número negativo como nodo inicial)" << endl;
        // Obtención de nodos (inicio y final)
        int inicio, final;
        cout << "Nodo de inicio: ";
        cin >> inicio;
        if (inicio < 0)
            return 0;
        cout << "Nodo final: ";
        cin >> final;

        // Ejecución (y resultados) de los algoritmos
        Problema* prob = new Problema(inicio, final);
        Solucion* sol = prob->BPA(); // BPA
        if (sol != NULL)
            cout << "Búsqueda Primero en Anchura" << endl << *sol << endl;

        sol = prob->BPP();           // BPP
        if (sol != NULL)
            cout << endl << "Búsqueda Primero en Profundidad" << endl << *sol << endl;
        
        /* MODIFICACIÓN 2 */
        sol = prob->BPP_mod();           // BPP
        if (sol != NULL)
            cout << endl << "Búsqueda Primero en Profundidad MODIFICADA" << endl << *sol << endl;
        else
            cout << endl << "No se ha encontrado solución" << endl;
        /* MODIFICACIÓN 2 */
        
        sol = prob->BAE();           // BAE
        if (sol != NULL)
            cout << endl << "Búsqueda A*" << endl << *sol << endl;
        
        cout << endl << "Pulse enter para continuar" << endl;
        cin.ignore().get();
    }
   return 0;
}


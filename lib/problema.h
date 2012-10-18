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

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>

#include "matriz.h"
#include "nodo.h"
#include "solucion.h"

using namespace std;

extern void ParseFile (const char* path, Matriz* &mat);
extern bool isInStack (stack<Nodo* > s, Nodo* &n);
extern bool isInVector (vector<Nodo* > &v, Nodo* &n);
extern int isInVector (vector<Nodo* > &v, uint16_t id);
extern void InsertarOrden(vector<Nodo* > &v, Nodo* &n);

#ifndef PROBLEMA_H
#define PROBLEMA_H

// Rutas a los ficheros de matriz por defecto
const string DEFAULT_ADY_MATRIX = "datos/MatrizAdyacencia.txt";
const string DEFAULT_COST_MATRIX = "datos/MatrizCostos.txt";
const string DEFAULT_HEU_MATRIX = "datos/MatrizEvaluacionHeuristica.txt";

class Problema{
    private:
        Matriz* _adyMat;   // Matriz de adyacencia
        Matriz* _costMat;  // Matriz de costos
        Matriz* _heuMat;   // Matriz de datos Heurísticos
        uint16_t _initID;  // ID del nodo de inicio
        uint16_t _endID;   // ID del nodo final
        /* He optado por utilizar las IDs en lugar de
            un puntero; puesto que el tipo de dato
            uint16_t ocupa la mitad en memoria que Nodo* */

        /* FUNCIONES DE CARGA DE MATRICES */
        inline void LoadAdy (const char* path = DEFAULT_ADY_MATRIX.data()) { ParseFile(path, _adyMat); }
        inline void LoadCost (const char* path = DEFAULT_COST_MATRIX.data()) { ParseFile(path, _costMat); }
        inline void LoadHeu (const char* path = DEFAULT_HEU_MATRIX.data()) { ParseFile(path, _heuMat); }

        /* FUNCIONES DE MANEJO DE NODOS */
        void ExpandNode (Nodo* &n); // Expande el nodo n
        /* MODIFICACIÓN */
        void ExpandNodemod(Nodo* &n); // Expande el nodo n, si va a expandir y encuentra un '9', elimina el resto de hijos y deja sólo al '9'
        /* MODIFICACIÓN */
        uint16_t CalculaGn(Nodo* n);
        uint16_t CalculaFn (Nodo* &n);

    public:
        Problema (uint16_t init = 0, uint16_t end = 0, const char* adyPath = DEFAULT_ADY_MATRIX.data(), const char* costPath = DEFAULT_COST_MATRIX.data(), const char* heuPath = DEFAULT_HEU_MATRIX.data()) : _initID(init), _endID(end){
            LoadAdy(adyPath);
            LoadCost(costPath);
            LoadHeu(heuPath);
        }

        /* ALGORITMOS DE BÚSQUEDA */
        Solucion* BPA (); // Búsqueda Primero en Anchura
        Solucion* BPP (); // Búsqueda Primero en Profundidad
        Solucion* BAE (); // Búsqueda A*
        Solucion* BAE_mod(); // Búsqueda A* de la modificación

};

#endif

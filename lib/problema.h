#include <stdlib.h>
#include "matriz.h"
#include "nodo.h"
#include "aux.h"

using namespace std;

#ifndef PROBLEMA_H
#define PROBLEMA_H

// Rutas a los ficheros de matriz por defecto
char* DEFAULT_ADY_MATRIX = "datos/MatrizAdyacencia.txt";
char* DEFAULT_COST_MATRIX = "datos/MatrizCostos.txt";
char* DEFAULT_HEU_MATRIX = "datos/MatrizEvaluacionHeuristica.txt";

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
    public:
        Problema (uint16_t init = 0, uint16_t end = 0, char* adyPath = DEFAULT_ADY_MATRIX, char* costPath = DEFAULT_COST_MATRIX, char* heuPath = DEFAULT_HEU_MATRIX) : _initID(init), _endID(end){
            LoadAdy(adyPath);
            LoadCost(costPath);
            LoadHeu(heuPath);

            /*
            // DEBUG
                _adyMat->Print();
                _costMat->Print();
                _heuMat->Print();
            */
        }
void LoadAdy (char* path = DEFAULT_ADY_MATRIX) { ParseFile(path, _adyMat); }
void LoadCost (char* path = DEFAULT_COST_MATRIX) { ParseFile(path, _costMat); }
void LoadHeu (char* path = DEFAULT_HEU_MATRIX) { ParseFile(path, _heuMat); }
};

#endif

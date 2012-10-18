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

#include "solucion.h"

void Solucion::Generar(){
    Nodo* n = _nSol;
    if (n != NULL){
        while (n->GetPadre() != NULL){
            _costo += _costMat->Get(n->GetPadre()->GetID() - 1, n->GetID() - 1);
            n = n->GetPadre();
        }
    }
}

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
#include <string>
#include "nodo.h"

using namespace std;

void Nodo::AddHijo(Nodo* n){
    _hijos.push_back(n);
    _nHijos++;
    // Añadir hijos a un nodo implica que éste ha sido analizado
    if (!_analizado)
        _analizado = true;
}

void Nodo::Print(){
    string indent = "";
    for (uint8_t i = 0; i < _level; i++)
        indent += " ";
    cout << indent << "··········" << endl;
    cout << indent << "| ID: " << _id << endl;
    cout << indent << "| Nivel: " << _level << endl;
    cout << indent << "| Número de hijos:" << _nHijos << endl;
    cout << indent << "| Hijos: ";
    for (uint16_t i = 0; i < _hijos.size(); i++)
        cout << _hijos[i]->GetID() << " ";
    cout << endl;
    if (_padre != NULL)
        cout << indent << "| Padre: " << _padre->GetID() << endl;
    else
        cout << indent << "| Padre: " << "NULL (Nodo Raíz)" << endl;
    cout << indent << "| Analizado: " << _analizado << endl;
}

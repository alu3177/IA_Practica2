#include <stdlib.h>
#include <iostream>
#include <string>
#include "nodo.h"

using namespace std;

void Nodo::AddHijo(Nodo* n){
    _hijos.push_back(n);
    _nHijos++;
    // Añadir hijos a un nodo implica que éste ha sido analizado
    // TODO: Estudiar ésto <---
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

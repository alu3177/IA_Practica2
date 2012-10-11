#include <stdlib.h>
#include <vector>

using namespace std;

#ifndef PROBLEMA_H
#define PROBLEMA_H

class Nodo{
    protected:
        uint16_t _id;     // ID del nodo
        uint16_t _level;  // Nivel de profundidad en el árbol
        uint16_t _nHijos; // Número de hijos
        Nodo* _padre;     // Puntero al nodo padre
        vector<Nodo* > _hijos;  // Punteros a nodos hijo
        bool _analizado;  // Indica si hemos analizado (expandido) el nodo
    public:
        // Constructor
        Nodo (uint16_t id = 0, Nodo* father = NULL, uint16_t lvl = 0) : _id(id), _level(lvl), _nHijos(0), _analizado(false){
            _padre = father;
            // Establecemos el nivel (profundidad) del nodo
            if ((_level == 0) && (_padre != NULL))
                    _level = _padre->GetLevel() + 1;
        }

uint16_t GetID(){ return _id; }
uint8_t GetLevel(){ return _level; }
vector<Nodo* >* GetHijos() { return &_hijos; }

void AddHijo(Nodo* n){
    _hijos.push_back(n);
    _nHijos++;
}


void Print(){
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

};


/* ESTO ES DE LA CLASE PROBLEMA

        uint16_t _inicio; // ID del nodo inicial 
        uint16_t _final;  // ID del nodo final 
        /* He optado por utilizar las IDs en lugar de
           un puntero; puesto que el tipo de dato
           uint16_t ocupa la mitad en memoria que Nodo* *_/
*/
#endif

#include <stdlib.h>
#include <iostream>
#include <string>

#include "matriz.h"
#include "nodo.h"

using namespace std;

extern void ParseFile (const char* path, Matriz* &mat);

#ifndef SOLUCION_H
#define SOLUCION_H

class Solucion{
    public:
        Matriz* _costMat;  // Matriz de costos
        uint32_t _costo;
        uint32_t _nGenerados;
        uint32_t _nVisitados;
        uint16_t _nInitID;
        Nodo* _nSol;    // Nodo desde el que empezar a generar la solución

        Solucion (Nodo* n = NULL, uint32_t gene = 0, uint32_t expand = 0, uint16_t nInit = 0, const char* costPath = "datos/MatrizCostos.txt") : _costo(0), _nGenerados(gene), _nVisitados(expand), _nInitID(nInit) {
            _nSol = n;
            ParseFile(costPath, _costMat);
            this->Generar();
        }

        void Generar(){
            Nodo* n = _nSol;
            if (n != NULL){
                while (n->GetPadre() != NULL){
                    _costo += _costMat->Get(n->GetPadre()->GetID() - 1, n->GetID() - 1);
                    n = n->GetPadre();
                }
            }
        }

friend ostream &operator<<(ostream& s,const Solucion &sol){
    Nodo* n = sol._nSol;
    if (n != NULL){
        while (n->GetPadre() != NULL){
            cout << n->GetID() << "<-";
            n = n->GetPadre();
        }
        cout << sol._nInitID << endl;
    }
    s << "Costo: " << sol._costo << endl;
    s << "Número de nodos generados: " << sol._nGenerados << endl;
    s << "Número de nodos analizados: " << sol._nVisitados;
    return s;
}

};

#endif

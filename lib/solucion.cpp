/*
#include "solucion.h"

using namespace std;

ostream &operator<<(ostream& s,const Solucion &sol){
    Nodo* n = sol._nSol;
    if (n != NULL){
        while (n->GetPadre() != NULL){
            cout << n->GetID() << "<-";
        }
        cout << sol._nSol->GetID() << endl;
    }
    s << "Costo: " << sol._costo << endl;
    s << "Número de nodo generados: " << sol._nGenerados << endl;
    s << "Número de nodo analizados: " << sol._nVisitados;
    return s;
}
*/

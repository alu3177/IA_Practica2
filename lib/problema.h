#include <stdlib.h>
#include <queue>
#include <stack>
#include <vector>

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

        /* FUNCIONES DE CARGA DE MATRICES */
        inline void LoadAdy (char* path = DEFAULT_ADY_MATRIX) { ParseFile(path, _adyMat); }
        inline void LoadCost (char* path = DEFAULT_COST_MATRIX) { ParseFile(path, _costMat); }
        inline void LoadHeu (char* path = DEFAULT_HEU_MATRIX) { ParseFile(path, _heuMat); }

// Expande el nodo n
void ExpandNode (Nodo* &n){
    uint16_t fila = n->GetID() - 1; // Obtenemos el numero de fila en la matriz
                                    //(Los nodos comienzan la numeración en 1 y las filas de la matriz en 0)
    Nodo* child;    // Puntero usado para añadir hijos
    for (uint16_t j = 0; j < _adyMat->GetDim(); j++){
        if (_adyMat->Get(fila, j) == 1){
            // Si NO ES nodo Raíz
            if (n->GetID() != _initID){
                if ((n->GetPadre()->GetID() != j + 1) && (j + 1 != _initID)){ // No añadimos el nodo padre a los hijos
                    child = new Nodo(j + 1, n);
                    n->AddHijo(child);
                }
            // Si ES nodo raíz
            } else {
                child = new Nodo(j + 1, n);
                n->AddHijo(child);
            }
        }
    }
}

void BuildResult (Nodo* &n, uint32_t generados, uint32_t expandidos){
    Nodo* actual = n;
    uint32_t coste = 0;

    while (actual != NULL){
        cout << actual->GetID() << endl;    // DEBUG
        if (actual->GetID() != _initID)
            coste += _costMat->Get(actual->GetPadre()->GetID() -1, actual->GetID() - 1);
        actual = actual->GetPadre();
    }
    cout << "Costo: " << coste << endl;
    cout << "Número de nodo generados: " << generados << endl;
    cout << "Número de nodo analizados: " << expandidos << endl;
}

/* BÚSQUEDA PRIMERO EN ANCHURA */
void BPA (){
    queue<Nodo*> abiertos;  // Cola con los nodos abiertos sin expandir
    uint32_t nGenerados = 1; // Número de nodos generados
    uint32_t nExpand = 1;    // Número de nodos expandidos/analizados (empieza a 1, pues ya hemos generado el nodo raíz)
    bool finish = false;
    Nodo* n = new Nodo(_initID);    // Puntero para añadir nuevos nodos
                                    // Inicializado al nodo raíz
    Nodo* actual;   // Puntero al nodo actual

    abiertos.push(n);
    while ((abiertos.size() > 0) && (!finish)){
        actual = abiertos.front(); abiertos.pop(); // Leemos el HEAD y lo extraemos
        // Si encontramos el NODO FINAL
        if (actual->GetID() == _endID){
            finish = true;
            cout << "FINAL !!" << endl;     // DEBUG
            BuildResult(actual, nGenerados, nExpand);
        // Expandir el nodo actual
        } else {
            ExpandNode(actual);
            nExpand++;
            for (uint16_t i = 0; i < actual->GetHijos()->size(); i++){
                abiertos.push(actual->GetHijos()->at(i));
                nGenerados++;
                //cout << actual->GetHijos()->at(i)->GetID() << endl; // DEBUG
            }
        }
        //cout << "Abiertos.Size = " << abiertos.size() << endl; // DEBUG
    }
}


bool isInStack (stack<Nodo* > s, Nodo* &n){
    while (s.size() > 0){
        if (s.top() == n)
            return true;
        s.pop();
    }
    return false;
}

bool isInVector (vector<Nodo* > &v, Nodo* &n){
    for (uint16_t i = 0; i < v.size(); i++)
        if (v[i] == n)
            return true;
    return false;
}


void ExpandNodeBPP (Nodo* &n){
    uint16_t fila = n->GetID() - 1; // Obtenemos el numero de fila en la matriz
                                    //(Los nodos comienzan la numeración en 1 y las filas de la matriz en 0)
    Nodo* child;    // Puntero usado para añadir hijos

    //for (uint16_t j = 0; j < _adyMat->GetDim(); j++){
    for (uint16_t j = _adyMat->GetDim() - 1; j > 0; j--){
        if (_adyMat->Get(fila, j) == 1){
            // Si NO ES nodo Raíz
            if (n->GetID() != _initID){
                if ((n->GetPadre()->GetID() != j + 1) && (j + 1 != _initID)){ // No añadimos el nodo padre a los hijos
                    child = new Nodo(j + 1, n);
                    n->AddHijo(child);
                }
            // Si ES nodo raíz
            } else {
                child = new Nodo(j + 1, n);
                n->AddHijo(child);
            }
        }
    }
}

/* BÚSQUEDA PRIMERO EN PROFUNDIDAD */
void BPP (){
    stack<Nodo* > abiertos;  // Pila con punteros a nodos abiertos sin expandir
    vector<Nodo* > cerrados; // Array de punteros a nodos cerrados (no son el final)
    uint32_t nGenerados = 1; // Número de nodos generados
    uint32_t nExpand = 1;    // Número de nodos expandidos/analizados (empieza a 1, pues ya hemos generado el nodo raíz)
    bool finish = false;
    Nodo* n = new Nodo(_initID);    // Puntero para añadir nuevos nodos
                                    // Inicializado al nodo raíz
    Nodo* actual;   // Puntero al nodo actual

    abiertos.push(n);
    while ((abiertos.size() > 0) && (!finish)){
        actual = abiertos.top(); abiertos.pop(); // Leemos el HEAD y lo extraemos
        // Si encontramos el NODO FINAL
        if (actual->GetID() == _endID){
            finish = true;
            cout << "FINAL !!" << endl;     // DEBUG
            BuildResult(actual, nGenerados, nExpand);
        // Expandir el nodo actual
        } else {
            cout << "actual " << actual->GetID() << endl;
            ExpandNodeBPP(actual);
            nExpand++;
            for (uint16_t i = 0; i < actual->GetHijos()->size(); i++){
                if ((!isInStack(abiertos, actual->GetHijos()->at(i))) && (!isInVector(cerrados, actual->GetHijos()->at(i)))){
                    abiertos.push(actual->GetHijos()->at(i));
                    nGenerados++;
                }
                //cout << actual->GetHijos()->at(i)->GetID() << endl; // DEBUG
            }
        }
    }
}

};

#endif

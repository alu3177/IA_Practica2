#include "aux.h"
#include "problema.h"

/* *********************************
 * Métodos para el manejo de Nodos *
 * *********************************/

// Expande el nodo n
void Problema::ExpandNode (Nodo* &n){
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

// Expande el nodo n, pero almacena los hijos alrevés (de mayor a menor ID)
void Problema::ExpandNodeInverse (Nodo* &n){
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

// Calcula g(n), que es el coste real del camino desde el inicio hasta 'n'
uint16_t Problema::CalculaGn(Nodo* n){
    uint16_t result = 0;
    while (n->GetPadre() != NULL){
        result += _costMat->Get(n->GetPadre()->GetID() - 1, n->GetID() - 1);
        n = n->GetPadre();
    }
    return result;
}

/* Calcula y almacena el valor de la función de coste estimado:
 * f(n) = g(n) + h(n)
 * Donde:
 * g(n) es el coste real del camino desde el inicio hasta 'n'
 * h(n) es el valor estimado de coste desde 'n' hasta el nodo final
 *
 * Devuelve el valor generado y almacernado en el nodo 'n'
 */
uint16_t Problema::CalculaFn (Nodo* &n){
    n->SetFn(CalculaGn(n) + _heuMat->Get(n->GetID() - 1, _endID - 1));
    return (n->GetFn());
}

/* BÚSQUEDA PRIMERO EN ANCHURA */
void Problema::BPA(){
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
            //cout << "FINAL !!" << endl;     // DEBUG
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

/* BÚSQUEDA PRIMERO EN PROFUNDIDAD */
void Problema::BPP(){
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
            //cout << "FINAL !!" << endl;     // DEBUG
            BuildResult(actual, nGenerados, nExpand);
        // Expandir el nodo actual
        } else {
            //cout << "actual " << actual->GetID() << endl;   // DEBUG
            cerrados.push_back(actual);
            ExpandNodeInverse(actual);
            nExpand++;
            for (uint16_t i = 0; i < actual->GetHijos()->size(); i++){
                if ((!isInStack(abiertos, actual->GetHijos()->at(i))) && (!isInVector(cerrados, actual->GetHijos()->at(i)))){
                    abiertos.push(actual->GetHijos()->at(i));
                }
                nGenerados++;
                //cout << actual->GetHijos()->at(i)->GetID() << endl; // DEBUG
            }
        }
    }
}

/* ****************************************************
 * Métodos que implementan los algoritmos de búsqueda *
 * ****************************************************/

/* BÚSQUEDA A* */
void Problema::BAE(){
    vector<Nodo* > abiertos;  // Array con punteros a nodos abiertos sin expandir
    vector<Nodo* > cerrados;  // Array de punteros a nodos cerrados (no son el final)
    uint32_t nGenerados = 1;  // Número de nodos generados
    uint32_t nExpand = 1;     // Número de nodos expandidos/analizados (empieza a 1, pues ya hemos generado el nodo raíz)
    bool finish = false;
    Nodo* n = new Nodo(_initID);    // Puntero para añadir nuevos nodos
                                    // Inicializado al nodo raíz
    Nodo* actual;   // Puntero al nodo actual

    abiertos.push_back(n);
    while ((abiertos.size() > 0) && (!finish)){
        actual = abiertos.front(); abiertos.erase(abiertos.begin()); // Leemos el HEAD y lo extraemos

        // Si encontramos el NODO FINAL
        if (actual->GetID() == _endID){
            finish = true;
            //cout << "FINAL !!" << endl;     // DEBUG
            BuildResult(actual, nGenerados, nExpand);
        // Expandir el nodo actual
        } else {
            //cout << "actual " << actual->GetID() << endl;   // DEBUG
            cerrados.push_back(actual);
            ExpandNode(actual);
            nExpand++;
            for (uint16_t i = 0; i < actual->GetHijos()->size(); i++){
                int posHijoA = isInVector(abiertos, actual->GetHijos()->at(i)->GetID()); // Obtenemos la posición dentro del vector de ABIERTOS
                if (posHijoA > -1){ // Está en el vector de abiertos
                    // El valor g(n) del nodo en abiertos es peor (mayor) que
                    // el del nodo dentro del vector de hijos de 'actual'
                    if (CalculaGn(abiertos[posHijoA]) > CalculaGn(actual->GetHijos()->at(i))){
                        abiertos[posHijoA]->SetPadre(actual);    // Cambiamos el padre
                        CalculaFn(abiertos[posHijoA]);   // Recalculamos f(n)
                    }/*else  // DEBUG
                        cout << actual->GetHijos()->at(i)->GetID() << " Está en Abiertos, pero es peor" << endl;   // DEBUG
                    */
                }
                int posHijoC = isInVector(cerrados, actual->GetHijos()->at(i)->GetID()); // Obtenemos la posición dentro del vector de CERRADOS
                if (posHijoC > -1){  // Está en el vector de cerrados
                    // El valor g(n) del nodo en cerrados es peor (mayor) que
                    // el del nodo dentro del vector de hijos de 'actual'
                    if (CalculaGn(cerrados[posHijoC]) > CalculaGn(actual->GetHijos()->at(i))){
                        cerrados[posHijoC]->SetPadre(actual);    // Cambiamos el padre
                        CalculaFn(cerrados[posHijoC]);
                    }/*else  // DEBUG
                        cout << actual->GetHijos()->at(i)->GetID() << " Está en Cerrados, pero es peor" << endl;   // DEBUG
                    */
                }
                if ((posHijoA == -1)&&(posHijoC == -1)){
                    CalculaFn(actual->GetHijos()->at(i));
                    InsertarOrden(abiertos, actual->GetHijos()->at(i));
                    /*
                    cout << "Insertando " << actual->GetHijos()->at(i)->GetID() << " en abiertos" << endl; // DEBUG
                    for (int i = 0; i < abiertos.size(); i++){
                        cout << abiertos[i]->GetID() << " [" << abiertos[i]->GetFn() << "]." << endl;
                    }
                    */
                }
                nGenerados++;
                //cout << actual->GetHijos()->at(i)->GetID() << endl; // DEBUG
            }
        }
    }
}

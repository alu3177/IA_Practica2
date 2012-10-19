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

/* ****************************************************
 * Métodos que implementan los algoritmos de búsqueda *
 * ****************************************************/

/* BÚSQUEDA PRIMERO EN ANCHURA */
Solucion* Problema::BPA(){
    queue<Nodo*> abiertos;   // Cola con los nodos abiertos sin expandir
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
            Solucion *sol = new Solucion(actual, nGenerados, nExpand, _initID);
            return sol;
        // Expandir el nodo actual
        } else {
            ExpandNode(actual);
            nExpand++;
            for (uint16_t i = 0; i < actual->GetHijos()->size(); i++){
                abiertos.push(actual->GetHijos()->at(i));
                nGenerados++;
            }
        }
    }
    return NULL;
}

/* BÚSQUEDA PRIMERO EN PROFUNDIDAD */
Solucion* Problema::BPP(){
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
            Solucion *sol = new Solucion(actual, nGenerados, nExpand, _initID);
            return sol;
        // Expandir el nodo actual
        } else {
            cerrados.push_back(actual);
            ExpandNode(actual);
            nExpand++;
            for (uint16_t i = actual->GetHijos()->size(); i > 0; i--){

                if ((!isInStack(abiertos, actual->GetHijos()->at(i - 1))) && (!isInVector(cerrados, actual->GetHijos()->at(i - 1)))){
                    abiertos.push(actual->GetHijos()->at(i - 1));
                }
                nGenerados++;
            }
        }
    }
    return NULL;
}



/* MODIFICACIÓN 2 */
// Implementa una BPP iterativa con una profundidad máxima de 5
Solucion* Problema::BPP_mod(){
    stack<Nodo* > abiertos;  // Pila con punteros a nodos abiertos sin expandir
    vector<Nodo* > cerrados; // Array de punteros a nodos cerrados (no son el final)
    uint32_t nGenerados = 1; // Número de nodos generados
    uint32_t nExpand = 1;    // Número de nodos expandidos/analizados (empieza a 1, pues ya hemos generado el nodo raíz)

    
    uint16_t level = 1;    // Nivel (iteración) actual
    uint16_t maxLevel = 5; // Nivel máximo
    
    while (level <= maxLevel){   // BUCLE que repite el algoritmo para cada nivel de profundidad
      // Vaciamos abiertos y cerrados en cada iteración
      while (abiertos.size() >0){
         abiertos.pop();
      }
      cerrados.clear();
      
      // Reinicializamos las variables del algoritmo
      bool finish = false;
      Nodo* n = new Nodo(_initID);    // Puntero para añadir nuevos nodos
                                      // Inicializado al nodo raíz
      Nodo* actual;                   // Puntero al nodo actual
      abiertos.push(n);
      
      while ((abiertos.size() > 0) && (!finish)){
        // Nos aseguramos de que no analizamos ningún nodo por encima del nivel 'level'
        if (abiertos.top()->GetLevel() <= level){
           actual = abiertos.top(); abiertos.pop(); // Leemos el HEAD y lo extraemos
           // Si encontramos el NODO FINAL
           if (actual->GetID() == _endID){
               finish = true;
               Solucion *sol = new Solucion(actual, nGenerados, nExpand, _initID);
               return sol;
           // Expandir el nodo actual
           } else {
               cerrados.push_back(actual);
               ExpandNode(actual);
               nExpand++;
               for (uint16_t i = actual->GetHijos()->size(); i > 0; i--){
   
                   if ((!isInStack(abiertos, actual->GetHijos()->at(i - 1))) && (!isInVector(cerrados, actual->GetHijos()->at(i - 1)))){
                       abiertos.push(actual->GetHijos()->at(i - 1));
                   }
                   nGenerados++;
               }
           }
        } else {
            // Si esa por encima del nivel máximo, lo sacamos de la pila.
            abiertos.pop();
        }
        
      }
      level++;
    }
    return NULL;
}
/* MODIFICACIÓN 2 */






/* BÚSQUEDA A* */
Solucion* Problema::BAE(){
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
            Solucion *sol = new Solucion(actual, nGenerados, nExpand, _initID);
            return sol;
        // Expandir el nodo actual
        } else {
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
                    }
                }
                int posHijoC = isInVector(cerrados, actual->GetHijos()->at(i)->GetID()); // Obtenemos la posición dentro del vector de CERRADOS
                if (posHijoC > -1){  // Está en el vector de cerrados
                    // El valor g(n) del nodo en cerrados es peor (mayor) que
                    // el del nodo dentro del vector de hijos de 'actual'
                    if (CalculaGn(cerrados[posHijoC]) > CalculaGn(actual->GetHijos()->at(i))){
                        cerrados[posHijoC]->SetPadre(actual);    // Cambiamos el padre
                        CalculaFn(cerrados[posHijoC]);
                    }
                }
                if ((posHijoA == -1)&&(posHijoC == -1)){
                    CalculaFn(actual->GetHijos()->at(i));
                    InsertarOrden(abiertos, actual->GetHijos()->at(i));
                }
                nGenerados++;
            }
        }
    }
    return NULL;
}


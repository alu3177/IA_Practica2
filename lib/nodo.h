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

#include <vector>
#include <stdint.h>

using namespace std;

#ifndef NODO_H
#define NODO_H
class Nodo{
    protected:
        uint16_t _id;     // ID del nodo
        uint16_t _level;  // Nivel de profundidad en el árbol
        uint16_t _nHijos; // Número de hijos
        Nodo* _padre;     // Puntero al nodo padre
        vector<Nodo* > _hijos;  // Punteros a nodos hijo
        bool _analizado;  // Indica si hemos analizado (expandido) el nodo  // TODO: Estudiar si hace falta <---
        uint16_t _fn;     // f(n), costo total estimado (sólo se usa en búsquedas informadas)
    public:
        /* Constructor */
        Nodo (uint16_t id = 0, Nodo* father = NULL, uint16_t lvl = 0) : _id(id), _level(lvl), _nHijos(0), _analizado(false){
            _padre = father;
            // Establecemos el nivel (profundidad) del nodo
            if ((_level == 0) && (_padre != NULL))
                    _level = _padre->GetLevel() + 1;
        }

        /* GETTERS */
        inline uint16_t GetID(){ return _id; }
        inline uint16_t GetLevel(){ return _level; }
        inline uint16_t GetFn(){return _fn; }
        inline vector<Nodo* >* GetHijos() { return &_hijos; }
        inline Nodo* GetPadre() { return _padre; }
        /* SETTERS */
        inline void SetFn (uint16_t f) { _fn = f; }
        inline void SetPadre(Nodo* p) { _padre = p; }

        /* OTRAS */
        void AddHijo(Nodo*);
        void Print();

        /* MODIFICACIÓN */
        inline void ClearHijos() { _hijos.clear(); }
        /* MODIFICACIÓN */

};
#endif

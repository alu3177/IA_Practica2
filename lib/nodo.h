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
    public:
        /* Constructor */
        Nodo (uint16_t id = 0, Nodo* father = NULL, uint16_t lvl = 0) : _id(id), _level(lvl), _nHijos(0), _analizado(false){
            _padre = father;
            // Establecemos el nivel (profundidad) del nodo
            if ((_level == 0) && (_padre != NULL))
                    _level = _padre->GetLevel() + 1;
        }


        void AddHijo(Nodo*);

        /* GETTERS */
        inline uint16_t GetID(){ return _id; }
        inline uint16_t GetLevel(){ return _level; }
        inline vector<Nodo* >* GetHijos() { return &_hijos; }
        inline Nodo* GetPadre() { return _padre; }

        /* OTRAS */
        void Print();

        /* SOBRECARGA DE OPERADORES */
        bool operator == (Nodo &n) const{
            cout << this->_id << " == " << n.GetID() <<  " && " << this->_padre->GetID() << " == " << n.GetPadre()->GetID() <<   " && " << this->_level << " == " << n.GetLevel() << endl;  // DEBUG
            return this->_id == n.GetID() && this->_padre->GetID() == n.GetPadre()->GetID() && this->_level == n.GetLevel();
        }

};

#endif

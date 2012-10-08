#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matriz.h"

using namespace std;

#ifndef ARBOL_H
#define ARBOL_H
class Nodo {
    private:
        uint16_t _id;
        vector<Nodo* > _hijos;
        vector<int> _costos;
    public:
        Nodo(uint16_t id){
            _id = id;
        }
};

class Arbol {
};
#endif

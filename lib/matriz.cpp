#include <stdlib.h>
#include <iostream>
#include "matriz.h"

using namespace std;

/* CONSTRUCTOR */
/*
Matriz::Matriz(uint16_t d = 4) : _dim(d){
    _base = (int **) calloc(_dim, sizeof(int *));
    for (uint16_t i = 0; i < _dim; i++)
        _base[i] = (int *) calloc(_dim, sizeof(int));
}
*/

/* GETTER */
// Devuelve el valor en la posición (i,j)
uint32_t Matriz::Get (uint16_t i, uint16_t j){
    if ((i < _dim)&&(j < _dim))
        return _base[i][j];
    return -1;
}

/* SETTER */
// Establece el valor en la posición (i,j) el valor 'value'
void Matriz::Set (uint16_t i, uint16_t j, uint32_t value){
    if ((i < _dim)&&(j < _dim))
        _base[i][j] = value;
}

/* SETDIM */
// Cambia el valor de "_dim" y vuelve a hacer el mapeo de memoria (si el nuevo tamaño es mayor al actual)
// Se pierde la infomación de la matriz (si el nuevo tamaño es mayor al actual)
void Matriz::SetDim (uint16_t d){
    if (_dim < d){
        _dim = d;
        _base = (uint32_t **) calloc(_dim, sizeof(uint32_t *));
        for (uint16_t i = 0; i < _dim; i++)
        _base[i] = (uint32_t *) calloc(_dim, sizeof(uint32_t));
    }else
    _dim = d;
}

/* PRINT */
// Muestra la matriz por pantalla
void Matriz::Print (){
    for (uint16_t i = 0; i < _dim; i++){
        for (uint16_t j = 0; j < _dim; j++){
            cout << _base[i][j] << " ";
        }
        cout << endl;
 }
}

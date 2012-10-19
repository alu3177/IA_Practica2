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

#include <stdint.h>

#ifndef MATRIZ_H
#define MATRIZ_H
class Matriz {
   // Esta clase implementa una matriz cuadrada de numeros enteros
   protected:
        uint32_t **_base; // Vector que almacenará la matriz
        uint16_t _dim;    // Tamaño de la matriz

   public:
   /* CONSTRUCTOR */
      // Constructor por defecto
        Matriz(uint16_t d = 4) : _dim(d){
            _base = (uint32_t **) calloc(_dim, sizeof(uint32_t *));
            for (uint16_t i = 0; i < _dim; i++)
                _base[i] = (uint32_t *) calloc(_dim, sizeof(uint32_t));
        }

   /* GETTER y SETTER */
        uint32_t Get (uint16_t i, uint16_t j);
        void Set (uint16_t i, uint16_t j, uint32_t value);
        void SetDim (uint16_t d);
        inline uint16_t GetDim () { return _dim; }

   /* OTRAS */
        void Print ();
};
#endif

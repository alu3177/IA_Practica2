#include <stdint.h>

#ifndef MATRIZ_H
#define MATRIZ_H
class Matriz {
   // Esta clase implementa una matriz cuadrada de numeros enteros
   protected:
      int **_base;    // Vector que almacenará la matriz
      uint8_t _dim;  // Tamaño de la matriz

   public:
   /* CONSTRUCTOR */
      // Constructor por defecto
      Matriz();

   /* GETTER y SETTER */
      int Get (uint8_t i, uint8_t j);
      void Set (uint8_t i, uint8_t j, int value);
      void SetDim (uint8_t d);

   /* OTRAS */
      void Print ();
};
#endif

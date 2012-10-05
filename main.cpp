#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

/*
   + Tres ficheros, uno para cada matriz (adyacencia, costos y heurística)

   + Fichero de valores Heurísticos:
   
      Es una matriz con estimaciones de las distancias.
      Matriz heurística
   
      4
      0 1 2 2
      pesos pesos pesos estimados
   
   
   
   
   + Los vértices de cada nivel de un árbol van ordenados segun su número, para mantener el orden de las búsquedas.
   
   + Debe preguntar al user los vértices inicial y final.
   + Como salida => El salido encontrado (con cada búsqueda) y cuantos nodos se han explorado.
*/

using namespace std;

#define BUFFSIZE 256
#define SEPARADOR ' '

class Matriz {
   // Esta clase implementa una matriz cuadrada de numeros enteros
   protected:
      int **_base;    // Vector que almacenará la matriz
      uint8_t _dim;  // Tamaño de la matriz

   public:
   /* CONSTRUCTORES */
      // Constructor por defecto
      Matriz(){
         _dim = 4;
         _base = (int **) calloc(_dim, sizeof(int *));
         for (uint16_t i = 0; i < _dim; i++){
            _base[i] = (int *) calloc(_dim, sizeof(int));
         }        
      }
      // Constructor con parámetro (tamaño de matriz)
      Matriz(uint8_t d){
         _dim = d;
         _base = (int **) calloc(_dim, sizeof(int *));
         for (uint16_t i = 0; i < _dim; i++){
            _base[i] = (int *) calloc(_dim, sizeof(int));
         }
      }

   /* GETTER y SETTER */
      // Devuelve el valor en la posición (i,j)
      int Get (uint8_t i, uint8_t j){
         if ((i < _dim)&&(j < _dim)){
            return _base[i][j];
         }
         return -1;
      }
      // Establece el valor en la posición (i,j) el valor 'value'
      void Set (uint8_t i, uint8_t j, int value){
         if ((i < _dim)&&(j < _dim)){
            _base[i][j] = value;
         }
      }
      // Cambia el valor de "_dim" y vuelve a hacer el mapeo de memoria (si el nuevo tamaño es mayor al actual)
      // Se pierde la infomación de la matriz (si el nuevo tamaño es mayor al actual)
      void SetDim (uint8_t d){
         if (_dim < d){
            _dim = d;
            _base = (int **) calloc(_dim, sizeof(int *));
            for (uint16_t i = 0; i < _dim; i++)
               _base[i] = (int *) calloc(_dim, sizeof(int));
         }else
            _dim = d;
      }

   /* OTRAS */
      // Muestra la matriz por pantalla
      void Print (){
         for (uint16_t i = 0; i < _dim; i++){
            for (uint16_t j = 0; j < _dim; j++){
               cout << _base[i][j] << " ";
            }
            cout << endl;
         }
      }
};

/* FUNCIONES AUXILIARES */
void ResetChar (char* str, uint16_t size){
   for (uint16_t i = 0; i < size; i++)
      str[i] = 0;
}

bool IsEmpty (char* str, uint16_t size){
   for (uint16_t i = 0; i < size; i++)
      if (str[i] != 0)
         return false;
   return true;
}

// Lee el fichero 'path' y parsea su contenido dentro de la matriz 'mat'
void ParseFile (char* path, Matriz *mat){
   fstream file;
   char *buff2 = new char[BUFFSIZE];
   string buff;
   bool size = false; // Indica si ya hemos leido el tamaño de la matriz (es decir la primera fila del fichero)
   uint16_t fila, col;  // Indica en que fila/columna nos encontramos
   fila = col = 0;
         
   file.open(path, fstream::in);
   if (file.is_open()){
      // Iteramos por el fichero mientras podamos
      while (file.good()){
         uint16_t i = 0;    // Iterador del Buffer 'buff'
         getline(file, buff);
         
         // Obtención del tamaño de la matriz
         if (!size){
            while (i < buff.size()){
               if (buff[i] != SEPARADOR)
                  buff2[i] = buff[i];
               i++;
            }
            mat->SetDim(atoi(buff2));
            size = true;
            cout << atoi(buff2) << endl;     // DEBUG
            buff.clear();
            ResetChar(buff2, BUFFSIZE);
            
         // Parseo de cada linea de la matriz
         }else{
            uint16_t j = 0; // Iterador del Buffer 'buff2'
            col = 0;        
            while (i <= buff.size()){
               // Copiar en Buffer 2
               // Si no se trata de un SEPARADOR o del último caracter
               if ((buff[i] != SEPARADOR)&&(i < buff.size())){
                  buff2[j] = buff[i];
                  j++;
               // Introducir numero en la matriz
               }else if (!IsEmpty(buff2, BUFFSIZE)){
                  mat->Set(fila, col, atoi(buff2));
                  col++;
                  ResetChar (buff2, BUFFSIZE);
                  j = 0;
               }
               i++;
            }
            fila++;
         }
      }
   }
}

int main (){

   Matriz *mat = new Matriz();
   
   ParseFile("datos/binary.dat", mat);
   mat->Print();
   ParseFile("datos/pesos.dat", mat);
   mat->Print();

   return 0;
}


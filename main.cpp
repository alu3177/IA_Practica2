#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

#include "lib/matriz.h"
#include "lib/problema.h"

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

/*
// Lee el fichero 'path' y parsea su contenido dentro de la matriz 'mat'
void ParseFile (char* path, Matriz* &mat){
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
            mat = new Matriz(atoi(buff2));
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
                  //cout << "Insertando: " << atoi(buff2) << endl;    // DEBUG
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
*/

int main (){

    Problema* prob = new Problema(1, 14);
    prob->BPA();
    prob->BPP();


/*
    vector<Nodo* > st;
    Nodo* n = new Nodo(1);
    Nodo* n1 = new Nodo(2, n);
    Nodo* n2 = new Nodo(3, n);
    st.push_back(n1);
    cout << st.size() << endl;
    cout << prob->isInVector(st, n1) << endl;
    cout << st.size() << endl;
*/

    /*
    Nodo* n = new Nodo(1);
    prob->ExpandNode(n);
    n->Print();
    n = new Nodo(2, n);
    prob->ExpandNode(n);
    n->Print();
    n = new Nodo(5, n);
    prob->ExpandNode(n);
    n->Print();
    n = new Nodo(6, n);
    prob->ExpandNode(n);
    n->Print();
    */
/*
   Nodo* node = new Nodo(1);
   Nodo* tmp = new Nodo(2, node);
   node->AddHijo(tmp);
   tmp = new Nodo(3, node);
   node->AddHijo(tmp);
   tmp = new Nodo(8, node);
   node->AddHijo(tmp);
   Nodo* tmp2 = new Nodo(4, tmp);
   tmp->AddHijo(tmp2);

   node->Print();
   node->GetHijos()->at(0)->Print();
   node->GetHijos()->at(1)->Print();
   node->GetHijos()->at(2)->Print();
   tmp->GetHijos()->at(0)->Print();

   //cout << sizeof(Nodo*) << ", " << sizeof(uint16_t) << endl;
*/
   return 0;
}


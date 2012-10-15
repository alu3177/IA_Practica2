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
    cout << "Búsqueda Primero en Anchura" << endl;
    prob->BPA();
    cout << endl << "Búsqueda Primero en Profundidad" << endl;
    prob->BPP();
    cout << endl << "Búsqueda A*" << endl;
    prob->BAE();

/*
    Nodo n1(1);
    Nodo n2(2, &n1);
    Nodo n3(3, &n1);

    n1.SetFn(9);
    n2.SetFn(7);
    n3.SetFn(8);

    list<Nodo > lst;
    lst.push_back(n3);
    lst.push_back(n2);
    lst.push_back(n1);
    lst.push_back(n3);

    list<Nodo >::iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
        cout << *it << " ";
    cout << endl;

    lst.sort();

    for (it = lst.begin(); it != lst.end(); ++it)
        cout << *it << " ";
    cout << endl;
*/

/*
    vector<Nodo* > st;
    Nodo* n = new Nodo(1);
    Nodo* n1 = new Nodo(2, n);
    Nodo* n2 = new Nodo(3, n);

    n->SetFn(30);
    n1->SetFn(75);
    n2->SetFn(105);

    st.push_back(n);
    st.push_back(n1);
    st.push_back(n2);

    for (int i = 0; i < st.size(); i++){
        cout << st[i]->GetID() << " [" << st[i]->GetFn() << "]." << endl << "###########" << endl;
    }

    n2 = new Nodo(4, n);
    n2->SetFn(10);
    prob->InsertarOrden(st, n2);
    n2 = new Nodo(5, n);
    n2->SetFn(70);
    prob->InsertarOrden(st, n2);
    n2 = new Nodo(6, n);
    n2->SetFn(25);
    prob->InsertarOrden(st, n2);
    n2 = new Nodo(7, n);
    n2->SetFn(110);
    prob->InsertarOrden(st, n2);
    n2 = new Nodo(8, n);
    n2->SetFn(75);
    prob->InsertarOrden(st, n2);

    for (int i = 0; i < st.size(); i++){
        cout << st[i]->GetID() << " [" << st[i]->GetFn() << "]." << endl;
    }
*/


/*
    cout << st.size() << endl;
    cout << prob->isInVector(st, n1) << endl;
    cout << st.size() << endl;
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

    cout << "f(4): " << prob->CalculaFn(tmp2) << endl;
*/
   //cout << sizeof(Nodo*) << ", " << sizeof(uint16_t) << endl;

   return 0;
}


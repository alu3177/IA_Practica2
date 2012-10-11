#include <stdlib.h>
#include <fstream>

using namespace std;

#define BUFFSIZE 256
#define SEPARADOR '	'

/* FUNCIONES AUXILIARES de manejo de char* */
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

/* Lee el fichero 'path' y parsea su contenido dentro
   de la matriz 'mat' */
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
            //cout << atoi(buff2) << endl;     // DEBUG
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

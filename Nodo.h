#ifndef NODOAB_H
#define NODOAB_H

#include <string>
#include <sstream>

using namespace std;

template<class T>
class Nodo
{
    public:
        T info;
        Nodo<T> *esq, *dir, *cima, *baixo, *pai;

        Nodo(){
            esq=dir=cima=baixo=pai=NULL;
        }

        Nodo(T inf)
        {
            esq=dir=cima=baixo=pai=NULL;
            info=inf;
        }

        void set_info(T inf)
        {
            info=inf;
        }

        string toString()
        {
            ostringstream aux;

            aux << info;

            return aux.str();
        }
};

#endif

#ifndef Arvore_H
#define Arvore_H

#include "Nodo.h"
#include <sstream>

using namespace std;

template<class T>
class Arvore
{
	private:
		Nodo<T>* raiz;
	public:
        Arvore()
        {
            raiz = NULL;
        }

        void set_raiz(Nodo<T>* no)
        {
            raiz = no;
        }

        Nodo<T>* get_raiz()
        {
            return raiz;
        }

        bool vazia()
        {
            bool ret=false;
            if(raiz == NULL)
                ret = true;
            return ret;
        }

        int tamanho()
        {
            return tamanho(raiz);
        }

        int tamanho(Nodo<T>* no)
        {
            if(no == NULL)
                return 0;
            else
                return 1 + tamanho(no->esq) + tamanho(no->dir) + tamanho(no->cima) + tamanho(no->baixo);
        }

        int altura()
        {
            return altura(raiz);
        }

        int altura(Nodo<T>* no)
        {
            int alte, altd;

            if(no == NULL)
                return -1;
            else {
                   alte = altura(no->esq);
                   altd = altura(no->dir);
                   return maior(alte,altd) + 1; /* if(alte > altd) return(alte + 1) else if return(altd + 1) */
            }
        }

        int maior(int aE,int aD)
        {
            int ret=0;

            if(aE > aD)
                ret=(aE + 1);
            else
                ret=(aD + 1);

            return ret;
        }

        Nodo<T>* pesquisar(T atributo)
        {
            return pesquisar(atributo,raiz);
        }

        Nodo<T>* pesquisar(T atributo,Nodo<T>* no)
        {
            Nodo<T> *aux=NULL;

            if(no!=NULL)
            {
                if(no->info.getX() == atributo.getX()&&no->info.getY() == atributo.getY())
                {
                    return no;
                } else {
                    aux = pesquisar(atributo,no->cima);
                    if(aux==NULL)
                    {
                        aux=pesquisar(atributo,no->baixo);
                        if(aux==NULL)
                        {
                            aux=pesquisar(atributo,no->esq);
                            if(aux==NULL)
                            {
                                aux=pesquisar(atributo,no->dir);
                            }
                        }
                    }
                    return aux;
                }
            }
        }

        bool jaExiste(T atributo)
        {
            bool ret=false;
            Nodo<T> *no;
            no=pesquisar(atributo);
            if(no!=NULL) ret=true;

            return ret;
        }

        ~Arvore()
        {
            destruir(raiz);
        }

        void destruir(Nodo<T>* no)
        {
            if(no!=NULL)
            {
                destruir(no->esq);
                destruir(no->dir);
                destruir(no->cima);
                destruir(no->baixo);
                delete no;
            }
        }

        string toString()
        {
            string tab;
            int tam=(this->tamanho(raiz))/2;
            ostringstream aux;

            for(int i=0;i<tam;i++) tab=tab+"\t";

            aux<<tab<<raiz->toString()<<'\n';
            aux<<this->toString(raiz->esq,tam-1)<<'\t';
            aux<<this->toString(raiz->cima,tam-1)<<'\t';
            aux<<this->toString(raiz->baixo,tam-1)<<'\t';
            aux<<this->toString(raiz->dir,tam-1)<<'\n';


            return aux.str();
        }

        string toString(Nodo<T>* no,int tam)
        {
            string tab;
            ostringstream aux;

            for(int i=0;i<tam;i++) tab=tab+"\t";

            if(no!=NULL)
            {
                aux<<tab<<no->toString()<<'\n';
                aux<<toString(no->esq,tam-1)<<'\t';
                aux<<this->toString(raiz->cima,tam-1)<<'\t';
                aux<<this->toString(raiz->baixo,tam-1)<<'\t';
                aux<<toString(no->dir,tam-1)<<'\n';
            }

            return aux.str();
        }
};

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "NoAVL.h"

using namespace std;

class ArvoreAVL{

    public:
        ArvoreAVL();
        ~ArvoreAVL();
        void insere(int chave);
        // procura chave 
        bool busca(int chave);
        void limpa();
        void imprime();
    private:
        // Raiz da arvore
        NoAVL* raiz;
        // indica se deve balancear ou nao
        bool balancear;
        inline NoAVL::Direction oposto(NoAVL::Direction dir);
        // Inserção e remoção recursivos
        void insere(int chave, NoAVL*& no, bool& balancear);
        bool remove(int chave, NoAVL*& no, bool& balancear);
        // balanceamento
        void rotacionaUmaVez(NoAVL*& no, NoAVL::Direction dir);
        void rotacionaDuasVezes(NoAVL*& no, NoAVL::Direction dir);
        void atualizaBalancear(NoAVL* no, NoAVL::Direction dir);
        void rebalancearInsere(NoAVL*& node, NoAVL::Direction dir, bool& balancear);
        void printAVL(const string& prefix, const NoAVL* no, bool isLeft);
};
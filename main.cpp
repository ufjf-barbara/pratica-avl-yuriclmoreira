
#include <iostream>
#include "ArvoreAVL.h"

using namespace std;

int main() {
    cout << "Arvore AVL!\n" << "Informe as chaves (inteiras) ou -1 para sair:\n";
    ArvoreAVL avl;
    int chave;
    scanf("%d", &chave);
    while(chave!=-1){
        avl.insere(chave);
        scanf("%d",&chave);
    }    
    avl.imprime();

}
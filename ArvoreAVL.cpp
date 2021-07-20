#include "ArvoreAVL.h"

using namespace std;

ArvoreAVL::ArvoreAVL(){
    this->raiz = NULL;
}    

ArvoreAVL::~ArvoreAVL(){
    this->limpa();
} 

void ArvoreAVL::limpa(){
    delete raiz;
    this->raiz = NULL;
} 

bool ArvoreAVL::busca(int chave){
    NoAVL* atual = this->raiz;

    while(atual != NULL){
        // compara
        if(chave > atual->chave)
            atual = atual->sub[NoAVL::DIR];
        else if(chave < atual->chave)
            atual = atual->sub[NoAVL::ESQ];
        else
            return true;
    }
    return false;
} 

// Retorna a direção oposta à direção dada

inline NoAVL::Direction ArvoreAVL::oposto(NoAVL::Direction dir){
    return (dir == NoAVL::DIR) ? NoAVL::ESQ : NoAVL::DIR;
}

// Realiza uma rotação simples numa determinada direção.  aceita como parâmetro um nó onde a operação será efetuada e uma direção (esquerda ou direita) para realizar a rotação.
void ArvoreAVL::rotacionaUmaVez(NoAVL*& no, NoAVL::Direction dir){
    int oposto = this->oposto(dir);
    NoAVL* filho = no->sub[dir];
    no->sub[dir] = filho->sub[oposto];
    filho->sub[oposto] = no;
    no = filho;
}

// Realiza uma rotação dupla numa determinada direção.  aceita como parâmetro um nó onde a operação será efetuada  e uma direção (esquerda ou direita) para realizar a rotação.
void ArvoreAVL::rotacionaDuasVezes(NoAVL*& no, NoAVL::Direction dir){
    int oposto = this->oposto(dir);
    NoAVL* filho = no->sub[dir]->sub[oposto];
    no->sub[dir]->sub[oposto] = filho->sub[dir];
    filho->sub[dir] = no->sub[dir];
    no->sub[dir] = filho;
    filho = no->sub[dir];
    no->sub[dir] = filho->sub[oposto];
    filho->sub[oposto] = no;
    no = filho;
}

// Atualiza os fatores de balanceamento após uma rotação

void ArvoreAVL::atualizaBalancear(NoAVL* no, NoAVL::Direction dir){
    int oposto = this->oposto(dir);
    int bal = no->sub[dir]->sub[oposto]->balanco;
    // Se o fator está pesado no mesmo lado
    if (bal == dir){
        no->balanco = NoAVL::IGUAL;
        no->sub[dir]->balanco = oposto;
    }
    // Se o fator está pesado do lado oposto
    else if (bal == oposto){
        no->balanco = dir;
        no->sub[dir]->balanco = NoAVL::IGUAL;
    }else // O fator de balanceamento está igual
    {
        no->balanco = no->sub[dir]->balanco = NoAVL::IGUAL;
    }
    no->sub[dir]->sub[oposto]->balanco = NoAVL::IGUAL;

} 

// Efetua o rebalanceamento após uma operação de inserção
void ArvoreAVL::rebalancearInsere(NoAVL*& no, NoAVL::Direction dir, bool& balancear){
    int oposto = this->oposto(dir);
    // Se o fator de balanceamento do nó era
    //  igual a direção em que houve a inserção,
    if (no->balanco == dir) // (ou seja o nó foi inserido
    {   //  na subárvore de maior altura
        // Temos 2 casos:
        if (no->sub[dir]->balanco == dir)
        {
            no->sub[dir]->balanco = 2;
            no->balanco = NoAVL::IGUAL;
            // Precisamos fazer uma rotação
            rotacionaUmaVez(no, dir);
        }
        else // Seu filho estava equilibrado ou
        {    //  pendendo para o lado oposto,
            atualizaBalancear(no, dir);
            rotacionaDuasVezes(no, dir);
        }
        balancear = false;
    }
    // Já se foi exatamente o oposto,
    else if (no->balanco == oposto)
    { // O nó agora está balanceado
        no->balanco = 2;
        balancear = false;
    }
    else // Se não, o nó já estava equilibrado
    { // e agora seu equilibrio foi deslocado.
        no->balanco = dir;
    }
}

// Insere um novo item na árvore 
void ArvoreAVL::insere(int chave){
    bool balancear = false; // Para passagem por referência
    // Chamamos o método recursivo para realizar a operação
    this->insere(chave, this->raiz, balancear);
}

// Insere um novo item na árvore (recursivo)
void ArvoreAVL::insere(int chave, NoAVL*& no, bool& balancear){   // Se o nó atual é nulo,
    if (no == NULL)
    {   // é aqui mesmo onde vamos inserir
        no = new NoAVL(chave);
        // marcamos que a altura mudou, é
        //  preciso chegar o balanceamento
        balancear = true;
    }
    else if (no->chave == chave)
    {
        // A informação já estava na árvore
        return;
    }
    else // Ainda não chegamos onde queríamos
    {// Prosseguimos com a pesquisa binária
        NoAVL::Direction dir = (chave > no->chave) ? NoAVL::DIR : NoAVL::ESQ;
        balancear = false; // preparamos e chamamos recursão
        insere(chave, no->sub[dir], balancear);
        if (balancear) // Se a altura mudou,
        {// Efetuamos o rebalanceamento
            this->rebalancearInsere(no, dir, balancear);
        }
    }
}

void ArvoreAVL::printAVL(const string& prefix, const NoAVL* no, bool isLeft){
    if(no != nullptr ){
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        // print the value of the node
        cout << no->chave << endl;
        // enter the next tree level - left and right branch
        printAVL( prefix + (isLeft ? "│   " : "    "), no->sub[NoAVL::ESQ], true);
        printAVL( prefix + (isLeft ? "│   " : "    "), no->sub[NoAVL::DIR], false);
    }
}

void ArvoreAVL::imprime(){
    printAVL("", this->raiz, false);    
}



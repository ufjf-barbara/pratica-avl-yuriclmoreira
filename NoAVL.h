// TAD para no da arvore AVL  
// http://crsouza.com/2008/11/22/arvore-avl-em-c/
using namespace std;

class NoAVL{
    public:
        // Enumeração para acesso às subárvores e direção de procura da pesquisa binária. Serve também para indicar o fator de balanceamento dos nós.
        enum Direction{ESQ = 0,DIR = 1, IGUAL = 2};

        NoAVL(int c){
            this->chave = c;
            this->sub[ESQ] = NULL;
            this->sub[DIR] = NULL;
            this->balanco = IGUAL;
        }

        // valor a ser armazenado
        int chave;
        // Filhos da arvore - subarvores esquerda e direita. Para acessar: ->sub[ESQ] e sub[DIR]
        NoAVL* sub[2];
        // balanceamento do no
        unsigned short balanco;
};
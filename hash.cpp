#include "hash.h"

// LOOK FOR THE COMMENTS IN THE .H 
// TO UNDERSTAND WHAT EACH FUNCTION MUST DO

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
 // CONSTRUTOR
    _hash_func = hf;
    _table.resize(tablesize);
}

int Hash::add(std::string str, int &collisions) { 
    if (contains(str, collisions) == 1){
        return 0;
    }

    else{
        _table[_hash_func(str)].push_front(str);
        return 1;
    }
    // porque existe 'return 0' neste codigo? 
    // para executar os testes, mesmo falhando, eh preciso compilar
    // assim, eh preciso retornar algum valor.
    // ** o aluno deve implementar a funcao completa e retornar o valor correto **

}//add

int Hash::remove(std::string str, int &collisions) { 
    if (contains(str, collisions) == 1){
        _table[_hash_func(str)].remove(str);
        return 1;
    }
    else{
        return 0;        
    }
}//remove


int Hash::hash(std::string str) { 
    int i = (*_hash_func)(str);
    return i;
}//hash
    
int Hash::contains(std::string str, int &collisions) { 
    int posicao = 0;
    int num_colisoes = 0;
    posicao = this->hash(str);
    collisions = 0;

    if(_table[posicao].empty()){
        collisions = 0;
        return 0;
    }
    else{
        for(std::string test : _table[posicao]){
            collisions += 1;
            if(str.compare(test)==0){
                return 1;
            }
        }
    }

    return 0;
}//contains


int Hash::worst_case() {
    int tamanho = this->_table.size();
    int maior = 0;
    int contador = 0;
    int i;
    for(i=0; i<tamanho; i++){
        contador = 0;
        if(!this->_table[i].empty()){
            for(std::string i: this->_table[i]){
                contador += 1;
            }
        }
        if(contador > maior){
            maior = contador;
        }
    }
    return maior;
}//worst_case

int Hash::size() {
    int tamanho = 0;
    for(auto i = 0; i < _table.size(); i++){
        for (auto j = _table[i].begin(); j != _table[i].end(); j++){
            tamanho += 1;
        }
    }
    return tamanho;
}//size

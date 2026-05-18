#include "Usuario.hpp"
using namespace std;
Usuario::Usuario(){
    nome = "";
    id = -1;
    idade = 0;
}
Usuario::Usuario(string nome, int id, int idade){
    this->nome = nome;
    this->id = id;
    this->idade = idade;
}

string Usuario::get_nome()const{
    return nome;
}
int Usuario::get_id()const{
    return id;
}
int Usuario::get_idade()const{
    return idade;
}

void Usuario::set_nome(string nome){
    this->nome = nome;
}
void Usuario::set_id(int id){
    this->id = id;
}
void Usuario::set_idade(int idade){
    this->idade = idade;
}
#include "Tema.hpp"
using namespace std;

Tema::Tema(){
    nome = "";
    id = -1;
    tipo = '\0';
}

Tema::Tema(string nome, int id, char tipo){
    this->nome = nome;
    this->id = id;
    this->tipo = tipo;
}

string Tema::get_nome()const{
    return nome;
}

int Tema::get_id()const{
    return id;
}
char Tema::get_tipo()const{
    return tipo;
}

void Tema::set_nome(string nome){
    this->nome = nome;
}
void Tema::set_id(int id){
    this->id = id;
}
void Tema::set_tipo(char tipo){
    this->tipo = tipo;
}
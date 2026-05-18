#include "No.hpp"

No::No(){
    id = -1;
    tipo = '\0';
}
No::No(int id, char tipo){
    this->id = id;
    this->tipo = tipo;
}

int No::get_id() const{
    return id;
}
char No::get_tipo() const{
    return tipo;
}

void No::set_id(int id){
    this->id = id;
}
void No::set_tipo(char tipo){
    this->tipo = tipo;
}
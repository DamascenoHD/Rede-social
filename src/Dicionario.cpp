#include "Dicionario.hpp"
Dicionario::Dicionario(){
    capacidade = 0;
    quantidade_usuarios = 0;
    quantidade_temas = 0;
    qnt_nos_social = 0;
    qnt_nos_usuario_tema = 0;
    qnt_nos_temas = 0;
    usuarios = nullptr;
    temas = nullptr;
    nos_social = nullptr;
    nos_usuario_tema = nullptr;
    nos_temas = nullptr;
}
Dicionario::Dicionario(int capacidade){
    this->capacidade = capacidade;
    quantidade_usuarios = 0;
    quantidade_temas = 0;
    qnt_nos_social = 0;
    qnt_nos_usuario_tema = 0;
    qnt_nos_temas = 0;
    usuarios = new Usuario[capacidade];
    temas = new Tema[capacidade];
    nos_social = new No[capacidade];
    nos_usuario_tema = new No[capacidade];
    nos_temas = new No[capacidade];
}
Dicionario::~Dicionario(){
    delete[] usuarios;
    delete[] temas;
    delete[] nos_social;
    delete[] nos_usuario_tema;
    delete[] nos_temas;
}

Usuario Dicionario::recuperar_usuario(int id_usuario)const{
    return usuarios[id_usuario];
}
Tema Dicionario::recuperar_tema(int id_tema)const{
    return temas[id_tema];
}
No Dicionario::recuperar_no_usuario_social(int id)const{
    return nos_social[id];
}
No Dicionario::recuperar_no_usuario_temas(int id)const{
    return nos_usuario_tema[id];
}
No Dicionario::recuperar_no_tema_temas(int id)const{
    return nos_temas[id];
}

void Dicionario::inserir_usuario(Usuario usuario){
    usuarios[quantidade_usuarios] = usuario;//provavelmente vai ter que fazer a sobrecarga do operador 
    quantidade_usuarios++;
}
void Dicionario::inserir_tema(Tema tema){
    temas[quantidade_temas] = tema;
    quantidade_temas++;
}
void Dicionario::inserir_no_social(No no_social){
    nos_social[qnt_nos_social] = no_social;
    qnt_nos_social++;
}
void Dicionario::inserir_no_usuario_tema(No no_user_tema){
    nos_usuario_tema[qnt_nos_usuario_tema]=no_user_tema;
    qnt_nos_usuario_tema++;
}
void Dicionario::inserir_no_tema(No no_tema){
    nos_temas[qnt_nos_temas] = no_tema;
    qnt_nos_temas++;
}
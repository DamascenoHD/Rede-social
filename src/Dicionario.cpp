#include "Dicionario.hpp"
Dicionario::Dicionario(){
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

Dicionario::~Dicionario(){
    delete[] usuarios;
    delete[] temas;
    delete[] nos_social;
    delete[] nos_usuario_tema;
    delete[] nos_temas;
}

Usuario Dicionario::recuperar_usuario(int id_usuario)const{
    if(id_usuario < 0 || id_usuario >= quantidade_usuarios)
        return Usuario();//interessante mas não necessário pro TP
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
    Usuario* novo_usuarios = new Usuario[quantidade_usuarios+1];
    for(int i=0; i<quantidade_usuarios; i++){
        novo_usuarios[i] = usuarios[i];
    }
    novo_usuarios[quantidade_usuarios] = usuario;
    delete[] usuarios;
    usuarios = novo_usuarios;
    quantidade_usuarios++;
}
void Dicionario::inserir_tema(Tema tema){
    Tema* novo_temas = new Tema[quantidade_temas+1];
    for(int i=0; i<quantidade_temas; i++){
        novo_temas[i] = temas[i];
    }
    novo_temas[quantidade_temas] = tema;
    delete[] temas;
    temas = novo_temas;
    quantidade_temas++;
}
void Dicionario::inserir_no_social(No no_social){
    No* novo_nos_social = new No[qnt_nos_social+1];
    for(int i=0; i<qnt_nos_social; i++){
        novo_nos_social[i] = nos_social[i];
    }
    novo_nos_social[qnt_nos_social] = no_social;
    delete[] nos_social;
    nos_social = novo_nos_social;
    qnt_nos_social++;
}
void Dicionario::inserir_no_usuario_tema(No no_user_tema){
    No* novo_nos_user_tema = new No[qnt_nos_usuario_tema+1];
    for(int i=0; i<qnt_nos_usuario_tema; i++){
        novo_nos_user_tema[i] = nos_usuario_tema[i];
    }
    novo_nos_user_tema[qnt_nos_usuario_tema] = no_user_tema;
    delete[] nos_usuario_tema;
    nos_usuario_tema = novo_nos_user_tema;
    qnt_nos_usuario_tema++;
}
void Dicionario::inserir_no_tema(No no_tema){
    No* novo_nos_tema = new No[qnt_nos_temas+1];
    for(int i=0; i<qnt_nos_temas; i++){
        novo_nos_tema[i] = nos_temas[i];
    }
    novo_nos_tema[qnt_nos_temas] = no_tema;
    delete[] nos_temas;
    nos_temas = novo_nos_tema;
    qnt_nos_temas++;
}

int Dicionario::get_qnt_temas(){
    return quantidade_temas;
}
int Dicionario::get_qnt_usuarios(){
    return quantidade_usuarios;
}
int Dicionario::get_qnt_nos_social(){
    return qnt_nos_social;
}
int Dicionario::get_qnt_nos_usuario_tema(){
    return qnt_nos_usuario_tema;
}

int Dicionario::get_qnt_nos_temas(){
    return qnt_nos_temas;
}

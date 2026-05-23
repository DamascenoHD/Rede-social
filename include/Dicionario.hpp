#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP
#include "Usuario.hpp"
#include "Tema.hpp"
#include "No.hpp"
class Dicionario{
    private:
        int quantidade_usuarios;
        int quantidade_temas;
        int qnt_nos_social;
        int qnt_nos_usuario_tema;
        int qnt_nos_temas;

        Usuario* usuarios;
        Tema* temas;
        No* nos_social;
        No* nos_usuario_tema;
        No* nos_temas;
    public:
        Dicionario();
        ~Dicionario();

        Usuario recuperar_usuario(int id_usuario)const;
        Tema recuperar_tema(int id_tema)const;
        No recuperar_no_usuario_social(int id)const;
        No recuperar_no_usuario_temas(int id)const;
        No recuperar_no_tema_temas(int id)const;

        void inserir_usuario(Usuario usuario);
        void inserir_tema(Tema tema);
        void inserir_no_social(No no_social);
        void inserir_no_usuario_tema(No no_user_tema);
        void inserir_no_tema(No no_tema);

        int get_qnt_temas();
        int get_qnt_usuarios();
        int get_qnt_nos_social();
        int get_qnt_nos_usuario_tema();
        int get_qnt_nos_temas();

};

#endif
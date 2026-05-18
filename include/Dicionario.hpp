#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP
#include "Usuario.hpp"
#include "Tema.hpp"
#include "No.hpp"
class Dicionario{
    private:
        Usuario* usuarios;
        Tema* temas;

        No* nos_social;
        No* nos_usuario_tema;
        No* nos_tema;
    public:
        Dicionario();
        ~Dicionario();

        Usuario recuperar_usuario(int id_usuario);
        Tema recuperar_tema(int id_tema);
        No recuperar_no_usuario_social(int id);
        No recuperar_no_usuario_temas(int id);
        No recuperar_no_tema_temas(int id);
};

#endif
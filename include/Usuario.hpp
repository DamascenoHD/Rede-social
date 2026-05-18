#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

class Usuario{
    private:
        std::string nome;
        int id;
        int idade;
    public:
        Usuario();
        Usuario(std::string nome, int id, int idade);
        

        std::string get_nome()const;
        int get_id()const;
        int get_idade()const;

        void set_nome(std::string nome);
        void set_id(int id);
        void set_idade(int idade);
};
#endif
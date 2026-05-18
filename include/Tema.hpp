#ifndef TEMA_HPP
#define TEMA_HPP
#include <string>

class Tema{
    private:
        std::string nome;
        int id;
        char tipo;
    public:
        Tema();
        Tema(std::string nome, int id, char tipo);
        

        std::string get_nome()const;
        int get_id()const;
        char get_tipo()const;

        void set_nome(std::string nome);
        void set_id(int id);
        void set_tipo(char tipo);
};
#endif
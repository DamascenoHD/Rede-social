#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include "Grafo.hpp"
#include "No.hpp"
#include "Dicionario.hpp"
#include "Tema.hpp"
#include "Usuario.hpp"

using namespace std;

int main() {
    std::string linha;
    Grafo grafo_social;
    Grafo grafo_temas;
    Dicionario dicionario;
    char modo = '\0';
    char representacao = '\0';
    while (std::getline(std::cin, linha)) {
        std::stringstream ss(linha);
        char tipo;
        if (!(ss >> tipo)) continue;
        if(tipo == 'A'){
            if(!(ss >> representacao)){
                continue;
            }
            cout << "A" << representacao << endl;
        }else if(tipo == 'T'){
            string nome;
            char tipo_tema;
            ss >> nome;
            ss >> tipo_tema;
            Tema tema = Tema(nome, dicionario.get_qnt_temas(), tipo_tema);
            dicionario.inserir_tema(tema);
            No no_tema(tema.get_id(), 'T');
            cout << "T" << tema.get_id() << endl;
        }else if(tipo == 'U'){
            string nome;
            int idade;
            ss >> nome >> idade;
            Usuario usuario(nome, dicionario.get_qnt_usuarios(), idade);
            dicionario.inserir_usuario(usuario);
            No no_usuario(usuario.get_id(), 'U');
            dicionario.inserir_no_social(no_usuario);
            dicionario.inserir_no_usuario_tema(no_usuario);
            grafo_social.inserir_vertice(no_usuario);
            grafo_temas.inserir_vertice(no_usuario);

            int id_tema;

            while(ss >> id_tema){
                if(id_tema >= 0 && id_tema < dicionario.get_qnt_temas()){
                    grafo_temas.inserir_aresta(usuario.get_id(), id_tema);
                }
            }
        cout << "U " << usuario.get_id() << endl;

        }else if(tipo=='S'){
        
        }else if(tipo == 'R'){

        }else if(tipo == 'L'){
            char subtipo;
            ss >> subtipo;
            if(subtipo == 'T'){

            }else if (subtipo == 'C'){

            }else if(subtipo == 'S'){

            }else if(subtipo == 'A'){

            }
        }else if(tipo == 'Q'){

        }else if(tipo == 'G'){

        }else if(tipo == 'F'){

        }
        
        
    }

}
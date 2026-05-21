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
            int id_1, id_2;
            ss >> id_1 >> id_2;
            grafo_social.inserir_aresta(id_1, id_2);
        }else if(tipo == 'R'){
            int id_1, id_2;
            ss >> id_1 >> id_2;
            grafo_social.remover_aresta(id_1, id_2);//a remoção da aresta é direcionada, talvez seja necessário mudar
        }else if(tipo == 'L'){
            char subtipo;
            int id_usuario;
            ss >> subtipo;
            if(subtipo == 'T'){
                ss >> id_usuario;
                //adicionar função listar em grafos
            }else if (subtipo == 'C'){
                ss >> id_usuario;
                //adicionar função listar em grafos
            }else if(subtipo == 'S'){
                ss >> id_usuario;
                //adicionar função listar em grafos
            }else if(subtipo == 'A'){
                ss >> id_usuario;
                //adicionar função listar em grafos
            }
        }else if(tipo == 'Q'){
            int id_1, id_2;
            int valor = 0;
            ss >> id_1 >> id_2;
            bool um_segue_2, dois_segue_1;
            um_segue_2 = grafo_social.existe_aresta(id_1, id_2);
            dois_segue_1 = grafo_social.existe_aresta(id_2, id_1);
            if(um_segue_2 ^ dois_segue_1){
                valor = 1;
            }else if(um_segue_2 && dois_segue_1){
                valor = 2;
            }
            cout << "Q " << dicionario.recuperar_usuario(id_1).get_nome() << " " << dicionario.recuperar_usuario(id_2).get_nome() << endl;
        }else if(tipo == 'G'){
             int id_usuario, id_tema;
             int valor = 0;
             ss >> id_usuario >> id_tema;
             if(grafo_temas.existe_aresta(id_usuario, id_tema))
                valor = 1;
            cout << "G " << dicionario.recuperar_usuario(id_usuario).get_nome() << " " << dicionario.recuperar_tema(id_tema).get_nome() << endl;
        }else if(tipo == 'F'){
            int id_tema;
            int quantidade = 0;
            ss >> id_tema;
            //fazer função que retorna quantos vértices to ligados nessa aresta
            cout << "F " << dicionario.recuperar_tema(id_tema).get_nome() << " " << quantidade << endl;
        }
        
        
    }

}
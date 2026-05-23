#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Grafo.hpp"
#include "No.hpp"
#include "Dicionario.hpp"
#include "Tema.hpp"
#include "Usuario.hpp"

using namespace std;

int main() {

    // Verifica se o nome do arquivo foi passado
    /*
    if(argc < 2){
        cerr << "Uso: ./programa <arquivo_entrada>" << endl;
        return 1;
    }

    // Abre o arquivo
    ifstream arquivo(argv[1]);
    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }
    
    */
    string linha;

    Grafo grafo_social;
    Grafo grafo_temas;
    Dicionario dicionario;

    char representacao = '\0';
    bool primeira_representacao = true;

    // Agora lê do arquivo em vez do cin
    while (getline(cin, linha)) {

        stringstream ss(linha);

        char tipo;

        if (!(ss >> tipo))
            continue;

        if(tipo == 'A'){

            ss >> representacao;

            if(primeira_representacao){

                grafo_social.configurar(true, representacao);
                grafo_temas.configurar(false, representacao);

                primeira_representacao = false;

            }else{

                grafo_social.mudar_representacao(representacao);
                grafo_temas.mudar_representacao(representacao);
            }

            cout << "A " << representacao << endl;

        }else if(tipo == 'T'){

            string nome;
            char tipo_tema;

            ss >> nome;
            ss >> tipo_tema;

            Tema tema(nome, dicionario.get_qnt_temas(), tipo_tema);

            dicionario.inserir_tema(tema);

            No no_tema(tema.get_id()*2+1, 'T');

            grafo_temas.inserir_vertice(no_tema);

            cout << "T " << tema.get_id() << endl;

        }else if(tipo == 'U'){

            string nome;
            int idade;

            ss >> nome >> idade;

            Usuario usuario(nome, dicionario.get_qnt_usuarios(), idade);
            dicionario.inserir_usuario(usuario);

            No no_usuario_social(usuario.get_id(), 'U');
            grafo_social.inserir_vertice(no_usuario_social);
            dicionario.inserir_no_social(no_usuario_social);

            No no_usuario_tema(usuario.get_id()*2, 'U');
            grafo_temas.inserir_vertice(no_usuario_tema);
            dicionario.inserir_no_usuario_tema(no_usuario_tema);

            int id_tema;

            while(ss >> id_tema){

                if(id_tema >= 0 && id_tema < dicionario.get_qnt_temas()){

                    grafo_temas.inserir_aresta(usuario.get_id()*2, id_tema*2+1);
                }
            }

            cout << "U " << usuario.get_id() << endl;

        }else if(tipo == 'S'){

            int id_1, id_2;

            ss >> id_1 >> id_2;

            grafo_social.inserir_aresta(id_1, id_2);

            cout << "S "
                 << dicionario.recuperar_usuario(id_1).get_nome()
                 << " "
                 << dicionario.recuperar_usuario(id_2).get_nome()
                 << endl;

        }else if(tipo == 'R'){

            int id_1, id_2;

            ss >> id_1 >> id_2;

            grafo_social.remover_aresta(id_1, id_2);

            cout << "R "
                 << dicionario.recuperar_usuario(id_1).get_nome()
                 << " "
                 << dicionario.recuperar_usuario(id_2).get_nome()
                 << endl;

        }else if(tipo == 'L'){

            char subtipo;
            int id_usuario;

            ss >> subtipo;

            if(subtipo == 'T'){

                ss >> id_usuario;

                int tam = grafo_temas.retorna_num_arestas_saindo(id_usuario*2);

                int* temas = grafo_temas.arestas_saindo(id_usuario*2);

                cout << "LT "
                     << dicionario.recuperar_usuario(id_usuario).get_nome();

                for(int i = 0; i < tam; i++){
                    int id_real_tema = (temas[i]-1)/2;
                    cout << " "
                         << dicionario.recuperar_tema(id_real_tema).get_nome();
                }

                cout << endl;

                delete[] temas;

            }else if(subtipo == 'C'){

                ss >> id_usuario;

                int tam = grafo_social.retorna_num_arestas_entrando(id_usuario);

                int* seguidores = grafo_social.arestas_entrando(id_usuario);

                cout << "LC "
                     << dicionario.recuperar_usuario(id_usuario).get_nome();

                for(int i = 0; i < tam; i++){

                    cout << " "
                         << dicionario.recuperar_usuario(seguidores[i]).get_nome();
                }

                cout << endl;

                delete[] seguidores;

            }else if(subtipo == 'S'){

                ss >> id_usuario;

                int tam = grafo_social.retorna_num_arestas_saindo(id_usuario);

                int* seguidos = grafo_social.arestas_saindo(id_usuario);

                cout << "LS "
                     << dicionario.recuperar_usuario(id_usuario).get_nome();

                for(int i = 0; i < tam; i++){

                    cout << " "
                         << dicionario.recuperar_usuario(seguidos[i]).get_nome();
                }

                cout << endl;

                delete[] seguidos;

            }else if(subtipo == 'A'){

                ss >> id_usuario;

                int tam = grafo_social.retorna_num_vertices_amigos(id_usuario);

                int* amigos = grafo_social.vertices_amigos(id_usuario);

                cout << "LA "
                     << dicionario.recuperar_usuario(id_usuario).get_nome();

                for(int i = 0; i < tam; i++){

                    cout << " "
                         << dicionario.recuperar_usuario(amigos[i]).get_nome();
                }

                cout << endl;

                delete[] amigos;
            }

        }else if(tipo == 'Q'){

            int id_1, id_2;
            int valor = 0;

            ss >> id_1 >> id_2;

            bool um_segue_2 = grafo_social.existe_aresta(id_1, id_2);
            bool dois_segue_1 = grafo_social.existe_aresta(id_2, id_1);

            if(um_segue_2 != dois_segue_1){

                if(um_segue_2)
                    valor = 1;
                else
                    valor = 2;

            }else if(um_segue_2 && dois_segue_1){

                valor = 3;
            }

            cout << "Q "
                 << dicionario.recuperar_usuario(id_1).get_nome()
                 << " "
                 << dicionario.recuperar_usuario(id_2).get_nome()
                 << " "
                 << valor
                 << endl;

        }else if(tipo == 'G'){

            int id_usuario, id_tema;
            int valor = 0;

            ss >> id_usuario >> id_tema;

            if(grafo_temas.existe_aresta(id_usuario*2, id_tema*2+1))
                valor = 1;

            cout << "G "
                 << dicionario.recuperar_usuario(id_usuario).get_nome()
                 << " "
                 << dicionario.recuperar_tema(id_tema).get_nome()
                 << " "
                 << valor
                 << endl;

        }else if(tipo == 'F'){

            int id_tema;
            int quantidade = 0;

            ss >> id_tema;

            quantidade = grafo_temas.retorna_num_arestas_entrando(id_tema*2+1);

            cout << "F "
                 << dicionario.recuperar_tema(id_tema).get_nome()
                 << " "
                 << quantidade
                 << endl;
        }
    }

    //arquivo.close();

    return 0;
}
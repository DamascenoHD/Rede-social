#ifndef GRAFO_HPP
#define GRAFO_HPP
#include "No.hpp"

struct Aresta {
    int destino;
    Aresta* prox;
};

class Grafo{
    private:
        bool direcionado;
        char representacao;
        int num_vertices;
        int tamanho = 0;
        int* ativo;
        No* vertices;
        int** matriz; 

        Aresta** listas;

    public:
        Grafo();
        Grafo(bool direcionado, char representacao);
        ~Grafo();

        void imprimir_grafo();

        void inserir_vertice(No no);
        void remover_vertice(int id_vertice);

        void inserir_aresta(int origem, int destino);
        void remover_aresta_lista(int origem, int destino);
        void remover_aresta(int origem, int destino);
        bool existe_aresta(int origem, int destino);
 
        void mudar_representacao(char nova_representacao);


        
        int retorna_num_arestas_entrando(int id);
        int retorna_num_arestas_saindo(int id);
        int retorna_num_vertices_amigos(int id);

        int* arestas_entrando(int id);//seguidores
        int* arestas_saindo(int id);//seguindo
        int* vertices_amigos(int id);//amigos

        void configurar(bool direcionando, char representacao);
};
#endif
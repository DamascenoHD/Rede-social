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
        //int obter_vertice(const char* rotulo);
        //int vertice_ativo(int id);
        //int vertice_adjacente(int vertice, int ultimo);

        void inserir_aresta(int origem, int destino);
        void remover_aresta_lista(int origem, int destino);
        void remover_aresta(int origem, int destino);
        bool existe_aresta(int origem, int destino);
        //int obter_aresta(int origem, int destino);
        
        void mudar_representacao(char nova_representacao);

        void aumentar_capacidade();

};
#endif
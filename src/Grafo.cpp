#include "Grafo.hpp"
#include <iostream>
Grafo::Grafo(){
    capacidade = 0;
    direcionado = false;
    representacao = '\0';
    num_vertices = 0;

    ativo = nullptr;
    vertices = nullptr;
    matriz = nullptr;
    listas = nullptr;
}
Grafo::Grafo(int capacidade, bool direcionado, char representacao){
    this->capacidade = capacidade;
    this->direcionado = direcionado;
    this->representacao = representacao;

    num_vertices = 0;

    vertices = new No[capacidade];
    ativo = new int[capacidade];
    for(int i = 0; i < capacidade; i++) {
        ativo[i] = 0;
    }
    if(representacao=='L'){
        listas = new Aresta*[capacidade];
        for(int i = 0; i < capacidade; i++) {
            listas[i] = nullptr;
        }
        matriz = nullptr;
    }else if(representacao=='M'){
        matriz = new int*[capacidade];
        for(int i = 0; i < capacidade; i++) {
            matriz[i] = new int[capacidade];
            for(int j = 0; j < capacidade; j++) {
                matriz[i][j] = 0;
            }
        }
        listas = nullptr;
    }else {
        matriz = nullptr;
        listas = nullptr;
    }   
}
Grafo::~Grafo(){
    delete[] ativo;
    delete [] vertices;
    if(matriz != nullptr){
        for(int i = 0; i < capacidade; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
    if(listas != nullptr){
        for(int i = 0; i < capacidade; i++) {
            Aresta* atual = listas[i];
            while(atual != nullptr) {
                Aresta* temp = atual;
                atual = atual->prox;
                delete temp;
            }
        }
        delete[] listas;
    }
}


void Grafo::inserir_vertice(No no){
    int id_no = no.get_id();
    if(id_no >= 0 && id_no < capacidade){
        vertices[id_no] = no;
        ativo[id_no] = 1;
        num_vertices++;
    }
}

void Grafo::inserir_aresta(int origem, int destino){
    if(origem< 0 || origem >= capacidade || destino < 0 || destino >= capacidade)
        return;
    if(!ativo[origem] || !ativo[destino])
        return;
    //adicionar verificação se a aresta já existe
    if(representacao == 'L'){
            Aresta* aresta = new Aresta;
            aresta->destino = destino;
            aresta->prox = listas[origem];
            listas[origem] = aresta;
            if(!direcionado){
                Aresta* aresta2 = new Aresta;
                aresta2->destino = origem;
                aresta2->prox = listas[destino];
                listas[destino] = aresta2; 
            }
    }
}
bool Grafo::existe_aresta(int origem, int destino){
     if(origem < 0 || origem >= capacidade ||
       destino < 0 || destino >= capacidade)
        return false;
    if(representacao == 'L'){
        Aresta* atual = listas[origem];
        while(atual!=nullptr){
            if(atual->destino==destino)
                return true;
            atual = atual->prox;
        }
        return false;
    }else if(representacao == 'M'){

        return matriz[origem][destino] != 0;
    }
    return false;
}
void Grafo::remover_aresta_lista(int origem, int destino){
    Aresta* atual = listas[origem];
    Aresta* anterior = nullptr;
    while(atual !=nullptr){
        if(atual->destino==destino){
            if(anterior==nullptr){
                listas[origem] = atual->prox;
            }else{
                anterior->prox = atual->prox;
            }
            delete atual;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void Grafo::remover_aresta(int origem, int destino){
    if(origem < 0 || origem >= capacidade ||
       destino < 0 || destino >= capacidade)
        return;
    if(!existe_aresta(origem, destino))
        return;
    if(representacao=='L'){
        remover_aresta_lista(origem, destino);
        if(!direcionado){
            remover_aresta_lista(destino, origem);
        }
    }
}
void Grafo::remover_vertice(int id_vertice){
    if(id_vertice<0 || id_vertice >=0)
        return;
    if(!ativo[id_vertice])
        return;
    if(representacao=='L'){
        //Removendo arestas saindo do vértice
        while(listas[id_vertice]!=nullptr){
            Aresta* temp = listas[id_vertice];
            listas[id_vertice] = listas[id_vertice]->prox;
            delete temp;
        }
        //Removendo arestas entrando no vértice
        for(int i=0; i<capacidade; i++){
            if(ativo[i] && i != id_vertice){
                remover_aresta(i, id_vertice);
            }
        }
    }
    ativo[id_vertice] = 0;
    num_vertices--;
}

void Grafo::imprimir_grafo(){
    if(representacao=='L'){
        for(int i=0; i<capacidade; i++){
            if(ativo[i]){
                std::cout << i << ": ";
                Aresta* atual = listas[i];
                while(atual != nullptr){
                    std::cout << atual->destino << " ";
                    atual = atual->prox;
                }
                std::cout << std::endl;
            }
        }
    }
}

void Grafo::mudar_representacao(char nova_representacao){

    if(nova_representacao == representacao)
        return;

    // LISTA -> MATRIZ
    if(representacao == 'L' && nova_representacao == 'M'){

        int** nova_matriz = new int*[capacidade];

        for(int i = 0; i < capacidade; i++){

            nova_matriz[i] = new int[capacidade];

            for(int j = 0; j < capacidade; j++){
                nova_matriz[i][j] = 0;
            }
        }

        // copiar arestas
        for(int i = 0; i < capacidade; i++){

            Aresta* atual = listas[i];

            while(atual != nullptr){

                nova_matriz[i][atual->destino] = 1;

                atual = atual->prox;
            }
        }

        // liberar listas antigas
        for(int i = 0; i < capacidade; i++){

            Aresta* atual = listas[i];

            while(atual != nullptr){

                Aresta* temp = atual;

                atual = atual->prox;

                delete temp;
            }
        }

        delete[] listas;

        listas = nullptr;

        matriz = nova_matriz;

        representacao = 'M';
    }

    // MATRIZ -> LISTA
    else if(representacao == 'M' && nova_representacao == 'L'){

        Aresta** novas_listas = new Aresta*[capacidade];

        for(int i = 0; i < capacidade; i++){
            novas_listas[i] = nullptr;
        }

        // copiar arestas
        for(int i = 0; i < capacidade; i++){

            for(int j = 0; j < capacidade; j++){

                if(matriz[i][j] != 0){

                    Aresta* nova = new Aresta;

                    nova->destino = j;

                    nova->prox = novas_listas[i];

                    novas_listas[i] = nova;
                }
            }
        }

        // liberar matriz antiga
        for(int i = 0; i < capacidade; i++){
            delete[] matriz[i];
        }

        delete[] matriz;

        matriz = nullptr;

        listas = novas_listas;

        representacao = 'L';
    }
}
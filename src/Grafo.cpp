#include "Grafo.hpp"
#include <iostream>
Grafo::Grafo(){
    direcionado = false;
    representacao = '\0';
    num_vertices = 0;
    tamanho = 0;
    ativo = nullptr;
    vertices = nullptr;
    matriz = nullptr;
    listas = nullptr;
}
Grafo::Grafo(bool direcionado, char representacao){
    this->direcionado = direcionado;
    this->representacao = representacao;
    tamanho = 0;
    num_vertices = 0;

    vertices = nullptr;
    ativo = nullptr;
    listas = nullptr;
    matriz = nullptr;
   
}
Grafo::~Grafo(){
    delete[] ativo;
    delete [] vertices;
    if(matriz != nullptr){
        for(int i = 0; i < tamanho; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
    if(listas != nullptr){
        for(int i = 0; i < tamanho; i++) {
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
    if(id_no < 0)
        return;
    while(id_no >= tamanho) {
        No* novo_vertices = new No[tamanho+1];
        int* novo_ativo = new int[tamanho+1];

        for(int i=0; i<tamanho+1; i++){
            novo_ativo[i] = 0;
        }

        for(int i=0; i<tamanho; i++){
            novo_vertices[i] = vertices[i];
            novo_ativo[i] = ativo[i];
        }
        delete[] vertices;
        delete[] ativo;

        vertices = novo_vertices;
        ativo = novo_ativo;
        
        if(representacao=='L'){
            Aresta** novas_listas = new Aresta*[tamanho + 1];

            for(int i = 0; i < tamanho + 1; i++){
                novas_listas[i] = nullptr;
            }

            for(int i = 0; i < tamanho; i++){
                novas_listas[i] = listas[i];
            }

            delete[] listas;

            listas = novas_listas;
        }else if(representacao=='M'){
            int** nova_matriz = new int*[tamanho + 1];

            for(int i = 0; i < tamanho + 1; i++){

                nova_matriz[i] = new int[tamanho + 1];

                for(int j = 0; j < tamanho + 1; j++){
                    nova_matriz[i][j] = 0;
                }
            }

            // copia matriz antiga
            for(int i = 0; i < tamanho; i++){
                for(int j = 0; j < tamanho; j++){
                    nova_matriz[i][j] = matriz[i][j];
                }
            }

            // libera antiga
            for(int i = 0; i < tamanho; i++){
                delete[] matriz[i];
            }

            delete[] matriz;

            matriz = nova_matriz;
        }
        tamanho++;
    }
    if(ativo[id_no])
        return;

    vertices[id_no] = no;
    ativo[id_no] = 1;
    num_vertices++;
}

bool Grafo::existe_aresta(int origem, int destino){
     if(origem < 0 || origem >= tamanho ||
       destino < 0 || destino >= tamanho)
        return false;
    if(!ativo[origem] || !ativo[destino])
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

void Grafo::inserir_aresta(int origem, int destino){
    if(origem< 0 || origem >= tamanho || destino < 0 || destino >= tamanho)
        return;
    if(!ativo[origem] || !ativo[destino])
        return;
    if(existe_aresta(origem, destino))
        return;
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
    }else if(representacao=='M'){
        matriz[origem][destino] = 1;
        if(!direcionado)
            matriz[destino][origem] = 1;
    }
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
    if(origem < 0 || origem >= tamanho ||
       destino < 0 || destino >= tamanho)
        return;
    if(!existe_aresta(origem, destino))
        return;
    if(representacao=='L'){
        remover_aresta_lista(origem, destino);
        if(!direcionado){
            remover_aresta_lista(destino, origem);
        }
    }else if(representacao=='M'){
        matriz[origem][destino]=0;
        if(!direcionado)
            matriz[destino][origem]=0;
    }
}
void Grafo::remover_vertice(int id_vertice){
    if(id_vertice < 0 || id_vertice >= tamanho)
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
        for(int i=0; i<tamanho; i++){
            if(ativo[i] && i != id_vertice){
                remover_aresta(i, id_vertice);
            }
        }
    }else if(representacao=='M'){
        //removendo vertices entrando e saindo
        for(int i=0; i<tamanho; i++){
            if(ativo[i]&&i!=id_vertice){
                remover_aresta(i, id_vertice);
                if(!direcionado)
                    remover_aresta(id_vertice,i);
            }

        }
    }
    ativo[id_vertice] = 0;
    num_vertices--;
}

void Grafo::imprimir_grafo(){
    if(representacao=='L'){
        for(int i=0; i<tamanho; i++){
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
    }else if(representacao=='M'){
        for(int i=0; i<tamanho; i++){
            if(!ativo[i])
                continue;
            for(int j=0; j<tamanho; j++){
                std::cout << matriz[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
}

void Grafo::mudar_representacao(char nova_representacao){

    if(nova_representacao == representacao)
        return;
    if(nova_representacao != 'L' && nova_representacao != 'M')
        return;
    // LISTA -> MATRIZ
    if(representacao == 'L' && nova_representacao == 'M'){

        int** nova_matriz = new int*[tamanho];

        for(int i = 0; i < tamanho; i++){

            nova_matriz[i] = new int[tamanho];

            for(int j = 0; j < tamanho; j++){
                nova_matriz[i][j] = 0;
            }
        }

        // copiar arestas
        for(int i = 0; i < tamanho; i++){

            Aresta* atual = listas[i];

            while(atual != nullptr){

                nova_matriz[i][atual->destino] = 1;

                atual = atual->prox;
            }
        }

        // liberar listas antigas
        for(int i = 0; i < tamanho; i++){

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

        Aresta** novas_listas = new Aresta*[tamanho];

        for(int i = 0; i < tamanho; i++){
            novas_listas[i] = nullptr;
        }

        // copiar arestas
        for(int i = 0; i < tamanho; i++){

            for(int j = 0; j < tamanho; j++){

                if(matriz[i][j] != 0){

                    Aresta* nova = new Aresta;

                    nova->destino = j;

                    nova->prox = novas_listas[i];

                    novas_listas[i] = nova;
                }
            }
        }

        // liberar matriz antiga
        for(int i = 0; i < tamanho; i++){
            delete[] matriz[i];
        }

        delete[] matriz;

        matriz = nullptr;

        listas = novas_listas;

        representacao = 'L';
    }
}

int* Grafo::listar_arestas_entrando(int id){
    if(id < 0 || id >= tamanho || !ativo[id])
        return nullptr;
    int num_arestas_entrando = retorna_num_arestas_entrando(id);
    int qnt_ja_no_vetor = 0;
    int* arestas_entrando = new int[num_arestas_entrando];
    for(int i=0; i<tamanho; i++){
        if(!ativo[i])
            continue;
        if(existe_aresta(i, id)){
            arestas_entrando[qnt_ja_no_vetor] = i;
            qnt_ja_no_vetor++;
            if(qnt_ja_no_vetor==num_arestas_entrando)
            break;
        }
    }
    return arestas_entrando;
}
int* Grafo::listar_arestas_saindo(int id){
    if(id < 0 || id >= tamanho || !ativo[id])
        return nullptr;
    int num_arestas_saindo = retorna_num_arestas_saindo(id);
    int qnt_ja_no_vetor = 0;
    int* arestas_saindo = new int[num_arestas_saindo];
    for(int i=0; i<tamanho; i++){
        if(!ativo[i])
            continue;
        if(existe_aresta(id, i)){
            arestas_saindo[qnt_ja_no_vetor] = i;
            qnt_ja_no_vetor++;
            if(qnt_ja_no_vetor==num_arestas_saindo)
            break;
        }
    }
    return arestas_saindo;
}

int* Grafo::listar_vertices_amigos(int id){
    if(id < 0 || id >= tamanho || !ativo[id])
        return nullptr;
    int num_amigos = retorna_num_vertices_amigos(id);
    int qnt_ja_no_vetor = 0;
    int* vertices_amigos = new int[num_amigos];
    for(int i=0; i<tamanho; i++){
        if(!ativo[i])
            continue;
        if(existe_aresta(i, id)&&existe_aresta(id, i)){
            vertices_amigos[qnt_ja_no_vetor] = i;
            qnt_ja_no_vetor++;
            if(qnt_ja_no_vetor==num_amigos)
            break;
        }
    }
    return vertices_amigos;
}

int Grafo::retorna_num_arestas_entrando(int id){
    int num = 0;
    for(int i=0; i<tamanho; i++){
        if(existe_aresta(i, id))
            num++;
    }
    return num;
}

int Grafo::retorna_num_arestas_saindo(int id){
    int num = 0;
    for(int i=0; i<tamanho; i++){
        if(existe_aresta(id, i))
            num++;
    }
    return num;
}

int Grafo::retorna_num_vertices_amigos(int id){
    int num = 0;
    for(int i=0; i<tamanho; i++){
        if(existe_aresta(id, i) && existe_aresta(i, id))
            num++;
    }
    return num;
}

void Grafo::configurar(bool direcionado, char representacao){
    this->direcionado = direcionado;
    this->representacao = representacao;

    tamanho = 0;
    num_vertices = 0;

    vertices = nullptr;
    ativo = nullptr;
    listas = nullptr;
    matriz = nullptr;
}
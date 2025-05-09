#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 52
#define INVALIDO printf("\n\t___RESPOSTA INVÁLIDA___\n");

typedef struct carta{ //Estrutura da carta
    int numero;
    int naipe;
    struct carta *anterior;
    struct carta *proximo;
} card;

typedef struct deck{ //Estrutura do baralho
    card *topo;
    card *inicio;
    int quant;
} deck;

typedef struct player{ //Estrutura do player
    char nome[30];
    deck *monte;
} player;



card *cria_carta(deck *p, int numero, int naipe);
player *cria_jogador(int n);
deck *cria_baralho();
void coloca_cartas(deck *p, int n);

void aleatorizar_baralho(deck *p);

card *compra_carta(deck *p);
void coloca_topo(deck *p, card *carta);
void rouba_monte(deck *p1, deck *p2);

card *verifica_descarte(deck *descarte, card *carta_vez, int *verifica);
//verifica se a carta da vez tem um numero igual a alguma da pilha de descarte;

void liberar_deck(deck *p);
deck *Ordenacao(deck *p);
//void Rankear_jogadores(player p[], int n);
int mostra_monte(deck *p);

int main(){
    int opcao, verifica, acao;
    int quant_player, quant_baralho;
    int i, j;
    card *carta_da_vez, *aux;

    srand(time(NULL));

    do{ 
        printf("\t\t  _______________________________________________________\n");
        printf("\t\t /                                                     / |\n");
        printf("\t\t/_____________________________________________________/  |\n");
        printf("\t\t|                                                     |  |\n");
        printf("\t\t|                                                     |  |\n");
        printf("\t\t|                ---ROUBA MONTES---                   |  |\n");
        printf("\t\t|                                                     |  |\n");
        printf("\t\t|                 1. Comecar jogo                     |  |\n");
        printf("\t\t|                 2. SAIR                             |  |\n");
        printf("\t\t|                                                     |  |\n");
        printf("\t\t|            *Esta no modo jogo automatico*           | /\n");
        printf("\t\t|_____________________________________________________|/\n");
        scanf(" %d", &opcao);

        switch(opcao){

            case 1: //Pré-jogo

                printf("\n\tDigite quantos jogadores terao: ");
                scanf(" %d", &quant_player);
                player *jogadores = cria_jogador(quant_player);

                for(i = 0; i < quant_player; i++){ //Coloca nome dos jogadores---
                    printf("\n\tNome do %d Jogador\n\t\t", i+1);
                    setbuf(stdin, NULL);
                    fgets(jogadores[i].nome, 30, stdin);
                }
                
                printf("\nDigite quantos baralhos serao usados: ");
                scanf("%d", &quant_baralho);

                //Cria os baralhos, e a pilha de descarte---
                deck *descarte = cria_baralho(); 
                deck *baralho = cria_baralho();
                coloca_cartas(baralho, quant_baralho);
                
        
                aux = baralho->topo;
                for(i=0; i<(52*quant_baralho); i++){
                    if((i+1)%10 == 0)
                        printf("\n");

                    printf("%d-%d\t", aux->numero, aux->naipe);
                    aux = aux->anterior;
                }
                printf("\n\n");

                aleatorizar_baralho(baralho); //Embaralha a pilha de compras

                aux = baralho->topo;
                for(i=0; i<(52*quant_baralho); i++){
                    if((i+1)%10 == 0)
                        printf("\n");

                    printf("%d-%d\t", aux->numero, aux->naipe);
                    aux = aux->anterior;
                }
                printf("\n\nQuantidade de cartas: %d", baralho->quant);
                system("pause");

                system("cls");
                int contagem = 0;
                printf("\t\t  ______________________________________________________\n");
                printf("\t\t /                                                    / |\n");
                printf("\t\t/____________________________________________________/  |\n");
                printf("\t\t|                                                    |  |\n");
                printf("\t\t|                ---ROUBA MONTES---                  |  |\n");
                printf("\t\t|                                                    | /\n");
                printf("\t\t|____________________________________________________|/\n");
                do{ //Começa o jogo ---------------------------------------------------------------------------------------------------

                    for(i = 0; i < quant_player; i++){
                        if(baralho->topo == NULL)
                            break;
                        //printado informações ------------------------------
                        printf("\t\t|[Jogada %d] --------------- Vez de %s", ++contagem, jogadores[i].nome);
                        printf("\t\t|-Pontos: %d\n", jogadores[i].monte->quant);
                        if(jogadores[i].monte->topo == NULL)
                            printf("\t\t|-Topo do monte: VAZIO\n");
                        else
                            printf("\t\t|-Topo do monte: %d\n", jogadores[i].monte->topo->numero);
                
                        carta_da_vez = compra_carta(baralho); //Retira uma carta do monte_compra
                        if(carta_da_vez == NULL)
                            break;
                        printf("\t\t|\n");
                        printf("\t\t|-Carta da vez: %d", carta_da_vez->numero);
                        acao = 0;
                        //Verificando condições-------------------------------
                        if(jogadores[i].monte->topo != NULL){
                            if(carta_da_vez->numero == jogadores[i].monte->topo->numero){ //Carta da Vez igual ao topo do jogador atual  
                            coloca_topo(jogadores[i].monte, carta_da_vez);
                                acao++;
                            }
                        }
                        

                        for(j = 0; j < quant_player; j++){
                            if(i != j){
                                if(jogadores[j].monte->topo != NULL){ //Carta da Vez igual ao topo de um jogador adversário
                                    if(carta_da_vez->numero == jogadores[j].monte->topo->numero){ 
                                        rouba_monte(jogadores[i].monte, jogadores[j].monte);
                                        acao++;
                                    }  
                                }
                            }
                        }
                        

                        aux = NULL;
                        aux = verifica_descarte(descarte, carta_da_vez, &verifica);
                        if(verifica == 1){ //Carta da Vez igual a uma carta no monte de Descarte
                            coloca_topo(jogadores[i].monte, aux);
                            coloca_topo(jogadores[i].monte, carta_da_vez);
                            acao++;
                        }                      
                        

                        printf("\n\t\t|-acao: %d\n", acao);
                        if(acao == 0)
                            coloca_topo(descarte, carta_da_vez);
                        else
                            --i;

                        printf("\t\t|\n");
                        printf("\t\t|\n");
                        printf("\t\t|Descarte: ");
                        aux = descarte->topo;
                        for(j=0; j<descarte->quant; j++){
                            if(aux == NULL)
                                break;
                            printf("%d-", aux->numero);
                            aux = aux->anterior;
                        }
                        printf("\n\t\t|____________________________________________________\n");
                        printf("\t\t|\n");
                    }
                

                } while(baralho->quant > 0);
                system("pause");
                system("cls");
                

                printf("\t\t  ______________________________________________________\n");
                printf("\t\t /                                                    / |\n");
                printf("\t\t/____________________________________________________/  |\n");
                printf("\t\t|                                                    |  |\n");
                printf("\t\t|                ---ROUBA MONTES---                  |  |\n");
                printf("\t\t|                                                    | /\n");
                printf("\t\t|____________________________________________________|/\n");
                printf("\t\t|\tPlacar dos Jogadores:\n");
                printf("\t\t|\n");
                for(i = 0; i < quant_player; i++){
                    printf("\t\t|\t%d. %s", i+1, jogadores[i].nome);
                    printf("\t\t|\tCartas: %d\n", jogadores[i].monte->quant);
                    printf("\t\t|\n");
                }
                printf("\t\t|\n");
                printf("\t\t|____________________________________________________\n");
                printf("\t\t|\n");
                printf("\t\t|             GANHADOR: ");
                int maior = 0;
                for(i=0; i < quant_player; i++){
                    if(jogadores[maior].monte->quant < jogadores[i].monte->quant)
                        maior = i; 
                }
                printf("%s", jogadores[maior].nome);
                printf("\t\t|-Cartas de %s", jogadores[maior].nome);
                //Ordenacao(jogadores[maior].monte);
                verifica = mostra_monte(jogadores[maior].monte);
                if(verifica == 0)
                    printf("\n\t\t___ERRO___\n");


                system("pause");
                //Liberar os ponteiros criados---
                for(i=0; i < quant_player; i++){
                    liberar_deck(jogadores[i].monte);
                }
                free(jogadores);
                liberar_deck(descarte);
                break;

            case 2:
                printf("\n\t\tFECHANDO JOGO...\n");
                system("pause");
                break;
            
            default:
                printf("\n\t\t___OPCAO INVALIDA___\n");
                break;

        }
        system("cls");
    }while( opcao != 2);

    return 0;
}


card *cria_carta(deck *p, int numero, int naipe){
    card *carta = (card*) malloc(1*sizeof(card));   
    
    carta->naipe = naipe;
    carta->numero = numero;
    carta->anterior = p->topo;
    carta->proximo = NULL;

    if(p->quant == 0)
        p->inicio = carta;
    else
        p->topo->proximo = carta;

    p->quant++;
    return carta;
}
   
void coloca_cartas(deck *p, int n){
    int numero;
    int naipe;
    int i, j, k;


    for(i = 0; i < n; i++){ //quantidade de baralhos
        naipe = 1;

        for(j = 0; j < 4; j++){ //quantidade de naipes
            numero = 1;

            for(k = 0; k < 13; k++){ //quantidade de numeroeros
                p->topo = cria_carta(p, numero, naipe);
                numero++;
            }
            naipe++;
        }
    }
}

deck *cria_baralho(){
    deck *p = (deck*) malloc(1*sizeof(deck));
    p->topo = NULL;
    p->inicio = NULL;
    p->quant = 0;

    return p;
}

player *cria_jogador(int n){ //Cria os montes dos jogadores
    player *jogador = (player*) malloc(n*sizeof(player));
    
    for(int i = 0; i < n; i++)
        jogador[i].monte = cria_baralho();

    return jogador;
}

card *compra_carta(deck *p){
    if(p->topo == NULL)
        return NULL;

    card *auxiliar = p->topo;
    if (p->topo->anterior != NULL){ // Se houver mais de uma carta no baralho
        p->topo = p->topo->anterior;
        p->topo->proximo = NULL;
    }
    else //Se houver apenas uma carta
        p->topo = NULL;
    
    p->quant--;
    auxiliar->anterior = NULL;
    auxiliar->proximo = NULL;

    return auxiliar;
}

void coloca_topo(deck *p, card *carta){
    if(p->quant == 0 || p->topo == NULL){
        p->inicio = carta;
        carta->anterior = NULL;
    }
    else{
        carta->anterior = p->topo;  //ligando a carta ao monte do player
        p->topo->proximo = carta;   //Ligando o monte do player a carta
    }
    carta->proximo = NULL;
    p->topo = carta;
    p->quant++;
}

void rouba_monte(deck *p1, deck *p2){
    card *auxiliar = p2->inicio;

    if(p1->topo == NULL){
        p1->inicio = auxiliar;
        p1->topo = p2->topo;
        p1->quant += p2->quant;
    }
    else{
        auxiliar->anterior = p1->topo;

        p1->topo->proximo = auxiliar;
        p1->topo = p2->topo;
        p1->quant += p2->quant;
    }

        p2->quant = 0;
        p2->topo = NULL;
        p2->inicio = NULL;
}

card *verifica_descarte(deck *descarte, card *carta_vez, int *verifica){
    if(descarte->topo == NULL){
        *verifica = 0;
        return NULL;
    }    
    else {
        card *aux = descarte->topo;

        if(descarte->topo->numero == carta_vez->numero){ //Topo é igual a Carta da vez
            descarte->topo = descarte->topo->anterior;
            descarte->topo->proximo = NULL;

            aux->anterior = NULL;
            *verifica = 1;
            return aux;
        }

        while(aux != NULL){
            if(aux->numero == carta_vez->numero){ //Demais cartas igual a Carta da vez
      
                if(aux->proximo != NULL)
                    aux->proximo->anterior = aux->anterior;
                if(aux->anterior != NULL)
                    aux->anterior->proximo = aux->proximo;

                aux->anterior = NULL;
                aux->proximo = NULL;
                *verifica = 1;
                return aux;
            }
            aux = aux->anterior;
        }
        *verifica = 0;
        return NULL;
    }
}

void liberar_deck(deck *p){ 
    card *auxiliar;

    while(p->topo != NULL){
        auxiliar = p->topo;
        p->topo = p->topo->anterior;

        free(auxiliar);
    }
    p->inicio = NULL;
    p->topo = NULL;
    p->quant = 0;
    free(p);
}

deck *Ordenacao(deck *p){
    deck *Ordenado = cria_baralho();
    card *aux;
    card *maior;
    int i;

    for(i=1; i < p->quant; i++){
        maior = p->topo;
        aux = p->topo->anterior;

        while(aux != NULL){
            if(maior->numero < aux->numero)
                maior = aux;
            
            aux = aux->anterior;
        }

        if(maior->proximo != NULL){
            maior->proximo->anterior = maior->anterior;    
        }
        else{
            p->topo = p->topo->anterior;
            p->topo->proximo = NULL;
        }
        if(maior->anterior != NULL)
            maior->anterior->proximo = maior->proximo;
        else{
            p->inicio = p->inicio->proximo;
            p->inicio->anterior = NULL;
        }

        Ordenado->topo = cria_carta(Ordenado, maior->numero, maior->naipe);
    }

    liberar_deck(p);
    return Ordenado;
}

void aleatorizar_baralho(deck *p){
    card *auxiliar;
    int i, j, n;

    for(i=0; i<(2*p->quant); i++){
        n = (rand() % p->quant) + 1;

        if(n == 1){ //Caso seja o primeiro card ---
            auxiliar = p->inicio;

            p->inicio = p->inicio->proximo;
            p->inicio->anterior = NULL;
        }
        else if(n == p->quant){ //Caso seja o ultimo card ---
            auxiliar = p->topo;

            p->topo = p->topo->anterior;
            p->topo->proximo = NULL;
        }
        else{ //Demais cards ---
            auxiliar = p->inicio;
            n--;

            for(int j=0; j<n; j++)
                auxiliar = auxiliar->proximo;

            auxiliar->proximo->anterior = auxiliar->anterior;
            auxiliar->anterior->proximo = auxiliar->proximo;
        }
        printf("%d %d-%d\n ", i+1, auxiliar->numero, auxiliar->naipe);

        auxiliar->anterior = p->topo;
        auxiliar->proximo = NULL;

        p->topo->proximo = auxiliar;
        p->topo = auxiliar;
    }
}

/*void Rankear_jogadores(player *p, int n){
    int i, j;
    player *auxiliar = cria_jogador(1);

    for(i=n-1; i>=0; i--){

        for(j=0; j<i; j++){

            if(p[j].monte->quant < p[j+1].monte->quant){
                *auxiliar = p[j+1];
                p[j+1] = p[j];
                p[j] = *auxiliar;
            }
        }
    }

    liberar_deck(auxiliar->monte);
    free(auxiliar);
}*/

int mostra_monte(deck *p){ 
    if(p->topo == NULL)
        return 0;

    card *auxiliar = p->topo;
    printf("\t\t|\n");
    int i;

    for(i=0; i < p->quant; i++){
        printf("\t\t| %d- ", auxiliar->numero);
        if(auxiliar->naipe == 1)
            printf("ESPADAS\n");
        else if(auxiliar->naipe == 2)
            printf("OUROS\n");
        else if(auxiliar->naipe == 3)
            printf("COPAS\n");
        else if(auxiliar->naipe == 4)
            printf("PAUS\n");
        
        auxiliar = auxiliar->anterior;
    }

    return 1;
}
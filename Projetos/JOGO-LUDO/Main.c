#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define invalido printf("\tOpcao Invalida!!!\n");
#define perdeu printf("\nVOCE PERDEU A VEZ\n");

typedef struct{
    int peao[4];
    int posicao_real_peao[4];
    int casas_finais[4];
    char nome[20];
    int percurso_completo;
} jogadores;

void interface(jogadores x[], int n, int dado[], int quant_jogadores);

int numero_de_jogadores();
void dado(int *contagem_dado, int *valores_dado);
int condicao_pecas_inicializadas(int condicao[], int n);
int opcao_usar_dado();
void inicializar_peao(jogadores x[], int n, int quant_jogadores);
void mover_peao(jogadores x[], int n, int dado[], int m);
bool seguras(int casas_s[], int n, jogadores x[], int m);
void comer_peao(jogadores x[], int n, int quant_jogadores);
void casas_finais(jogadores x[], int n, int n_peca);
void analisa_vencedor(jogadores x[], int n);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< FUNCAO PRINCIPAL >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(){
    jogadores *jogador;
    int quant_jogadores;
    int casas_seguras[8] = {1, 9, 14, 22, 27, 35, 40, 48};
    int VENCEDOR = 0;
    int i, j, q;
    int r;
    bool condicao;

    quant_jogadores = numero_de_jogadores(); //Determina quantos jogadores terão

    jogador = (jogadores*) malloc(quant_jogadores*sizeof(jogadores));
    if(jogador == NULL){
        printf("\n\tMEMÓRIA INSUFICIENTE!");
        system("pause");
        exit(1);
    }

    for(i=0; i<quant_jogadores; i++){ //Zerar a posição das pecas
        jogador[i].percurso_completo = 0;

        for(j=0; j<4; j++){
            jogador[i].peao[j] = 0;
            jogador[i].posicao_real_peao[j] = 0;
            jogador[i].casas_finais[j] = 0;
        }
    }

    int k;
    for(i=0; i<quant_jogadores; i++){ //Colocar o nome dos jogadores
        printf("\nNome do JOGADOR %d: ", i+1);
        setbuf(stdin, NULL);
        fgets(jogador[i].nome, 20, stdin);
        k = strlen(jogador[i].nome) - 1;
        jogador[i].nome[k] = '\0';
    }

    srand(time(NULL)); //Serve para aleatorizar os dados toda vez que for lançá-los

    printf("\n\tCOMECAR LUDO\n");
    system("pause");


    system("cls");

    int contagem_dado; //Quantidade de dados jogados em uma rodada
    int valores_dado[3] = {0, 0, 0}; //Valores que o jogador tira nos dados
    int opcao;
    int quant_pecas_jogador; //quantidade de pecas que estão na trilha

    do{ //Loop das rodadas até ter um Vencedor

        for(r=0; r<quant_jogadores; r++){ //Vez de cada Jogador
            contagem_dado = 0;

            dado(&contagem_dado, valores_dado);
            interface(jogador, r, valores_dado, quant_jogadores);

            switch(contagem_dado){  //Analiza se o jogador perdeu ou não sua jogada
                case 0: 
                    perdeu break;

                default:
                    for(i=0; i<contagem_dado; i++){
                        quant_pecas_jogador = condicao_pecas_inicializadas(jogador[r].peao, 4);

                        //Quando nenhuma peca do jogador está no tabuleiro
                        if(quant_pecas_jogador == 0){
                            if(valores_dado[i] == 6){
                                inicializar_peao(jogador, r, quant_jogadores);  //restará a opcao de tirar os peos do inicio
                                interface(jogador, r, valores_dado, quant_jogadores);
                            }
                            else{
                                perdeu
                            }
                        }

                        //Quando todas as pecas do jogador estão no tabuleiro
                        else if(quant_pecas_jogador == 4){
                            mover_peao(jogador, r, valores_dado, i);  //restará a opcao de mover os peoes
                            interface(jogador, r, valores_dado, quant_jogadores);
                        }
                        
                        //Quando tem pecas do jogador dentro e fora do tabuleiro
                        else{
                            
                            if(valores_dado[i] == 6){
                                opcao = opcao_usar_dado();
                                switch(opcao){
                                    case 1:
                                        inicializar_peao(jogador, r, quant_jogadores);
                                        interface(jogador, r, valores_dado, quant_jogadores);
                                        break;
                                    case 2:
                                        mover_peao(jogador, r, valores_dado, i);
                                        interface(jogador, r, valores_dado, quant_jogadores);
                                        break;
                                }
                            }
                            else{
                                mover_peao(jogador, r, valores_dado, i);
                                interface(jogador, r, valores_dado, quant_jogadores);
                            }
                        }
                        
                        for(q=0; q<4; q++){
                            if(jogador[r].peao[q] != 0){
                                condicao = seguras(casas_seguras, 8, jogador, r);
                                switch(condicao){
                                    case false: //Caso não esteja em uma casa segura
                                        comer_peao(jogador, r, quant_jogadores);
                                        interface(jogador, r, valores_dado, quant_jogadores);
                                        break;
                                    case true: //Caso esteje em uma casa segura
                                        break;
                                }
                            }
                        }

                    }
                    break;
            }
            printf("\n");
            system("pause");

            void analisa_vencedor(jogadores x[], int n);
            if(jogador[r].percurso_completo == 4)
                break;       
        }

        if(jogador[r].percurso_completo == 4) //Condição para verificar se algum jogador venceu
            VENCEDOR = r;

    } while(VENCEDOR == 0);

    printf("\n\tPARABENS %s, VOCE VENCEU!!!!!!!!\n\n", jogador[VENCEDOR].nome);
    system("pause");

    free(jogador);

    return 0;
}

//Mostra a interfaçe, as posições dos peões de cada jogador <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void interface(jogadores x[], int n, int dado[], int quant_jogadores){
    int i, j;

    system("cls");

    for(i=0; i<quant_jogadores; i++)
        printf("%s\t\t", x[i].nome); 
    printf("\n");

    for(i=0; i<4; i++){
        for(j=0; j<quant_jogadores; j++)
            printf("%d-peao: %d/%d\t", i+1, x[j].peao[i], x[j].posicao_real_peao[i]);
        printf("\n");
    }

    i = 0;
    printf("\nVez de %s, jogue o dado:", x[n].nome);
    do{
        printf("\n%d-Dado: %d", i+1, dado[i]);
        ++i;

    } while(dado[i-1] == 6);
    printf("\n");
}

//Identifica quantos jogadores terão na partida >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int numero_de_jogadores(){
    int num;

    do{
    printf("Quantos Jogadores terao(2-4): ");
    scanf(" %d", &num);
    if(num != 2 && num != 4){
        invalido
    }
    } while(num != 2 && num != 4);

    return num;
}

//Joga o dado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void dado(int *contagem_dado, int *valores_dado){
    int d = 0;

    do{
        valores_dado[d] = rand()%6 + 1;
        *contagem_dado += 1;
        
        if(*contagem_dado == 3 && valores_dado[d] == 6){
            *contagem_dado = 0;
            break;
        }
        ++d;

    } while(valores_dado[d-1] == 6);
    
    return;
}

//Analisa quantas pecas do jogador estão em campo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int condicao_pecas_inicializadas(int condicao[], int n){
    int i;
    int contador = 0;

    for(i=0; i<n; i++){
        if(condicao[i] > 0){
            contador++;
        }
    }
    return contador;
}

//Opções de como usar o dado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int opcao_usar_dado(){
    int opcao;

        do{
            printf("\nOpcoes:");
            printf("\n1.Tirar uma peca da posicao inicial");
            printf("\n2.Mover alguma peca ");
            scanf(" %d", &opcao);

            if(opcao<1 || opcao>2)
                invalido
            
        } while(opcao<1 || opcao>2);

    return opcao;
}

//Analisa e se possível coloca uma peca no tabuleiro >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void inicializar_peao(jogadores x[], int n, int quant_jogadores){
    int n_peca; //numeração do peao
    int i;

    do{
        printf("\nEscolha uma peca para inicializa-la:\n");
        for(i=0; i<4; i++){
            if(x[n].peao[i] == 0){
                printf("Peao-%d\n", i+1);
            }
        }

        do{
            scanf(" %d", &n_peca);
            n_peca += (-1);

            if(x[n].peao[n_peca] != 0)
                invalido
        
        } while(x[n].peao[n_peca] != 0);

        if(n_peca<0 || n_peca>3)
            invalido

    } while(n_peca<0 || n_peca>3);

    x[n].peao[n_peca] = 1;
    switch(quant_jogadores){ //Posicionará o peão no tabuleiro de acordo com a quantidade de jogadores
        case 2: x[n].posicao_real_peao[n_peca] = 1 + (26*n); break;
        case 4: x[n].posicao_real_peao[n_peca] = 1 + (13*n); break;
    }
    return;
}

//Movimenta o peao escolhido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void mover_peao(jogadores x[], int n, int dado[], int m){
    int i;
    int n_peca;
    int k = 0;
    
    printf("\nPeoes disponiveis para mover:"); //Mostra quais peoes estão disponíveis para movimentar
    for(i=0; i<4; i++){
        if(x[n].peao[i] > 0 && (x[n].peao[n_peca] + dado[m]) < 57){
            printf("\nPeao-%d ", i+1);
            k++;
        }
    }
    //Caso não mostre nenhuma opção, significa que não é possível andar com nenhuma peça
    if(k == 0){perdeu return;}


    do{ //Analisa se a peça é válida
        scanf(" %d", &n_peca);
        n_peca += (-1);
        if(x[n].peao[n_peca] == 0 || x[n].peao[n_peca] == 57 || (x[n].peao[n_peca] + dado[m]) > 57){
            invalido
        }
    } while(x[n].peao[n_peca] == 0 || x[n].peao[n_peca] == 57 || (x[n].peao[n_peca] + dado[m]) > 57);


    if((x[n].peao[n_peca] + dado[m]) < 57){ //Adiciona o valor do dado ao valor da peca
        x[n].peao[n_peca] += dado[m];
        x[n].posicao_real_peao[n_peca] += dado[m];
    }
    else if((x[n].peao[n_peca] + dado[m]) == 57){   //Caso a peca complete a trilha
        x[n].peao[n_peca] += dado[m];
        x[n].posicao_real_peao[n_peca] += dado[m];
        /*x[n].percurso_completo++;*/
    }

    if(x[n].posicao_real_peao[n_peca] > 52){
        x[n].posicao_real_peao[n_peca] -= 52;
    }

    casas_finais(x, n, n_peca);

    return;
}

//Averigua se está em uma casa segura >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool seguras(int casas_s[], int n, jogadores x[], int m){
    int i, j;

    for(i=0; i<4; i++){
        for(j=0; j<n; j++){
           if(x[m].posicao_real_peao[i] == casas_s[j]){
                return true;
           }
        }
    }
    return false;
}

//Come o peão que está na mesma posição >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void comer_peao(jogadores x[], int n, int quant_jogadores){
    int i, j, w;
    
    for(i=0; i<quant_jogadores; i++){
        for(w=0; w<4; w++){
            for(j=0; j<4; j++){
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<RECCEBAA!!!!!!!!!!!!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                if(i != n){ //Não pode analizar o as pecas do próprio jogador
                    if(x[n].peao[w] <= 51){ //Verifica se está nas ultimas 6 casas do tabuleiro
                        if(x[i].posicao_real_peao[j] > 0){  //Verifica se não está na casa inicial
                            if(x[n].posicao_real_peao[w] == x[i].posicao_real_peao[j]){ //Compara as pecas de casa jogador
                                x[i].posicao_real_peao[j] = 0;
                                x[i].peao[j] = 0;
                                printf("\nO peao %d comeu o peao de %s\n", w+1, x[i].nome);
                                system("pause"); 

                                return;
                            }
                        }
                    }
                }

            }
        }
    }
    return;
}

//Analisa se está e move os peões nas casas finais >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void casas_finais(jogadores x[], int n, int n_peca){
    
    if(x[n].peao[n_peca] > 51){ //Verifica se está nas ultimas 6 casas
        if(((x[n].peao[n_peca] - 51)) <= 6){ //Verifica se não vai passar do final do tabuleiro
            x[n].casas_finais[n_peca] = (x[n].peao[n_peca] - 51);
            x[n].posicao_real_peao[n_peca] = x[n].casas_finais[n_peca];
        }  
    }

}

//Analiza se o jogador atual venceu ou não o jogo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void analisa_vencedor(jogadores x[], int n){
    int i;
    int peoes_finalizados = 0;

    for(i=0; i<4; i++){
        if(x[n].peao[i] == 57){
            peoes_finalizados++;
        }
    }
    x[n].percurso_completo = peoes_finalizados;
}
//FAZER O TABULEIRO

// Gustavo esteve aqui
//Código bem estruturado. Gostei!!! (Marco Tulio)
//Muito bom !!! (Raphael)

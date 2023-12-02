#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tretis {
    char nome[15];
    int pontuacao[12];
    int somap;
};

//Funcao que verifica o nome digitado
int verificaNome(char *nome) {
    int tam = strlen(nome);

    if (tam < 1 || tam > 15) {
        printf("O tamanho do nome deve estar entre 1 e 15 caracteres.\n");
        return 0;
    }
    //verifica se a primeira letra é maiuscula
    if (!isupper(nome[0])) {
        printf("A primeira letra do nome deve ser maiuscula.\n");
        return 0;
    }
    //verifica se o resto sao minusculas
    for (int i = 1; i < tam; i++) {
        if (!islower(nome[i])) {
            printf("Os caracteres restantes do nome devem ser minusculas.\n");
            return 0;
        }
    }

    return 1;
}

//funcao onde se digita o nome e a pontuacao de cada jogador
void digitandoInfo(struct tretis *jog, int num){

    int result = 0;

    for(int i = 0; i < num; i++){
            printf("Jogador %d: ", i + 1);
            printf("\n");
            
            printf("Nome: ");
            do{
                scanf("%s", jog[i].nome);
                result = verificaNome(jog[i].nome);
            }while(result == 0);
            
            for(int z = 0; z < 12; z++){
                printf("Pontuação %d: ", z + 1);
                do{
                    scanf("%d", &jog[i].pontuacao[z]);
                    if(jog[i].pontuacao[z] >= 0 && jog[i].pontuacao[z] <= 1000){
                        result = 1;
                    }
                    else{
                        printf("Voce digitou um numero menor que 0 ou maior que 1000\n");
                        result = 0;
                    }
                }while(result == 0);
            }
            jog[i].somap = 0;
        }
}


//Funcao que ordena do menor para o maior as pontuacoes
void ordenandoPontuacao(struct tretis *jog, int num){
    int interm; //variavel que serve como intermediaria na copia de segundo para primeiro

    for(int i = 0; i < num; i++){
        for(int primeiro = 0; primeiro < 12; primeiro++){
            for(int segundo = primeiro + 1; segundo < 12; segundo++){
                if (jog[i].pontuacao[primeiro] > jog[i].pontuacao[segundo]){
                        interm = jog[i].pontuacao[primeiro];
                        jog[i].pontuacao[primeiro] = jog[i].pontuacao[segundo];
                        jog[i].pontuacao[segundo] = interm;
                }
            }
        }
    }
}

//funcao que soma as pontuacoes
void somandoPontuacao(struct tretis *jog, int num){

    //jogador
    for(int njogador = 0; njogador < num; njogador++){
        //pontuação
        for(int npont = 0; npont < 12; npont++){
            if(npont != 0 && npont != 11) {
                jog[njogador].somap = jog[njogador].somap + jog[njogador].pontuacao[npont];
            }
        }
    }
}


//funcao que ordena os jogadores, do maior pro menor
void ordenandoJogadores(struct tretis *jog, int num){

    int intermSP;
    char intermNome[15];

    for(int vjog1 = 0; vjog1 < num; vjog1++){
        for(int vjog2 = vjog1 + 1; vjog2 < num; vjog2++){

            //se a soma for igual
            if(jog[vjog1].somap == jog[vjog2].somap){
                int comparacao = strcmp(jog[vjog1].nome, jog[vjog2].nome); //compara os nomes
                if(comparacao > 0) {
                    intermSP = jog[vjog1].somap;
                    jog[vjog1].somap = jog[vjog2].somap;
                    jog[vjog2].somap = intermSP;

                    strcpy(intermNome, jog[vjog1].nome);
                    strcpy(jog[vjog1].nome, jog[vjog2].nome);
                    strcpy(jog[vjog2].nome, intermNome); 
                }
            }

            else if(jog[vjog1].somap < jog[vjog2].somap){
                intermSP = jog[vjog1].somap;
                jog[vjog1].somap = jog[vjog2].somap;
                jog[vjog2].somap = intermSP;
                
                strcpy(intermNome, jog[vjog1].nome);
                strcpy(jog[vjog1].nome, jog[vjog2].nome);
                strcpy(jog[vjog2].nome, intermNome);
                
            }
        }
    }
}


int main(){

    int teste = 0;
    int nj; //numero de jogadores
    int verificacao; //variavel de verificacao de algum dado inserido. Libera o looping.
 
    do{
        teste++;
        verificacao = 0;

        printf("Teste %d\n", teste);
        printf("Digite o número de jogadores: ");

        do{
            scanf("%d", &nj);
            if(nj >= 0 && nj <= 1000){
                verificacao = 1;        
            }
            else{
                printf("Voce digitou um numero menor que 0 e maior que 1000\n");
                verificacao = 0;
            }
        }while(verificacao == 0);


        if(nj != 0){

            struct tretis jogador[nj];
            
            digitandoInfo(jogador, nj);
            ordenandoPontuacao(jogador, nj);
            somandoPontuacao(jogador, nj);
            ordenandoJogadores(jogador, nj);
            
            //Abrindo arquivo gravar nele
            FILE *tabela = fopen("tabela.txt", "a");
                

                fprintf(tabela, "teste %d\n", teste);

                int cont = 1; //contador que vai mostrar a posicao

                for(int i = 0; i < nj; i++){
                    fprintf(tabela, "%d %d %s\n\n", cont, jogador[i].somap, jogador[i].nome);
                    if(jogador[i].somap != jogador[i + 1].somap){
                        cont++;
                    }
                }
            fclose(tabela);
        }
    }while(nj != 0);
    
    //abrindo o arquivo para le-lo
    FILE *tabela_leitura = fopen("tabela.txt", "r");
    if (tabela_leitura == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 1;
    }

    printf("\nTabela de Classificação:\n");

    char linha[500]; 
    while (fgets(linha, sizeof(linha), tabela_leitura) != NULL) {
        printf("%s", linha);
    }

    fclose(tabela_leitura);

    return 0;
}

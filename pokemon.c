#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTAM 1000
#define SUPEREFETIVO 1.2
#define POUCOEFETIVO 0.8

//Estrutura que armazena os atributos de um pokemon
typedef struct{
	char nome[100];
	float ataque;
	float defesa;
	float vida;
	char tipo[100];
} pokemon;

//Estrutura que armazena o pokemon vencedor e o derrotado em um turno
typedef struct{
	char vencedor[100];
	char derrotado[100];
}decisao;

//Transfere dados contidos em uma linha do arquivo para a estrutura de pokemons de um jogador
void transfereDados(pokemon *J, char *linha){
	strcpy(J->nome,strtok(linha," "));
	J->ataque=atof(strtok(NULL," "));
	J->defesa=atof(strtok(NULL," "));
	J->vida=atof(strtok(NULL," "));
	strcpy(J->tipo,strtok(NULL," "));
}

//Conforme definido previamente, N é o número de pokemons do jogador 1, e M, do 2
int inserir(FILE *arq, pokemon *J1, pokemon *J2, int *N, int*M, char *linha){
	//Variável indexadora das estruturas do tipo pokémon. Será utilizada para percorrer os vetores nos loops for:
	int i;
	
	//Conforme o número de pokémons atribuído ao jogador 1 (N), um loop for transfere os dados de cada linha, referente a cada pokémon, para o vetor estruturado do jogador 1:
	for(i=0;i<(*N);i++){
		if(fgets(linha,MAXTAM,arq)){
		transfereDados(&J1[i],linha);
		//Caso algum atributo lido tenha valor negativo, a execução da função é abortada
		if(J1[i].ataque<=0 || J1[i].defesa<=0 || J1[i].vida<=0 ){
	return 0;
	break;
	}
	}
}

   //Conforme o número de pokémons atribuído ao jogador 2 (M), um loop for transfere os dados de cada linha, referente a cada pokémon, para o vetor estruturado do jogador 2:
   for(i=0;i<(*M);i++){
		if(fgets(linha,MAXTAM,arq)){
		transfereDados(&J2[i],linha);
		//Caso algum atributo lido tenha valor negativo, a execução da função é abortada
		if(J2[i].ataque<=0 || J2[i].defesa<=0 || J2[i].vida<=0){
	return 0;
	break;
	}
	}
}

return 1;

}

float tipoAtaque(char tipoDefensorForte, char tipoDefensorFraco, pokemon *JAtacante, pokemon *JDefensor){
    // Caso o tipo do defensor seja fraco contra o atacante, atribui-se ao agressor um dano adicional super efetivo:
    if(JDefensor->tipo[0]==tipoDefensorFraco){
        return JAtacante->ataque*SUPEREFETIVO;
		// Caso o tipo do defensor seja forte contra o atacante, atribui-se ao agressor um dano adicional pouco efetivo:
		}else if(JDefensor->tipo[0]==tipoDefensorForte) {
        return JAtacante->ataque*POUCOEFETIVO;
    }else{
    	// Caso o tipo do defensor não seja nem forte nem fraco contra o agressor, o valor original do ataque é mantido:
    	return JAtacante->ataque;
	}
    
}

float calculaDano(pokemon *JAtacante, pokemon *JDefensor){
	char opc;
	//Recebe a inicial da string do campo "Tipo" do pokémon do jogador atacante
	opc=JAtacante->tipo[0];
	//Para cado caso possível de inicial, a função convocada, "tipoAtaque", recebe, como parâmetro, as iniciais dos tipos de defensor forte e fraco
	switch (opc){
		case 'p':
				return tipoAtaque('g','e',JAtacante, JDefensor);
			break;
			
		case 'e':
			    return tipoAtaque('p','a',JAtacante, JDefensor);
			
			break;
			
		case 'a':
			    return tipoAtaque('e','f',JAtacante, JDefensor);
			
			break;
			
		case 'f':
			    return tipoAtaque('a','g',JAtacante, JDefensor);
			
			break;
			
		case 'g':
			    return tipoAtaque('f','p',JAtacante, JDefensor);
			break;
			
		default:
			printf("Tipo inválido");
			break;
	}
	
}

void batalha(pokemon *J1, pokemon *J2, int *N, int*M, decisao *d, int *k){
	int i=0, j=0; 
	float dano;
	(*k)=0;
	//O do-while permanecerá em iteração infinitamente, até que se esgotem os pokémons de um dos jogadores, isto é, que i>=N ou j>=M
	do{
		
		if(i<(*N)){
			//A variável "dano" recebe o valor retornado pela função "calculaDano", que compara os tipos dos pokémons:
			dano=calculaDano(&J1[i],&J2[j]);
			//Se o dano for maior que a defesa, desconta-se, da vida do pokémon defensor, a diferença. Do contrário, decrementa-se, em uma unidade, a vida do atacado:
            if((dano)>(J2[j].defesa)){
        J2[j].vida-=dano-J2[j].defesa;
		}else{
        J2[j].vida--;
		}
		//Se a vida do pokémon do jogador 1 for <=0, isso significa que este está morto. Seu nome e o de seu sicário são armazenados na estrutura "d", que contém as relações dos resultados finais de cada partida:
			if(J2[j].vida<=0){
			strcpy(d[*k].derrotado,J2[j].nome);
			strcpy(d[*k].vencedor,J1[i].nome);
			(*k)++;
			j++;
			}
			
		}else{
			//Caso i>=N, isso significa que o número de pokémons do jogador 1 se esgotou. Logo, o jogador 2 é o vencedor:
			strcpy(d[*k].vencedor, "Jogador 2");
			break;	
		}
		
		if(j<(*M)){
			//A variável "dano" recebe o valor retornado pela função "calculaDano", que compara os tipos dos pokémons:
			dano=calculaDano(&J2[j],&J1[i]);
			//Se o dano for maior que a defesa, desconta-se, da vida do pokémon defensor, a diferença. Do contrário, decrementa-se, em uma unidade, a vida do atacado:
            if((dano)>(J1[i].defesa)){
        J1[i].vida-=dano-J1[i].defesa;
		}else{
        J1[i].vida--;
		}
		//Se a vida do pokémon do jogador 1 for <=0, isso significa que este está morto. Seu nome e o de seu sicário são armazenados na estrutura "d", que contém as relações dos resultados finais de cada partida:
			if(J1[i].vida<=0){
			strcpy(d[*k].derrotado,J1[i].nome);
			strcpy(d[*k].vencedor,J2[j].nome);
			(*k)++;
			i++;
			}
			
		}else{
			//Caso j>=M, isso significa que o número de pokémons do jogador 2 se esgotou. Logo, o jogador 1 é o vencedor:
			strcpy(d[*k].vencedor, "Jogador 1");
			break;
		}
		
	
}while(1);

}


void resultado(decisao *d, pokemon *J1, pokemon *J2, int k, int *N, int*M){
	int i;
	
	//Através de um loop for, são impressos os campos da estrutura d, do tipo "Decisão", que armazenou os nomes dos vencedores e derrotados em cada partida:
	for(i=0;i<k;i++){
		printf("\n%s venceu %s",d[i].vencedor,d[i].derrotado);
	}
	
	printf("\n%s venceu\n",d[k]);
	
	//Através de um loop for, são impressos os nomes de todos os pokémons do jogador 1 os quais sobreviveram, isto é, possuem o campo "vida" superior a 0:
	
	printf("\nPokemons sobreviventes:\n");
	for(i=0;i<(*N);i++){
		if(J1[i].vida>0){
			printf("%s\n",J1[i].nome);
		}
	}
	
	//O mesmo processo é feito no array de estruturas de pokémons do jogador 2:
	
	for(i=0;i<(*M);i++){
		if(J2[i].vida>0){
			printf("%s\n",J2[i].nome);
		}
	}
	
	//Através de um loop for, são impressos os nomes de todos os pokémons do jogador 1 os quais foram derrotados, isto é, possuem o campo "vida" inferior ou igual a 0:
	
	printf("\nPokemons derrotados:\n");
	for(i=0;i<(*N);i++){
		if(J1[i].vida<=0){
			printf("%s\n",J1[i].nome);
		}
	}
	
	//O mesmo processo é feito no array de estruturas de pokémons do jogador 2:
	for(i=0;i<(*M);i++){
		if(J2[i].vida<=0){
			printf("%s\n",J2[i].nome);
		}
	}
	
}
	

int main(){
	FILE *arq;
	//Considere "N" o número de pokémons do jogador 1 e "M" o número do jogador 2. 
	//O inteiro "i" é índice de loops futuros; o "k" será, ao mesmo tempo, indexador e contador da estrutura "decisão", que armazenará os resultados de cada partida.
	//A variável "flag" será utilizada como retorno da função "inserir", e será um indicador da presença de números negativos nos atributos dos pokémons, a qual leva à interrupção do programa por incompatibilidade.
	int N=0, M=0, i, k, flag;
	//A string "linha" receberá os registros do arquivo a ser lido pelo programa através da função "fgets".
	char linha[MAXTAM];
	//Vetores de estruturas que representam os pokemons à disposição dos jogadores 1 (J1) e 2 (J2), respectivamente:
	pokemon J1[MAXTAM], J2[MAXTAM];
	//Vetor de estruturas que armazena os pokemons vencedores e derrotados em cada partida:
	decisao d[MAXTAM];
	
	printf("---------- Pokemon, eu escolho voce! ----------\n\n");
	
	
	arq=fopen("poke.txt","r");
	
	//Após a leitura do arquivo, caso fopen não retorne NULL, é executada a função de inserção de informações dos pokémons do arquivo nas estruturas dos jogadores:
	if(arq!=NULL){
		
	//Lê a primeira linha do arquivo, consumindo as informações quanto às quantidades de pokemons de cada jogador
	fgets(linha,MAXTAM,arq);
    N=atoi(strtok(linha," "));
	M=atoi(strtok(NULL," "));
	
	//Caso o número de pokemons de cada jogador esteja dentro das condições estabelecidas, os atributos serão transferidos para os campos das estruturas
	if( (N<=100 && N>=1) && (M<=100 && M>=1) ){
	
	flag=inserir(arq,J1,J2,&N,&M,linha);
	
	if(flag){
	
	//Imprime, na tela, as informações contidas no arquivo
	printf("%d %d \n",N,M);
	for(i=0;i<N;i++){
		printf("%s %.0f %.0f %.0f %s",J1[i].nome,J1[i].ataque,J1[i].defesa,J1[i].vida,J1[i].tipo);
	}
	for(i=0;i<M;i++){
		printf("%s %.0f %.0f %.0f %s",J2[i].nome,J2[i].ataque,J2[i].defesa,J2[i].vida,J2[i].tipo);
	}
	
	printf("\n");
	
	batalha(J1,J2,&N,&M,d,&k);
    resultado(d,J1,J2,k,&N,&M);
    //Caso haja um valor negativo ou igual a 0 dentre os atributos lidos na função inserir:
}else{
	printf("Os atributos dos pokemons dados no arquivo sao invalidos.");
}
	//Caso os números "N" e "M", lidos inicialmente do arquivo, não obedeçam às condições pré-estabelecidas:
}else{
	printf("O(s) numero(s) de pokemons dado(s) no arquivo e(sao) invalido(s) ou nao existem.");
}
    // Caso o arquivo lido seja nulo:
}else{
	printf("O nome do arquivo disposto nao existe ou voce nao tem permissao para abri-lo.\n\n");
}

}

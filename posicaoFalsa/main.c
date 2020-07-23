/*
	Este progrma localiza zeros reais em funcoes reais
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//Arg1
float equacao(float x){
	float eq;

	eq = sin(x) + x*x - 1; // Intervalos que tem raiz [1.3 e 1.4] e [0 e 1]

	return eq;
}

int main(void){
	
	//Limites
	float mim; // Arg 2
	float max; // Arg 3 
	float atual;
	float erro; // Arg 4
    int maxIt; // Arg 5

	//Equacoes
	float eqMim;
	float eqMax;
	float eqAtual;
	float sinalMim;
	float sinalMax;

	//Contador de iteracoes
	int k=1;	//Inicia em 1, pois a primeira iteracao eh feita fora do while -- Arg 6

	puts("\nEste programa encontra zeros reais em funcoes reais pelo metodo da falsa posicao");

	puts("Digite seu valor minimo");
	scanf("%f", &mim);
	puts("Digite seu valor maximo");
	scanf("%f", &max);
    puts("Digite seu o erro");
	scanf("%f", &erro);
    puts("Digite seu o max de iteracoes");
	scanf("%d", &maxIt);

    if (equacao(mim) == 0 || equacao(max) == 0) {
        printf("Raiz é um dos limites do intervalo. Raiz é %f\n", equacao(mim) == 0 ? mim : max);
        exit(0);
    } else if (maxIt <= 0) {
        printf("O numero maximo de iteracoes tem que ser superior a 0");
        exit(0);
    }



	eqMim = equacao(mim);
	eqMax = equacao(max);
	atual = (mim*eqMax - max*eqMim)/(eqMax - eqMim);

	while( fabs(equacao(atual)) > erro ){
		eqMim = equacao(mim);
		eqMax = equacao(max);
		eqAtual = equacao(atual);

		atual = (mim*eqMax - max*eqMim)/(eqMax - eqMim);

		sinalMim = equacao(mim) * equacao(atual);

		if(sinalMim < 0){
			mim = atual;
		} else {
			max = atual;
		}
        
        if (maxIt == k) {
            printf("Numero de iteracoes maximo atingido: arg5 %d ", maxIt);
            printf("\nf(x%d) = %f",k, eqAtual );
            printf("\nNumero de iteracoes: %d", k);
            printf("\nA funcao parou no valor: %5.5f", atual);  // Arg 7
            puts("\n\nFIM DO PROCESSO.\n");
            return 0;
        }
		k++;
	}
    if(fabs(equacao(atual)) < erro) {
        printf("\nf(x%d) = %f",k, equacao(atual) );
        printf("\nNumero de iteracoes: %d", k);
        printf("\nA funcao chega no zero no valor: %5.5f", atual);  // Arg 7
        puts("\n\nFIM DO PROCESSO.\n");
    } else {
        printf("\nf(x%d) = %f",k, equacao(atual) );
        printf("\nNumero de iteracoes: %d", k);
        printf("\nA funcao nao atingiu a precisao desejada no itervalo, ultimo valor testado: %5.5f", atual);  // Arg 7
        puts("\n\nFIM DO PROCESSO.\n");
    }
	return 0;
}
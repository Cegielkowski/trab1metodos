/*
	Este progrma localiza zeros reais em funcoes reais
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef float (funcao)(float arg);

float executaFuncao(funcao *funcao, float arg ){
    float resultado;
    if( funcao != NULL ){
        resultado = funcao(arg);
        return resultado;
    }
    printf("Erro ao executar função");
    exit(0);
}

float funcao1(float x){  // Entre 0 e 1
    return sin(x) + x*x - 1;
}
float funcao2(float x){ // Entre 0.5 e 1
    return 4*cos(x) - exp(x);
}
float funcao3(float x){ // Entre 1 e 3
    return x *x *x - 18;
}

float posicaoFalsa(funcao *f, float a, float b, float e, int maxIteracao){

	float eqMin, eqMax, eqAtual, sinalMin, sinalMax, atual;
	int iteracao=1;	//Inicia em 1, pois a primeira iteracao eh feita fora do while -- Arg 6



	eqMin = f(a);
	eqMax = f(b);
	atual = (a*eqMax - b*eqMin)/(eqMax - eqMin);
	printf("Ite\ta\t\tf(a)\t\tb\t\tf(b)\t\tXk\n");
	printf("%2d\t%4.6f\t%4.6f\t%4.6f\t%4.6f\t%4.6f\n", iteracao, a, eqMin, b, eqMax, atual);

	while( fabs(f(atual)) > e ){
		eqMin = f(a);
		eqMax = f(b);
		eqAtual = f(atual);

		atual = (a*eqMax - b*eqMin)/(eqMax - eqMin);

		sinalMin = f(a) * f(atual);

		if(sinalMin < 0){
			a = atual;
		} else {
			b = atual;
		}
		printf("%2d\t%4.6f\t%4.6f\t%4.6f\t%4.6f\t%4.6f\n", iteracao, a, eqMin, b, eqMax, atual);

        if (maxIteracao == iteracao) {
            printf("Numero de iteracoes maximo atingido: arg5 %d ", maxIteracao);
            printf("\nf(x%d) = %f",iteracao, eqAtual );
            printf("\nNumero de iteracoes: %d", iteracao);
            printf("\nA funcao parou no valor: %5.5f", atual);  // Arg 7
            printf("\n\nFIM DO PROCESSO.\n");
            return atual;
        }
		iteracao++;
	}
    if(fabs(f(atual)) < e) {
        printf("\nf(x%d) = %f",iteracao, f(atual) );
        printf("\nNumero de iteracoes: %d", iteracao);
        printf("\nA funcao chega no zero no valor: %5.5f", atual);  // Arg 7
        printf("\n\nFIM DO PROCESSO.\n");
        return atual;
    } else {
        printf("\nf(x%d) = %f",iteracao, f(atual) );
        printf("\nNumero de iteracoes: %d", iteracao);
        printf("\nA funcao nao atingiu a precisao desejada no itervalo, ultimo valor testado: %5.5f", atual);  // Arg 7
        printf("\n\nFIM DO PROCESSO.\n");
        return atual;
    }
}



int main(void){

	float limiteInferior, limiteSuperior, erro; // Arg 2, 3, 4
    int maxIteracao, escolha; // Arg 5
    int *funcaoEscolhida[4];

    //Mapeando as 3 funções
    funcaoEscolhida[1] = &funcao1;
	funcaoEscolhida[2] = &funcao2;
	funcaoEscolhida[3] = &funcao3;

	printf("\nEste programa encontra zeros reais em funcoes reais pelo metodo da falsa posicao\n\n");
    printf("\nEscolha a funcao\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
	scanf("%d", &escolha);
	printf("Digite seu valor minimo:\n");
	scanf("%f", &limiteInferior);
	printf("Digite seu valor maximo:\n");
	scanf("%f", &limiteSuperior);
    printf("Digite seu o erro:\n");
	scanf("%f", &erro);
    printf("Digite seu o max de iteracoes:\n");
	scanf("%d", &maxIteracao);

    if (executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 || executaFuncao(funcaoEscolhida[escolha], limiteSuperior) == 0) {
        printf("Raiz é um dos limites do intervalo. Raiz é %f\n", executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 ? limiteInferior : limiteSuperior);
        exit(0);
    } else if (maxIteracao <= 0) {
        printf("O numero maximo de iteracoes tem que ser superior a 0");
        exit(0);
    }

    posicaoFalsa(funcaoEscolhida[escolha], limiteInferior, limiteSuperior, erro, maxIteracao);

	return 0;
}

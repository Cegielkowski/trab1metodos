/*  Método de Newton para disciplina de Métodos Numéricos Computacionais
    UNESP Bauru 1 Semestre - 2020
*/

#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

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

float funcao1(float x){
    return 3 *x - cos(x) -1;
}
float funcao2(float x){
    return 4*cos(x) - exp(x);
}
float funcao3(float x){
    return x *x *x - 18;
}

// Método derivada
float derivada(funcao *f, float x){
    float h = 1.0e-6; // Numero tendendo a 0
    return (f(x+h)-f(x-h))/(2*h);
}


int NewtonMethod(funcao *f, float x0, float e, int maxIteracao){
    float x1, f0, f1, g0, erro=1;
    int iteracao = 1;
    printf("\nIteracao\tx0\t\tf(x0)\t\tx1\t\tf(x1)\t\tErro\n");
    do{
        g0 = derivada(f, x0);
        f0 = f(x0);
        if(g0 == 0.0){
            printf("Erro de Calculo!\nF'(x) nao pode ser 0 para que o erro possa ser calculado.");
            //Somente para o programa não fechar
            getch();
            exit(0);
        }

        x1 = x0 - f0/g0;
        f1 = f(x1);
        erro = fabs(x1-x0)/fabs(x1);

        printf("%d\t\t%f\t%f\t%f\t%f\t%f\n",iteracao,x0,f0,x1,f1,erro);
        x0 = x1;

        iteracao = iteracao+1;

        if(iteracao > maxIteracao){
            printf("Nao convergiu no maximo das iteracoes.");
            //Somente para o programa não fechar
            getch();
            exit(0);
        }



	}while(erro>e);

	printf("\nA raiz aproximada e': %.4f e foram necessarias %d iteracoes para chegar nesse valor.", x1, iteracao-1);
}


void main()
{
	 float xInicial, erro;
	 int maxIteracao, escolha;
	 int *funcaoEscolhida[4];

    //Mapeando as 3 funções
	 funcaoEscolhida[1] = &funcao1;
	 funcaoEscolhida[2] = &funcao2;
	 funcaoEscolhida[3] = &funcao3;

	 printf("\nEscolha a funcao\n[1] 3x - cos(x) - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
	 scanf("%d", &escolha);
	 printf("\nDigite o chute inicial:\n");
	 scanf("%f", &xInicial);
	 printf("Digite o erro maximo:\n");
	 scanf("%f", &erro);
	 printf("Digite o numero maximo de iteracoes:\n");
	 scanf("%d", &maxIteracao);


    /* Chamada do método de Newton Args ( Função Escolhida, Chute Inicial, Erro Máximo e Máximo de Iterações */
    NewtonMethod(funcaoEscolhida[escolha], xInicial, erro, maxIteracao);

    //Somente para o programa não fechar
    getch();
}

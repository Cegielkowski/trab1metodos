/*
TRABALHO 1 DISCIPLINA DE M�TODOS NUM�RICOS COMPUTACIONAIS
UNESP Bauru - 1 SEM 2020
AMANDA MEIRA
ARTHUR CIPOLARI 151022071
LUCAS CEGIELKOWSKI
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Declarando equa��o para executar como fun��o
typedef double (*funcao)(double arg);
// M�todo que executa a equa��o fora da fun��o para valida��es
double executaFuncao(funcao funcao, double arg){
    if( funcao != NULL ){
        return (*funcao)(arg);
    }
    printf("Erro ao executar fun��o");
    exit(0);
}
// Fun��es definidas
double funcao1(double x){  // Entre 0 e 1
    return (sin(x) + (x*x) - 1);
}
double funcao2(double x){ // Entre 0.5 e 1
    return ((4*cos(x)) - exp(x));
}
double funcao3(double x){ // Entre 1 e 3
    return ((x *x *x) - 18);
}
// M�todo bisseccao
double bisseccao(funcao f, double a, double b, double e, int maxIteracao){

      int iteracao = 1;
      double raizAuxiliar, raiz, erroParcial;

  printf("Ite\ta\t\tb\t\tm\t\tf(m)\t\terror\n");
  do {

    raizAuxiliar = raiz;
    raiz = (a + b) / 2;
    printf("%2d\t%4.6lf\t%4.6lf\t%4.6f\t%4.6lf\t", iteracao, a, b, raiz, (*f)(raiz));
    if ((*f)(raiz) == 0) {
      printf("A raiz e %4.6lf\n", raiz);
    } else if (((*f)(a) * (*f)(raiz)) < 0) {
      b = raiz;
    } else a = raiz;
    erroParcial = fabs(raiz - raizAuxiliar);
    if (iteracao == 1) {
      printf("----\n");
    } else printf("%4.6lf\n", erroParcial);

    if (erroParcial < e) {
      printf("A raiz aproximada e %4.6lf  Numero de iteracoes: %d ", raiz, iteracao);
      return 0;
    }

    if (maxIteracao == iteracao) {
      printf("Numero de iteracoes maximo atingido: %d ", maxIteracao);
      return 0;
    }
    iteracao++;
  } while (erroParcial > e);
}
// M�todo posi��o falsa
double posicaoFalsa(funcao f, double a, double b, double e, int maxIteracao){

	double eqMin, eqMax, eqAtual, sinalMin, sinalMax, atual;
	int iteracao=1;	//Inicia em 1, pois a primeira iteracao eh feita fora do while -- Arg 6



	eqMin = (*f)(a);
	eqMax = (*f)(b);
	atual = (a*eqMax - b*eqMin)/(eqMax - eqMin);
	printf("Ite\ta\t\tf(a)\t\tb\t\tf(b)\t\tXk\n");
	printf("%2d\t%4.6lf\t%4.6lf\t%4.6lf\t%4.6lf\t%4.6lf\n", iteracao, a, eqMin, b, eqMax, atual);

	while( fabs((*f)(atual)) > e ){
		eqMin = (*f)(a);
		eqMax = (*f)(b);
		eqAtual = (*f)(atual);

		atual = (a*eqMax - b*eqMin)/(eqMax - eqMin);

		sinalMin = (*f)(a) * (*f)(atual);

		if(sinalMin < 0){
			a = atual;
		} else {
			b = atual;
		}
		printf("%2d\t%4.6lf\t%4.6lf\t%4.6lf\t%4.6lf\t%4.6lf\n", iteracao, a, eqMin, b, eqMax, atual);

        if (maxIteracao == iteracao) {
            printf("Numero de iteracoes maximo atingido: arg5 %d ", maxIteracao);
            printf("\nf(x%d) = %lf",iteracao, eqAtual );
            printf("\nNumero de iteracoes: %d", iteracao);
            printf("\nA funcao parou no valor: %5.5lf", atual);  // Arg 7
            printf("\n\nFIM DO PROCESSO.\n");
            return atual;
        }
		iteracao++;
	}
    if(fabs((*f)(atual)) < e) {
        printf("\nf(x%d) = %lf",iteracao, (*f)(atual) );
        printf("\nNumero de iteracoes: %d", iteracao);
        printf("\nA funcao chega no zero no valor: %5.5lf", atual);  // Arg 7
        printf("\n\nFIM DO PROCESSO.\n");
        return atual;
    } else {
        printf("\nf(x%d) = %lf",iteracao, (*f)(atual) );
        printf("\nNumero de iteracoes: %d", iteracao);
        printf("\nA funcao nao atingiu a precisao desejada no itervalo, ultimo valor testado: %5.5lf", atual);  // Arg 7
        printf("\n\nFIM DO PROCESSO.\n");
        return atual;
    }
}
// M�todo derivada
double derivada(funcao f, double x){
    double h = 1.0e-6; // Numero tendendo a 0
    return ((*f)(x+h)-(*f)(x-h))/(2*h);
}
// M�todo Newton
double NewtonMethod(funcao f, double x0, double e, int maxIteracao){
    double x1, f0, f1, g0, erro=1;
    int iteracao = 1;
    printf("\nIteracao\tx0\t\tf(x0)\t\tx1\t\tf(x1)\t\tErro\n");
    do{
        g0 = derivada(f, x0);
        f0 = (*f)(x0);
        if(g0 == 0.0){
            printf("Erro de Calculo!\nF'(x) nao pode ser 0 para que o erro possa ser calculado.");
            return 0;
        }

        x1 = x0 - f0/g0;
        f1 = (*f)(x1);
        erro = fabs(x1-x0)/fabs(x1);

        printf("%d\t\t%lf\t%lf\t%lf\t%lf\t%lf\n",iteracao,x0,f0,x1,f1,erro);
        x0 = x1;

        iteracao = iteracao+1;

        if(iteracao > maxIteracao){
            printf("Nao convergiu no maximo das iteracoes.");
            return 0;
        }

	}while(erro>e);

	printf("\nA raiz aproximada e': %.4lf e foram necessarias %d iteracoes para chegar nesse valor.", x1, iteracao-1);
}

int main(void){

    double xInicial, limiteInferior, limiteSuperior, erro; // Arg 2, Arg 3, Arg 4
    int maxIteracao, escolha, metodo=9; // Arg 5
    funcao funcaoEscolhida[4]; // Arg 1

    //Mapeando as 3 fun��es
    funcaoEscolhida[1] = &funcao1;
	funcaoEscolhida[2] = &funcao2;
	funcaoEscolhida[3] = &funcao3;

	printf("Programa desenvolvido para o Trabalho 1 da\ndisciplina de Metodos Numericos Computacionais\nda UNESP Bauru - 1 Sem 2020\n\n\n");


    while (metodo!=0){
        printf("\n\n=============MENU===============");
        printf("\n================================");
        printf("\n===  1-Metodo Bissecao       ===");
        printf("\n===  2-Metodo Posicao Falsa  ===");
        printf("\n===  3-Calcular Derivada     ===");
        printf("\n===  4-Metodo Newton         ===");
        printf("\n===  0-Para Sair             ===");
        printf("\n================================");
        printf("\n================================");
        printf("\nEscolha: ");
        scanf ("%d", &metodo);
        if(metodo==0){
            printf ("\nPressione qualquer tecla para fechar...\n");
            exit(0);
        }
        switch (metodo){
        case 1:
            printf("\nMETODO BISSECCAO ESCOLHIDO\n\n");
            printf("\nEscolha a funcao\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\nEscolha: ");
            scanf("%d", &escolha);
            printf("Digite o intervalo [a , b] Ex: 1 3: \n");
            scanf("%lf %lf", &limiteInferior, &limiteSuperior);
            printf("Digite o erro maximo:\n");
            scanf("%lf", &erro);
            printf("Digite o numero maximo de iteracoes:\n");
            scanf("%d", &maxIteracao);

            if ((executaFuncao(funcaoEscolhida[escolha], limiteInferior) * executaFuncao(funcaoEscolhida[escolha], limiteSuperior)) > 0) {
                printf("Valores f inferior %lf f superior %lf", executaFuncao(funcaoEscolhida[escolha], limiteInferior), executaFuncao(funcaoEscolhida[escolha], limiteSuperior) );
                printf("Intervalo invalido!"); //para testar se o intervalo de pesquisa
                break;                           //esta ok ou nao
            } else if (executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 || executaFuncao(funcaoEscolhida[escolha], limiteSuperior) == 0) {
                printf("Raiz � um dos limites do intervalo. Raiz � %lf\n", executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 ? limiteInferior : limiteSuperior);
                break;
            } else if (maxIteracao <= 0) {
                printf("O numero maximo de iteracoes tem que ser superior a 0");
                break;
            }
            bisseccao(*funcaoEscolhida[escolha], limiteInferior, limiteSuperior, erro, maxIteracao);
            break;

        case 2:
           	printf("\nMETODO POSICAO FALSA ESCOLHIDO\n\n");
            printf("\nEscolha a funcao\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
            scanf("%d", &escolha);
            printf("Digite o intervalo [a , b] Ex: 1 3: \n");
            scanf("%lf %lf", &limiteInferior, &limiteSuperior);
            printf("Digite o erro maximo:\n");
            scanf("%lf", &erro);
            printf("Digite o numero maximo de iteracoes:\n");
            scanf("%d", &maxIteracao);

            if (executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 || executaFuncao(funcaoEscolhida[escolha], limiteSuperior) == 0) {
                printf("Raiz � um dos limites do intervalo. Raiz � %lf\n", executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 ? limiteInferior : limiteSuperior);
                break;
            } else if (maxIteracao <= 0) {
                printf("O numero maximo de iteracoes tem que ser superior a 0");
                break;
            }

            posicaoFalsa(funcaoEscolhida[escolha], limiteInferior, limiteSuperior, erro, maxIteracao);
            break;

        case 3:
            printf("\nCALCULO DA DERIVADA ESCOLHIDO\n\n");
            printf("\nEscolha a funcao para calcular a derivada no ponto\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
            scanf("%d", &escolha);
            printf("Digite o ponto a ser calculada a derivada:\n");
            scanf("%lf", &xInicial);
            printf("\n\nA f'(%lf) e': %lf", xInicial, derivada(funcaoEscolhida[escolha], xInicial));
            break;

        case 4:
            printf("\nMETODO NEWTON ESCOLHIDO\n\n");
            printf("\nEscolha a funcao\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
            scanf("%d", &escolha);
            printf("\nDigite o chute inicial:\n");
            scanf("%lf", &xInicial);
            printf("Digite o erro maximo:\n");
            scanf("%lf", &erro);
            printf("Digite o numero maximo de iteracoes:\n");
            scanf("%d", &maxIteracao);


            /* Chamada do m�todo de Newton Args ( Fun��o Escolhida, Chute Inicial, Erro M�ximo e M�ximo de Itera��es */
            NewtonMethod(funcaoEscolhida[escolha], xInicial, erro, maxIteracao);
            break;

        default:
            printf("\nOpcao Invalida!\nEscolha novamente...\n\n");
        }
    }
    return 0;
}



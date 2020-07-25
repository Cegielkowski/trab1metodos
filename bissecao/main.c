#include <stdio.h>
#include <stdlib.h>
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


int bisseccao(funcao *f, float a, float b, float e, int maxIteracao){

      int iteracao = 1;
      float raizAuxiliar, raiz, erroParcial;

  printf("Ite\ta\t\tb\t\tm\t\tf(m)\t\terror\n");
  do {

    raizAuxiliar = raiz;
    raiz = (a + b) / 2;
    printf("%2d\t%4.6f\t%4.6f\t%4.6f\t%4.6f\t", iteracao, a, b, raiz, f(raiz));
    if (f(raiz) == 0) {
      printf("A raiz e %4.6f\n", raiz);
    } else if ((f(a) * f(raiz)) < 0) {
      b = raiz;
    } else a = raiz;
    erroParcial = fabs(raiz - raizAuxiliar);
    if (iteracao == 1) {
      printf("----\n");
    } else printf("%4.6f\n", erroParcial);

    if (erroParcial < e) {
      printf("A raiz aproximada e %4.6f  Numero de iteracoes: %d ", raiz, iteracao);
      return 0;
    }

    if (maxIteracao == iteracao) {
      printf("Numero de iteracoes maximo atingido: %d ", maxIteracao);
      return 0;
    }
    iteracao++;
  } while (erroParcial > e);
}


int main() {

    float limiteInferior, limiteSuperior, erro;
    int escolha, maxIteracao;
    int *funcaoEscolhida[4];
    //Mapeando as 3 funções
    funcaoEscolhida[1] = &funcao1;
	funcaoEscolhida[2] = &funcao2;
	funcaoEscolhida[3] = &funcao3;



	printf("\nEscolha a funcao\n[1] sen(x) - x^2 - 1 \n[2] 4cos(x) - exp(x)\n[3] x^3 - 18\n");
	scanf("%d", &escolha);
    printf("Digite o intervalo [a , b] Ex: 1 3: \n");
    scanf("%f %f", &limiteInferior, &limiteSuperior);
    printf("Erro esperado: \n");
    scanf("%f", &erro);
    printf("Numero maximo de iteracoes: \n");
    scanf("%d", &maxIteracao);

    if ((executaFuncao(funcaoEscolhida[escolha], limiteInferior) * executaFuncao(funcaoEscolhida[escolha], limiteSuperior)) > 0) {
        printf("Intervalo invalido!"); //para testar se o intervalo de pesquisa
        exit(1);                            //esta ok ou nao
    } else if (executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 || executaFuncao(funcaoEscolhida[escolha], limiteSuperior) == 0) {
        printf("Raiz é um dos limites do intervalo. Raiz é %f\n", executaFuncao(funcaoEscolhida[escolha], limiteInferior) == 0 ? limiteInferior : limiteSuperior);
        exit(0);
    } else if (maxIteracao <= 0) {
        printf("O numero maximo de iteracoes tem que ser superior a 0");
        exit(0);
    }

    bisseccao(funcaoEscolhida[escolha], limiteInferior, limiteSuperior, erro, maxIteracao);

  return 0;
}

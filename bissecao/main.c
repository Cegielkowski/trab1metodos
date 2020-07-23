#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#define f(x)((x * x * x) - 18)

int main() {
  float arg2 = 0, arg3 = 0, error = 0, arg7, mold, arg4;
  int i = 0, arg6, arg5;
  printf("Digite o intervalo arg2 e arg3 ( ex: 1 3 ): ");
  scanf("%f %f", & arg2, & arg3);
  printf("Erro esperado: ");
  scanf("%f", & arg4);
  printf("Numero maximo de iteracoes: ");
  scanf("%d", & arg5);
  if ((f(arg2) * f(arg3)) > 0) {
    printf("Intervalo invalido Exit!"); //para testar se o intervalo de pesquisa
    exit(1); // Esta ok ou nao
  } else if (f(arg2) == 0 || f(arg3) == 0) {
    printf("Raiz é um dos limites do intervalo. Raiz é %f\n", f(arg2) == 0 ? arg2 : arg3);
    exit(0);
  } else if (arg5 <= 0) {
    printf("O numero maximo de iteracoes tem que ser superior a 0");
    exit(0);
  }
  printf("Ite\ta\t\tb\t\tm\t\tf(m)\t\terror\n");
  do {
    arg6 = i + 1;
    mold = arg7;
    arg7 = (arg2 + arg3) / 2;
    printf("%2d\t%4.6f\t%4.6f\t%4.6f\t%4.6f\t", i++, arg2, arg3, arg7, f(arg7));
    if (f(arg7) == 0) {
      printf("A raiz e %4.6f\n", arg7);
    } else if ((f(arg2) * f(arg7)) < 0) {
      arg3 = arg7;
    } else arg2 = arg7;
    error = fabs(arg7 - mold);
    if (i == 1) {
      printf("----\n");
    } else printf("%4.6f\n", error);

    if (error < arg4) {
      printf("A raiz aproximada e %4.6f  Numero de iteracoes: %d ", arg7, arg6);
      return 0;
    }

    if (arg5 == arg6) {
      printf("Numero de iteracoes maximo atingido: arg5 %d ", arg5);
      return 0;
    }
  } while (error > arg4);

  return 0;
}
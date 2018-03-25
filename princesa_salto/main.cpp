#include <stdio.h>

void pop_front(int vet[], int * qtd){
    for(int i = 0; i < *qtd - 1; i++){
        vet[i] = vet[i + 1];
    }
    *qtd -= 1;
}
void push_back(int vet[], int * qtd, int value){
    vet[*qtd] = value;
    *qtd += 1;
}

void mostrar(int vet[],int qtd){
    for(int i=0;i<qtd;i++){
        printf("%d \n \n",vet[i]);
    }
}

void rodar(int vet[], int * qtd, int valor){
        push_back(vet,&(*qtd),valor);
        pop_front(vet,&(*qtd));
}

int main()
{
    int qtd=0;
    scanf("%i",&qtd);
    int escolhido=0;
    scanf("%i",&escolhido);

    int vet[qtd];
    for(int i=0;i<qtd;i++)
        vet[i]=i+1;

    while(vet[0] != escolhido){
        rodar(vet,&qtd,vet[0]);
    }


    while (qtd > 1) {
        rodar(vet,&qtd,vet[0]);
        pop_front(vet,&qtd);
        for(int i=0;i<escolhido;i++)
            rodar(vet,&qtd,vet[0]);

        escolhido=vet[0];


    }
    mostrar(vet,qtd);

    return 0;
}

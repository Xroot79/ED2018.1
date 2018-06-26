#include <iostream>
#include <ctime>
#include <cstdlib> //rand
#include "libs/ed_sort.h"

using namespace std;

//cores rgbcymkw
//red, green, blue, cyan, yellow, magenta, black, white





void palma_sort(vector<int>& vet){
    int ultimo = vet.size() - 1;
    for(int i = 0; i <= ultimo; i++, ultimo--){
        int imaior = i;
        int imenor = i;
        view_set_faixa(i, ultimo);
        for(int j = i; j <= ultimo; j++){
            view_show(vet, {i, j, imenor, imaior, ultimo}, "rgyyr");
            if(vet[j] < vet[imenor]){
                imenor = j;
                view_show(vet, {i, j, imenor, imaior, ultimo}, "rgyyr");
            }
            else if(vet[j] > vet[imaior]){
                imaior = j;
                view_show(vet, {i, j, imenor, imaior, ultimo}, "rgyyr");
            }
        }
        std::swap(vet[imenor], vet[i]);
        if(imaior == i)
            imaior = imenor;
        std::swap(vet[imaior], vet[ultimo]);
        view_show(vet, {i, imenor, imaior, ultimo}, "ryyr");
    }
}
void m_palma_sort(vector<int>& vet){
    int ultimo = vet.size()-1; //identifica pos do ultimo elemento
    for(int i = 0 ; i <= ultimo; i++ ,ultimo--){//percorre batendo palma (incrementando o primeiro e decrementando o ultimo)
        int imenor = 0;//cria pos que vai fkr o valor menor
        int imaior = 0;//cria pos que vai fkr o valor maior
        for(int j = i;j <= ultimo; j++ ){//percorre o vetor até o ultimo elemento a cada iteraçao de i
            if(vet[j] < vet[imenor]){//verifica se vetor na pos j e menor q vetor na posicao imenor
                imenor = j;//se sim imenor recebe a pos j
            }else if(vet[j] > vet[imaior]){//se nao verifica se é maior
                imaior = j;//se for imaior recebe a pos j
            }
        }
        std::swap(vet[imenor],vet[i]);//depois de uma iteraçao de i sabendo imenor e imaior troca o imenor com o primeiro elemento (i)
        if(imaior = i)//verifica se por acaso o imaior por coincidencia comeõu em i
            imaior=imenor;//se for o caso o imaior vai receber o imenor
        std::swap(vet[imaior],vet[ultimo])//troca o vaor do maior pro ultimo elemento;
    }
}

//intervalos fechados [C, F]
#define qshow view_show(vet, {C, F, i, j}, "rgby")
void quick_sort(vector<int> & vet, int C, int F){
    if(C >= F)
        return;
    int pivo = vet[C];
    int i = C;
    int j = F;
    while(i <= j){
        while(vet[i] < pivo)
            i++;
        while(vet[j] > pivo)
            j--;
        if(i <= j)
            std::swap(vet[i++], vet[j--]);
    }
    quick_sort(vet, C, j);
    quick_sort(vet, i, F);
}
void m_quicksort(vector<int>& vet, int comeco , fim){
    if(comeco>=fim)//se começo maior ou igual ao fim não tem mais oq fazer retorna
        return;
    int pivo = vet[comeco]; // defininfo pivo como valor valido
    int begin = comeco; //atribuindo valores aos limite_comeco
    int end = fim; //atribuindo valores aos limite_fim

    while(begin <= end){//enquanto n se cruzar
        while(vet[begin] < pivo) //enquanto não achar um valor maior que pivo avance
            begin++;
        while(vet[end] > pivo) //enquanto não achar um valor menor que pivo retroceda
            end--;
        if(begin <= end){ //se saiu das condições tem um valor maior na esquerda e valor menor na direira
            std::swap(vet[begin],vet[end]);//troque os valores
            begin++;end--;
        }
    }
    m_quicksort(vet,comeco,begin);//chame pra outra particao
    m_quicksort(vet,begin,end);
}

void merge(vector<int>& vet, int a, int b, int c){
    int i = a;
    int j = b;
    vector<int> vaux;
    vaux.reserve(c - a);
    while((i < b) && (j < c)){ //comparar particoes
        if(vet[i] < vet[j])
            vaux.push_back(vet[i++]);
        else
            vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(i < b){
        vaux.push_back(vet[i++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(j < c){
        vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    for(int i = 0; i < (int) vaux.size(); i++){
        vet[a + i] = vaux[i];
        view_show(vet, {a + i}, "r");
    }
}
void m_merge(vector<int>& vet, int comeco, int meio ,int fim){

    int i= comeco;//pegando pos comeco
    int j= meio;//pegando a posicao meio
    vector<int> vet_aux ;//criando vetro auxiliar
    vet_aux.reserve(fim-comeco);// reservando no vetor o espaço fim - comeco
    while((i < meio) && (j < fim) ){ //enquanto a particao existir
        if(vet[i] < vet[j])//compare se valor do i é menor q j
            vet_aux.push_back(vet[i++]);//se sim adicione i no vetor auxiliar e ande
        else//se nao
            vet_aux.push_back(vet[j++]);//adicione j no vetor auxiliar e ande
    }
    //saiu do while mas tenho que verificar se ainda tem elementos nas partições
    while(i < meio){
        vaux.push_back(vet[i++]);
    }
    while(j < fim){
        vaux.push_back(vet[j++]);
    }
    //organiza o vetor
    for(int i = 0;i < vet_aux.size();i++)
        vet[a+i]=vet_aux[i]

}

//particao [C, F[
void mergesort(vector<int>& vet, int a, int c){
    if(c == a + 1)
        return;
    int b = (a + c)/2;
    mergesort(vet, a, b);
    mergesort(vet, b, c);
    merge(vet, a, b, c);
}
void m_mergesort(vector<int>& vet,int comeco, int fim){
    if(fim == comeco+1)//se fim = comeco não há nd pra fazer retorne
        return;
    int meio = (comeco+fim)/2;//atribuindo valor do meio
    m_mergesort(vet,comeco,meio);//aplica o mergesort no comeco e meio
    m_mergesort(vet,meio,fim);//aplica o mergesort no meio e fim
    m_merge(vet,comeco,meio,fim);//com o vet ja organizado aplica-se o merge nele todo.
}




int main(){
    srand(time(NULL));

    const int qtd = 70;
    vector<int> vet(qtd, 0);

    int min = 10;
    int max = 400;

    for(int i = 0; i < qtd; i++)
        vet[i] = (rand() % (max - min + 1) + min);

//    view_set_dot();
    view_set_bar();
//    view_set_faixa(0, qtd - 1);


    //palma_sort(vet);
    //quick_sort(vet, 0, vet.size() - 1);
    mergesort(vet, 0, vet.size());

   // test_sort(vet);
    view_lock();
    return 0;
}






















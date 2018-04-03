#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;


const int nc = 60;
const int nl = 20;

struct Par{
    int l,c;
    Par(int l =0,int c=0){
        this->l=l;
        this->c=c;
    }
};

vector<Par> pegaVizinhos(Par par){
    vector<Par> vetor;
    vetor.push_back(Par(par.l,par.c+1));
    vetor.push_back(Par(par.l,par.c-1));
    vetor.push_back(Par(par.l+1,par.c));
    vetor.push_back(Par(par.l-1,par.c));
    return vetor;
}

vector<Par> embaralhar_posicoes(vector<Par> vetor){
    for(int i=0;i< (int) vetor.size();i++){
            int aleatorio = rand() % vetor.size();
            swap(vetor[i],vetor[aleatorio]);
    }

    return vetor;
}

void mostrar(vector<string>& mat){
    cout << string(50, '\n');
    for(string s : mat)
        cout << s << endl;
    getchar();
}


int queimar(vector<string> &mat, int l, int c,int cont){
    if(l < 0 || l >= nl)
        return 0;
    if(c < 0 || c >= nc)
        return 0;
    if(mat[l][c] != '#')
        return 0;

    mat[l][c]='0'+(cont%10);
    mostrar(mat);

    cont++;

    int total = 0;
    total++;


    for(Par par : embaralhar_posicoes( pegaVizinhos(Par(l,c))))
        total += queimar(mat,par.l,par.c,cont);

    mat[l][c]='*';
    mostrar(mat);

    return total;
}


int main()
{
    srand(time(NULL));
    //os containers tem uma construção padrao
    //container<tipo> nome(qtd, elemento_default)
    //cria um vetor de string
    //com nl elementos da string default
    //a string default sao 30 char ' '
    vector<string> mat(nl, string(nc, '#'));
    //int narvores = nl * nc * 1.5;
    //insere varias arvores em lugares aleatorios
    //muitas serao superpostas
//    for(int i = 0; i < narvores; i++){
//        mat[rand() % nl][rand() % nc] = '#';
//    }

    mostrar(mat);
    int total = queimar(mat, 0, 0,0);

    cout << total << " arvores queimaram\n";

    return 0;
}

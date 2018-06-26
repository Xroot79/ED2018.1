#include <vector>
#include <list>
#include <algorithm>
#include <ctime>//funcao time
#include <cstdlib> //funcao srand
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

//Cada dia possui 6 horas de trabalho
//60 minutos x 6 horas = 360 minutos
//cada minuto eh um turno.
const int TURNOS_DIA = 360;

//A quantidade máxima de caixa.
const int MAX_CAIXAS = 10;

//Esse valor determina o quanto o banco por caixa por dia de trabalho
const int CUSTO_CAIXA_DIA = 100;

//numero de simulacoes de teste
const int N_EXEC_TESTE = 100;

struct Cliente
{
    int paciencia;
    int documentos;
    std::string nome;

    Cliente(int paciencia, int documentos)
    {
        gerarNomeAleatorio();
        this->paciencia = paciencia;
        this->documentos = documentos;
    }

    void gerarNomeAleatorio(){
        std::string consoantes = "bcdfghjklmnpqrstvxyz";
        std::string vogais = "aeiou";
        this->nome = std::string(1, consoantes[std::rand() % consoantes.size()]);
        this->nome += std::string(1, vogais[std::rand() % vogais.size()]);
    }
};



//gera um numero entre min e max, [min, max]
int rand_mm(int min, int max){
    static int init = 1;
    if(init){
        init = 0;
        srand(time(NULL));
    }
    return rand() % (max - min + 1) + min;
}

std::string to_string(const Cliente *cliente){
    std::stringstream str;
    str << "[" << cliente->nome << ":";
    str << "d" << setw(2) << cliente->documentos <<
           ":p" << setw(2) << cliente->paciencia << "]";
    return str.str();
}


void print_banco(list<Cliente *> fila, vector<Cliente *> caixas, int turno, int lucro){
    Cliente dummy(0, 0);
    int slot = to_string(&dummy).size();//quandos caracteres ocupa um cliente
    std::cout << string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "|";
    for(auto& x : caixas){
        if(x == nullptr)
            cout << std::string(slot - 2, ' ');
        else
            cout << to_string(x);
        cout << "|";
    }
    for(int x = 0; x < MAX_CAIXAS - (int) caixas.size(); x++)
        std::cout << std::string(slot - 2, '-') << "|";
    std::cout << endl;
    std::cout << "-" << std::string(slot - 2, ' ') << std::string((slot - 1) * MAX_CAIXAS, '-') << std::endl;

    std::cout << " ";
    int ind = 1;
    for(auto it = fila.begin(); it != fila.end(); it++, ind++){
        if(ind % MAX_CAIXAS == 0)
            cout << endl << " ";
        cout << to_string(*it) << " ";
    }
    std::cout << std::endl;
    std::cout << std::string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "Turno : " << turno << endl;
    std::cout << "Lucro : " << lucro << endl;
}

//pac é paciencia do cliente, entre min e max
//doc é a quantidade de documentos do cliente
//cli é a quantidade de clientes que entra por minuto
//numCaixas é o número de caixas no banco
int simulacao(pair<int, int> pac, pair<int, int> doc, pair<int, int> cli, int numCaixas){
    std::vector<Cliente*> caixa(numCaixas);
    std::list<Cliente*> fila;
    int turno = 1;
    int lucro = 0;

    //enquanto o banco estiver aberto ou houver clientes no banco faça:
        //gera aleatoriamento clientes de acordo com os parametros e insere
            //na fila de espera
        //para cada caixa
            //se o caixa esta vazio, chama alguém da fila de espera
        //para cada cliente da fila de espera
            //decremente a paciencia
            //se a paciencia for 0
                //retire o cliente do banco
        //para cada caixa
            //se tem cliente no caixa
                //decremente um documento do cliente e incremente 1 no lucro do banco
            //se nao tem mais documentos
                //envia o cliente para casa
    //retorne lucro - qtd_caixas * valor_diaria_do_caixa


    while(turno<=TURNOS_DIA || !fila.empty()){


        int qtd_cliAuto = rand_mm(cli.first,cli.second);
        for(int i = 0; i < qtd_cliAuto;i++)
            fila.push_back(new Cliente (rand_mm(pac.first, pac.second),
                                    rand_mm(doc.first, doc.second)));


        for(int i = 0;i <(int) numCaixas ; i++){
            if(caixa[i]!=nullptr){
                if(caixa[i]->documentos > 0){
                    caixa[i]->documentos--;
                    lucro++;
                }else{
                    auto c_aux= caixa[i];
                    caixa[i] = nullptr;
                    delete c_aux;
                }
            }else{
                if(fila.size() != 0){
                    caixa[i] = fila.front();
                    fila.pop_front();
                }
            }
        }

        for(auto it = fila.begin();it != fila.end();){
            if((*it)->paciencia !=0){
                (*it)->paciencia--;
                it++;
            }else{
               it = fila.erase(it);
            }
        }
    turno++;
    }
    return lucro - (numCaixas * CUSTO_CAIXA_DIA);
}

void calcular_melhorQtdCaixas(pair<int, int> pac, pair<int, int> doc, pair<int, int> cli){
    cout << " Numero de clientes chegando: " <<cli.first <<" - "<<cli.second<< endl;
    cout << " Paciência dos clientes:  " <<pac.first <<" - "<<pac.second<< endl;
    cout << " Documentos por cliente:  " <<doc.first <<" - "<<doc.second<< endl;
    vector<float> lucro_caixa(MAX_CAIXAS+1);

    for(int qtd_caixa = 1; qtd_caixa <= MAX_CAIXAS; qtd_caixa++){
        lucro_caixa[qtd_caixa] = 0;
        for(int teste = 0 ; teste < N_EXEC_TESTE ;teste++){
            lucro_caixa[qtd_caixa] += simulacao({pac.first,pac.second},{doc.first,doc.second},{cli.first,cli.second},qtd_caixa);
        }
        lucro_caixa[qtd_caixa] = lucro_caixa[qtd_caixa]/N_EXEC_TESTE;
    }


    int qtd_caixa_maior_lucro = 0;

    for(int qtd_caixa = 1; qtd_caixa <= MAX_CAIXAS; qtd_caixa++){
        if(lucro_caixa[qtd_caixa] > lucro_caixa[qtd_caixa_maior_lucro])
            qtd_caixa_maior_lucro = qtd_caixa;
    }


    cout << " Qtd. ideal de caixas: " <<qtd_caixa_maior_lucro << endl;

}



int main ()
{
    calcular_melhorQtdCaixas({1,5},{1,2},{0,4});
    //calcular_melhorQtdCaixas({1,60},{1,10},{0,1});
    //calcular_melhorQtdCaixas({1,20},{1,10},{0,2});
    //calcular_melhorQtdCaixas({1,25},{1,10},{0,5});
    return 0;
}

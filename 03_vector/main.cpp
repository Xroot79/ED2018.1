#include <iostream>

using namespace std;
struct Vetor{
    int * _data;
    int _capacidade;
    int _size;

    Vetor(int capacidade){
        this->_capacidade=capacidade;
        this->_size = 0;
        this->_data = new int[capacidade];
    }

    void push_back(int value){
        if(this->_size == this->_capacidade)
            return;

        this->reserve(2*_capacidade);
        this->_data[this->_size] = value;
        this->_size++;
    }

    void pop_back(){
        if(this->_size>0)
            this->_size--;;

        this->_data[_size] = 0;
        this->_size--;
    }

    int& front(){
        return _data[0];
    }

    int& back(){
        return _data[_size-1];
    }

    int* begin(){
        return &_data[0];
    }

    int* end(){
        return &_data[_size];
    }

    void reserve(int value){
        int capacidade_aux=_capacidade;
        int * data_aux =new int[_capacidade];
        for(int i=0;i<capacidade_aux;i++)
            data_aux[i]=_data[i];

        _capacidade=value;
        _data=new int[_capacidade];
        for(int i=0;i<capacidade_aux;i++)
            _data[i]=data_aux[i];
    }

    int capacity(){
        return _capacidade;
    }

    int& at(int posicao){
        return _data[posicao];
    }

    int size(){
        return _size;
    }

};




int main()
{
    Vetor vetor(1);
        vetor.push_back(1);
        vetor.push_back(3);
        vetor.push_back(5);

        vetor.reserve(100);
        cout<<vetor.size();
        cout<<"\n";
        cout<<vetor.capacity();
        cout<<"\n";
        cout<<vetor.front();
        cout<<"\n";
        cout<<vetor.back();
        cout<<"\n";
        cout<<vetor.begin();
        cout<<"\n";
        cout<<vetor.end();


    return 0;
}

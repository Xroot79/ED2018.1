#include <iostream>
#include <vector>
#include <tuple>
using namespace std;


enum Marcador {VAZIO = 0, CHEIO = 1, DELETADO = 2};

struct Elem {
    int key;
    string value;

    Elem(int key = 0, string value = ""){
        this->key = key;
        this->value = value;
    }

    bool operator ==(Elem other){
        return key == other.key;
    }

    friend ostream& operator << (ostream& os, Elem e){
        os << e.key;
        return os;
    }
};

struct Item {
    Elem elem;
    Marcador marc;
};

struct HashLinear{ //linear probing
    pair<Elem, Marcador> * vet;
    int capacity;
    int size;
    HashLinear(int capacity){
        vet = new pair<Elem, Marcador>[capacity];
        this->capacity = capacity;
        this->size = 0;
        for(int i = 0; i < capacity; i++){
            vet[i].first = Elem();
            vet[i].second = VAZIO;
        }
    }

    bool insert(Elem elem){
        int it = find(elem.key);
        if(it == -1)
            return false;
        int pos = elem.key % this->size;
        while( this->vet[pos].second != VAZIO ||  this->vet[pos].second != DELETADO)
            pos = (pos + 1) % capacity;
        this->vet[pos].first = elem;
        this->vet[pos].second = CHEIO;
        this->size++;

    }


    bool remove(int key){
        auto pos = find(key);
        if (key != -1)
            this->vet[pos].second = DELETADO;
        size--;
    }

    //implementação sem marcação, com realocacao
    bool m_remove(int key){
        int pos = find(key);
        if(pos != -1){
            vet[pos].second = VAZIO;
            return false;
        }
        size--;
        pos = (pos + 1) % capacity;
        while(vet[pos].second != VAZIO){
            vet[pos].second =  VAZIO;
            insert(vet[pos].first);
            pos = (pos + 1) % capacity;
        }
        return true;
    }

    //retorna posicao que encontrou o elemento ou -1
    int find(int key){
        int base = key % capacity;
        int i = 0;
        int pos = base;
        while (vet[pos].second != VAZIO || vet[pos].first == NULL){
            i++;
            pos = (base + i * i) % capacity;
        }
        if(vet[pos].second == VAZIO)
            return -1;
        return pos;
    }

    void resize(int capacity){
        pair<Elem, Marcador> * vet_old = this->vet;
        this->vet = new pair<Elem,Marcador>[capacity];
        for(auto i = 0;i < this->size;i++)
            this->vet[i].second = VAZIO;
        for(int i = 0; i < this->size;i++)
            insert(vet_old[i].first);
        delete vet_old;
    }

};

int main()
{
    return 0;
}

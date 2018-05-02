#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct  Node{
    int value;
    Node* next;

    Node(int value = 0, Node * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

struct SList{

    Node* head;

    SList(){
        this->head = nullptr;
    }

    ~SList(){
       head = deletarTudo(head);
    }

    Node * deletarTudo(Node * node){
        if(node == nullptr)
            return nullptr;

        deletarTudo(node->next);
        delete node;
        return nullptr;
    }


    //procura o valor, remove desse no em diante
    Node * cortarRabo(Node * node, int value){
        if(node == nullptr)
            return nullptr;

        node->next = cortarRabo(node->next,value);
        if(node->next == nullptr){
            if(node->value != value){
                delete node;
                return nullptr;
            }else{
                return node;
            }
        }
        return node;
    }


    void push_front(int value){
        //this->head = new Node(value, this->head);
        Node * node = new Node(value);
        node->next = head;
        this->head = node;
    }

    void pop_front(){
        if(head == nullptr)
            return;
        Node * aux = head;
        head = head->next;
        delete aux;
    }

    void push_back(int value){
        if(head == nullptr){
            head = new Node(value);
            return;
        }
        auto node = head;
        while(node->next != nullptr)
            node = node->next;
        node->next = new Node(value);
    }

    void _rpush_back(Node * node, int value){
        if(node->next == nullptr){
            node->next = new Node(value);
            return ;
        }
        _rpush_back(node->next,value);
    }

    void rpush_back(int value){
        if(head==nullptr){
            head = new Node(value);
        }else
        _rpush_back(head,value);
    }



    void pop_back(){
        if(head == nullptr)
            return;
        if(head->next == nullptr){
            delete head;
            head = nullptr;
            return;
        }
        auto node = head;
        while(node->next->next != nullptr)
            node = node->next;
        delete node->next;
        node->next = nullptr;
    }

    Node * _rpop_back(Node * node){
        if(node->next == nullptr){
            delete node;
            return nullptr;
        }
        node->next = _rpop_back(node->next);
    }

    void rpop_back(){
        this->head = _rpop_back(head);
    }

    void ishow(){
        auto node = head;
        while(node != nullptr){
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }
private:
    void _rshow(Node * node){
        if(node == nullptr)
            return;
        cout << node->value << " ";
        _rshow(node->next);
    }
public:
    void rshow(){
        _rshow(head);
        cout << endl;
    }

    Node * _remove(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value){
            auto aux = node->next;
            delete node;
            return aux;
        }
        node->next = _remove(node->next, value);
    }

    void rremove(int value){
       head = _remove(head, value);
    }

    Node * iremove(int value){
        if(head == nullptr)
            return nullptr;

        auto node = head;
        while(node->value != value){
            node = node->next;
        }
            auto aux = node->next;
            delete node;
            return aux;
    }

    void inserir_ordenado(int value){
        auto node = head;
        if(head == nullptr || head->value > value){
            this->head = new Node(value, head);
            return;
        }
        while(node->next != nullptr && node->next->value < value){
            node = node->next;
        }
        node->next = new Node(value, node->next);
    }

    void _rinserir_ordenado(Node * node, int value){
       if(node->next == nullptr || node->next->value > value)
           return;

       _rinserir_ordenado(node->next,value);
       node->next = new Node(value, node->next);
    }

    void rinserir_ordenado(int value){
        if(head == nullptr || head->value > value){
            head = new Node(value, head);
        }else
        _rinserir_ordenado(head,value);
    }

    int size(){
        int cont=0;
        if(head==nullptr)
            return 0;

        Node * node = head;
        while(node != nullptr){
            node = node->next;
            cont++;
        }
        return cont;
    }

    int _rsomar(Node * node){
        if(node->next == nullptr){
            return node->value;
        }
        return node->value + _rsomar(node->next);
    }

    int rsomar(){
        return _rsomar(head);
    }

    int _rmin(Node * node){
        if(node->next == nullptr)
            return node->value;
        return std::min(node->value, _rmin(node->next));
    }

    int rmin(){
        return _rmin(head);
    }

};

int main(){
    SList lista;
    lista.rpush_back(1);
    lista.rpush_back(2);
    lista.rpush_back(3);
    lista.rpush_back(4);
    lista.rinserir_ordenado(0);
    lista.rshow();
    cout << lista.rsomar() <<endl;
    cout << lista.rmin() << endl;
    cout << lista.size() << endl;
    lista.iremove(3);
    lista.rshow();
    return 0;
}



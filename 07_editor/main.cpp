#include <iostream>
#include <list>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "libs/sftext.h"

using namespace std;

struct Ambiente{
    list<char> texto;
    list<char>::iterator cursor;
    Ambiente(){
        cursor = texto.end();
    }

    string toString(){
        stringstream ss;
        for(auto it = texto.begin(); it != texto.end(); it++){
            if(it == cursor)
                ss << "|";
            ss << (*it);
        }
        if(cursor == texto.end())
            ss << "|";
        return ss.str();
    }
};

int main()
{
    Ambiente amb;

    list<Ambiente> ambientes;

    sf::RenderWindow janela(sf::VideoMode(800, 600), "Janela");

    while(janela.isOpen()){

        sf::Event event;
        while(janela.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                janela.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.control && (event.key.code == sf::Keyboard::Z)){
                    cout << "control z" << endl;
                    while(*amb.cursor != ' ' && *amb.cursor != '\n' && amb.cursor != amb.texto.begin() ){
                        amb.cursor--;
                    }
                   Ambiente novoAmbiente=amb;
                   if(!ambientes.empty()){
                       amb = ambientes.front();
                       ambientes.pop_front();
                       amb.cursor=amb.texto.end();
                   }else{
                       ambientes.push_front(novoAmbiente);
                       amb.cursor = amb.texto.erase(amb.cursor++,amb.texto.end());
                   }
                }
                else if(event.key.control && (event.key.code == sf::Keyboard::R)){
                        cout << "control r" << endl;
                        amb = ambientes.front();
                        amb.cursor=amb.texto.end();
                }
                else if((event.key.code >= sf::Keyboard::A) && (event.key.code <= sf::Keyboard::Z)){
                    char tecla = (event.key.code - sf::Keyboard::A) + 'a';
                    cout << tecla << endl;
                    amb.texto.insert(amb.cursor,tecla);
                }
                else if((event.key.code == sf::Keyboard::Return)){
                    cout << "enter" << endl;
                    amb.texto.insert(amb.cursor,'\n');
                }
                else if((event.key.code == sf::Keyboard::Space)){
                    cout << "espaco" << endl;
                    amb.texto.insert(amb.cursor,' ');
                }
                else if(event.key.code == sf::Keyboard::BackSpace){
                    cout << "backspace" << endl;
                    Ambiente novoAmbiente = amb ;
                    ambientes.push_front(novoAmbiente);
                    if(amb.cursor != amb.texto.begin())
                         amb.texto.erase(amb.cursor++,amb.cursor--);

                    novoAmbiente = amb;
                    ambientes.push_back(novoAmbiente);
                }
                else if(event.key.code == sf::Keyboard::Delete){
                    cout << "delete" << endl;
                    Ambiente novoAmbiente = amb ;
                    ambientes.push_front(novoAmbiente);
                    if(amb.cursor != amb.texto.end())
                         amb.texto.erase(amb.cursor++);

                    novoAmbiente = amb;
                    ambientes.push_back(novoAmbiente);
                }
                else if(event.key.code == sf::Keyboard::Left){
                    if(amb.cursor != amb.texto.begin())
                        amb.cursor--;
                }
                else if(event.key.code == sf::Keyboard::Right){
                    if(amb.cursor != amb.texto.end())
                        amb.cursor++;
                }
            }
        }

        auto pos = sf::Vector2f(30, 50);
        janela.clear();
        janela.draw(sfText(pos, amb.toString(), sf::Color::White, 30));
        janela.display();
    }
    return 0;
}





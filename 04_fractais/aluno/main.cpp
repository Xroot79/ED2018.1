#include <lib/pen.h>

void triangulo(Pen &p, int lado){
    if(lado < 10)
        return;
    for(int i = 0; i < 3; i++){
        p.walk(lado);
        p.left(120);
        triangulo(p, lado/2);
        p.setColor(rand() % 255, rand() % 255, rand() % 255);
    }
}

void gelo(Pen &p, int lado){
       int angulo = 72;
       if(lado < 1)
           return;

       for(int  i = 0; i < 5; i++){
            p.setColor(255,0,255);
            p.walk(lado);
            gelo(p, lado * 0.35);
            p.setColor(255,255,255);
            p.walk(-lado);
            p.right(angulo);
       }
}

void estrela(Pen &p, int dist){
    int angulo = 72;
    if(dist < 0.1){
        return;
    }
    for(int  i = 0; i < 5; i++){
        p.walk(dist);
        estrela(p, dist/3);
        p.setColor(0,0,144);
        p.walk(-dist);
        p.right(angulo);
        p.walk(dist);
        estrela(p, dist/3);
    }
}

void trigo(Pen &p, int lado){
    int dec=3;
    int angulo=60;
    if(lado<1)
        return;

    for(int i=0;i<4;i++){
        p.walk(lado);
        p.right(angulo);
        trigo(p,lado/dec);
        p.left(2*angulo);
        trigo(p,lado/dec);
        p.right(angulo);
    }
    p.walk(-lado*4);
}


void arvore(Pen& p, int lado){
    float tronco = 5;
    float ang = 35;
    float dec = 0.75;
    lado -= (p.rand() % 7 - 3);
    if(lado < 10)
        return;
    p.setThickness(6);
    p.setColor(50,205,50);
    p.walk(lado);
    p.right(ang);
    arvore(p, lado * dec);
    p.setThickness(3);
    p.left(ang);
    arvore(p, lado * dec);
    p.setThickness(2);
    p.left(ang);
    arvore(p, lado * dec);
    p.setColor(50,51,23);
    p.right(ang);
    p.walk(-lado);

}

void fractalGelo(){
    Pen p(1000, 700);
    float dist = 100;
    p.setXY(500, 500);
    p.setColor(255,255,255);
    p.setHeading(90);
    p.setSpeed(0);
    p.setThickness(1);
    gelo(p, dist);
    p.wait();
}

void fractalTrigo(){
    Pen p(800, 600);
    int lado = 100;
    p.setXY(300, 600);
    p.setColor(255,255,255);
    p.setHeading(90);
    p.setSpeed(0);
    p.setThickness(1);
    trigo(p,lado);
    p.wait();
}

void fractalEstrela(){
    Pen p(1000, 700);
    float dist = 120;
    p.setXY(430, 300);
    p.setColor(255,255,255);
    p.setHeading(72);
    p.setSpeed(200);
    p.setThickness(1);
    estrela(p, dist);
    p.wait();
}

void fractalArvore(){
    Pen p(800, 600);
    //coloca o pincel na posicao x 300 y 500
    p.setXY(400, 500);

    //faz o pincel apontar pra direita
    p.setHeading(90);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade
    p.setSpeed(500);
    arvore(p, 100);
    //espera clicar no botao de fechar
    p.wait();
}

void fractalTriangulo(){
    Pen p(800, 600);
    p.setThickness(1);
    p.setXY(400, 500);
    p.setHeading(60);
    p.setSpeed(250);
    triangulo(p, 400);
    p.wait();
}

int main(){
    //fractalArvore();
    //fractalGelo();
    //fractalEstrela();
    //fractalTriangulo();
    //fractalTrigo();
    return 0;
}

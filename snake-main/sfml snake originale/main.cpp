# include <SFML/graphics.hpp>
# include <iostream>
# include <cstdlib>
#include<string.h>

using namespace std;
using namespace sf;

int Size = 30;
int width = Size * Size, height = Size * Size;
int corps = 3;
int dir = 1;
int point = 0;
int score = 0;

//la tête du serpent
struct snake
{
    int x, y;
}s[100];

//le fruit
struct fruit
{
    int x, y;
}f;

void action()
{
    //mouvement du corps du serpent
    for(int i = corps; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    //suivi de la tête par le reste du corps
    if(dir== 0) s[0].y -= 1;
    if(dir == 1) s[0].x += 1;
    if(dir== 2) s[0].y += 1;
    if(dir== 3) s[0].x -= 1;

    //si la position de la tête est égale a celle du fruit
    if(s[0].x == f.x && s[0].y == f.y)
    {
        corps++;
        score = score++;
        f.x = rand() % Size;
        f.y = rand() % Size;
    }

    //passer d'un bord a l'autre
    if(s[0].x < 0) s[0].x = 30;
    if(s[0].x > Size) s[0].x = 0;
    if(s[0].y < 0) s[0].y = 30;
    if(s[0].y > Size) s[0].y = 0;
}

/*void restartGame()
{
    dir=1;
    corps=3;
    f.x = rand() % Size;
    f.y = rand() % Size;
    s[0].x = 2;
    s[0].y = 2;
}*/


int main()
{
    int rejouer = 1;
    bool startScreen = 0;
    bool gameoverScreen = 0;

    Texture MainMenu, GameOver, Fond, fruit;
    Sprite spriteMenu, spriteGO, spriteFond;

    MainMenu.loadFromFile("Img.png");
        spriteMenu.setTexture(MainMenu);
        spriteMenu.setScale(1.5,1.8);

    GameOver.loadFromFile("lose.png");
        spriteGO.setTexture(GameOver);
        spriteGO.setScale(1.1,3);


    Fond.loadFromFile("fond2.jpg");
        spriteFond.setTexture(Fond);
        spriteFond.setScale(0.5,0.7);

    RenderWindow app(VideoMode(width, height), "space snake", Style::Titlebar);
    app.setFramerateLimit(60);

    RectangleShape box(Vector2f(Size, Size));
    box.setFillColor(Color::Green);

    RectangleShape tete(Vector2f(Size, Size));
    tete.setFillColor(Color::White);

    RectangleShape apple(Vector2f(Size, Size));
    apple.setFillColor(Color::Blue);

    Clock timer;


    //positionnement aléatoire du fruit
    f.x = rand() % Size;
    f.y = rand() % Size;

    while(app.isOpen())
    {

        Event event;
        while(app.pollEvent(event))
        {
            if(event.type == Event::Closed)
                app.close();
        }
        while(startScreen == 0)
        {
            app.clear();
            app.draw(spriteMenu);
            app.display();

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                startScreen = 1;
                rejouer;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Up) && dir != 2)
            dir = 0;
        else if (dir == 0)
        {
            if (Keyboard::isKeyPressed(Keyboard::Down))
                dir = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 3)
            dir = 1;
        else if (dir == 1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))
                dir = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 0)
            dir = 2;
        else if (dir == 2)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
                dir = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 1)
            dir = 3;
        else if (dir == 3)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
                dir = 3;
        }

        //vitesse d'execution du mouvement du corps
        if(timer.getElapsedTime().asMilliseconds() > 100)
        {
            action();
         if(s[0].x < 0 || s[0].y < 0 || s[0].x >= Size ||s[0].y>= Size)// sort de la fenêtre
        {
            while(gameoverScreen == 0)
            {
                app.clear();
                app.draw(spriteGO);
                app.display();

                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                    gameoverScreen = 1;
                    app.clear();
                    rejouer;
                }
                    for (int i = 1; i < corps; i++) //collision
                    if(s[0].x == s[i].x && s[0].y == s[i].y)
                    {
                        while(gameoverScreen == 1)
                        {
                            app.clear();
                            app.draw(spriteGO);
                            app.display();

                            if(Keyboard::isKeyPressed(Keyboard::Space))
                            {
                                gameoverScreen = 1;
                                app.clear();
                                rejouer;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                app.close();
                            }
                        }
                    }
            }
         }
        timer.restart();
        }
        app.clear();
        app.draw(spriteFond);

        for (int i = 0; i < corps; i++)//tout dessiner
        {
            box.setPosition(s[i].x *Size, s[i].y *Size);
            app.draw(box);
            tete.setPosition(s[0].x *Size, s[0].y *Size);
            app.draw(tete);
        }
            apple.setPosition(f.x *Size, f.y *Size);
            app.draw(apple);
            app.display();
        }
}


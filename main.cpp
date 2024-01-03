#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <ctime>

using namespace std;

void loadSprite(sf::Sprite &sprite, sf::Texture &texture, float scale, string loadFromFile, float orx, float ory, float posx, float posy)
{
    //Loads a sprite with settings in it
    //Pre: sprite and texture must be variables, and the rest are constants
    //Post: sets the texture, scale, origin, and position of a sprite
    texture.loadFromFile(loadFromFile);
    sprite.setScale(scale, scale);
    sprite.setTexture(texture);
    sprite.setOrigin(orx, ory);
    sprite.setPosition(posx, posy);
}

void loadText(sf::Font &gameFont, sf::Text &text, float x, float y, int csize, string str)
{
    //this function loads the text
    //Pre: need a font and text and constants
    //Post: sets the font, color, position, character size, and text of a text
    gameFont.loadFromFile("ethnocen.ttf");
    text.setFont(gameFont);
    text.setColor(sf::Color::White);
    text.setPosition(x, y);
    text.setCharacterSize(csize);
    text.setString(str);
}

void loadRectangle(sf::RectangleShape &rs, int vx, int vy, int x, int y, sf::Color c, int othick, sf::Color oc)
{
    //loads a rectangleshape
    //Pre: needs a rectangleshape and constants
    //Post: sets the size, position, origin, color, outline color, and outline thickness of a rectangleshape
    rs.setSize(sf::Vector2f(vx, vy));
    rs.setPosition(x, y);
    rs.setOrigin(vx / 2, vy / 2);
    rs.setFillColor(c);
    rs.setOutlineColor(oc);
    rs.setOutlineThickness(othick);
}

void loadSound(sf::SoundBuffer &sb, sf::Sound &s, string file)
{
    //Loads in a sound
    //Pre: a soundbuffer, sound, and a constant name file
    //Post: attaches a buffer to a sound
    sb.loadFromFile(file);
    s.setBuffer(sb);
}

bool mouseOverButton(sf::RectangleShape &button, sf::RenderWindow &window)
{
    //checks whether the position of a mouse is hovering over a rectangleshape (button)
    //Pre: a rectangleshape and a renderwindow
    //Post: returns true or false depending on whether this condition is true
    if (button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        return true;
    } else {
        return false;
    }
}

void animateButton(sf::RectangleShape &button, sf::Text &buttText, sf::RenderWindow &window)
{
    //makes a button and its text yellow when the mouseoverbutton function is true
    //Pre: the rectangle, the text, and the renderwindow
    //Post: sets them yellow or white
    if (mouseOverButton(button, window)) {
        button.setOutlineColor(sf::Color::Yellow);
        buttText.setFillColor(sf::Color::Yellow);
    } else {
        button.setOutlineColor(sf::Color::White);
        buttText.setFillColor(sf::Color::White);
    }
}

void animateShapes(sf::CircleShape cs[50], double mtspeed[50], double mtangles[50])
{
    //animates the moving triangles in the title and end screen, moving them and rotating them
    //takes in 3 arrays: the triangle, the speed, and angles
    //Post: moves and rotates them as well as setting them to the top after they reach the bottom
    for (int i = 0; i < 50; i++) {
        cs[i].move(0, mtspeed[i]);
        cs[i].rotate(mtangles[i]);
        if (cs[i].getPosition().y > 850) {
            cs[i].move(0, -900);
        }
    }
}

void moveAim(sf::Sprite &crosshair, sf::RectangleShape &mortarBase, sf::RectangleShape &mortarPipe)
{
    //Moves the red crosshair and the mortar according to keyboard inputs
    //Pre: the crosshair and the parts of the mortar
    //Post: moves the crosshair and mortar
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && crosshair.getPosition().y > 35) {
        crosshair.move(0, -8);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && crosshair.getPosition().y < 765)
    {
        crosshair.move(0, 8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && crosshair.getPosition().x < 1165) {
        crosshair.move(8, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && crosshair.getPosition().x > 210)
    {
        crosshair.move(-8, 0);
    }
    mortarBase.setPosition(mortarBase.getPosition().x, crosshair.getPosition().y);
    mortarPipe.setPosition(mortarBase.getPosition().x, mortarBase.getPosition().y - 35);
}

void drawTitle(sf::RenderWindow &window, sf::Sprite &background, sf::Text &titleText, sf::RectangleShape playButton, sf::Text playText, sf::CircleShape menuTriangles[50], sf::RectangleShape &toPlayButton, sf::Text &toPlayText, bool &howToPlayOpen, sf::RectangleShape &instructionPanel, sf::Text &instructions)
{
    //Draws everything in the title screen
    //Pre: all declared sf
    //Post: draws all the parameters
    window.draw(background);
    int ii = 0;
    do {
        window.draw(menuTriangles[ii]);
        ii++;
    } while (ii < 50);
    window.draw(titleText);
    window.draw(playButton);
    window.draw(playText);
    window.draw(toPlayButton);
    window.draw(toPlayText);
    if (howToPlayOpen == true) {
        window.draw(instructionPanel);
        window.draw(instructions);
    }
}

void drawEnd(sf::RenderWindow &window, sf::Sprite &background, sf::CircleShape menuTriangles[50], sf::RectangleShape &statBox, sf::Text &gameOver, sf::Text &stats, sf::RectangleShape &mainMenu, sf::Text &menuText)
{
    //Draws everything in the end screen
    //Pre: all declared sf
    //Post: draws all the parameters
    window.draw(background);
    for (int i = 0; i < 50; i++) {
        window.draw(menuTriangles[i]);
    }
    window.draw(statBox);
    window.draw(gameOver);
    window.draw(stats);
    window.draw(mainMenu);
    window.draw(menuText);
}

void drawGame(sf::RenderWindow &window, sf::Sprite &background, sf::CircleShape enemy1[20], sf::CircleShape enemy2[10], sf::CircleShape enemy3[50], sf::RectangleShape e1hb[20], sf::RectangleShape e1h[20], sf::RectangleShape e2hb[10], sf::RectangleShape e2h[10], sf::RectangleShape e3hb[50], sf::RectangleShape e3h[50], sf::RectangleShape &platform, sf::RectangleShape &wall, int mt[20],
              sf::Sprite targets[20], sf::Sprite eSprite[20], sf::Sprite mortarShell[20], sf::RectangleShape &mortarBase, sf::RectangleShape &mortarPipe, sf::Text &timer, sf::Text &g, sf::Text &hp, sf::Text &mLevel, sf::Text &sub1, sf::Text &sub2, sf::Sprite &crosshair, int &countdown, sf::Text &downCount)
{
    //Draws everything in the game screen
    //Pre: all declared sf
    //Post: draws all the parameters
    window.draw(background);
    for (int i = 0; i < 20; i++) {
        window.draw(enemy1[i]);
    }
    for (int i = 0; i < 10; i++) {
        window.draw(enemy2[i]);
    }
    for (int i = 0; i < 50; i++) {
        window.draw(enemy3[i]);
    }
    for (int i = 0; i < 10; i++) {
        window.draw(e2hb[i]);
        window.draw(e2h[i]);
    }
    for (int i = 0; i < 20; i++) {
        window.draw(e1hb[i]);
        window.draw(e1h[i]);
    }
    for (int i = 0; i < 50; i++) {
        window.draw(e3hb[i]);
        window.draw(e3h[i]);
    }
    window.draw(platform);
    window.draw(wall);
    for (int i = 0; i < 20; i++) {
        if (mt[i] >= 1 && mt[i] <= 56) {
            window.draw(targets[i]);
        }
        if (mt[i] >= 60) {
            window.draw(eSprite[i]);
        }
        if (mt[i] >= 1 && mt[i] <= 56) {
            window.draw(mortarShell[i]);
        }
    }
    window.draw(mortarBase);
    window.draw(mortarPipe);
    window.draw(timer);
    window.draw(g);
    window.draw(hp);
    window.draw(mLevel);
    window.draw(sub1);
    window.draw(sub2);
    window.draw(crosshair);
    if (countdown != 0) {
        window.draw(downCount);
    }
}

int main()
{
    srand(time(0));
    //Variables
    string gameState = "title"; bool howToPlayOpen = false; int cooldown = 60; int mt[20]; int gold = 0;
    double mtspeed[50], mtangles[50], aimPosx[10], aimPosy[10];
    int soundindex = 0; int time = 0, countdown = 3, frames = 0;
    int iii = 3; int iiii = 0; int iiiii = 0;
    int health = 20;
    int mc = 90; int ll = 1;
    int cost1 = 5, cost2 = 5;
    int enemy2hp[10];
    int enemy3hp[50]; double espeed = 1;
    int killed = 0;
    for (int i = 0; i < 20; i++) {
        mt[i] = 0;
    }

    //triangles in title animation
    for (int i = 0; i < 50; i++) {
        mtspeed[i] = (rand() % 3) + 3;
        mtangles[i] = ((rand() % 10) - 5) / 10.0;
    }

    //Load
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Polygon Defense");

    //Clok
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f / 60.f);

    sf::Font gameFont; sf::Text titleText;
    loadText(gameFont, titleText, 120, 70, 70, "[POLYGON DEFENSE]");

    sf::RectangleShape playButton;
    loadRectangle(playButton, 250, 80, 600, 400, sf::Color::Red, 5, sf::Color::White);
    sf::Text playText;
    loadText(gameFont, playText, 500, 370, 50, "|PLAY|");

    sf::RectangleShape toPlayButton;
    loadRectangle(toPlayButton, 330, 60, 600, 600, sf::Color::Red, 5, sf::Color::White);
    sf::Text toPlayText;
    loadText(gameFont, toPlayText, 445, 580, 30, "|HOW TO PLAY|");

    sf::Text downCount;
    loadText(gameFont, downCount, 550, 230, 100, "3");
    sf::Text timer;
    loadText(gameFont, timer, 900, 30, 40, "TIME: 0");

    sf::Text g;
    loadText(gameFont, g, 500, 30, 40, "GOLD: 0");

    sf::Text hp;
    loadText(gameFont, hp, 168, 300, 25, "HP: 20");
    hp.setRotation(90);

    sf::Text mLevel;
    loadText(gameFont, mLevel, 200, 30, 40, "M.LVL: 1");

    sf::Text sub1, sub2;
    loadText(gameFont, sub1, 220, 80, 15, "[1] Cost: 5");
    loadText(gameFont, sub2, 160, 480, 15, "[2] Cost: 5");
    sub2.setRotation(90);

    sf::RectangleShape instructionPanel;
    loadRectangle(instructionPanel, 800, 500, 600, 500, sf::Color::Black, 5, sf::Color::White);
    sf::Text instructions;
    loadText(gameFont, instructions, 230, 280, 20, "\nSURVIVE THE ATTACKS FOR AS LONG AS YOU CAN\n\n\n\nARROW KEYS TO CONTROL MORTAR AIM\n\nSPACE = SHOOT MORTAR\n\n\n1 = UPGRADE FIRE RATE (5 GOLD)\n2 = REPAIR WALL (5 GOLD)\n\nSecond polemeny in 40 sec\nThird polemeny in 100 sec\n\n(note: sound is recommended)\n\nCLICK ANYWHERE TO EXIT");

    sf::RectangleShape wall; sf::Texture wt; sf::Texture t3;
    loadRectangle(wall, 40, 800, 150, 400, sf::Color::White, 2, sf::Color::White);
    wt.loadFromFile("walltex.png");
    wall.setTexture(&wt);
    t3.loadFromFile("texture3.jpg");

    sf::Color Silver(192, 192, 192);
    sf::Color Gray(120, 120, 130);

    sf::RectangleShape platform;
    loadRectangle(platform, 130, 800, 65, 400, Gray, 0, sf::Color::Transparent);
    platform.setTexture(&t3);
    sf::RectangleShape mortarBase;
    loadRectangle(mortarBase, 60, 60, 60, 50, Silver, 5, sf::Color::Cyan);

    sf::RectangleShape mortarPipe;
    loadRectangle(mortarPipe, 20, 80, 60, 50, sf::Color::Black, 5, sf::Color::Cyan);

    sf::CircleShape menuTriangles[50]; sf::Texture t1;
    sf::CircleShape enemy1[20];
    t1.loadFromFile("texture1.jpg");

    sf::Texture t5;
    t5.loadFromFile("texture5.jpg");

    sf::CircleShape enemy2[10]; sf::Texture t4;
    t4.loadFromFile("texture4.jpeg");
    sf::RectangleShape e2hb[10];
    sf::RectangleShape e2h[10];

    sf::RectangleShape e1hb[20];
    sf::RectangleShape e1h[20];

    int i = 0;
    while (i < 50) {
        menuTriangles[i].setPointCount(3);
        menuTriangles[i].setTexture(&t1);
        menuTriangles[i].setRadius((rand() % 41) + 30);
        menuTriangles[i].setOrigin(menuTriangles[i].getRadius(), menuTriangles[i].getRadius());
        menuTriangles[i].setPosition(rand() % 1200, rand() % 800);
        menuTriangles[i].setRotation(rand() % 360);
        menuTriangles[i].setOutlineColor(sf::Color::Cyan);
        menuTriangles[i].setOutlineThickness(2);
        i++;
    }

    for (int i = 0; i < 20; i++) {
        enemy1[i].setPointCount(3);
        enemy1[i].setFillColor(sf::Color::Green);
        enemy1[i].setRadius(15);
        enemy1[i].setOrigin(enemy1[i].getRadius(), enemy1[i].getRadius());
        enemy1[i].setRotation(270);
        enemy1[i].setOutlineColor(sf::Color::White);
        enemy1[i].setOutlineThickness(2);
        enemy1[i].setPosition(rand() % 1000 + 1300, rand() % 801);
        e1hb[i].setPosition(enemy1[i].getPosition().x, enemy1[i].getPosition().y);
        e1hb[i].setSize(sf::Vector2f(30, 6));
        e1hb[i].setFillColor(sf::Color::Red);
        e1hb[i].setOutlineColor(sf::Color::White);
        e1hb[i].setOutlineThickness(1);
        e1h[i].setFillColor(sf::Color::Green);
        e1h[i].setSize(sf::Vector2f(30, 5));
        e1h[i].setPosition(e1hb[i].getPosition().x, e1hb[i].getPosition().y);
    }

    for (int i = 0; i < 10; i++) {
        enemy2[i].setRadius(25);
        enemy2[i].setTexture(&t4);
        enemy2[i].setPointCount(5);
        enemy2[i].setOrigin(enemy2[i].getRadius(), enemy2[i].getRadius());
        enemy2[i].setRotation(270);
        enemy2[i].setOutlineColor(sf::Color::White);
        enemy2[i].setOutlineThickness(5);
        enemy2[i].setPosition(rand() % 1000 + 1300, rand() % 801);
        e2hb[i].setPosition(enemy2[i].getPosition().x, enemy2[i].getPosition().y);
        e2hb[i].setSize(sf::Vector2f(50, 6));
        e2hb[i].setFillColor(sf::Color::Red);
        e2hb[i].setOutlineColor(sf::Color::White);
        e2hb[i].setOutlineThickness(1);
        e2h[i].setSize(sf::Vector2f(50, 5));
        e2h[i].setPosition(e1hb[i].getPosition().x, e1hb[i].getPosition().y);
        e2h[i].setFillColor(sf::Color::Green);
        enemy2hp[i] = 5;
    }

    sf::CircleShape enemy3[50];
    sf::RectangleShape e3hb[50];
    sf::RectangleShape e3h[50];

    sf::Texture backgroundTexture; sf::Sprite background;
    loadSprite(background, backgroundTexture, 0.75, "b1.jpg", 0, 0, 0, 0);

    sf::Texture crossTexture; sf::Sprite crosshair;
    loadSprite(crosshair, crossTexture, 0.15, "crosshair.png", 250, 250, 600, 400);

    sf::Texture eTexture;
    eTexture.loadFromFile("ExplosionSprite.png");
    sf::IntRect rectSourceSprite[20];
    for (int i = 0; i < 20; i++) {
        rectSourceSprite[i].width = 96;
        rectSourceSprite[i].height = 96;
        rectSourceSprite[i].left = 0;
        rectSourceSprite[i].top = 0;
    }
    sf::Sprite eSprite[20];
    sf::Sprite mortarShell[20]; sf::Texture shellTexture;
    sf::Sprite targets[20]; sf::Texture target;
    target.loadFromFile("target.png");
    shellTexture.loadFromFile("shell.png");
    for (int i = 0; i < 20; i++) {
        eSprite[i].setTexture(eTexture);
        eSprite[i].setTextureRect(rectSourceSprite[i]);
        eSprite[i].setOrigin(42, 76);
        eSprite[i].setScale(2, 2);
        mortarShell[i].setTexture(shellTexture);
        mortarShell[i].setOrigin(250, 300);
        mortarShell[i].setScale(0.2,0.2);
        mortarShell[i].setPosition(600,400);
        targets[i].setTexture(target);
        targets[i].setScale(0.1, 0.1);
        targets[i].setOrigin(150, 150);
    }

    sf::SoundBuffer sb1; sf::Sound buttonSound;
    loadSound(sb1, buttonSound, "button.wav");

    sf::SoundBuffer noiseBuffer; sf::Sound menuSounds;
    loadSound(noiseBuffer, menuSounds, "menuSound.wav");
    menuSounds.play();
    menuSounds.setLoop(true);

    sf::SoundBuffer sb2; sf::Sound morFire;
    loadSound(sb2, morFire, "mortar.wav");

    sf::SoundBuffer sb3; sf::Sound upgrade;
    loadSound(sb3, upgrade, "blip.wav");

    sf::SoundBuffer sb4; sf::Sound hurt;
    loadSound(sb4, hurt, "hurt.wav");

    sf::SoundBuffer explosions;
    explosions.loadFromFile("explosion.wav");
    sf::Sound explosionsSound[5];
    for (int i = 0; i < 5; i++) {
        explosionsSound[i].setBuffer(explosions);
    }

    for (int i = 0; i < 50; i++) {
        enemy3[i].setRadius(40);
        enemy3[i].setTexture(&t5);
        enemy3[i].setPointCount(11);
        enemy3[i].setOrigin(enemy3[i].getRadius(), enemy3[i].getRadius());
        enemy3[i].setRotation(270);
        enemy3[i].setOutlineColor(sf::Color::White);
        enemy3[i].setOutlineThickness(10);
        enemy3[i].setPosition(rand() % 1000 + 1300, rand() % 801);
        e3hb[i].setPosition(enemy3[i].getPosition().x, enemy3[i].getPosition().y);
        e3hb[i].setSize(sf::Vector2f(70, 6));
        e3hb[i].setFillColor(sf::Color::Red);
        e3hb[i].setOutlineColor(sf::Color::White);
        e3hb[i].setOutlineThickness(1);
        e3h[i].setSize(sf::Vector2f(70, 5));
        e3h[i].setPosition(e3hb[i].getPosition().x, e3hb[i].getPosition().y);
        e3h[i].setFillColor(sf::Color::Green);
        enemy3hp[i] = 15;
    }

    sf::Text gameOver;
    loadText(gameFont, gameOver, 250, 70, 70, "[GAME OVER]");
    sf::Text stats;
    loadText(gameFont, stats, 330, 225, 24, "null");

    sf::RectangleShape mainMenu;
    loadRectangle(mainMenu, 500, 80, 600, 600, sf::Color::Red, 5, sf::Color::White);
    sf::Text menuText;
    loadText(gameFont, menuText, 380, 570, 50, "|MAIN MENU|");

    sf::RectangleShape statBox;
    loadRectangle(statBox, 600, 300, 600, 350, sf::Color::Black, 5, sf::Color::White);

    while (window.isOpen())
    {
        //Event Listener
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (gameState == "title") {
                    if (howToPlayOpen == false) {
                        if (mouseOverButton(playButton, window)) {
                            gameState = "game";
                            loadSprite(background, backgroundTexture, 0.75, "background.jpg", 0, 0, 0, 0);
                            buttonSound.play();
                            menuSounds.stop();
                        }
                        else if (mouseOverButton(toPlayButton, window))
                        {
                            howToPlayOpen = true;
                            buttonSound.play();
                        }
                    } else {
                        howToPlayOpen = false;
                        buttonSound.play();
                    }
                }
                else if (gameState == "end")
                {
                    if (mouseOverButton(mainMenu, window)) {
                        gameState = "title";
                        buttonSound.play();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (gameState == "game") {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        //First upgrade
                        if (gold >= cost1 && ll < 13) {
                            gold -= cost1;
                            g.setString("GOLD: " + std::to_string(gold));
                            mc -= 7;
                            ll++;
                            mLevel.setString("M.LVL: " + std::to_string(ll));
                            upgrade.play();
                            cost1 *= 1.5;
                            if (ll == 13) {
                                sub1.setString("[1] MAX");
                            } else {
                                sub1.setString("[1] COST: " + std::to_string(cost1));
                            }
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                        //Second upgrade
                        if (gold >= cost2) {
                            gold -= cost2;
                            g.setString("GOLD: " + std::to_string(gold));
                            health += 10;
                            hp.setString("HP: " + std::to_string(health));
                            upgrade.play();
                            cost2 += 5;
                            sub2.setString("[1] COST: " + std::to_string(cost2));
                        }
                    }
                }
            }

        }


        //Game Logic

        while (accumulator > ups) {
            accumulator -= ups;
            if (gameState == "title") {
                animateButton(playButton, playText, window);
                animateButton(toPlayButton, toPlayText, window);
                animateShapes(menuTriangles, mtspeed, mtangles);
            }
            else if (gameState == "end")
            {
                animateButton(mainMenu, menuText, window);
                animateShapes(menuTriangles, mtspeed, mtangles);
            }
            if (gameState == "game") {
                moveAim(crosshair, mortarBase, mortarPipe);


                //All the framerate and time stuff
                if (frames < 60) {
                    frames++;
                } else {
                    frames = 0;
                    if (countdown != 0) {
                        countdown--;
                        downCount.setString(std::to_string(countdown));
                        buttonSound.play();
                    } else {
                        time++;
                        //algorithm for spawning enemies
                        if (time % 20 == 0 && iii + 2 < 20) {
                            iii += 2;
                        }
                        if (time >= 40 && time % 40 == 0 && iiii + 1 < 10) {
                            iiii += 1;
                        }
                        if (time > 100 && time < 360) {
                            if (time % 80 == 0) {
                                iiiii += 1;
                            }
                        } else if (time > 360) {
                            if (time % 10 == 0 && iiiii + 1 < 50) {
                                iiiii += 1;
                            }
                            if (time % 15 == 0) {
                                espeed += 0.1;
                            }
                        }
                        timer.setString("TIME: " + std::to_string(time));
                    }
                }

                if (countdown == 0) {
                    //moves enemies and checks if they reach the wall
                    for (int i = 0; i < iii; i++) {
                        enemy1[i].move(-0.9 * espeed, 0);
                        e1hb[i].setPosition(enemy1[i].getPosition().x - 20, enemy1[i].getPosition().y - 30);
                        e1h[i].setPosition(e1hb[i].getPosition().x, e1hb[i].getPosition().y);
                        if (enemy1[i].getPosition().x < 150) {
                            enemy1[i].setPosition(1300, rand() % 801);
                            health -= 4;
                            hp.setString("HP: "+ std::to_string(health));
                            hurt.play();
                        }
                    }
                    for (int i = 0; i < iiii; i++) {
                        enemy2[i].move(-0.6 * espeed, 0);
                        e2hb[i].setPosition(enemy2[i].getPosition().x - 25, enemy2[i].getPosition().y - 35);
                        e2h[i].setPosition(e2hb[i].getPosition().x, e2hb[i].getPosition().y);
                        if (enemy2[i].getPosition().x < 150) {
                            enemy2[i].setPosition(1300, rand() % 801);
                            health -= 8;
                            hp.setString("HP: " + std::to_string(health));
                            hurt.play();
                        }
                    }
                    for (int i = 0; i < iiiii; i++) {
                        enemy3[i].move(-0.4 * espeed, 0);
                        e3hb[i].setPosition(enemy3[i].getPosition().x - 25, enemy3[i].getPosition().y - 45);
                        e3h[i].setPosition(e3hb[i].getPosition().x, e3hb[i].getPosition().y);
                        if (enemy3[i].getPosition().x < 150) {
                            enemy3[i].setPosition(1300, rand() % 801);
                            health -= 20;
                            hp.setString("HP: " + std::to_string(health));
                            hurt.play();
                        }
                    }
                    //resets everything once hp reaches zero, sets the state to the end screen
                    if (health <= 0) {
                        gameState = "end";
                        loadSprite(background, backgroundTexture, 0.75, "b1.jpg", 0, 0, 0, 0);
                        menuSounds.play();
                        buttonSound.play();
                        health = 20;
                        hp.setString("HP: 20");
                        stats.setString("FINAL TIME: " + std::to_string(time) + "\n\nPOLENEMIES DESTROYED: " + std::to_string(killed));
                        gold = 0;
                        g.setString("GOLD: 0");
                        time = 0;
                        timer.setString("TIME: 0");
                        ll = 0;
                        mLevel.setString("M.LVL: 1");
                        countdown = 3;
                        downCount.setString(std::to_string(countdown));
                        crosshair.setPosition(600, 400);
                        frames = 0;
                        killed = 0;
                        espeed = 1;
                        iii = 3;
                        iiii = 0;
                        iiiii = 0;
                        cost1 = 5;
                        cost2 = 5;
                        sub1.setString("[1] COST: 5");
                        sub2.setString("[2] COST: 5");
                        cooldown = 60;
                        mc = 90;
                        for (int i = 0; i < 50; i++) {
                            enemy3[i].setRadius(40);
                            enemy3[i].setPosition(rand() % 1000 + 1300, rand() % 801);
                            e3hb[i].setPosition(enemy3[i].getPosition().x, enemy3[i].getPosition().y);
                            e3h[i].setPosition(e3hb[i].getPosition().x, e3hb[i].getPosition().y);
                            e3h[i].setScale(1, 1);
                            enemy3hp[i] = 15;
                            if (i < 20) {
                                enemy1[i].setPosition(rand() % 1000 + 1300, rand() % 801);
                                e1hb[i].setPosition(enemy1[i].getPosition().x, enemy1[i].getPosition().y);
                                e1h[i].setPosition(e1hb[i].getPosition().x, e1hb[i].getPosition().y);
                                e1h[i].setScale(1, 1);
                                if (i < 10) {
                                    enemy2[i].setPosition(rand() % 1000 + 1300, rand() % 801);
                                    e2hb[i].setPosition(enemy2[i].getPosition().x, enemy2[i].getPosition().y);
                                    e2h[i].setPosition(e1hb[i].getPosition().x, e1hb[i].getPosition().y);
                                    enemy2hp[i] = 5;
                                    e2h[i].setScale(1, 1);
                                }
                                mt[i] = 0;
                            }
                        }
                    }
                }

                //all the shooting mechanics
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cooldown == 0) {
                    //fires only when cooldown reaches zero
                    cooldown = mc;
                    morFire.play();
                    for (int i = 0; i < 20; i++) {
                        if (mt[i] == 0) {
                            mt[i] = 1;
                            mortarShell[i].setPosition(mortarPipe.getPosition().x, mortarPipe.getPosition().y);
                            break;
                        }
                    }
                    for (int i = 0; i < 20; i++) {
                        if (mt[i] == 1) {
                            eSprite[i].setPosition(crosshair.getPosition().x, crosshair.getPosition().y);
                            aimPosx[i] = crosshair.getPosition().x;
                            aimPosy[i] = crosshair.getPosition().y;
                            targets[i].setPosition(crosshair.getPosition().x, crosshair.getPosition().y);
                        }
                    }
                }

                if (cooldown > 0) {
                    cooldown--;
                } else {
                    cooldown = 0;
                }

                for (int i = 0; i < 20; i++) {
                    if (mt[i] != 0) {
                        //mortar shell animations
                        if (mt[i] < 15 && mortarShell[i].getPosition().y > -100) {
                            mortarShell[i].move(0, -55);
                        } else if (mt[i] == 41) {
                            mortarShell[i].setPosition(aimPosx[i], aimPosy[i] - 825);
                            mortarShell[i].setRotation(180);
                        } else if (mt[i] > 41) {
                            mortarShell[i].move(0, 55);
                        }
                        if (mt[i] >= 120) {
                            mt[i] = 0;
                            mortarShell[i].setRotation(0);
                            rectSourceSprite[i].left = 0;
                            rectSourceSprite[i].top = 0;
                            continue;
                        } else if (mt[i] >= 36) {
                            if (mt[i] == 56) {
                                explosionsSound[soundindex].play();
                                soundindex++;
                                if (soundindex == 5) {
                                    soundindex = 0;
                                }
                                //checks if explosion hits enemies and adjusts variables accordingly
                                for (int j = 0; j < iii; j++) {
                                    if (enemy1[j].getGlobalBounds().intersects(eSprite[i].getGlobalBounds())) {
                                        if (e1h[j].getScale() == sf::Vector2f(0.5, 1)) {
                                            enemy1[j].setPosition(2500, rand() % 801);
                                            gold += 2;
                                            g.setString("GOLD: " + std::to_string(gold));
                                            e1h[j].setScale(1, 1);
                                            killed++;
                                        } else {
                                            e1h[j].setScale(0.5, 1);
                                        }
                                    }
                                }
                                for (int j = 0; j < iiii; j++) {
                                    if (enemy2[j].getGlobalBounds().intersects(eSprite[i].getGlobalBounds())) {
                                        if (e2h[j].getScale() == sf::Vector2f(0.2, 1)) {
                                            enemy2[j].setPosition(2500, rand() % 801);
                                            gold += 6;
                                            g.setString("GOLD: " + std::to_string(gold));
                                            e2h[j].setScale(1, 1);
                                            enemy2hp[j] = 5;
                                            killed++;
                                        } else {
                                            enemy2hp[j] -= 1;
                                            e2h[j].setScale(enemy2hp[j] / 5.0, 1);
                                        }
                                    }
                                }
                                for (int j = 0; j < iiiii; j++) {
                                    if (enemy3[j].getGlobalBounds().intersects(eSprite[i].getGlobalBounds())) {
                                        if (enemy3hp[j] == 1) {
                                            enemy3[j].setPosition(2500, rand() % 801);
                                            gold += 40;
                                            g.setString("GOLD: " + std::to_string(gold));
                                            e3h[j].setScale(1, 1);
                                            enemy3hp[j] = 15;
                                            killed++;
                                        } else {
                                            enemy3hp[j] -= 1;
                                            e3h[j].setScale(enemy3hp[j] / 15.0, 1);
                                        }
                                    }
                                }
                            }
                            if (mt[i] % 6 == 0 && i < 20) {
                                //explosion spritesheet animation
                                if (rectSourceSprite[i].left == 384) {
                                    rectSourceSprite[i].left = 0;
                                    if (rectSourceSprite[i].top == 192) {
                                        rectSourceSprite[i].top = 0;
                                    } else {
                                        rectSourceSprite[i].top += 96;
                                    }
                                } else {
                                    rectSourceSprite[i].left += 96;
                                }
                                eSprite[i].setTextureRect(rectSourceSprite[i]);
                            }
                        }
                        mt[i]++;
                    }
                }
            }
        }

        //Rendering
        window.clear();
        //loads depending on gamestate
        if (gameState == "title") {
            drawTitle(window, background, titleText, playButton, playText, menuTriangles, toPlayButton, toPlayText, howToPlayOpen, instructionPanel, instructions);
        } else if (gameState == "game") {
            drawGame(window, background, enemy1, enemy2, enemy3, e1hb, e1h, e2hb, e2h, e3hb, e3h, platform, wall, mt, targets, eSprite, mortarShell, mortarBase, mortarPipe, timer, g, hp, mLevel, sub1, sub2, crosshair, countdown, downCount);
        } else if (gameState == "end") {
            drawEnd(window, background, menuTriangles, statBox, gameOver, stats, mainMenu, menuText);
        }
        window.display();
        accumulator += clock.restart();
    }
    return 0;
}

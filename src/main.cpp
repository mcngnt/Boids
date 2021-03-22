
#include <SFML/Graphics.hpp>

#include "utils.h"
#include "vector.h"
#include "bird.h"

#include <iostream>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H, 32), "Boids", sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);

    sf::Sprite renderSprt;
    sf::RenderTexture renderTex;
    renderTex.create(SCREEN_W, SCREEN_H);
    renderTex.setSmooth(true);
    renderSprt.setTexture(renderTex.getTexture());
    renderTex.clear();

    int tick = 0;
    float currentFrameTime = 0.f;
    float deltaTime;
    sf::Clock clock;

    std::vector<Vector> obstacles;
    int obstaclesNB = 0;

    sf::Transform tr;
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].color = sf::Color(102,153,204,255);
    triangle[1].color = sf::Color(102,153,204,255);
    triangle[2].color = sf::Color(102,153,204,255);

    Bird birds[BIRDS_NB];

    for (int i = 0; i < BIRDS_NB; ++i)
    {
        birds[i] = bird_b(random_vec_v(0, SCREEN_W, 0, SCREEN_H), (float)(rand()%100)/100.f * 2*PI, i);
    }

    while (window.isOpen())
    {
    	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
                obstacles.push_back(vec_v(mousePos.x, SCREEN_H - mousePos.y, 0));
                obstaclesNB++;
			}
        }


        deltaTime = clock.restart().asSeconds();
        currentFrameTime += deltaTime;
        if (currentFrameTime > 0.f)
        {
        	tick++;

            for (int i = 0; i < BIRDS_NB; ++i)
            {
                Bird* b = &birds[i];
                flock(b, birds, BIRDS_NB, &obstacles[0], obstaclesNB);
            }

            for (int i = 0; i < BIRDS_NB; ++i)
            {
                Bird* b = &birds[i];
                accelerate_b(b);
                move_b(b);
            }

        	currentFrameTime = 0.f;
        }

        window.clear();
        renderTex.clear(sf::Color(25.50, 25.50, 25.50));

        
        for (int i = 0; i < BIRDS_NB; ++i)
        {
            tr.translate(birds[i].pos.x, birds[i].pos.y);
            tr.rotate(birds[i].angle * 57.32f);
            tr.translate(-birds[i].pos.x, -birds[i].pos.y);
            triangle[0].position = sf::Vector2f(birds[i].pos.x - B_DRAW_SIZE, birds[i].pos.y + B_DRAW_SIZE);
            triangle[1].position = sf::Vector2f(birds[i].pos.x, birds[i].pos.y - B_DRAW_SIZE);
            triangle[2].position = sf::Vector2f(birds[i].pos.x + B_DRAW_SIZE, birds[i].pos.y + B_DRAW_SIZE);
            triangle[0].color = birds[i].color;
            triangle[1].color = birds[i].color;
            triangle[2].color = birds[i].color;
            renderTex.draw(triangle, tr);
            tr = sf::Transform::Identity;
        }
        sf::CircleShape rect(20.f);
        rect.setOrigin(sf::Vector2f(10.f,10.f));
        rect.setFillColor(sf::Color(0,0,0,255));
        for (int i = 0; i < obstaclesNB; ++i)
        {
            rect.setPosition(vec_to_sfvec2_v(obstacles[i]));
            renderTex.draw(rect);
        }

        window.draw(renderSprt);

        window.display();
    }

    return EXIT_SUCCESS;
}

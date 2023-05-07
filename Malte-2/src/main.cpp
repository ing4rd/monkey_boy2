#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../header/constants.h"
#include "../header/object.h"
#include "../header/file_handler.h"

void handle_input(File_handler &file_handler)
{

    auto player = dynamic_cast<Player *>(file_handler.m_obj.at(player_idx));
    sf::Vector2f old_pos = player->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        player->move(-player->get_speed(), 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        player->move(player->get_speed(), 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && player->get_cool_down() == player_cd)
    {
        player->attack(file_handler);
    }

    for (auto &border : file_handler.m_borders)
    {
        if (player->getGlobalBounds().intersects(border.getGlobalBounds()))
        {
            player->setPosition(old_pos);
            break;
        }
    }
}

void handle_logic(File_handler &file_handler)
{
    for (auto &obj : file_handler.m_obj)
    {
        obj->update(file_handler);
    }
}

void handle_render(sf::RenderWindow &window, File_handler &file_handler)
{
    window.clear();
    for (auto const &border : file_handler.m_borders)
    {
        window.draw(border);
    }
    for (auto sprites : file_handler.m_obj)
    {
        window.draw(*sprites);
    }
}

void handle_fps(sf::RenderWindow &window, sf::Time const target, sf::Clock const &clock)
{
    window.display();
    auto wait_time{target - clock.getElapsedTime()};
    sf::sleep(std::max(sf::Time::Zero, wait_time));
}

int main()
{
    File_handler file_handler{};
    sf::RenderWindow window{sf::VideoMode{width, height}, "Monkeyboy 2"};

    // Create sprites-------------------------------------------------

    Player *player{new Player{file_handler.m_texture["monkeyboy.png"], 3}};
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(player->getTexture()->getSize());
    player->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    player->setPosition(960, 930);
    player->setScale(1.5f, 1.5f);
    file_handler.m_obj.push_back(player);

    Monkey *monkey{new Monkey{file_handler.m_texture["monkey.png"], 3}};
    textureSize = static_cast<sf::Vector2f>(monkey->getTexture()->getSize());
    monkey->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    monkey->setPosition(left_spawn, 100);
    monkey->setScale(1.5f, 1.5f);
    file_handler.m_obj.push_back(monkey);

    monkey = new Monkey{file_handler.m_texture["monkey.png"], 3};
    textureSize = static_cast<sf::Vector2f>(monkey->getTexture()->getSize());
    monkey->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    monkey->setPosition(right_spawn, 100);
    monkey->setScale(1.5f, 1.5f);
    file_handler.m_obj.push_back(monkey);

    //----------------------------------------------------------------

    while (window.isOpen())
    {
        sf::Clock clock;
        clock.restart();
        auto const target{sf::milliseconds(1000.0 / fps)};

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        handle_input(file_handler);
        handle_logic(file_handler);
        handle_render(window, file_handler);
        handle_fps(window, target, clock);
    }
}
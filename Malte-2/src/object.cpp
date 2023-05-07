#include "../header/constants.h"
#include "../header/object.h"
#include "../header/file_handler.h"
#include <cmath>

bool Mob::no_clipping(File_handler &file_handler)
{
    // Check for collisions with other objects
    for (Object *obj : file_handler.m_obj)
    {
        // Ignore collisions with self
        if (obj == this)
            continue;

        // Check for collision on the x-axis
        if (getGlobalBounds().intersects(obj->getGlobalBounds()))
        {
            // Calculate minimum translation distance (MTD) on the x-axis
            sf::Vector2f mtd;
            float dx = getPosition().x - obj->getPosition().x;
            float min_distance = getGlobalBounds().width / 2.0f + obj->getGlobalBounds().width / 2.0f;
            if (std::abs(dx) < min_distance)
            {
                mtd.x = dx > 0 ? min_distance - std::abs(dx) : -min_distance + std::abs(dx);
            }
            // Adjust position to move out of collision on the x-axis
            move(getPosition() + mtd);

            return false;
        }
    }

    // No collisions detected
    return true;
}

void Player::update(File_handler &file_handler)
{
    m_cool_down++;
    m_cool_down = std::min(player_cd, m_cool_down);

    if (m_hp < 0)
    {
        // exit(0);
    }
}

void Mob::update(File_handler &file_handler)
{
    m_cool_down++;
    int cool_down = (dynamic_cast<Monkey *>(this) ? monkey_cd : monkey_boss_cd);
    m_cool_down = std::min(cool_down, m_cool_down);

    Object *player_pos{file_handler.m_obj.at(player_idx)};
    sf::Vector2f pos = getPosition();

    // Attack
    float distance_to_player = std::abs(getPosition().x - player_pos->getPosition().x);
    if (distance_to_player < attack_range && m_cool_down == cool_down)
    {
        attack(file_handler);
    }

    if (getGlobalBounds().left < player_pos->getGlobalBounds().left && no_clipping(file_handler))
    {
        pos.x += m_speed;
    }
    else if (getGlobalBounds().left > player_pos->getGlobalBounds().left && no_clipping(file_handler))
    {
        pos.x -= m_speed;
    }
    setPosition(pos);

    // Check if pepsi
    if (m_hp < 0)
    {
        auto it = std::find(file_handler.m_obj.begin(), file_handler.m_obj.end(), this);
        if (it != file_handler.m_obj.end())
        {
            file_handler.m_obj.erase(it);
            delete this;
        }
    }
}

void Projectile::update(File_handler &file_handler)
{
    // movement
    if (dynamic_cast<Arrow *>(this))
        move(0, -m_speed);
    else
        move(0, m_speed);

    if (this->getPosition().y < 0 || this->getPosition().y > height)
    {
        auto it = std::find(file_handler.m_obj.begin(), file_handler.m_obj.end(), this);
        if (it != file_handler.m_obj.end())
        {
            file_handler.m_obj.erase(it);
            delete this;
        }
    }

    // Collision
    for (auto &obj : file_handler.m_obj)
    {
        if (this->getGlobalBounds().intersects(obj->getGlobalBounds()))
        {
            if (obj == this)
                continue;

            if (Mob *mob = dynamic_cast<Mob *>(obj))
            {
                mob->take_dmg(get_dmg());
            }

            auto it = std::find(file_handler.m_obj.begin(), file_handler.m_obj.end(), this);
            if (it != file_handler.m_obj.end())
            {
                file_handler.m_obj.erase(it);
                delete this;
            }
            break;
        }
    }
}

// Player------------------------------------------
void Player::attack(File_handler &file_handler)
{
    m_cool_down = 0;

    Arrow *arrow{new Arrow{file_handler.m_texture["arrow.png"], 3, 1}};
    arrow->setPosition(getPosition().x, offset_arrow);
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(arrow->getTexture()->getSize());
    arrow->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    file_handler.m_obj.push_back(arrow);
}
// Monkey-------------------------------------------
void Monkey::attack(File_handler &file_handler)
{
    m_cool_down = 0;

    Stone *stone{new Stone{file_handler.m_texture["stone.png"], 3, 1}};
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(stone->getTexture()->getSize());
    stone->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    stone->setPosition(getPosition().x, offset_stone);
    file_handler.m_obj.push_back(stone);
}
// Monkey_boss--------------------------------------
void Monkey_Boss::attack(File_handler &file_handler)
{
    m_cool_down = 0;

    Stone *stone{new Stone{file_handler.m_texture["stone.png"], 7, 1}};
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(stone->getTexture()->getSize());
    stone->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    stone->setPosition(getPosition().x, offset_stone);
    file_handler.m_obj.push_back(stone);
}
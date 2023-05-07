#pragma once
#include <SFML/Graphics.hpp>
#include "file_handler.h"
#include <string>
#include <cstdlib>

// Main class------------------------------------------------
class Object : public sf::Sprite
{
public:
    Object() = default;
    Object &operator=(const Object &) = delete;
    Object(const Object &) = delete;
    virtual ~Object() = default;
    Object(sf::Texture &texture, double move)
        : sf::Sprite{texture}, m_speed{move} {};
    auto get_speed() const { return m_speed; };

    virtual void update(File_handler &file_handler) = 0;

protected:
    double m_speed;
};
// Mobs classes----------------------------------------------
class Mob : public Object
{
public:
    Mob() = default;
    virtual ~Mob() = default;
    Mob(sf::Texture &texture, int hp, double move)
        : Object{texture, move}, m_hp{hp}, m_cool_down{} {};
    int get_hp() const { return m_hp; };

    virtual void attack(File_handler &file_handler) = 0;
    void take_dmg(int const dmg) { m_hp -= dmg; };
    void update(File_handler &file_handler) override;
    int get_cool_down() const { return m_cool_down; };

protected:
    bool no_clipping(File_handler &file_handler);
    int m_hp;
    int m_cool_down;
};

class Player : public Mob
{
public:
    Player() = default;
    virtual ~Player() = default;
    Player(sf::Texture &texture, int hp)
        : Mob{texture, hp, 4.0} {};

    void update(File_handler &file_handler) override;
    void attack(File_handler &file_handler) override;
};

class Monkey : public Mob
{
public:
    Monkey() = default;
    virtual ~Monkey() = default;
    Monkey(sf::Texture &texture, int hp)
        : Mob{texture, hp, 1.0} {};
    void attack(File_handler &file_handler) override;
};

class Monkey_Boss : public Mob
{
public:
    Monkey_Boss() = default;
    virtual ~Monkey_Boss() = default;
    Monkey_Boss(sf::Texture &texture, int hp)
        : Mob{texture, hp, 0.2} {};
    void attack(File_handler &file_handler) override;
};
// Projectile classes-------------------------------------------

class Projectile : public Object
{
public:
    Projectile(sf::Texture &texture, double move, int dmg)
        : Object{texture, move}, m_dmg{dmg} {};
    virtual ~Projectile() = default;
    int get_dmg() const { return m_dmg; };

    void update(File_handler &file_handler) override;

protected:
    int m_dmg;
};

class Arrow : public Projectile
{
public:
    Arrow(sf::Texture &texture, double move, int dmg)
        : Projectile{texture, move, dmg} {};
    virtual ~Arrow() = default;
};

class Stone : public Projectile
{
public:
    Stone(sf::Texture &texture, double move, int dmg)
        : Projectile{texture, move, dmg} {};
    virtual ~Stone() = default;
};

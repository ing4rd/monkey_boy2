#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <filesystem>
#include <iostream>

class Object;

class File_handler
{
public:
    File_handler()
        : m_texture{initialize_sprites()}, m_borders{initialize_borders()}, m_obj{} {};

    ~File_handler() = default;
    std::unordered_map<std::string, sf::Texture> initialize_sprites();
    std::array<sf::RectangleShape, 6> initialize_borders();
    // std::vector<Object *> initialize_objects();

    std::unordered_map<std::string, sf::Texture> m_texture;
    std::array<sf::RectangleShape, 6> m_borders;
    std::vector<Object *> m_obj;
};
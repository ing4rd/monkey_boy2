#include "../header/file_handler.h"
#include "../header/object.h"

std::unordered_map<std::string, sf::Texture> File_handler::initialize_sprites()
{
    namespace fs = std::filesystem;
    std::unordered_map<std::string, sf::Texture> m_texture;

    fs::path dirPath("resources/images");

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        std::cout << "Error while looking for image path!\n";
    }

    for (const auto &entry : fs::directory_iterator(dirPath))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            sf::Texture texture;
            if (texture.loadFromFile(entry.path().string()))
            {
                m_texture[filename] = texture;
            }
            else
            {
                std::cout << "Error reading image!\n";
            }
        }
    }
    return m_texture;
};

std::array<sf::RectangleShape, 6> File_handler::initialize_borders()
{
    std::array<sf::RectangleShape, 6> m_borders;

    m_borders[0] = sf::RectangleShape(sf::Vector2f(1920, 20)); // Player floor.
    m_borders[0].setPosition(0, 1000);
    m_borders[0].setFillColor(sf::Color::Blue);

    m_borders[1] = sf::RectangleShape(sf::Vector2f(20, 1750));
    m_borders[1].setPosition(1620, 170);
    m_borders[1].setFillColor(sf::Color::Green);

    m_borders[2] = sf::RectangleShape(sf::Vector2f(1920, 20)); // Enemy floor.
    m_borders[2].setPosition(0, 170);
    m_borders[2].setFillColor(sf::Color::Blue);

    m_borders[3] = sf::RectangleShape(sf::Vector2f(20, 1750));
    m_borders[3].setPosition(300, 170);
    m_borders[3].setFillColor(sf::Color::Green);

    m_borders[4] = sf::RectangleShape(sf::Vector2f(20, 170));
    m_borders[4].setPosition(1900, 0);
    m_borders[4].setFillColor(sf::Color::Green);

    m_borders[5] = sf::RectangleShape(sf::Vector2f(20, 170));
    m_borders[5].setPosition(0, 0);
    m_borders[5].setFillColor(sf::Color::Green);

    return m_borders;
}
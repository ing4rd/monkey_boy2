// #include <SFML/Graphics.hpp>
// #include "../header/object.h"

// using namespace sf;

// int main()
// {
//   RenderWindow gamewindow{
//       VideoMode{1920, 1170}, "Monkeyboy 2"};

//   RectangleShape platform1(Vector2f(1920, 20));
//   platform1.setPosition(0, 1000);
//   platform1.setFillColor(Color::Green);
//   RectangleShape platform2(Vector2f(20, 1750));
//   platform2.setPosition(1620, 170);
//   platform2.setFillColor(Color::Green);
//   RectangleShape platform3(Vector2f(1920, 20));
//   platform3.setPosition(0, 170);
//   platform3.setFillColor(Color::Green);
//   RectangleShape platform4(Vector2f(20, 1750));
//   platform4.setPosition(300, 170);
//   platform4.setFillColor(Color::Green);
//   RectangleShape platform5(Vector2f(20, 170));
//   platform5.setPosition(1900, 0);
//   platform5.setFillColor(Color::Green);
//   RectangleShape platform6(Vector2f(20, 170));
//   platform6.setPosition(0, 0);
//   platform6.setFillColor(Color::Green);

//   Texture t_monkeyboy;
//   if (!t_monkeyboy.loadFromFile("resources/images/monkeyboy.png"))
//   {
//     return 1;
//   }
//   Sprite s_monkeyboy{t_monkeyboy};
//   s_monkeyboy.setPosition(960, 930);
//   Player player{"Hasse", &s_monkeyboy, 5};

//   Texture t_monkey;
//   if (!t_monkey.loadFromFile("resources/images/monkey.png"))
//   {
//     return 1;
//   }
//   Sprite s_monkey{t_monkey};
//   s_monkey.setPosition(100, 100);
//   Monkey monkey{"Nisse", &s_monkey, 5};

//   float const speed{4.0};

//   // float const speed { 4.0 };
//   Clock clock;
//   double const fps{60.0};
//   auto const target{milliseconds(1000.0 / fps)};

//   while (gamewindow.isOpen())
//   {
//     clock.restart();
//     Event event;

//     while (gamewindow.pollEvent(event))
//     {
//       if (event.type == Event::Closed)
//       {
//         gamewindow.close();
//       }
//     }

//     auto old_position{s_monkeyboy.getPosition()};
//     auto rectangle_box1{platform1.getGlobalBounds()};
//     auto rectangle_box2{platform2.getGlobalBounds()};
//     auto rectangle_box3{platform3.getGlobalBounds()};
//     auto rectangle_box4{platform4.getGlobalBounds()};
//     auto rectangle_box5{platform5.getGlobalBounds()};
//     auto rectangle_box6{platform6.getGlobalBounds()};

//     if (Keyboard::isKeyPressed(Keyboard::Key::W))
//     {
//       s_monkeyboy.setRotation(0);
//     }
//     else if (Keyboard::isKeyPressed(Keyboard::Key::A))
//     {
//       s_monkeyboy.move(-speed, 0);
//     }
//     else if (Keyboard::isKeyPressed(Keyboard::Key::D))
//     {
//       s_monkeyboy.move(speed, 0);
//     }

//     auto sprite_box{s_monkeyboy.getGlobalBounds()};
//     if (sprite_box.intersects(rectangle_box1) || sprite_box.intersects(rectangle_box2) || sprite_box.intersects(rectangle_box3) || sprite_box.intersects(rectangle_box4))
//     {
//       // om kollision, flytta tillbaks sprite
//       s_monkeyboy.setPosition(old_position);
//     }

//     gamewindow.clear();
//     gamewindow.draw(platform1);
//     gamewindow.draw(platform2);
//     gamewindow.draw(platform3);
//     gamewindow.draw(platform4);
//     gamewindow.draw(platform5);
//     gamewindow.draw(platform6);
//     gamewindow.draw(s_monkey);
//     gamewindow.draw(s_monkeyboy);
//   }
// }

// Libraries
#include <iostream>
#include <SFML/Graphics.hpp>

// Start
int main()
{
    // States
    char states[3][3] =
        {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '},

        };

    // Winner
    char winner = ' ';

    // Turns
    bool x_turn = true;

    // Position
    int cursor_x = 0;
    int cursor_y = 0;

    // Window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Tic Tac Toe");

    // Forms
    sf::CircleShape Circle;
    Circle.setPointCount(60);
    sf::RectangleShape Rectangle;
    sf::RectangleShape cursor;

    // Lambda function
    // Grid
    auto DrawGrid = [&](float space, float width, float position_x, float position_y)
    {
        Rectangle.setSize({space * 3, width});
        Rectangle.setOrigin(Rectangle.getGeometricCenter());
        Rectangle.setFillColor(sf::Color(128, 128, 128));

        // Horizontal
        Rectangle.setRotation(sf::degrees(0.f));
        Rectangle.setPosition({position_x, position_y - space / 2});
        window.draw(Rectangle);
        Rectangle.setPosition({position_x, position_y + space / 2});
        window.draw(Rectangle);

        // Vertical
        Rectangle.setRotation(sf::degrees(90.f));
        Rectangle.setPosition({position_x - space / 2, position_y});
        window.draw(Rectangle);
        Rectangle.setPosition({position_x + space / 2, position_y});
        window.draw(Rectangle);
    };

    // X
    auto DrawX = [&](float size, float width, float position_x, float position_y)
    {
        Rectangle.setSize({size, width});
        Rectangle.setOrigin(Rectangle.getGeometricCenter());
        Rectangle.setFillColor(sf::Color::Green);
        Rectangle.setPosition({position_x, position_y});
        Rectangle.setRotation(sf::degrees(45.f));
        window.draw(Rectangle);
        Rectangle.setRotation(sf::degrees(-45.f));
        window.draw(Rectangle);
    };

    // O
    auto DrawO = [&](float size, float width, float position_x, float position_y)
    {
        Circle.setRadius(size / 2);
        Circle.setOrigin(Circle.getGeometricCenter());
        Circle.setFillColor(sf::Color::Transparent);
        Circle.setOutlineColor(sf::Color::Blue);
        Circle.setOutlineThickness(-width);
        Circle.setPosition({position_x, position_y});
        window.draw(Circle);
    };

    // Victory line
    auto DrawWinningLines = [&](float size, float width, float position_x, float position_y, float angle, float scale = 1.f)
    {
        // Linha de vitoria
        Rectangle.setSize({size * scale, width});
        Rectangle.setOrigin(Rectangle.getGeometricCenter());
        Rectangle.setFillColor(sf::Color(220, 220, 220));
        Rectangle.setPosition({position_x, position_y});
        Rectangle.setRotation(sf::degrees(angle));
        window.draw(Rectangle);
    };

    // Cursor
    auto DrawCursor = [&](float size, float width, float position_x, float position_y)
    {
        cursor.setSize({size, size});
        cursor.setOrigin(cursor.getGeometricCenter());
        cursor.setFillColor(sf::Color::Transparent);
        cursor.setOutlineColor(sf::Color::White);
        cursor.setOutlineThickness(-width);
        cursor.setPosition({position_x, position_y});
        window.draw(cursor);
    };

    // Events
    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            // Close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Resize the window
            else if (event->is<sf::Event::Resized>())
            {
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
            }

            // Keyboard controls
            else if (auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                // No winner yet
                if (winner == ' ')
                {

                    // WASD

                    // A
                    if (key->scancode == sf::Keyboard::Scancode::A and cursor_x > 0)
                    {
                        cursor_x--;
                    }

                    // D
                    if (key->scancode == sf::Keyboard::Scancode::D and cursor_x < 2)
                    {
                        cursor_x++;
                    }

                    // S
                    if (key->scancode == sf::Keyboard::Scancode::S and cursor_y < 2)
                    {
                        cursor_y++;
                    }

                    // W
                    if (key->scancode == sf::Keyboard::Scancode::W and cursor_y > 0)
                    {
                        cursor_y--;
                    }

                    // Arrows

                    // Left
                    if (key->scancode == sf::Keyboard::Scancode::Left and cursor_x > 0)
                    {
                        cursor_x--;
                    }

                    // Right
                    if (key->scancode == sf::Keyboard::Scancode::Right and cursor_x < 2)
                    {
                        cursor_x++;
                    }

                    // Down
                    if (key->scancode == sf::Keyboard::Scancode::Down and cursor_y < 2)
                    {
                        cursor_y++;
                    }

                    // Up
                    if (key->scancode == sf::Keyboard::Scancode::Up and cursor_y > 0)
                    {
                        cursor_y--;
                    }

                    // Marking

                    /* X with X                                        X with LCtrl
                    if ((key->scancode == sf::Keyboard::Scancode::X or key->scancode == sf::Keyboard::Scancode::LControl) and states[cursor_y][cursor_x] == ' ')
                    {
                        if (x_turn)
                        {
                            states[cursor_y][cursor_x] = 'X';
                            x_turn = !x_turn;
                        }
                    }*/

                    // O with O                                             O with Enter
                    else if ((key->scancode == sf::Keyboard::Scancode::O or key->scancode == sf::Keyboard::Scancode::Enter) and states[cursor_y][cursor_x] == ' ')
                    {
                        if (!x_turn)
                        {
                            states[cursor_y][cursor_x] = 'O';
                            x_turn = !x_turn;
                        }

                        // IA starts playing
                        //Various analisys of conditions and possible plays

                        if (states[1][1] == ' ')
                        {
                            states[1][1] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[0][1] == ' ' and x_turn == true)
                        {
                            states[0][1] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[2][1] == ' ' and x_turn == true)
                        {
                            states[2][1] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[0][2] == ' ' and x_turn == true)
                        {
                            states[0][2] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[2][0] == ' ' and x_turn == true)
                        {
                            states[2][0] = 'X';
                            x_turn = !x_turn;
                        }
                        if (states[0][1] == ' ' and x_turn == true)
                        {
                            states[0][1] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[0][2] == ' ' and x_turn == true)
                        {
                            states[0][2] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[2][0] == ' ' and x_turn == true)
                        {
                            states[2][0] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[1][2] == ' ' and x_turn == true)
                        {
                            states[1][2] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[0][0] == ' ' and x_turn == true)
                        {
                            states[0][0] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[2][2] == ' ' and x_turn == true)
                        {
                            states[2][2] = 'X';
                            x_turn = !x_turn;
                        }
                        else if (states[1][0] == ' ' and x_turn == true)
                        {
                            states[1][0] = 'X';
                            x_turn = !x_turn;
                        }
                    }
                }

                // Reset com Esc
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            states[i][j] = ' ';

                    // Reset cursor
                    cursor_x = 1;
                    cursor_y = 1;

                    // Reset turn
                    x_turn = true;

                    // Reset Winner
                    winner = ' ';
                }
            }

            // Window size
            float window_w = window.getView().getSize().x;
            float window_h = window.getView().getSize().y;
            float window_min = (window_w < window_h) ? window_w : window_h;

            // Parameters
            float space = 0.3f * window_min;
            float size = 0.8f * space;
            float width = 0.1f * size;

            // Background (Color)
            window.clear(sf::Color::Black);

            // Draw Grid
            DrawGrid(space, width / 4, window_w / 2, window_h / 2);

            // Drawing
            for (int y = 0; y < 3; y++)
            {
                // X e O (Loops)
                for (int x = 0; x < 3; x++)
                {
                    // Draw O
                    if (states[y][x] == 'O')
                    {
                        DrawO(size, width, window_w / 2 + space * (x - 1), window_h / 2 + space * (y - 1));
                    }

                    // Draw X
                    else if (states[y][x] == 'X')
                    {
                        DrawX(size, width, window_w / 2 + space * (x - 1), window_h / 2 + space * (y - 1));
                    }
                }
            }
            // Victory lines
            for (int i = 0; i < 3; i++)
            {
                // Horizontal
                if ((states[i][0] != ' ') and (states[i][0] == states[i][1]) and (states[i][1] == states[i][2]))
                {
                    DrawWinningLines(space * 3, width / 2, window_w / 2, window_h / 2 + space * (i - 1), 0.f);
                    winner = states[0][i];
                }

                // Vertical
                if ((states[0][i] != ' ') and (states[0][i] == states[1][i]) and (states[1][i] == states[2][i]))
                {
                    DrawWinningLines(space * 3, width / 2, window_w / 2 + space * (i - 1), window_h / 2, 90.f);
                    winner = states[0][0];
                }
            }

            // Diagonal 1
            if ((states[0][0] != ' ') and (states[0][0] == states[1][1]) and (states[1][1] == states[2][2]))
            {
                DrawWinningLines(space * 3, width / 2, window_w / 2, window_h / 2, 45.f, 1.4f);
                winner = states[0][0];
            }

            // Diagonal 2
            if ((states[0][2] != ' ') and (states[0][2] == states[1][1]) and (states[1][1] == states[2][0]))
            {
                DrawWinningLines(space * 3, width / 2, window_w / 2, window_h / 2, -45.f, 1.4f);
                winner = states[0][2];
            }

            // Cursor
            if (winner == ' ')
            {
                DrawCursor(space, width / 2, window_w / 2 + space * (cursor_x - 1), window_h / 2 + space * (cursor_y - 1));
            }

            // Display
            window.display();
        }
    }
    return 0;
}

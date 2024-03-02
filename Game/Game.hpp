#include "../Header.hpp"
#include "../InternalServer/InternalServer.hpp"

class Game
{
private:
    const unsigned int windowWidth;
    const unsigned int windowHeight;

    Unit player;
    std::list<NPC*> npcs;
    Camera camera;
    sf::Font font;

    InternalServer server;
    sf::RenderWindow* window;

    void createNPC();
    void keyboardCheck();
public:
    Game(const unsigned int windowWidth, const unsigned int windowHeight, sf::RenderWindow& window);
    void setFont(sf::Font& font);
    void run();
    ~Game();
};

Game::Game(const unsigned int windowWidth, const unsigned int windowHeight, sf::RenderWindow& window)
: windowWidth(windowWidth),
  windowHeight(windowHeight)
{
    this->window = &window;

    player = Unit(Coordinates(30, 30), Vector2d(0.8, 0.8), *server.getLayout());
    player.setSpeed(0.1);

    camera = Camera(player, *server.getLayout(), 21, window, windowWidth, windowHeight);

    debuger.setWindow(&window);
}

void Game::setFont(sf::Font& font)
{
    this->font = font;
    debuger.setFont(font);
}


void Game::run()
{
    FpsCounter fpsCounter(font);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }
            if (event.type == sf::Event::MouseWheelScrolled and event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    camera.setScale(camera.getScale() * 1.1);
                }
                else
                {
                    camera.setScale(camera.getScale() * 0.9);
                }
            }
        }

        fpsCounter.getStartTime();

        // for (auto i : npcList) i->move(animal.getPos());

        server.tick();

        keyboardCheck();

        if (!window->isOpen()) return;

        window->clear();

        camera.render();

        fpsCounter.getEndTime();

        fpsCounter.draw(*window, windowWidth);

        debuger.drawConsole();

        window->display();
    }
}

void Game::keyboardCheck()
{
    int x = 0;
    int y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x++;

    if (x != 0 or y != 0)
    {
        player.move(atan2(y, x) * 180 / M_PI);
    }
}

void Game::createNPC()
{
    if (npcs.size() < 10) 
    {
        NPC* npc = new NPC(Coordinates(rand() % 30 + 30, rand() % 30 + 30), Vector2d(1, 1), *server.getLayout());
        npc->setSpeed((rand() % 40 + 10) / 1000.0);
        npcs.push_back(npc);
    }
}

Game::~Game()
{
    for (auto i : npcs) delete i;
}

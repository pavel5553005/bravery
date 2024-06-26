#include "../Header.hpp"

class Game
{
private:

    Unit player;
    std::list<NPC*> npcs;
    Camera camera;
    std::list<sf::Keyboard::Key> pressedKeys;

    InternalServer server;

    void createNPC();
    void keyboardCheck();
    bool oneKeyPressed(sf::Keyboard::Key key);
public:
    Game();
    void run();
    ~Game();
};

Game::Game() : player(Coordinates(0, 0, 0), Vector2d(0.75, 0.75))
{
    player.setLayout(server.getLayout());
    camera = Camera(player, 100);
    camera.generateTextures();

    player.setSpeed(0.1001);
}

void Game::run()
{
    while (BaS.window.isOpen())
    {
        sf::Event event;
        while (BaS.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                
                BaS.window.close();
                server.~InternalServer();
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

        BaS.counter.getStartTime();

        // for (auto i : npcList) i->move(animal.getPos());

        server.tick();

        keyboardCheck();

        if (!BaS.window.isOpen()) return;

        BaS.window.clear();

        camera.render();

        BaS.counter.getEndTime();

        BaS.counter.draw(BaS.window);

        BaS.console.drawConsole();

        BaS.window.display();
    }
}

bool Game::oneKeyPressed(sf::Keyboard::Key key)
{
    if (!sf::Keyboard::isKeyPressed(key))
    {
        for (auto i : pressedKeys)
        {
            if (i == key)
            {
                pressedKeys.remove(i);
                return false;
            }
        }
        return false;
    }
    else
    {
        for (auto i : pressedKeys)
        {
            if (i == key)
            {
                return false;
            }
        }
        pressedKeys.push_back(key);
        return true;
    }
}
void Game::keyboardCheck()
{
    int x = 0;
    int y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) BaS.window.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x++;
    if (oneKeyPressed(sf::Keyboard::E))
    {
        handler.generateEvent(Event(Event::Type::TestEvent));
    }
    if (oneKeyPressed(sf::Keyboard::N))
    {
        player.setPos(Coordinates(player.getPos().x, player.getPos().y, player.getPos().z - 1));
        BaS.console.log(std::to_string(player.getPos().z));
    }
    if (oneKeyPressed(sf::Keyboard::H))
    {
        player.setPos(Coordinates(player.getPos().x, player.getPos().y, player.getPos().z + 1));
        BaS.console.log(std::to_string(player.getPos().z));
    }

    if (x != 0 or y != 0)
    {
        player.move(atan2(y, x) * 180 / M_PI);
    }
}

void Game::createNPC()
{
    if (npcs.size() < 10) 
    {
        NPC* npc = new NPC(Coordinates(rand() % 30 + 30, rand() % 30 + 30, 0), Vector2d(1, 1));
        npc->setSpeed((rand() % 40 + 10) / 1000.0);
        npcs.push_back(npc);
    }
}

Game::~Game()
{
    server.~InternalServer();
}

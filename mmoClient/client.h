#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "actor.h"
#include "level.h"

class Client{
	sf::RenderWindow window; // Create a window.
	sf::SocketSelector selector;  // Create selector for listening sockets (only for receiving info).
	sf::TcpSocket socket; // Create a Socket.
	sf::Clock mainClock; // Creat mainClock of the client loop.
	sf::Time mainTimer; // Create mainTimer of the client loop.
	sf::Time lastUpdate; // Time of the last update of the client.
	sf::Time drawUpdate;

	std::vector<Actor> actors;
	//Actor *me;

	int myId; // Id of client charakters.

	bool focused; // Determine if window have focus.

	Map test;

	sf::Thread r_thread;
public:
	Client();
	~Client();
	void run(); // 
	void draw(); // Drawing window and dispaying it.
	void receive(); // Receiving messages.
	void send(); // Sending messages.
	void transferFromBuffor(std::vector<Actor>&);
	bool connect(); // Connecting to the server.
};

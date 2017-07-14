#include "client.h"

Client::Client() : r_thread(&Client::receive, this) {
	window.create(sf::VideoMode(500, 500), "SFML works!"); // Initialize the window.
	window.setFramerateLimit(30); // Set FPS limit for the window.
	mainTimer = sf::Time::Zero; // Initialize the mainTimer.
	lastUpdate = sf::Time::Zero; // initialize the lastUpdate timer.
	drawUpdate = sf::Time::Zero; // initialize the drawUpdate timer.
	myId = 0;
	players.resize(0);
	focused = 1;

	test.init(0);
	wsadIndex = 4;

	mainManager.load();

	mouseButtonIndex = 0;

	rPlayersSize = 0;
	rEnemiesSize = 0;
}

Client::~Client(){

}

void Client::run(){
	if (!connect()){ // Try to connect with the server.
		std::cout << "Nie mozna polaczyc!" << std::endl;
	}
	else {
		std::cout << "Polaczono z serverem!" << std::endl;
		selector.add(socket); // Add the socket to the selector.
		r_thread.launch();
	}

	while (window.isOpen()) // The main loop start here.
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // Closing window.
			{
				socket.disconnect();
				window.close();
				break;
			}
			if (event.type == sf::Event::LostFocus) focused = 0; // Loseing focus.
			if (event.type == sf::Event::GainedFocus) focused = 1; // Gaining focus.
			if (focused) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
				wsadIndex = 4;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) wsadIndex = 0;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) wsadIndex = 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) wsadIndex = 2;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) wsadIndex = 3;
				mouseButtonIndex = 0;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))mouseButtonIndex = 1;
			}
		}

		mainTimer = mainClock.getElapsedTime(); // Get the main time;
		if (mainTimer.asMilliseconds() - lastUpdate.asMilliseconds() >= 20){ // Update scene and send data only every 50 milliseconds;
			for (unsigned i = 0; i < enemies.size(); i++){
				enemies[i].update();
			}  
			for (unsigned i = 0; i < players.size(); i++){
				players[i].update(); // Update players (pos, render state etc)
				//actors[i].showStats(); // Just for checking player stats.
			}
			draw();
			send(); // Send messages to the server.
			lastUpdate = mainTimer;
		}
	}
}

void Client::draw(){
	window.clear(sf::Color::Green); // Clear the window and set green color for backgroud.
	test.draw(&window);
	for (unsigned i = 0; i < enemies.size(); i++){
		enemies[i].draw(&window); // Draw all actors.
	}
	for (unsigned i = 0; i < players.size(); i++){
		players[i].draw(&window); // Draw all actors.
	}
	window.display(); // Display window.
}

void Client::receive(){
	while (window.isOpen()) // The main loop start here.
	{
		if (selector.wait()) // How long will it wait for activity.
		{
			// Test the listener
			if (selector.isReady(socket))
			{
				sf::Packet packet;
				sf::Socket::Status status = socket.receive(packet); // Get status of action.
				if (status == sf::Socket::Done) // Check status, if receiving was successfull.
				{
					std::string type;
					packet >> type;
					if (type == "INIT"){ // If packet contains only id of player, set it.
						packet >> myId;
						std::cout << myId << std::endl;
					}
					if (type == "DATAS"){ // If packet contains player states render them.
						std::vector<ActorTCPdatas> buffor; // Create buffor for incoming datas.
						packet >> rPlayersSize >> rEnemiesSize;
						//std::cout << rPlayersSize << " , " << rEnemiesSize << std::endl;
						for (unsigned i = 0; i < rPlayersSize + rEnemiesSize; i++){
							ActorTCPdatas tmp;
							packet >> tmp;
							buffor.push_back(tmp);
						}
						transferFromBuffor(buffor); // Copy datas from buffor to actors vector.
					}
				}
				if (status == sf::Socket::Disconnected)
				{
					std::cout << "Utracono polaczenie z serwerem." << std::endl;
				}
			}
		}
	}
}

void Client::send(){
	sf::Packet packet;
	packet << wsadIndex << mouseButtonIndex;
	socket.send(packet);
}

void Client::transferFromBuffor(std::vector<ActorTCPdatas> &buffor){
	if (players.size() > rPlayersSize){
		// Now we delete objects which server didnt send.
		for (unsigned i = 0; i < players.size(); i++){
			bool exist = false;
			for (unsigned j = 0; j < rPlayersSize; j++){
				if (players[i].getId() == buffor[j].getId()) exist = true;
			}
			if (!exist) players.erase(players.begin() + i);
		}
	}
	else if (players.size() < rPlayersSize){
		// Find objects to add and add them.
		for (unsigned j = 0; j < buffor.size(); j++){
			bool exist = false;
			for (unsigned i = 0; i < players.size(); i++){
				if (buffor[j].getId() == players[i].getId()) exist = true;
			}
			if (!exist){
				Player tmp;
				tmp.init(buffor[j].getId());
				players.push_back(tmp);
			}
		}
	}
	// Just copy data from buffor to actros.
	for (unsigned i = 0; i < players.size(); i++){
		for (unsigned j = 0; j < rPlayersSize; j++){
			if (players[i].getId() == buffor[j].getId()){
				players[i].captureData(buffor[j]);
			}
		}
	}

	if (enemies.size() > rEnemiesSize){
		// Now we delete objects which server didnt send.
		for (unsigned i = 0; i < enemies.size(); i++){
			bool exist = false;
			for (unsigned j = rPlayersSize; j < rPlayersSize + rEnemiesSize; j++){
				if (enemies[i].getId() == buffor[j].getId()) exist = true;
			}
			if (!exist) enemies.erase(enemies.begin() + i);
		}
	}
	else if (enemies.size() < rEnemiesSize){
		// Find objects to add and add them.
		for (unsigned j = rPlayersSize; j < rPlayersSize + rEnemiesSize; j++){
			bool exist = false;
			for (unsigned i = 0; i < enemies.size(); i++){
				if (buffor[j].getId() == enemies[i].getId()) exist = true;
			}
			if (!exist){
				Enemy tmp;
				tmp.init(buffor[j].getId());
				enemies.push_back(tmp);
			}
		}
	}
	// Just copy data from buffor to enemies.
	for (unsigned i = 0; i < enemies.size(); i++){
		for (unsigned j = rPlayersSize; j < rPlayersSize + rEnemiesSize; j++){
			if (enemies[i].getId() == buffor[j].getId()){
				enemies[i].captureData(buffor[j]);
			}
		}
	}
}

bool Client::connect(){
	sf::Socket::Status status = socket.connect("25.60.3.40", 55001); // 
	return status == sf::Socket::Done;
}

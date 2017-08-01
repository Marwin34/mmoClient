#include "client.h"

Client::Client() : r_thread(&Client::receive, this){
	window.create(sf::VideoMode(500, 500), "SFML works!"); // Initialize the window.
	window.setFramerateLimit(30); // Set FPS limit for the window.
	mainTimer = sf::Time::Zero; // Initialize the mainTimer.
	lastUpdate = sf::Time::Zero; // initialize the lastUpdate timer.
	myIndex = 0;
	players.resize(0);
	focused = 1;

	test.init(0);
	wsadIndex = 4;

	mainManager.load();
	me.loadGraphics();

	mouseButtonIndex = 0;

	rPlayersSize = 0;
	rEnemiesSize = 0;

	clientTick = 0;
	received = false;
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
				me.input();
			}
		}

		mainTimer = mainClock.getElapsedTime(); // Get the main time;
		if (mainTimer.asMilliseconds() - lastUpdate.asMilliseconds() >= 33){ // Update scene and send data only every 50 milliseconds;			
			me.update(&test.getObstacles());
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
			clientTick++;
		}
		sf::sleep(sf::milliseconds(5));
	}
}

void Client::draw(){
	if (received) {
		window.clear(sf::Color::Green); // Clear the window and set green color for backgroud.
		test.draw(&window);
		me.draw(&window);
		for (unsigned i = 0; i < enemies.size(); i++){
			enemies[i].draw(&window); // Draw all actors.
		}
		for (unsigned i = 0; i < players.size(); i++){
			players[i].draw(&window); // Draw all actors.
		}
		window.display(); // Display window.
	}
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
					//std::cout << "RPS : " << 1.f / receiveClock.getElapsedTime().asSeconds() << std::endl;
					//receiveClock.restart();
					std::string type;
					packet >> type;
					if (type == "DATAS"){ // If packet contains player states render them.
						std::vector<ActorTCPdatas> buffor; // Create buffor for incoming datas.
						PlayerTCPdatas meBuffor;
						packet >> rPlayersSize >> rEnemiesSize;
						packet >> meBuffor;
						//std::cout << rPlayersSize << " , " << rEnemiesSize << std::endl;
						for (unsigned i = 0; i < rPlayersSize + rEnemiesSize; i++){
							ActorTCPdatas tmp;
							packet >> tmp;
							buffor.push_back(tmp);
						}
						transferFromBuffor(buffor, meBuffor); // Copy datas from buffor to actors vector.
						received = true;
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
	if (me.mustSend()){
		sf::Packet packet;
		packet << me;
		socket.send(packet);
		me.sended();
	}
}

void Client::transferFromBuffor(std::vector<ActorTCPdatas> &buffor, PlayerTCPdatas &meBuffor){
	me.captureData(meBuffor);
	players.resize(rPlayersSize);
	enemies.resize(rEnemiesSize);

	for (unsigned i = 0; i < rPlayersSize + rEnemiesSize; i++){
		if (i < players.size()){
			players[i].captureData(buffor[i]);
		}
		else {
			enemies[i - players.size()].captureData(buffor[i]);
		}
	}
}
bool Client::connect(){
	sf::Socket::Status status = socket.connect("25.60.3.40", 55001); // 
	return status == sf::Socket::Done;
}

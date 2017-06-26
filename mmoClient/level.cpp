#include "level.h"

Map::Map(){
	width = 0;
	height = 0;
	sprite.setPosition(0, 0);
	obstacles.resize(0);
}

Map::~Map(){

}

void Map::init(int index){
	switch (index){
	case 0: // Starting zone.
		if (!loadFromFile("starting")) std::cout << "Unable to load map" << std::endl;
		break;
	}
}

void Map::draw(sf::RenderWindow *win){
	win->draw(sprite);
}

bool Map::loadFromFile(std::string path){

	if (!image.loadFromFile("./img/maps/" + path + ".png")) return false; // Check if image of the map was loaded.

	std::fstream file("./resources/" + path+".txt", std::ios::in); // Check if .txt file was opened.
	if (!file) return false;

	// Set texture and load coliders.
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	std::string linia;
	int cnt = 0;

	std::string tmp;
	std::string tmp2;
	std::istringstream stream("");

	while (!file.eof()){
		std::getline(file, linia);
		if (linia.find("width") != std::string::npos && linia.find("width") == 0) { // wczytanie width
			tmp = linia.substr(linia.find("=") + 1, linia.length() - linia.find("=") - 1);
			stream.clear();
			stream.str(tmp);
			stream >> width;
		}

		if (linia.find("height") != std::string::npos && linia.find("height") == 0) { // wczytanie height
			tmp = linia.substr(linia.find("=") + 1, linia.length() - linia.find("=") - 1);
			stream.clear();
			stream.str(tmp);
			stream >> height;
		}

		if (linia.find("type=colider") != std::string::npos && linia.find("type=colider") == 0){ // If there is any colider on the map, read it.
			std::vector<float> tmpObstacle; // Create temporary obstacle
			while (1){
				file >> tmp;
				if (tmp.find("location") != std::string::npos && tmp.find("location") == 0){ // Fin its location and read it to memory.
					tmp = tmp.substr(tmp.find("=") + 1, tmp.length() - tmp.find("=") - 1);
					stream.clear();
					stream.str(tmp);
					while (tmp.length()){
						if (tmp.find(",") != std::string::npos){ // For 3 first stats.
							tmp2 = tmp.substr(0, tmp.find(","));
							stream.clear();
							stream.str(tmp2);
							float tmpInt;
							stream >> tmpInt;
							tmpObstacle.push_back(tmpInt);
							tmp = tmp.substr(tmp.find(",") + 1, tmp.length() - tmp.find(",") - 1);
						}
						else { // For last stat.
							stream.clear();
							stream.str(tmp);
							float tmpInt;
							stream >> tmpInt;
							tmpObstacle.push_back(tmpInt);
							tmp = ""; // Set tmp string to empty.
						}
					}
					break;
				}
			}
			if (tmpObstacle.size() == 4) obstacles.push_back(tmpObstacle); // If succesfully readed all 4 obstacle statistics, add it to vector.
		}
	}
	file.close();

	return true; 
}

std::vector<std::vector<float>> Map::getObstacles(){
	return obstacles;
}
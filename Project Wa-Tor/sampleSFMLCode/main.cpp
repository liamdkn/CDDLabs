//Author: Liam Durkan 8/11/23
//rhiks

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

using namespace std;

struct Location{
    int xAxis;
    int yAxis;
};

struct Cell{
    int id;
    int breed;
    int starve;
};

struct Neighbours{
    int above;
    int below;
    int left;
    int right;
};

// Variables
int NumShark = 40;
int NumFish = 40;
int FishBreed = 4;
int SharkBreed = 5;
int Starve = 5;
int GridSize = 1000;
int Threads;


const int xdim = 100;
const int ydim= 100;

int WindowXSize=800;
int WindowYSize=600;
int cellXSize=WindowXSize/xdim;
int cellYSize=WindowYSize/ydim;

int randomNumber;

//Array representing whats in a cell
Cell oceanGrid[xdim][ydim];
Cell newOceanGrid[xdim][ydim];
sf::RectangleShape recArray[xdim][ydim];


Location randomLocation(){
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}

void initialiseOcean(){
    for(int i = 0; i < xdim; i++){
        for(int j = 0; j < ydim; j++){
            oceanGrid[i][j].id = 0;
        }
    }
}

void populateAnimals(){
    for(int i = 0; i < NumFish; i++){
        Location fishLocation;
        do{
            fishLocation = randomLocation();
        } while(oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id != 0);
        oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id = 2;
    }
    for(int i = 0; i < NumShark; i++){
        Location sharkLocation;
        do{
            sharkLocation = randomLocation();
        }while(oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id != 0);
        oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id = 1;
    }
}


void moveFish(int x, int y){
    int newX = x;
    int newY = y;

    switch(((std::rand() % 4) + 1)){
        case 1:
            newY = (y - 1 + ydim) % ydim;  // up
            break;
        case 2:
            newY = (y + 1) % ydim;  // down
            break;
        case 3:
            newX = (x - 1 + xdim) % xdim;  // left
            break;
        case 4:
            newX = (x + 1) % xdim;  // right
            break;
        default:
            break;
    }

    if(newOceanGrid[newX][newY].id == 0){
        if(newOceanGrid[x][y].breed >= FishBreed){
            newOceanGrid[newX][newY].id = 2;
            newOceanGrid[newX][newY].breed = 0; 
            newOceanGrid[x][y].breed = 0; 
            return;
        } 
        else{
            newOceanGrid[newX][newY].id = 2;
            newOceanGrid[x][y].id = 0;
            newOceanGrid[newX][newY].breed = newOceanGrid[x][y].breed + 1; 
            return;
        }
    }
}

void moveShark(int x, int y){
    int newX = x;
    int newY = y;
    std::vector<std::pair<int, int> > fishNeighbors;  
    
    if(y > 0 && oceanGrid[x][y - 1].id == 2){
        fishNeighbors.push_back(std::make_pair(x, y - 1)); //above
    }
    if(y < ydim - 1 && oceanGrid[x][y + 1].id == 2){
        fishNeighbors.push_back(std::make_pair(x, y + 1));  //below
    }
    if(x > 0 && oceanGrid[x - 1][y].id == 2){
        fishNeighbors.push_back(std::make_pair(x - 1, y));  //left
    }
    if(x < xdim - 1 && oceanGrid[x + 1][y].id == 2){
        fishNeighbors.push_back(std::make_pair(x + 1, y));  //right
    }

    if(!fishNeighbors.empty()){
        int randomFishIndex = std::rand() % fishNeighbors.size();
        int fishX = fishNeighbors[randomFishIndex].first;
        int fishY = fishNeighbors[randomFishIndex].second;

        newOceanGrid[fishX][fishY].id = 1;  
        newOceanGrid[x][y].id = 0;          
        newOceanGrid[fishX][fishY].breed = 0; 
        return;
    }else{
        switch(((std::rand() % 4) + 1)){
        case 1:
            newY = (y - 1 + ydim) % ydim;  // up
            break;
        case 2:
            newY = (y + 1) % ydim;  // down
            break;
        case 3:
            newX = (x - 1 + xdim) % xdim;  // left
            break;
        case 4:
            newX = (x + 1) % xdim;  // right
            break;
        default:
            break;
        }
        
        if(newOceanGrid[newX][newY].id == 0){
            if(newOceanGrid[x][y].breed >= SharkBreed){
                newOceanGrid[newX][newY].id = 1;
                newOceanGrid[newX][newY].breed = 0; 
                newOceanGrid[x][y].breed = 0; 
                return;
            }else{
                newOceanGrid[newX][newY].id = 1;
                newOceanGrid[x][y].id = 0;
                newOceanGrid[newX][newY].breed = newOceanGrid[x][y].breed + 1; 
                return;
            }
        }
    }
}


void moveAnimal(){
    for(int x = 0; x < xdim; x++){
        for(int y = 0; y < ydim; y++){
            if(oceanGrid[x][y].id == 1){
                moveShark(x, y);
            }else if(oceanGrid[x][y].id == 2){
                moveFish(x, y);
            }
        }
    }
    // copy changes from newOceanGrid to oceanGrid
    for(int x = 0; x < xdim; x++){
        for(int y = 0; y < ydim; y++){
            oceanGrid[x][y] = newOceanGrid[x][y];
        }
    }
}

void updateOcean(){
    for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
            recArray[i][k].setSize(sf::Vector2f(static_cast<float>(cellXSize), static_cast<float>(cellYSize)));
            recArray[i][k].setPosition(i * cellXSize, k * cellYSize);

            if(oceanGrid[i][k].id == 1){
                recArray[i][k].setFillColor(sf::Color::Green);  // shark
            }
            else if(oceanGrid[i][k].id == 2){
                recArray[i][k].setFillColor(sf::Color::Red);    // fish
            }
            else{
                recArray[i][k].setFillColor(sf::Color::Blue);   // empty
            }
        }
    }
}

int main() {

    std::srand(std::time(0));
    initialiseOcean();
    populateAnimals();
    updateOcean();

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Wa-Tor world");

    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    moveAnimal();
    updateOcean();

    window.clear(sf::Color::Black);
    for (int i = 0; i < xdim; ++i) {
        for (int k = 0; k < ydim; ++k) {
            window.draw(recArray[i][k]);
        }
    }
    window.display();
    sf::sleep(sf::seconds(1.0f / 1.0f));
}

return 0;
}
/*void moveShark(int x, int y) {
    int newX = x;
    int newY = y;
    std::vector<std::pair<int, int> > fishNeighbors;  
    
    if (y > 0 && oceanGrid[x][y - 1].id == 2) {
        fishNeighbors.push_back(std::make_pair(x, y - 1)); //above
    }
    if (y < ydim - 1 && oceanGrid[x][y + 1].id == 2) {
        fishNeighbors.push_back(std::make_pair(x, y + 1));  //below
    }
    if (x > 0 && oceanGrid[x - 1][y].id == 2) {
        fishNeighbors.push_back(std::make_pair(x - 1, y));  //left
    }
    if (x < xdim - 1 && oceanGrid[x + 1][y].id == 2) {
        fishNeighbors.push_back(std::make_pair(x + 1, y));  //right
    }

    if (!fishNeighbors.empty()) {
        int randomFishIndex = std::rand() % fishNeighbors.size();
        int fishX = fishNeighbors[randomFishIndex].first;
        int fishY = fishNeighbors[randomFishIndex].second;

        newOceanGrid[fishX][fishY].id = 1;  
        newOceanGrid[x][y].id = 0;          
        newOceanGrid[fishX][fishY].breed = 0; 
        return;
    } else {
        switch ((std::rand() % 4) + 1) {
            case 1:
                newOceanGrid[x][((y - 1) + ydim) % ydim].id = 1;  // up
                newOceanGrid[x][y].id = 0;
                break;
            case 2:
                newOceanGrid[x][(y + 1) % ydim].id = 1;  // down
                newOceanGrid[x][y].id = 0;
                break;
            case 3:
                newOceanGrid[((x - 1) + xdim) % xdim][y].id = 1;  // left
                newOceanGrid[x][y].id = 0;
                break;
            case 4:
                newOceanGrid[(x + 1) % xdim][y].id = 1;  // right
                newOceanGrid[x][y].id = 0;
                break;
            default:
                break;
        }
    }
}*/
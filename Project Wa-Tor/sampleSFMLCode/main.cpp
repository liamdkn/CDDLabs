//Author: Liam Durkan 8/11/23
//rhiks

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>

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

std::mutex myMutex; 

// Variables
int NumShark = 1;   
int NumFish = 2; 
int FishBreed = 110;   
int SharkBreed =60; 
int Starve = 60;//number of moves a shark can move before dying withouth eating  
int GridSize = 1000;
int numThreads;
int sharkCount = 0;
int fishCount = 0;


const int xdim = 100;
const int ydim= 100;

int WindowXSize=800;
int WindowYSize=600;
int cellXSize=WindowXSize/xdim;
int cellYSize=WindowYSize/ydim;

//Array representing whats in a cell
Cell oceanGrid[xdim][ydim];
Cell tempOceanGrid[xdim][ydim];
sf::RectangleShape recArray[xdim][ydim];

Location randomLocation(){  
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}

void initialiseOcean(){ //set up cells and initalize them to 0 
    for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
            recArray[i][k].setSize(sf::Vector2f(static_cast<float>(cellXSize), static_cast<float>(cellYSize)));
            recArray[i][k].setPosition(i * cellXSize, k * cellYSize);
        }
    }
    for(int i = 0; i < xdim; i++){
        for(int j = 0; j < ydim; j++){
            oceanGrid[i][j].id = 0;
            oceanGrid[i][j].starve = 0;
        }
    }
}

void populateAnimals(){
    for(int i = 0; i < NumFish; i++){
        Location fishLocation;
        do{
            fishLocation = randomLocation();    //Get random location on the grid
        } while(oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id != 0); //while the location is ocean 
        oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id = 2;   //place a 'fish' here 
        oceanGrid[fishLocation.xAxis][fishLocation.yAxis].breed = 0;
    }
    for(int i = 0; i < NumShark; i++){  //for the amount of initial sharks 
        Location sharkLocation; 
        do{
            sharkLocation = randomLocation();
        }while(oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id != 0);    //while the location is ocean 
        oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id = 1; //place a shark here
        oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].starve = 0;
    }
}

std::pair<int, int> randomDirection(int x, int y){
    int newX = x;
    int newY = y;

    switch(((std::rand() % 4) + 1)){    //randomly chose between 1 - 4
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
    }
    return std::make_pair(newX, newY);  //return new random move 
}

void starveShark(int sharkX, int sharkY){
    tempOceanGrid[sharkX][sharkY].id = 0;
    tempOceanGrid[sharkX][sharkY].breed = 0;
    tempOceanGrid[sharkX][sharkY].starve = 0;
}

void eatFish(std::vector<std::pair<int, int> > fishNeighbors, int sharkX, int sharkY){
    int randomFish = std::rand() % fishNeighbors.size();
    int fishX = fishNeighbors[randomFish].first;
    int fishY = fishNeighbors[randomFish].second;

    tempOceanGrid[fishX][fishY].id = 1; //Shark moves to fish location
    tempOceanGrid[fishX][fishY].starve = Starve; //Starve reset
    tempOceanGrid[fishX][fishY].breed = tempOceanGrid[sharkX][sharkY].breed;
    tempOceanGrid[sharkX][sharkY].id = 0; //Remove sharks last location  
    tempOceanGrid[sharkX][sharkY].starve = 0; //Clear starve           
}

std::vector<std::pair<int, int> > findFish(int x, int y) {
    std::vector<std::pair<int, int> > fishNeighbors;

    if (y > 0 && oceanGrid[x][y - 1].id == 2) {
        fishNeighbors.push_back(std::make_pair(x, y - 1));  // above
    }
    if (y < ydim - 1 && oceanGrid[x][y + 1].id == 2) {
        fishNeighbors.push_back(std::make_pair(x, y + 1));  // below
    }
    if (x > 0 && oceanGrid[x - 1][y].id == 2) {
        fishNeighbors.push_back(std::make_pair(x - 1, y));  // left
    }
    if (x < xdim - 1 && oceanGrid[x + 1][y].id == 2) {
        fishNeighbors.push_back(std::make_pair(x + 1, y));  // right
    }

    return fishNeighbors;
}

void moveFish(int x, int y){
    std::pair<int, int> newLocation = randomDirection(x, y);
    int newX = newLocation.first;
    int newY = newLocation.second;

    if (tempOceanGrid[newX][newY].id == 0) {
        if(tempOceanGrid[x][y].breed >= FishBreed) {
            tempOceanGrid[newX][newY].id = 2;
            tempOceanGrid[newX][newY].breed = 0; 
            tempOceanGrid[x][y].breed = 0; 
            return;
        } 
        else {
            tempOceanGrid[newX][newY].id = 2;
            tempOceanGrid[x][y].id = 0;
            tempOceanGrid[newX][newY].breed = tempOceanGrid[x][y].breed + 1; 
            return;
    }
    } 
    else if (tempOceanGrid[x][y].breed >= FishBreed) {
        tempOceanGrid[x][y].breed = 0;// Reproduce in the current cell if the breed condition is met
        return;
    }
    oceanGrid[x][y] = tempOceanGrid[x][y];
}

void moveShark(int x, int y) {
    int newX = x;
    int newY = y;
    tempOceanGrid[x][y].starve++;

    if (tempOceanGrid[x][y].starve >= Starve) {
        starveShark(x, y);
        return;
    }
    else{
    std::vector<std::pair<int, int> > fishNeighbors = findFish(x, y);

    if (!fishNeighbors.empty()) {
        eatFish(fishNeighbors, x, y);
    } else {
        // Move to a random location
        std::pair<int, int> newLocation = randomDirection(x, y);
        newX = newLocation.first;
        newY = newLocation.second;

        if (tempOceanGrid[newX][newY].id == 0) {
            if (tempOceanGrid[x][y].breed >= SharkBreed) {
                tempOceanGrid[newX][newY].id = 1;
                tempOceanGrid[newX][newY].breed = 0;
                tempOceanGrid[x][y].breed = 0;
                std::cout << "shark breeding:" << tempOceanGrid[x][y].starve << std::endl;

            } else {
                tempOceanGrid[newX][newY].id = 1;
                tempOceanGrid[x][y].id = 0;
                tempOceanGrid[newX][newY].breed = tempOceanGrid[x][y].breed + 1;
            }
        }
    }
    }
    oceanGrid[x][y] = tempOceanGrid[x][y];
}

void moveAnimal(){
    sharkCount = 0;
    fishCount = 0;
    for(int x = 0; x < xdim; x++){
        for(int y = 0; y < ydim; y++){
            if(oceanGrid[x][y].id == 1){
                moveShark(x, y);
                sharkCount++;
            }else if(oceanGrid[x][y].id == 2){
                moveFish(x, y);
                fishCount++;
            }
        }
    }
    // copy changes from tempOceanGrid to oceanGrid
    for(int x = 0; x < xdim; x++){
        for(int y = 0; y < ydim; y++){
            oceanGrid[x][y] = tempOceanGrid[x][y];
        }
    }
}

void updateOcean(){
    for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
            if(oceanGrid[i][k].id == 1){
                recArray[i][k].setFillColor(sf::Color::Red);  // shark
            }
            else if(oceanGrid[i][k].id == 2){
                recArray[i][k].setFillColor(sf::Color::Green);    // fish
            }
            else{
                recArray[i][k].setFillColor(sf::Color::Blue);   // empty
            }
        }
    }
}


int main() {
    int chronon = 0;
    int ChrononDuration = 1; 
    int maxChronons = 10000000; 


    sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Wa-Tor world");
    std::srand(std::time(0));
    initialiseOcean();
    populateAnimals();
    updateOcean();


    while (window.isOpen() && chronon < maxChronons) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    for (int step = 0; step < ChrononDuration; ++step) {
        moveAnimal();  
        updateOcean(); 
    }

    window.clear(sf::Color::Black);
    for (int i = 0; i < xdim; ++i) {
        for (int k = 0; k < ydim; ++k) {
            window.draw(recArray[i][k]);
        }
    }
    window.display();

    ++chronon; 
}

std::cout << "Generation: " << chronon << std::endl;
std::cout << "Shark: " << sharkCount << std::endl;
std::cout << "Fish: " << fishCount << std::endl;

    return 0;
}
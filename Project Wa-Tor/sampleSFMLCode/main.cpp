/**
 * @file main.cpp
 * @brief A program that simulates an ocean with fish & sharks 
 * @author Liam Durkan
 * @date 8/11/23
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// Structures

/**
 * @struct Location
 * @brief Represents the location of a cell in the 2D grid
 */
struct Location{
    int xAxis; /**< The x-axis of the cell */
    int yAxis; /**< The y-axis of the cell */
};

/**
 * @struct Cell
 * @brief Represents a cell in the ocean grid.
 */
struct Cell{
    int id;     /**< Fish/Shark/Water */
    int breed;  /**< How many moves left before breeding */
    int starve; /**< The starvation counter(shark only) */
};

// Variables
int NumShark = 2;   /**< Number of initial sharks */
int NumFish = 2;    /**< Number of initial fish  */
int FishBreed = 70; /**< How mnay steps a fish must go to be able to breed */
int SharkBreed = 60; /**< How mnay steps a shark must go to be able to breed */
int Starve = 100;    /**< The number of moves a shark can make before starving */
int numThreads;     /**< The number of threads for parallel processing */
int sharkCount = 0; /**< Number of sharks currently  */
int fishCount = 0;  /**< Number of fish currently */

const int xdim = 100; /**< x dimension of the ocean grid */
const int ydim = 100; /**< y dimension of the ocean grid */

int WindowXSize = 800;  /**< Width of the application window */
int WindowYSize = 600;  /**< Height of the application window */
int cellXSize = WindowXSize / xdim;
int cellYSize = WindowYSize / ydim;

// Array representing what's in a cell
Cell oceanGrid[xdim][ydim]; /**< Main ocean grid */
Cell tempOceanGrid[xdim][ydim]; /**< Temporary ocean grid */
sf::RectangleShape recArray[xdim][ydim];

/**
 * @brief Generates a random location within the ocean grid.
 * @return A Location struct representing a random location.
 */
Location randomLocation(){  
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}

/**
 * @brief Initializes the ocean grid
 *
 * This function initializes the ocean grid by setting cell and starvation counters to zero
 */
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

/**
 * @brief Populates the ocean grid with a specified number of fish and sharks
 *
 * This function populates fisb and sharks randomly into empty cells in the ocean 
 * Fish are represented by number 2, and sharks by number 1
 */
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

/**
 * @brief Generates a random direction for movement
 *
 * @param x The current x-coordinate.
 * @param y The current y-coordinate.
 * @return A pair of ints representing the next random direction
 */
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

/**
 * @brief Resets all sharks attributes to 0
 *
 * @param sharkX The x-coordinate of the shark
 * @param sharkY The y-coordinate of the shark
 */
void starveShark(int sharkX, int sharkY){
    tempOceanGrid[sharkX][sharkY].id = 0;
    tempOceanGrid[sharkX][sharkY].breed = 0;
    tempOceanGrid[sharkX][sharkY].starve = 0;
}

/**
 * @brief Shark eats a fish, moves to the location and updates starve status
 *
 * @param fishNeighbors A vector of std::pair<int, int> representing the positions of neighboring fish
 * @param sharkX The x-coordinate of the shark
 * @param sharkY The y-coordinate of the shark
 */
void eatFish(std::vector<std::pair<int, int> > fishNeighbors, int sharkX, int sharkY){
    int randomFish = std::rand() % fishNeighbors.size();
    int fishX = fishNeighbors[randomFish].first;
    int fishY = fishNeighbors[randomFish].second;

    tempOceanGrid[fishX][fishY].id = 1; //Shark moves to fish location
    tempOceanGrid[sharkX][sharkY].id = 0; //Remove sharks last location  
    tempOceanGrid[fishX][fishY].breed = tempOceanGrid[sharkX][sharkY].breed;
    tempOceanGrid[sharkX][sharkY].breed = 0;
    tempOceanGrid[sharkX][sharkY].starve = 0; //Clear starve   
    tempOceanGrid[fishX][fishY].starve = 0;   
}

/**
 * @brief Finds neighboring fish around a specified location
 *
 * @param x The x-coordinate of the position
 * @param y The y-coordinate of the position
 * @return A vector of coordinates where the shark has fish as neighbors 
 */
std::vector<std::pair<int, int> > findFish(int x, int y) {
    std::vector<std::pair<int, int> > fishNeighbors;

    if (y > 0 && oceanGrid[x][y - 1].id == 2) { /**< if y-1 == fish */
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

/**
 * @brief Moves a fish to a random neighbour and reproduces if condion is met 
 *
 * @param x The x-coordinate of the fish's position.
 * @param y The y-coordinate of the fish's position.
 */
void moveFish(int x, int y){
    std::pair<int, int> newLocation = randomDirection(x, y);
    int newX = newLocation.first;
    int newY = newLocation.second;

    if (tempOceanGrid[newX][newY].id == 0) {
        if(tempOceanGrid[x][y].breed >= FishBreed) {
            tempOceanGrid[newX][newY].id = 2;
            tempOceanGrid[newX][newY].breed = 0; 
            tempOceanGrid[x][y].breed = 0; 
            std::cout << "fish breeding"  << std::endl;

            return;
        } 
        else {
            tempOceanGrid[newX][newY].id = 2;
            tempOceanGrid[x][y].id = 0;
            tempOceanGrid[newX][newY].breed = tempOceanGrid[x][y].breed + 1; 
            return;
    }
    } 
    /*else if (tempOceanGrid[x][y].breed >= FishBreed) {
        tempOceanGrid[x][y].breed = 0;// Reproduce in the current cell if the breed condition is met
        return;
    }*/
    oceanGrid[x][y] = tempOceanGrid[x][y];
}

/**
 * @brief Moves a shark, updates its attributes, calls eatFish function and shark breeding
 *
 * @param x The x-coordinate of the shark's position.
 * @param y The y-coordinate of the shark's position.
 */
void moveShark(int x, int y) {
    int newX = x;
    int newY = y;

    if(tempOceanGrid[x][y].starve >= Starve){ /**< if starve is == to the threshold we remove the shark  */
        starveShark(x, y);
        return;
    }
    else{
    std::vector<std::pair<int, int> > fishNeighbors = findFish(x, y);//returns a vector of neighbors that are fish 

    if(!fishNeighbors.empty()){
        eatFish(fishNeighbors, x, y);
    }else{
        // Move to a random location
        std::pair<int, int> newLocation = randomDirection(x, y);
        newX = newLocation.first;
        newY = newLocation.second;

        if (tempOceanGrid[newX][newY].id == 0) {
            if (tempOceanGrid[x][y].breed >= SharkBreed) {
                tempOceanGrid[newX][newY].id = 1;
                tempOceanGrid[newX][newY].breed = 0;
                tempOceanGrid[x][y].breed = 0;
                std::cout << "shark breeding" << std::endl;

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
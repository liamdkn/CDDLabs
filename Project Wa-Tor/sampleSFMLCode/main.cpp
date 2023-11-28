//Author: Liam Durkan 8/11/23

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>


struct Location{
    int xAxis;
    int yAxis;
};

struct Cell{
    int id;
    int health;
};

struct Neighbours{
    int above;
    int below;
    int left;
    int right;
};

using namespace std;

// Variables
int NumShark = 3;
int NumFish = 3;
int FishBreed = 5;
int SharkBreed = 5;
int Starve = 5;
int GridSize = 10;
int Threads;

const int xdim = 10;
const int ydim= 10;

int WindowXSize=800;
int WindowYSize=600;
int cellXSize=WindowXSize/xdim;
int cellYSize=WindowYSize/ydim;

int randomNumber;
//int chron = 10000;

//Array representing whats in a cell
Cell oceanGrid[xdim][ydim];
sf::RectangleShape recArray[xdim][ydim];


Location randomLocation(){
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}

void initaliseOcean(){
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            oceanGrid[i][j].id = 0; //  Initalise every element in the array to zero
        }
    }
}

void populateShark() {
    for (int i = 0; i < NumShark; i++) {
        Location sharkLocation;
        do {
            sharkLocation = randomLocation();
        } while (oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id != 0);
        oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id = 1;
    }
}

void populateFish() {
    for (int i = 0; i < NumFish; i++) {
        Location fishLocation;
        do {
            fishLocation = randomLocation();
        } while (oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id != 0);
        oceanGrid[fishLocation.xAxis][fishLocation.yAxis].id = 2;
    }
}

Neighbours getNeighbours(int x, int y) {
    Neighbours neighbours;
    neighbours.above = ((y + 1) < ydim) ? oceanGrid[x][y + 1].id : oceanGrid[x][0].id;
    neighbours.below = ((y - 1) >= 0) ? oceanGrid[x][y - 1].id : oceanGrid[x][ydim - 1].id;
    neighbours.left = ((x - 1) >= 0) ? oceanGrid[x - 1][y].id : oceanGrid[xdim - 1][y].id;
    neighbours.right = ((x + 1) < xdim) ? oceanGrid[x + 1][y].id : oceanGrid[0][y].id;
    return neighbours;
}

void moveShark(int x, int y){
    Neighbours neighbours = getNeighbours(x, y);

    /*if (neighbours.above == 2) {
        oceanGrid[x][y - 1].id = oceanGrid[x][y].id;
        oceanGrid[x][y].id = 0;
    } else if (neighbours.below == 2) {
        oceanGrid[x][y + 1].id = oceanGrid[x][y].id;
        oceanGrid[x][y].id = 0;
    } else if (neighbours.left == 2) {
        oceanGrid[x - 1][y].id = oceanGrid[x][y].id;
        oceanGrid[x][y].id = 0;
    } else if (neighbours.right == 2) {
        oceanGrid[x + 1][y].id = oceanGrid[x][y].id;
        oceanGrid[x][y].id = 0;
    } else {*/
        randomNumber = (std::rand() % 4) + 1;
        switch (randomNumber) {
            case 1:
                if (neighbours.above == 0) {
                    oceanGrid[x][y - 1].id = oceanGrid[x][y].id;
                    oceanGrid[x][y].id = 0;
                }
                break;
            case 2:
                if (neighbours.below == 0) {
                    oceanGrid[x][y + 1].id = oceanGrid[x][y].id;
                    oceanGrid[x][y].id = 0;
                }
                break;
            case 3:
                if (neighbours.left == 0) {
                    oceanGrid[x - 1][y].id = oceanGrid[x][y].id;
                    oceanGrid[x][y].id = 0;
                }
                break;
            case 4:
                if (neighbours.right == 0) {
                    oceanGrid[x + 1][y].id = oceanGrid[x][y].id;
                    oceanGrid[x][y].id = 0;
                }
                break;
        }
    }
//}


void moveFish(int x, int y){
    Neighbours neighbours = getNeighbours(x,y);
    
    randomNumber = (std::rand() % 4) + 1;
    switch (randomNumber) {
        case 1:
            if(neighbours.above == 0){
                oceanGrid[x][y+1].id = oceanGrid[x][y].id;
                oceanGrid[x][y].id = 0;
            }
            break;
        case 2:
            if(neighbours.below == 0){
                oceanGrid[x][y-1].id = oceanGrid[x][y].id;
                oceanGrid[x][y].id = 0;
            }
            break;
        case 3:
            if(neighbours.left == 0){
            oceanGrid[x-1][y].id = oceanGrid[x][y].id;
            oceanGrid[x][y].id = 0;
            }
            break;
        case 4:
            if(neighbours.right == 0){
            oceanGrid[x+1][y].id = oceanGrid[x][y].id;
            oceanGrid[x][y].id = 0;
            }
            break;
    }
}

void updateOcean(){
    for(int i=0;i<xdim;++i){
        for(int k=0;k<ydim;++k){//give each one a size, position and color
            recArray[i][k].setSize(sf::Vector2f(80.f,60.f));
            recArray[i][k].setPosition(i*cellXSize,k*cellYSize);//position is top left corner!

            if(oceanGrid[i][k].id == 1){
                recArray[i][k].setFillColor(sf::Color::Green);
            }
            else if(oceanGrid[i][k].id == 2){
                recArray[i][k].setFillColor(sf::Color::Red);
            }
            else{
                recArray[i][k].setFillColor(sf::Color::Blue);
            }  
        }
    }
}

int main()
{
    sf::Clock clock;
    sf::Time elapsed;

    initaliseOcean();
    populateFish();
    populateShark();

    //each shape will represent either a fish, shark or empty space
    //e.g. blue for empty, red for shark and green for fish
    
    sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");

    updateOcean();

    while (window.isOpen())
    {
        elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //loop to move fish/sharks
        for (int i = 0; i < xdim; i++) {
                for (int j = 0; j < ydim; j++) {
                    if(oceanGrid[i][j].id == 1){
                        moveShark(i,j);
                    }
                    else if(oceanGrid[i][j].id == 2){
                        moveFish(i,j);
                    }
                }
            }

        updateOcean();
    
    //loop these three lines to draw frames
        window.clear(sf::Color::Black);
        for(int i=0;i<xdim;++i){
            for(int k=0;k<ydim;++k){
            window.draw(recArray[i][k]);
            }
        }
        window.display();
        sf::sleep(sf::seconds(1.0f / 1.0f));
        }
    return 0;
}
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
int NumShark = 1;
int NumFish = 2;
int FishBreed = 5;
int SharkBreed = 5;
int Starve = 5;
int GridSize = 100;
int Threads;

const int xdim = 10;
const int ydim= 10;

int randomNumber;
int chron = 10000;

//Array representing whats in a cell
Cell cellState[xdim][ydim];


Location randomLocation(){
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}

void initaliseOcean(){
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            cellState[i][j].id = 0; //  Initalise every element in the array to zero
        }
    }
}

void populateShark() {
    for (int i = 0; i < NumShark; i++) {
        Location sharkLocation;
        do {
            sharkLocation = randomLocation();
        } while (cellState[sharkLocation.xAxis][sharkLocation.yAxis].id != 0);
        cellState[sharkLocation.xAxis][sharkLocation.yAxis].id = 1;
    }
}

void populateFish() {
    for (int i = 0; i < NumFish; i++) {
        Location fishLocation;
        do {
            fishLocation = randomLocation();
        } while (cellState[fishLocation.xAxis][fishLocation.yAxis].id != 0);
        cellState[fishLocation.xAxis][fishLocation.yAxis].id = 2;
    }
}

getNeighbours(){
    
}

void moveFish(int x, int y){
    Neighbours neighbours;
    neighbours.above = (y + 1 < ydim) ? cellState[x][y + 1].id : cellState[x][0].id;
    neighbours.below = (y - 1 >= 0) ? cellState[x][y - 1].id : cellState[x][ydim - 1].id;
    neighbours.left = (x - 1 >= 0) ? cellState[x - 1][y].id : cellState[xdim - 1][y].id;
    neighbours.right = (x + 1 < xdim) ? cellState[x + 1][y].id : cellState[0][y].id;
    
    randomNumber = (std::rand() % 4) + 1;
     switch (randomNumber) {
        case 1:
            cellState[x][y+1].id = cellState[x][y].id;
            cellState[x][y].id = 0;
            break;
        case 2:
            cellState[x][y-1].id = cellState[x][y].id;
            cellState[x][y].id = 0;
            break;
        case 3:
            cellState[x-1][y].id = cellState[x][y].id;
            cellState[x][y].id = 0;
            break;
        case 4:
            cellState[x+1][y].id = cellState[x][y].id;
            cellState[x][y].id = 0;
            break;
        default:
            std::cout << "Fish Switch statement default" << std::endl;
            break;
    }

}

void updateOcean(sf::RectangleShape (&recArray)[xdim][ydim], int cellXSize, int cellYSize){
    for(int i=0;i<xdim;++i){
        for(int k=0;k<ydim;++k){//give each one a size, position and color
            recArray[i][k].setSize(sf::Vector2f(80.f,60.f));
            recArray[i][k].setPosition(i*cellXSize,k*cellYSize);//position is top left corner!

            if(cellState[i][k].id == 1){
                recArray[i][k].setFillColor(sf::Color::Green);
            }
            else if(cellState[i][k].id == 2){
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
    int WindowXSize=800;
    int WindowYSize=600;
    int cellXSize=WindowXSize/xdim;
    int cellYSize=WindowYSize/ydim;

    sf::Clock clock;
    sf::Time elapsed;

    initaliseOcean();
    populateFish();
    populateShark();

    //each shape will represent either a fish, shark or empty space
    //e.g. blue for empty, red for shark and green for fish
    sf::RectangleShape recArray[xdim][ydim];
    sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");

    updateOcean(recArray,cellXSize,cellYSize);

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
                    if(cellState[i][j].id == 1){
                        moveFish(i,j);
                    }
                    else if(cellState[i][j].id == 2){
                        //moveShark(i,j)
                    }
                }
            }

    updateOcean(recArray,cellXSize,cellYSize);
    
    //loop these three lines to draw frames
        window.clear(sf::Color::Black);
    for(int i=0;i<xdim;++i){
        for(int k=0;k<ydim;++k){
        window.draw(recArray[i][k]);
        }
    }
        window.display();
        sf::sleep(sf::seconds(1.0f / 10.0f)); // Adjust the frame rate by changing the divisor

    }

    return 0;
}
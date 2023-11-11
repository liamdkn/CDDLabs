//Author: Liam Durkan 8/11/23

#include <iostream>
#include <SFML/Graphics.hpp>

struct Location{
    int xAxis;
    int yAxis;
};

using namespace std;

int NumShark = 1;
int NumFish = 5;
int FishBreed = 5;
int SharkBreed = 5;
int Starve = 5;
int GridSize = 100;
int Threads;

const int xdim = 10;
const int ydim= 10;

//Array representing whats in a cell
int cellState[xdim][ydim];

Location randomLocation(){
    Location randomLoc;
    randomLoc.xAxis = rand() % xdim;
    randomLoc.yAxis = rand() % ydim;
    return randomLoc;
}


void populateFish() {
    for (int i = 0; i < NumFish; i++) {
        Location fishLocation;

        do {
            fishLocation = randomLocation();
        } while (cellState[fishLocation.xAxis][fishLocation.yAxis] != 0);

        cellState[fishLocation.xAxis][fishLocation.yAxis] = 2;
    }
}


int main()
{
    
    int WindowXSize=800;
    int WindowYSize=600;
    int cellXSize=WindowXSize/xdim;
    int cellYSize=WindowYSize/ydim;

    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            cellState[i][j] = 0; // Set each element to 0
        }
    }

    populateFish();

    

    //each shape will represent either a fish, shark or empty space
    //e.g. blue for empty, red for shark and green for fish
    sf::RectangleShape recArray[xdim][ydim];
    for(int i=0;i<xdim;++i){

        for(int k=0;k<ydim;++k){//give each one a size, position and color
            recArray[i][k].setSize(sf::Vector2f(80.f,60.f));
            recArray[i][k].setPosition(i*cellXSize,k*cellYSize);//position is top left corner!

            if(cellState[i][k] == 1){
                recArray[i][k].setFillColor(sf::Color::Green);
            }
            else if(cellState[i][k] == 2){
                recArray[i][k].setFillColor(sf::Color::Red);
            }
            else{
                recArray[i][k].setFillColor(sf::Color::Blue);
            }  
        }
    }
    sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    //loop these three lines to draw frames
        window.clear(sf::Color::Black);
    for(int i=0;i<xdim;++i){
        for(int k=0;k<ydim;++k){
        window.draw(recArray[i][k]);
        }
    }
        window.display();
    }

    return 0;
}
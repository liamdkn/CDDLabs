//Author: Liam Durkan 8/11/23

#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;

int NumShark = 5;
int NumFish = 5;
int FishBreed = 5;
int SharkBreed = 5;
int Starve = 5;
int GridSize = 100;
int Threads;

void gui(){  
    int xdim = 100;
    int ydim= 100;
    int WindowXSize=800;
    int WindowYSize=600;
    int cellXSize=WindowXSize/xdim;
    int cellYSize=WindowYSize/ydim;
    //each shape will represent either a fish, shark or empty space
    //e.g. blue for empty, red for shark and green for fish
    sf::RectangleShape recArray[xdim][ydim];
    for(int i=0;i<xdim;++i){
    for(int k=0;k<ydim;++k){//give each one a size, position and color
        recArray[i][k].setSize(sf::Vector2f(80.f,60.f));
        recArray[i][k].setPosition(i*cellXSize,k*cellYSize);//position is top left corner!
        int id=i*1-+k;
        if (id%2==0) recArray[i][k].setFillColor(sf::Color::Green);
        else recArray[i][k].setFillColor(sf::Color::Blue);
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

    //return 0;
}

int main()
{
  gui();
}
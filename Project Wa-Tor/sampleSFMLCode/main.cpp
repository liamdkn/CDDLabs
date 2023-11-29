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
    int health;
};

struct Neighbours{
    int above;
    int below;
    int left;
    int right;
};

// Variables
int NumShark = 4;
int NumFish = 4;
int FishBreed = 0;
int SharkBreed = 0;
int Starve = 0;
int GridSize = 10;
int Threads;

const int xdim = 10;
const int ydim= 10;

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
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            oceanGrid[i][j].id = 0;
        }
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

void populateShark() {
    for (int i = 0; i < NumShark; i++) {
        Location sharkLocation;
        do {
            sharkLocation = randomLocation();
        } while (oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id != 0);
        oceanGrid[sharkLocation.xAxis][sharkLocation.yAxis].id = 1;
    }
}

void moveAnimal(int x, int y, int id) {
    randomNumber = (std::rand() % 4) + 1;
    switch (randomNumber) {
        case 1:
            newOceanGrid[x][((y - 1) + ydim) % ydim].id = id;  // up
            newOceanGrid[x][y].id = 0;
            break;
        case 2:
            newOceanGrid[x][(y + 1) % ydim].id = id;  // down
            newOceanGrid[x][y].id = 0;
            break;
        case 3:
            newOceanGrid[((x - 1) + xdim) % xdim][y].id = id;  // left
            newOceanGrid[x][y].id = 0;
            break;
        case 4:
            newOceanGrid[(x + 1) % xdim][y].id = id;  // right
            newOceanGrid[x][y].id = 0;
            break;
    }
}

void moveAnimal() {
    for (int x = 0; x < xdim; x++) {
        for (int y = 0; y < ydim; y++) {
            if (oceanGrid[x][y].id == 1) {
                moveAnimal(x, y, 1);
            } else if (oceanGrid[x][y].id == 2) {
                moveAnimal(x, y, 2);
            }
        }
    }
    // Copy changes from newOceanGrid to oceanGrid
    for (int x = 0; x < xdim; x++) {
        for (int y = 0; y < ydim; y++) {
            oceanGrid[x][y] = newOceanGrid[x][y];
        }
    }
}

void updateOcean(){
    for (int i = 0; i < xdim; ++i) {
        for (int k = 0; k < ydim; ++k) {
            recArray[i][k].setSize(sf::Vector2f(80.f, 60.f));
            recArray[i][k].setPosition(i * 80.f, k * 60.f);

            if (oceanGrid[i][k].id == 1) {
                recArray[i][k].setFillColor(sf::Color::Green);
            }
            else if(oceanGrid[i][k].id == 2) {
                recArray[i][k].setFillColor(sf::Color::Red);
            }
            else {
                recArray[i][k].setFillColor(sf::Color::Blue);
            }
        }
    }
}
int main() {

    std::srand(std::time(0));
    initialiseOcean();
    populateShark();
    populateFish();
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
        sf::sleep(sf::seconds(1.0f / 10.0f));
    }

    return 0;
}


/*
void moveAnimal(){
//loop to move fish/sharks
        for (int i = 0; i < xdim; i++) {
                for (int j = 0; j < ydim; j++) {
                    if(oceanGrid[i][j].id == 1){
                        //moveShark(i,j);
                    }
                    else if(oceanGrid[i][j].id == 2){
                        //moveFish(i,j);
                    }
                }
            }
}
void moveAnimal(){
    // Create a temporary grid to store the new state
    
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            newOceanGrid[i][j] = oceanGrid[i][j];
        }
    }

    // Move sharks and fish in the temporary grid
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            if (oceanGrid[i][j].id == 1) {
                moveShark(i, j);
            } else if (oceanGrid[i][j].id == 2) {
                moveFish(i, j);
            }
        }
    }

    // Update the original oceanGrid based on the new state
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            oceanGrid[i][j] = newOceanGrid[i][j];
        }
    }
}*/

/*
void moveShark(int x, int y){
    Neighbours neighbours = getNeighbours(x, y);

    if (neighbours.above == 2) {
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
    } else {
        randomNumber = (std::rand() % 4) + 1;
    //std::cout << "The value of the number is: " << randomNumber << std::endl;
        switch (randomNumber) {
            case 1:
                if (neighbours.above == 0) {
                    newOceanGrid[x][y - 1].id = newOceanGrid[x][y].id;
                    newOceanGrid[x][y].id = 0;
                }
                break;
            case 2:
                if (neighbours.below == 0) {
                    newOceanGrid[x][y + 1].id = newOceanGrid[x][y].id;
                    newOceanGrid[x][y].id = 0;
                }
                break;
            case 3:
                if (neighbours.left == 0) {
                    newOceanGrid[x - 1][y].id = newOceanGrid[x][y].id;
                    newOceanGrid[x][y].id = 0;
                }
                break;
            case 4:
                if (neighbours.right == 0) {
                    newOceanGrid[x + 1][y].id = newOceanGrid[x][y].id;
                    newOceanGrid[x][y].id = 0;
                }
                break;
        }
    }

//}


void moveFish(int x, int y){
    Neighbours neighbours = getNeighbours(x,y);
    
    randomNumber = (std::rand() % 4) + 1;
    //std::cout << "The value of the number is: " << randomNumber << std::endl;
    switch (randomNumber) {
        case 1:
            if(neighbours.above == 0){
                newOceanGrid[x][y+1].id = newOceanGrid[x][y].id;
                newOceanGrid[x][y].id = 0;
            }
            break;
        case 2:
            if(neighbours.below == 0){
                newOceanGrid[x][y-1].id = newOceanGrid[x][y].id;
                newOceanGrid[x][y].id = 0;
            }
            break;
        case 3:
            if(neighbours.left == 0){
            newOceanGrid[x-1][y].id = newOceanGrid[x][y].id;
            newOceanGrid[x][y].id = 0;
            }
            break;
        case 4:
            if(neighbours.right == 0){
            newOceanGrid[x+1][y].id = newOceanGrid[x][y].id;
            newOceanGrid[x][y].id = 0;
            }
            break;
    }

}
*/
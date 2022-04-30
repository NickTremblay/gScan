///////////////////////
// IMPORTS /
//////////////////////
#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Plane/Plane.h"
#include "Point/Point.h"
#include "Line/Line.hpp"

// Prompt user for input corresponding to context menu choice
void addPointsFromContextChoice(int contextChoice, Plane* plane, bool* done, bool* listenForClicks){
    // Append points to plane based on contextChoice
    switch(contextChoice){
        case 1:{
            // Click on plane
            
            // Enable SFML event handler for clicks
            *listenForClicks = true;
            
            // Ask when done and validate input
            char doneClicking;
            while(true){
                std::cout << "Click on plane to add each point and enter 'd' here when done:";
                if (std::cin >> doneClicking && doneClicking == 'd'){
                    *listenForClicks = false;
                    *done = true;
                    break;
                }else{
                    std::cout << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            // Sort finalized points in prep for gScan
            plane->sortPoints();
            // Invoke gScan driver
            plane->gScan();
            break;
        }
            
        case 2:{
            // Manually enter points
            
            while(true){
                int x;
                
                // Validate x input
                while(true) {
                    std::cout << "Enter x:";
                    if (std::cin >> x && x <= plane->getWidth()){
                        break;
                    }else{
                        std::cout << "Invalid x coord. Try again." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                
                int y;
                // Validate y input
                while(true) {
                    std::cout << "Enter y:";
                    if (std::cin >> y && y <= plane->getHeight()){
                        break;
                    }else{
                        std::cout << "Invalid y coord. Try again." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                
                // Declare new point on p and add to plane
                plane->addPoint(new Point(x, y, sf::Color::Black));
                
                // Prompt user for another coord and validate input
                char enterAnotherCoord;
                while(true){
                    std::cout << "Enter another coord?(y/n):";
                    if (std::cin >> enterAnotherCoord && (enterAnotherCoord == 'y' || enterAnotherCoord == 'n')){
                        break;
                    }else{
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                
                if(enterAnotherCoord == 'n') break;
            }
            *done = true;
            
            // Sort finalized points in prep for gScan
            plane->sortPoints();
            // Invoke gScan driver
            plane->gScan();
            break;
        }
            
        case 3: {
            // Random point generation
            
            // Seed randomness with current time
            std::srand(std::time(nullptr));
            
            int nPoints;
            // Validate nPoints input
            while(true) {
                std::cout << "Enter amount of points:";
                // If nPoints is unsigned int and less than or equal to max points
                if(std::cin >> nPoints && nPoints <= (plane->getWidth() + plane->getHeight()) / 20){
                    break;
                }else{
                    std::cout << "Invalid amount of points. Try again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            // Generate points
            for(int i = 0; i < nPoints; i++){
                int x = 20 + (rand() % (plane->getWidth() - 40));
                int y = 20 + (rand() % (plane->getHeight() - 40));
                plane->addPoint(new Point(x, y, sf::Color::Black));
            }
            
            // Ask when done and validate input
            char go;
            while(true){
                std::cout << "Your points are rendered. Enter 'g' to go:";
                if (std::cin >> go && go == 'g'){
                    *done = true;
                    break;
                }else{
                    std::cout << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            // Sort finalized points in prep for gScan
            plane->sortPoints();{
                // Invoke gScan driver if convex hull is possible
                plane->gScan();
            }
            break;
        }
    }
}

int main(){
    //////////////////////////////////
    // CONTEXT MENU /
    /////////////////////////////////
    
    // Print banner
    std::cout << "|\\   ____\\|\\   ____\\|\\   ____\\|\\   __  \\|\\   ___  \\" << std::endl;
    std::cout << "\\ \\  \\___|\\ \\  \\___|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\ \\  \\" << std::endl;
    std::cout << " \\ \\  \\  __\\ \\_____  \\ \\  \\    \\ \\   __  \\ \\  \\\\ \\  \\" << std::endl;
    std::cout << "  \\ \\  \\|\\  \\|____|\\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\ \\  \\" << std::endl;
    std::cout << "   \\ \\_______\\____\\_\\  \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ \\  \\" << std::endl;
    std::cout << "    \\|_______|\\_________\\|_______|\\|__|\\|__|\\|__| \\|__|" << std::endl;
    std::cout << "             \\|_________|" << std::endl;
    std::cout << std::endl;
    
    //Print options
    std::cout << "1) Click to add each point on the plane" << std::endl;
    std::cout << "2) Manually enter x,y coordinates for each point on the plane" << std::endl;
    std::cout << "3) Randomly generate x amount of points" << std::endl;
    std::cout << "Choose from methods 1-3 for entering coordinates" << std::endl;
    
    // Init flag for valid answer
    int contextChoice;
    
    // Loop until valid answer is made
    while(true) {
        std::cout << "Enter choice(1-3):";
        if (std::cin >> contextChoice && contextChoice <= 3) {
            break;
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    // Init plane object with default windowSize
    Plane plane(500, 500);
    
    // Init flags for feedback from contextMenuThread
    bool contextDone = false;
    bool listenForClicks = (contextChoice == 1);
    
    // Launch remainder of contextMenu and gScan on new thread
    std::thread contextThread(addPointsFromContextChoice, contextChoice, &plane, &contextDone, &listenForClicks);
    
    // Init SFML window
    sf::RenderWindow window(sf::VideoMode(plane.getWidth(), plane.getHeight()), "gScan");
    
    
    //////////////////////////////////////
    // MAIN SFML LOOP /
    /////////////////////////////////////

    while (window.isOpen()){
        // If contextMenu is open then sync window size with plane size
        if(!contextDone){
            window.setSize(sf::Vector2u(plane.getWidth(), plane.getHeight()));
        }
        
        // Event listener
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                // Handle window close
                case sf::Event::Closed:{
                    window.close();
                    // Wait for contextThread to finish, close contextThread, and return out of main()
                    contextThread.join();
                    return 0;
                    break;
                }
                    
                // Handle window resize
                case sf::Event::Resized: {
                    // Expand visible area to enter window
                    sf::FloatRect visibleArea(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height));
                    window.setView(sf::View(visibleArea));
                    // Update plane size
                    plane.setWidth(event.size.width);
                    plane.setHeight(event.size.height);
                    break;
                }
                
                // Handle mouse click
                case sf::Event::MouseButtonPressed:{
                    // If left click and listening for clicks
                    if(event.mouseButton.button == sf::Mouse::Left && listenForClicks){
                        plane.addPoint(new Point(event.mouseButton.x, event.mouseButton.y, sf::Color::Black));
                    }
                    
                    break;
                }
                
                // Ignore unhandled events
                default:
                    break;
            }
        }
        
        // Set background color and clear previous frame
        window.clear(sf::Color(255, 255, 255, 255));
        
        // Draw each line in plane
        for(int i = 0; i < plane.getLineCount(); i++){
            Line* l = plane.getLine(i);
            window.draw(l->vertices, 2, sf::Lines);
        }
        
        // Draw each point in plane
        for(int j = 0; j < plane.getPointCount(); j++){
            Point* p = plane.getPoint(j);
            sf::CircleShape circle(3.f);
            circle.setPosition(sf::Vector2f(p->x, p->y));
            circle.setFillColor(p->color);
            window.draw(circle);
        }
        
        // Display new frame
        window.display();
    }
    
    return 0;
}

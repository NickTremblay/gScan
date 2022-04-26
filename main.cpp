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
#include "Plane/Plane.h"
#include "Point/Point.h"
#include "Line/Line.hpp"

// Prompt user for input corresponding to context menu choice
void addPointsFromContextChoice(unsigned int contextChoice, Plane* plane, bool* done, bool* listenForClicks){
    // Append points to plane based on contextChoice
    switch(contextChoice){
        case 1:{
            // Click on plane-
            // Set window event listener for SFML window object on heap in main loop
            // Instantiate point object using data from event object passed into handler
            // Call w.addPoint(p)
            // Listen for escape key to terminate event listener and call gScan driver
            break;
        }
            
        case 2:{
            // Manually enter points
            
            while(!(*done)){
                unsigned int x;
                
                // Validate x input
                while(true) {
                    std::cout << "Enter x:";
                    if (std::cin >> x && x <= plane->width){
                        break;
                    }else{
                        std::cout << "Invalid x coord. Try again." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                
                unsigned int y;
                // Validate y input
                while(true) {
                    std::cout << "Enter y:";
                    if (std::cin >> y && y <= plane->height){
                        break;
                    }else{
                        std::cout << "Invalid y coord. Try again." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                
                // Declare new point on p and add to plane
                plane->addPoint(new Point(x, y, "#000000"));
                
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
            break;
        }
            
        case 3: {
            // Enter from file-
            
            break;
        }
    }
    
    // Update flag in mainframe
    *done = true;
    
    // Sort finalized points in prep for gScan
    plane->sortPoints();
    // Invoke gScan driver
    plane->gScan();
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
    std::cout << "3) Enter path to file listing coordinates" << std::endl;
    std::cout << "Choose from methods 1-3 for entering coordinates: ";
    
    // Init flag for valid answer
    unsigned int contextChoice;
    
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
    sf::RenderWindow window(sf::VideoMode(plane.width, plane.height), "gScan");
    
    
    //////////////////////////////////////
    // MAIN SFML LOOP /
    /////////////////////////////////////

    while (window.isOpen()){
        // If contextMenu is open then sync window size with plane size
        if(!contextDone){
            window.setSize(sf::Vector2u(plane.width, plane.height));
        }
        
        // Event listener
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                // Handle window close
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
                    
                // Handle window resize
                case sf::Event::Resized: {
                    // Expand visible area to enter window
                    sf::FloatRect visibleArea(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height));
                    window.setView(sf::View(visibleArea));
                    // Update plane size
                    plane.width = event.size.width;
                    plane.height = event.size.height;
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
        for(int i = 0; i < plane.lines.size(); i++){
            Line* l = plane.lines[i];
            window.draw(l->vertices, 2, sf::Lines);
        }
        
        // Draw each point in plane
        for(int i  = 0; i < plane.points.size(); i++){
            Point* p = plane.points[i];
            sf::CircleShape circle(3.f);
            circle.setPosition(sf::Vector2f(p->x, p->y));
            circle.setFillColor(sf::Color(0, 0, 0));
            window.draw(circle);
        }
        
        // Display new frame
        window.display();
    }
    
    return 0;
}

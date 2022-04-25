///////////////////////
// IMPORTS /
//////////////////////
#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Plane/Plane.h"
#include "Point/Point.h"


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
    bool validContextChoice = false;
    unsigned int contextChoice;
    
    // Loop until valid answer is made
    while(!validContextChoice){
        try{
            std::cin >> contextChoice;
            std::cout << std::endl;
        }catch(const std::exception&){
            std::cout << "Invalid choice. Choose number from 1-3:";
            continue;
        }
        
        if(contextChoice > 0 && contextChoice <= 3){
            validContextChoice = true;
            break;
        }else{
            std::cout << "Invalid choice. Choose number from 1-3:";
        }
    }
    
    Plane plane(500, 500);
    
    // Append points to plane based on contextChoice
    switch(contextChoice){
        case 1:{
            // Click on plane-
            // Set window event listener for SFML window object on heap in main loop
            // Instantiate point object using data from event object passed into handler
            // Call w.addPoint(p)
            // Listen for escape key to terminate event listener and call gScan driver
            break;}
            
        case 2:{
            // Manually enter
            
            // Init flag for valid coords
            bool validCoords = false;
            while(!validCoords){
                unsigned int x;
                std::cout << "Enter X:";
                
                // Validate x
                try{
                    std::cin >> x;
                    
                }catch(const std::exception&){
                    std::cout << "Invalid x coord try again" << std::endl;
                    continue;
                }
                
                if(x > plane.width){
                    std::cout << "Invalid x coord try again" << std::endl;
                    continue;
                }
                
                unsigned int y;
                std::cout << "Enter Y:";
                // Validate y
                try{
                    std::cin >> y;
                    
                }catch(const std::exception&){
                    std::cout << "Invalid y coord try again" << std::endl;
                    continue;
                }
                
                if(y > plane.height){
                    std::cout << "Invalid y coord try again" << std::endl;
                    continue;
                }
                
                // Declare new point on p and add to plane
                Point* p = new Point(x, y, "#000000");
                plane.addPoint(p);
                
                // Prompt user for another coord
                char enterAnotherCoord;
                while(true){
                    // Overridden if invalid x or y
                    std::cout << "Enter another coord(y/n)? ";
                    
                    try{
                        std::cin >> enterAnotherCoord;
                    }catch(const std::exception&){
                        std::cout << std::endl;
                        continue;
                    }
                    
                    if(enterAnotherCoord != 'y' && enterAnotherCoord != 'n'){
                        std::cout << std::endl;
                        continue;
                    }else break;
                }
                
                if(enterAnotherCoord == 'n') break;
            }
            break;}
            
        case 3: {
            // Enter from file-
            
            break;
        }
    }
    
    // Init SFML window
    sf::RenderWindow window(sf::VideoMode(plane.width, plane.height), "gScan");
    
    
    //////////////////////////////////////
    // MAIN SFML LOOP /
    /////////////////////////////////////

    while (window.isOpen())
    {
        // Event listener
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Handle window close
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Set background color and clear previous frame
        window.clear(sf::Color(255, 255, 255, 255));
        
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

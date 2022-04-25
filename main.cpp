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
    
    // TODO: INIT SFML WINDOW OBJECT
    // TODO: INIT COORD PLANE OBJECT
    
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
                }
                
            }
            
            // call addPoint after instantiating point object
            // break loop when escape phrase is entered
            
            
            break;}
            
        case 3: {
            // Enter from file-
            
            break;
        }
    }
    
    // TODO: MAIN SFML LOOP
    
    return 0;
}

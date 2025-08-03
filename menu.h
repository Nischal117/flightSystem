
#ifndef MENU_H
#define MENU_H

#define ACODE 117


#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdbool.h>
#include <map>
#include <sstream>
#include <fstream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::map;
using std::stringstream;


    
class Menu {
private:
    WINDOW* win; // ncurses window, managed with RAII
    std::vector<std::string> options; // Menu options (e.g., airport names)
    int width, height; // Window dimensions
    int highlight; // Currently highlighted option

    // Helper to center and display the menu
    void displayMenu();

public:
    // Constructor: Initializes window and options
    Menu(const std::vector<std::string>& opts,int h = getmaxy(stdscr) ,int w = getmaxx(stdscr));

 // Menu(const std::vector<std::string>& opts, int h = 12, int w = 50);
    
    // Destructor: Cleans up ncurses window
    ~Menu();

    // Displays menu and returns selected option index (or -1 for cancel)
    int strictDisplay();
    int display();

    // Displays menu with a text input field at given index, returns input string no need..
    std::string inputField(int fieldIndex, const std::string& initial = "");
};


    
    


#endif

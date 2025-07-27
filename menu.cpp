#include "menu.h"
#include <algorithm>

Menu::Menu(const std::vector<std::string>& opts, int h, int w)
    : options(opts), height(h), width(w), highlight(0) {
    // Initialize ncurses window, centered on screen
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    win = newwin(height, width, (maxY - height) / 2, (maxX - width) / 2);
    keypad(win, TRUE); // Enable arrow keys
}

Menu::~Menu() {
    if (win) {
        delwin(win); // RAII: Clean up window
    }
}

void Menu::displayMenu() {
    wclear(win);
    int maxY, maxX;
    getmaxyx(win, maxY, maxX);

    // Center options vertically
    int startY = (maxY - options.size()) / 2;

    for (size_t i = 0; i < options.size(); ++i) {
        int startX = (maxX - options[i].length()) / 2; // Center horizontally
        wmove(win, startY + i, startX);
        if (static_cast<int>(i) == highlight) {
            wattron(win, A_REVERSE); // Highlight selected option
        }
        wprintw(win, "%s", options[i].c_str());
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

int Menu::display() {
    while (true) {
        displayMenu();
        int input = wgetch(win);

        switch (input) {
            case KEY_UP:
                highlight = (highlight - 1 + options.size()) % options.size();
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % options.size();
                break;
            case 10: // Enter key
                return highlight; // Return selected option index
            case 27: // Escape key
                return -1; // Cancel
        }
    }
}



std::string Menu::inputField(int fieldIndex, const std::string& initial) {
    std::string input = initial;
  //  curs_set(1); // Show cursor for input
    while (true) {
        wclear(win);
        int maxY, maxX;
        getmaxyx(win, maxY, maxX);
        int startY = (maxY - options.size()) / 2;

        for (size_t i = 0; i < options.size(); ++i) {
            int startX = (maxX - options[i].length()) / 2;
            wmove(win, startY + i, startX);
            if (static_cast<int>(i) == fieldIndex) {
                wattron(win, A_REVERSE);
                wprintw(win, "%s%s", options[i].c_str(), input.c_str());
                wprintw(win, "%s", static_cast<int>(i) == fieldIndex ? "|" : "");
                wattroff(win, A_REVERSE);
            } else {
                wprintw(win, "%s", options[i].c_str());
            }
        }
        wrefresh(win);

        int inC = wgetch(win);
        if (inC == 10) { // Enter: Submit input
          //  curs_set(0);
            return input;
        } else if (inC == 27) { // Escape: Cancel
        //    curs_set(0);
            return "";
        } else if ((inC == KEY_BACKSPACE || inC == 8 || inC == 127) && !input.empty()) {
            input.pop_back(); // Delete last character
        } else if (inC >= 32 && inC <= 126) { // Printable characters
            if(fieldIndex == 3 && (inC == 'M' || inC == 'F')) {
            input +=

            }
            input += static_cast<char>(inC);
        }
    }
}

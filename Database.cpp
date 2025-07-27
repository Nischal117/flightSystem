#include "Database.h"


Database::Database() noexcept {
 airportsFile = "airports.csv";
 flightFile = "flights.csv";
 bookingsFile = "bookings.csv";
    
    loadFlights();
}



//save booking function

    void Database::saveBooking(const Booking& booking)
    {
std::ofstream file(bookingsFile, std::ios::app);
    if (file.is_open()) {
        file << booking.bookingId << "," << booking.name << "," << booking.sex << ","
             << booking.flightId << "," << booking.airline << "," << booking.origin << ","
             << booking.dest << "," << booking.departureTime << "," << booking.baggage << ","
             << booking.mealPreference << "," << booking.cost << "\n";
        file.close();
    }

    }




// generate booking Id
    string Database::generateBookingID() {
    
    string bookId = "SSN" + std::to_string(bookingCounter);
    
    bookingCounter++;
    return bookId;

    }






bool Database::userBook(Database::Booking* booking) {
    // Initialize vector to store inputs for each field
    std::vector<std::string> getInput(4, "");
    std::vector<std::string> labels = {
        "Enter Name: ",
        "Enter Sex (M/F): ",
        "Enter Baggage Number: ",
        "Enter Meal Preference (Veg/Non-Veg): "
    };

    // Get screen dimensions
    int maxY = getmaxy(stdscr);
    int maxX = getmaxx(stdscr);

    // Process each field sequentially
    for (int i = 0; i < 4; ++i) {
        bool validInput = false;
        while (!validInput) {
            // Create a new window for the current field
            WINDOW* win = newwin(5, 50, (maxY - 5) / 2, (maxX - 50) / 2);
            wclear(win);
            wmove(win, 2, 2);
            wattron(win, A_REVERSE);
            wprintw(win, "%s%s|", labels[i].c_str(), getInput[i].c_str());
            wattroff(win, A_REVERSE);
            wrefresh(win);

            // Handle input
            int inC = wgetch(win);
            if (inC == 27) { // Escape: Cancel booking
                delwin(win);
                clear();
                refresh();
                return false;
            } else if (inC == KEY_BACKSPACE || inC == 8 || inC == 127) { // Backspace
                if (!getInput[i].empty()) {
                    getInput[i].pop_back();
                }
            } else if (inC >= 32 && inC <= 126) { // Printable characters
                getInput[i] += (char)inC; // Direct cast to char
            } else if (inC == '\n') { // Enter: Validate and proceed
                // Simple validation
                bool isValid = true;
                std::string errorMsg;
                if (i == 0) { // Name
                    if (getInput[i].empty()) {
                        isValid = false;
                        errorMsg = "Name cannot be empty";
                    }
                } else if (i == 1) { // Sex
                    if (getInput[i].empty() || (getInput[i] != "M" && getInput[i] != "F")) {
                        isValid = false;
                        errorMsg = "Sex must be M or F";
                    }
                } else if (i == 2) { // Baggage
                    bool allDigits = !getInput[i].empty();
                    for (char c : getInput[i]) {
                        if (c < '0' || c > '9') {
                            allDigits = false;
                            break;
                        }
                    }
                    if (!allDigits) {
                        isValid = false;
                        errorMsg = "Baggage number must be a number";
                    }
                } else if (i == 3) { // Meal Preference
                    if (getInput[i].empty() || (getInput[i] != "Veg" && getInput[i] != "Non-Veg")) {
                        isValid = false;
                        errorMsg = "Meal preference must be Veg or Non-Veg";
                    }
                }

                if (isValid) {
                    validInput = true;
                } else {
                    // Show error message
                    WINDOW* errorWin = newwin(5, 50, (maxY - 5) / 2, (maxX - 50) / 2);
                    wclear(errorWin);
                    wmove(errorWin, 2, 2);
                    wprintw(errorWin, "%s. Press any key to retry.", errorMsg.c_str());
                    wrefresh(errorWin);
                    wgetch(errorWin);
                    delwin(errorWin);
                }
            }

            // Clean up window
            delwin(win);
            clear();
            refresh();
        }
    }

    // Store validated inputs in the Booking struct
    booking->name = getInput[0];
    booking->sex = getInput[1];
    booking->baggage = 0;
    for (char c : getInput[2]) {
        booking->baggage = booking->baggage * 10 + (c - '0');
    }
    booking->mealPreference = getInput[3];

    // Hide cursor and clean up
    curs_set(0);
    clear();
    refresh();
    return true;
}















    

void Database::loadFlights()
    {
    std::ifstream takeFly(flightFile);

    if(!takeFly.is_open())
    {
    return;
    }

    string discardLine;
    getline(takeFly,discardLine);
 
    string line;
    while(getline(takeFly , line))
    {
    //    string line;
     std::stringstream temp(line);
     string fly_id , airline , ori , des , leaveTime , duration , cost;

     if(getline(temp , fly_id , ',') && getline(temp , airline , ',') && getline(temp , ori , ',') && getline(temp , des , ',') && getline(temp , leaveTime , ',') && getline(temp , duration , ',') && getline(temp , cost))
     {
        int dur =  std::stoi(duration);
        float price = std::stod(cost);
        flights.push_back(Database::Flight{fly_id , airline , ori , des , leaveTime , dur , price});



     }

    }

        takeFly.close();



    }



void Database::loadAirports() {
    std::ifstream file(airportsFile);
    
    if(!file.is_open())
    {
        return;
    }
    
    string discardLine;
    getline(file , discardLine);

    string line;
    while(getline(file , line)) {
        std::stringstream ss(line);
        string id , name;
        if(getline(ss , id , ',') && getline(ss , name , ',')) {
             
             airports.push_back({id , name});

        }

        }
        file.close();

    }



string Database::getAirportID(int index) const {

    if(index < 0 || index > airports.size())
    {
    return "";
    }

    else
        return airports[index].id;


}






vector<Database::Flight> Database::getFlights(const std::string& origin , const string& dest) const    {
        vector<Database::Flight> foundFlight;

        for(size_t i = 0 ; i < flights.size() ; ++i)
        {
            if(flights[i].origin == origin && flights[i].dest == dest)
            {
            foundFlight.push_back(flights[i]);

            }


        }
        return foundFlight;

    }




vector<string> Database::getAirportNames() const {
vector<string> result;

    for(size_t i = 0 ; i < airports.size(); ++i)
    {
  //   if(i == 0) continue;
     string name = airports[i].name + " - "  + airports[i].id;
     result.push_back(name);
    }
    
    return result;;
}



/*

void Database::saveBooking(const Booking& bookNow);
    {
    
    ofstream saveFile(bookingsFlight , std::ios::app);
    
    if(!saveFile.is_open())
    {
        WINDOW* msg_win = newwin(10 , 50 , (getmaxy(stdscr) - 10) / 2 , (getmaxx(stdscr) - 50) / 2 ;
        wmove(msg_win , 2 , 2);
        wprintw(msg_win , "Error openning file.");
        wmove(msg_win , 6 , 2);
        wprintw(msg_win , "Press any key to continue.");
        wrefresh(msg_win);
        getch();
        delwin(msg_win);
        return;
    }



    }
    
*/

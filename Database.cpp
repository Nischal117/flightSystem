#include "Database.h"


Database::Database() noexcept {
 airportsFile = "airports.csv";
 flightFile = "flights.csv";
 bookingsFile = "bookings.csv";
    
    loadFlights();
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

    saveFile << 
    


    

   



    }
    


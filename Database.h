#ifndef DATABASE_H
#define DATABASE_H



#include<fstream>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<vector>
#include<string>
#include<ncurses.h>
#include<cmath>


using std::string;
using std::vector;

class Database {




public:
    
    Database() noexcept;

    struct Airport {
    string id;
    string name;
//    string id;
    };

    struct Flight {
    string flightId;
    string airline;
    string origin;
    string dest;
    string date;
    string departureTime;
    int duration;
    float price;
    };

    struct Booking {
    string bookingId;       //unique id for every booking to later dlt the row
//    string userId;
    string name;           //Customer Name          -> taking userInput(U)
    string flightId;       //flight Number Id       -> saved in flights.csv
    string airline;        //airline name           -> saved in flights.csv
    string origin;         //departure location     -> save in flights.csv
    string dest;           //destination location   -> save in flights.csv
    int duration;          //flight duration in mins -> save in flights.csv
    string departureTime;  //time of departure -> saved in flights.cvs
//  string bookingDate;
    string flightDate;
    string sex;            //Taking user input(U)
    string gmail;          //saving by getters in same process
    int baggage;           //getting from user(U)
    string mealPreference; // getting from user(U)
    float cost;            // taking from flights.csv and adding additional bag                               gage cost and the addign

    };

    std::string getAirportID(int index) const;
    std::string getAirName(int index) const;
    void loadAirports();
    void loadFlights();
    vector<std::string> getAirportNames() const;
    vector<Flight> getFlights(const std::string& origin, const std::string& dest) const;
    void saveBooking(const Booking& booking);
    string generateBookingID();



    bool userBook(Database::Booking* booking);



private:
    vector<Airport> airports;
    vector<Flight> flights;
    vector<Booking> bookings;
    string airportsFile;
    string flightFile;
    string bookingsFile;       
    int bookingCounter = 700;     //to generate unique booking ID;

};
      







#endif





#include "showBook.h"




void showFlight::ticket(const string& bookId) 
    {
        ticketPg t;
        bool findFlight = false;
       std::ifstream file("bookings.csv");

if (!file.is_open()) {
         
        WINDOW* msg_win = newwin(10 , 50 ,(getmaxy(stdscr) - 10) / 2 , (getmaxx(stdscr) - 50) / 2 );
        wmove(msg_win , 2 , 2);
        wprintw(msg_win , "Error! Couldn't open the file!");
        wmove(msg_win , 3 , 2);
        wprintw(msg_win , "Press any key to exit");
     wrefresh(msg_win);
     getch();
     delwin(msg_win);
        return;
    }

   string line;
   getline(file , line);

   
   while(getline(file , line))
   {
std::stringstream ss(line);

string bookingId , name , flightId , airline , origin , destination , departureDate , departureTime , mealPreference , tempBaggage , tempCost , tempDuration , discardgmail;
    
    if(getline(ss , bookingId , ',') && getline(ss , name , ',') && getline(ss , mealPreference , ',') && getline(ss , origin , ',') && getline(ss , destination , ',') && getline(ss , departureDate , ',') && getline(ss , departureTime , ',') && getline(ss , tempDuration , ',') && getline(ss , tempBaggage , ',') && getline(ss , tempCost , ',') && getline(ss , flightId , ',') && getline(ss , airline , ',') && getline(ss , discardgmail))
        {   
            if(bookingId == bookId)
            {
            
            t.bookingId = bookingId;
            t.name = name;
            t.flightId = flightId;
            t.airline = airline;
            t.origin = origin;
            t.departureDate = departureDate;
            t.departureTime = departureTime;
            t.destination = destination;
            t.mealPreference = mealPreference;
            int sbaggage = std::stoi(tempBaggage);
            int sduration = std::stoi(tempDuration);
            float scost = std::round(std::stof(tempCost)*100)/100;
            t.duration = sduration;
            t.baggage = sbaggage;
            t.cost = scost;
            findFlight = true;
            }




        }


   }


  if(findFlight == true)
  {
    WINDOW* t_win = newwin(14 , 70 , (getmaxy(stdscr)-14)/2 , (getmaxx(stdscr)-70) / 2);
    box(t_win , 0 , 0);
    wmove(t_win , 1 ,(66 - (t.airline).length()) / 2);
    wprintw(t_win , "%s Airlines", (t.airline).c_str());
    wmove(t_win , 3 , 2);
    wprintw(t_win , "ID : %s" , (t.bookingId).c_str());
    wmove(t_win , 5 , 2);
    wprintw(t_win , "Name : %s" , (t.name).c_str());
    wmove(t_win , 5 , 52);
    wprintw(t_win , "Date : %s" , (t.departureDate).c_str());
    wmove(t_win , 6 , 52);
    wprintw(t_win , "Time : %s" , (t.departureTime).c_str());
    wmove(t_win , 7 , 2);
    wprintw(t_win , "Meal : %s" , (t.mealPreference).c_str());
    wmove(t_win , 7 , 52);
    wprintw(t_win , "Duration : %d" , t.duration);
    wmove(t_win , 8 , 52);
    wprintw(t_win , "Baggage : %d" , t.baggage);
    wmove(t_win , 9 , 2);
    wprintw(t_win , "Departure : %s" , (t.origin).c_str());
    wmove(t_win , 10 , 2);
    wprintw(t_win , "Destination : %s" , (t.destination).c_str());
    wmove(t_win , 12 , 2);
    wprintw(t_win , "FlightID : %s" , (t.flightId).c_str());
    wmove(t_win , 12 , 52);
    wprintw(t_win , "Cost : $%.2f" , t.cost );
  
    wrefresh(t_win);
    
    WINDOW* msg = newwin(2 , 30 , (getmaxy(stdscr) - 4) , (getmaxx(stdscr)-30)/2);
    wmove(msg , 1 , 2);
    wprintw(msg , "Press any key to Return.");
    wrefresh(msg);
    getch();
    delwin(t_win);
    delwin(msg);
    clear();
    refresh();

    







  }

file.close();

    }








string showFlight::displayUserFlight(const string& mail)
    {

    vector<booking> userBookings;

    std::ifstream file("bookings.csv");

    if (!file.is_open()) {
         
        WINDOW* msg_win = newwin(10 , 50 ,(getmaxy(stdscr) - 10) / 2 , (getmaxx(stdscr) - 50) / 2 );
        wmove(msg_win , 2 , 2);
        wprintw(msg_win , "Error! Couldn't open the file!");
        wmove(msg_win , 3 , 2);
        wprintw(msg_win , "Press any key to exit");
     wrefresh(msg_win);
     getch();
     delwin(msg_win);
        return "";
    }

    string discardLine;
    getline(file , discardLine);
    string line;
    
    while(getline(file , line))
    {
    std::stringstream ss(line);
   string bookinId , userName ,flightId , date , departureTime , origin , destination , email , discard1 , discard2 , discard3 , discard4 , discard5;

    if(getline(ss , bookinId , ',') && getline(ss , userName , ',') && getline(ss , discard1 , ',') , getline(ss , origin , ',') && getline(ss , destination , ',') && getline(ss , date , ',') && getline(ss , departureTime , ',') && getline(ss , discard2 , ',') && getline(ss , discard3 , ',') && getline(ss , discard4 , ',' ) && getline(ss , flightId , ',') && getline(ss , discard5 , ',') && getline(ss , email) )
    {
        if(email == mail )
        {
            booking b;
            b.bookId = bookinId;
            b.name= userName;
            b.flightId = flightId;
            b.flightDate = date;
     //     b.departureTime = departureTime;
            b.origin = origin;
            b.destination = destination;
            userBookings.push_back(b);
        }
        
    }
    
  }
    file.close();
    

    if (userBookings.empty()) {
    WINDOW* msg_win = newwin(10, 50, (getmaxy(stdscr) - 10) / 2, (getmaxx(stdscr) - 50) / 2);
    wmove(msg_win, 2, 2);
    wprintw(msg_win, "No bookings found for %s", mail.c_str());
    wmove(msg_win, 3, 2);
    wprintw(msg_win, "Press any key to exit");
    wrefresh(msg_win);
    getch();
    delwin(msg_win);
    endwin();
    return "";
}


 WINDOW* win = newwin(12 ,66 ,(getmaxy(stdscr) - 12) /2, (getmaxx(stdscr) - 66) /2);
 keypad(win , TRUE);
   int highlight = 0;
   int choice = 0;
  
    while(true)  {
       wclear(win); 
    for(size_t i = 0 ; i < userBookings.size() ; ++i)
       {
    string displayStr = "ID: " + userBookings[i].bookId + " | Name: " + userBookings[i].name + " | Date: " + userBookings[i].flightDate + " | Origin: " + userBookings[i].origin + " | Destination: " + userBookings[i].destination + " | FlightID: " + userBookings[i].flightId + "\n";

     int startX = (66 - displayStr.length()) / 2;

  wmove(win, 2 + i, startX);
        if (i == highlight) wattron(win, A_REVERSE);
        wprintw(win, "%s", displayStr.c_str());
        if (i == highlight) wattroff(win, A_REVERSE);
    }

    wrefresh(win);

    int inC = wgetch(win);

        switch (inC) {
            case KEY_UP:
                highlight = (highlight - 1 + userBookings.size()) % userBookings.size();
                break;
               
               case KEY_DOWN:
                highlight = (highlight + 1) % userBookings.size();
                break;
              
              case 10: // Enter key
                choice = 1;
                break;

            case 27: // Escape key
            choice = 2;
             break;
             }
       
       if(choice == 1 || choice == 2) {
           break;
    }
}

delwin(win);
clear();
refresh();


if (choice == 1) {
    return userBookings[highlight].bookId;
}

    
   
    return "";

    }


#include "logIn.h"


//authentication for Admin;
bool logIn::isAdminAuthenticated()
    {
    ifstream file("adminUser.csv");

    if(!file.is_open())  {
    return false;
    }
    else {
    string discardLine;
    getline(file , discardLine);
    
    string getAdmin;
    while(getline(file , getAdmin))
    {   
        if(getAdmin == adminId)
        {
         return true;
        }

    }
     file.close();
    

    }

    return false;

    }




//authentication for users Log In
bool logIn::isAuthenticated(){

    map<string , string>userData;

   ifstream file("user.csv");

   if(!file.is_open())
   {
    return false;
   }
   
   else {
   
   string discardLine;
   getline(file , discardLine);
   string line;

   while(getline(file , line)) {

   stringstream store(line);
   string uName , gMail , passWord;
    
    if(getline(store , uName,  ',') && getline(store , gMail , ',') && getline(store , passWord) )
        {
         userData[gMail] = passWord;
         userData[uName] = passWord;
         if (uName == tempId || gMail == tempId) {
                // Store the gmail when a match is found
                gmail = gMail;
            }

        }

    }
    file.close();
    
    auto it1 = userData.find(tempId);
    if(it1 != userData.end() && it1->second == password)
    {

      return true;
    }

   

    }

return false;

}


//Inside logIn checks if the user is a customer or admin if admin redirects to admin panel for log in
int logIn::customerOrAdmin(const vector<string>& choice)
    {
     WINDOW* win = newwin(5 , 40 , (getmaxy(stdscr) - 5) / 2 , (getmaxx(stdscr) - 40) / 2);
     int active_input = 0;
         while(true)
     {
        wclear(win);

        for(int i = 0 ; i < 2 ; ++i)
        {
         wmove(win , i*2 + 0 , 2);
         if(i == active_input) wattron(win , A_REVERSE);
         wprintw(win , "%s" , choice[i].c_str());
         wattroff(win , A_REVERSE);
        }

        wrefresh(win);

        int inC = getch();

        if(inC == KEY_UP ) 
        {
        active_input = (active_input - 1 + 2) % 2; 
        }
         else if(inC == KEY_DOWN)
        {
        active_input = (active_input + 1) % 2; 
        }
        else if(inC == 27)
        {
           delwin(win);
           clear();
           refresh();
           
           return 2;  
         }
        else if(inC == '\n')
        {
         delwin(win);
         clear();
         refresh();
    
         return active_input;
        }

       
     }

   return active_input;
    }



/*
    void clearCodeFunc(int choice) {
     if(choice == 0)
        {
    //     clear();
    //     refresh();
         WINDOW* msg_win = newwin(5 , 40 , (getmaxy(stdscr)-5)/2 , (getmaxx(stdscr)-40) / 2);
         wmove(msg_win , 2 , 2 );
         wprintw(msg_win , "Press any key to continue to User login");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);

        }

        else if(choice== 1)
        {
   //      clear();
   //      refresh();
         WINDOW* msg_win = newwin(5 , 40 , (getmaxy(stdscr) - 5) / 2 , (getmaxx(stdscr) - 40) / 2);

         wmove(msg_win , 2 , 2);
         wprintw(msg_win , "Press any key to continue to Admin Login");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);
         goto adminLogIn;
        }
        else if(choice == 2)
        {
        continue;
        }
    
   }

*/








//to show admin logIn interface 


bool logIn::adminLogIn(const vector<string>& options)
 {   
 int maxY = getmaxy(stdscr);
 int maxX = getmaxx(stdscr);
 int failAttempt = 0;
 WINDOW* win = newwin(10 , 50 , (getmaxy(stdscr) - 10)/2 , (getmaxx(stdscr) - 50)/2 );
int active_input = 0;
    while(true)
    {
     wclear(win);
    
    for(int i = 0 ; i < options.size() ; ++i)
     {
      wmove(win , i*2 + 2 , 2);
      if(i == active_input) wattron(win , A_REVERSE);
      wprintw(win , "%s" , options[i].c_str());
      if(i == 0) wprintw(win , "%s%s",  adminId.c_str() , i == active_input ? "|" : "");
      if(i == 1) wprintw(win , "%s%s" , string(adminPass.size() , '*').c_str() , i == active_input ? "|" : "" );
      wattroff(win , A_REVERSE);

     }

     wrefresh(win);

     int inC = getch();

    if(inC == KEY_UP || (inC == '\t' && active_input > 0))
       {        
        active_input = (active_input - 1 + options.size()) % options.size();
       }
  else if(inC == KEY_DOWN || (inC == '\t'&& active_input < options.size() - 1)
     ||(inC == 10 && active_input < 2) )
    {
     active_input = (active_input + 1) % options.size();
    }
    else if(inC == 27)
    {
    delwin(win);
    clear();
    refresh();
    return false;

    }
    else if(inC == '\n' && active_input == 2)
        {   
        if(adminId.empty() || adminPass.empty())
        {
         wclear(win);
         clear();
         refresh();

         WINDOW* msg_win = newwin(5 , 50 , (maxY - 5)/2 , (maxX-50)/2 );
         wmove(msg_win , 2 , 2);
         wprintw(msg_win , "No field can be empty");
         mvwprintw(msg_win , 4 , 2 , "Press any key to continue");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);
         continue;
        }
        
   
      
        if(isAdminAuthenticated())
        {
              int num = std::stoi(adminPass); 
        
         if(num == ACODE)
         {
         wclear(win);
         clear();
         refresh();
         WINDOW* msg_win = newwin(5 , 50 , (maxY - 5) / 2 , (maxX - 50) / 2);
         mvwprintw(msg_win , 2 , 2 , "LogIn Successful..");
         mvwprintw(msg_win , 4 , 2 , "Press any key to continue");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);
         return true;
         }
         else
         {
            goto wrong_pass;
         }
       

        }
         else {
       
      wrong_pass:
      wclear(win);
      clear();
      refresh();
      WINDOW* msg_win = newwin(5 , 50 , (getmaxy(stdscr) - 5) / 2 , (getmaxx(stdscr) - 50) / 2);
         wmove(msg_win , 2 , 2);
         wprintw(msg_win ,"Login In Unsuccessful.Press any key to continue.");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);
         clear();
         refresh();
        adminId = "";
        adminPass = "";
        failAttempt++;
        active_input = 0;

         if(failAttempt > 2){
            delwin(win);
            clear();
            refresh();
           return false;
         }
       
        continue;
         
      }

        clear();
        return false;
        }   

          else if(inC == '\n' && active_input == 3){
 delwin(win);
 clear();
 refresh();
 WINDOW* msg_win = newwin(5 , 50 , (getmaxy(stdscr)-5)/2 , (getmaxx(stdscr)-50)/2);
 wmove(msg_win , 2 , 2);
 wprintw(msg_win , "Canceled! press any key to exit");
 wrefresh(msg_win);
 getch();
 delwin(msg_win);
  refresh();
 return false;

    }



   else if((inC == KEY_BACKSPACE || inC == 8 || inC ==127 )&& active_input < 2)
    {
     if(active_input == 0 && !adminId.empty()) adminId.pop_back();
     else if(active_input == 1 && !adminPass.empty()) adminPass.pop_back();
    }
    else if(inC >= 32 && inC <= 127 && active_input < 2)
    {
     if(active_input == 0)  adminId += inC;
     
     else if((active_input == 1) && isdigit(inC)) adminPass += inC;
    }
  
    }

    return false;

 }






//to show user logIn interface for customer

bool logIn::showLogIn(const vector<string>& options)
  {
 int logInAttempt = 0;
 WINDOW* win = newwin(10,50,(getmaxy(stdscr) - 10) / 2 , (getmaxx(stdscr)-50) / 2);
 int active_input = 0;

    while(true)
    {
        wclear(win);

    for(int i = 0 ; i < options.size() ; ++i)
    {
    wmove(win , 2 + i*2 , 2);
    if(i == active_input) wattron(win , A_REVERSE);
    wprintw(win ,"%s" , options[i].c_str());
    if(i == 0) wprintw(win , "%s%s" , tempId.c_str() , i == active_input  ? "|" : "");
    if(i == 1) wprintw(win , "%s%s" , string(password.length() ,'*').c_str() , i == active_input ? "|" : "");
    wattroff(win , A_REVERSE);

    }

    wrefresh(win);

    int inC = getch();

    //(ch == KEY_UP || (ch == '\t' && active_field > 0)) 
//(ch == KEY_DOWN || (ch == '\t' && active_field < labels.size() - 1))
//(ch == 27)  // esc ascii value
//(ch == '\n' && active_field == 3) //submit
//(ch == '\n' && active_field == 4) // exit
//(ch == KEY_BACKSPACE && active_field < 3)
//(ch >= 32 && ch <= 126 && active_field < 3)

  if(inC == KEY_UP || (inC == '\t' && active_input > 0))
  {
    active_input = (active_input - 1 + options.size()) % options.size();
  }
  else if(inC == KEY_DOWN ||(inC == '\t' && active_input < options.size() - 1) || (inC == 10 && active_input < 2))  {
    active_input = (active_input + 1) % options.size();
  }
  else if(inC == 27)
  {
    delwin(win);
    clear();
    refresh();
    WINDOW* cancel_win = newwin(5 , 40 , (getmaxy(stdscr)-5)/2 , (getmaxx(stdscr) - 40)/2);
    wmove(cancel_win , 2 , 2);
    wprintw(cancel_win , "Log in cancel. press any key to continue.");
    wrefresh(cancel_win);
    getch();
    delwin(cancel_win);
    delwin(win);
    refresh();
    return false;
  }
    else if(inC == '\n' && active_input == 2)
        {
         if(tempId.empty() || password.empty())
         {
          wclear(win);
          clear();
          refresh();
          WINDOW* msg_win = newwin(5 , 40 , (getmaxy(stdscr) - 5)/2 ,(getmaxx(stdscr) - 40) / 2);
          wmove(msg_win , 2 , 2);
          wprintw(msg_win , "No field should be empty..");
          wmove(msg_win , 5 , 2);
          wprintw(msg_win , "Press any key to continue.");
          wrefresh(msg_win);
          getch();
          delwin(msg_win);
          continue;
         }
        
              
         if(isAuthenticated())
         {
        wclear(win);
        clear();
        refresh();
        WINDOW* msg_win = newwin(5 , 50 , (getmaxy(stdscr) - 5) / 2 , (getmaxx(stdscr) - 50) / 2);
          wmove(msg_win , 2 , 2);
          wprintw(msg_win , "Log In Successfull. Press any key to process");
          wrefresh(msg_win);
          getch();
          delwin(msg_win); 
          delwin(win);
          clear();
          refresh();
          return true;          
         }

         else {
             wclear(win);
             clear();
             refresh();
         WINDOW* msg_win = newwin(5 , 50 , (getmaxy(stdscr) - 5) / 2 , (getmaxx(stdscr) - 50) / 2);
         wmove(msg_win , 2 , 2);
         wprintw(msg_win ,"Login In Unsuccessful.Press any key to continue.");
         wrefresh(msg_win);
         getch();
         delwin(msg_win);
         clear();
         refresh();
        tempId = "";
        password = "";
        logInAttempt++;

         if(logInAttempt > 2){
            delwin(win);
            clear();
            refresh();
            return false;
         }
            
         continue;
            }


    //    clear();
        refresh();
        return false;


        }
    
    else if(inC == '\n' && active_input == 3){
 delwin(win);
 clear();
 refresh();
 WINDOW* msg_win = newwin(5 , 50 , (getmaxy(stdscr)-5)/2 , (getmaxx(stdscr)-50)/2);
 wmove(msg_win , 2 , 2);
 wprintw(msg_win , "Canceled! press any key to exit");
 wrefresh(msg_win);
 getch();
 delwin(msg_win);
  refresh();
 return false;

    }


   else if((inC == KEY_BACKSPACE || inC == 8 || inC ==127 )&& active_input < 2)
    {
     if(active_input == 0 && !tempId.empty()) tempId.pop_back();  
     else if(active_input == 1 && !password.empty()) password.pop_back();
    }
    else if(inC >= 32 && inC <= 127 && active_input < 2)
    {
     if(active_input == 0) tempId += inC;
     else if(active_input == 1) password += inC;
    }





    }

    
    return false;


  }

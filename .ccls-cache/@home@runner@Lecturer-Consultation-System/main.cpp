// https://replit.com/@0133519/Lecturer-Consultation-System#main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

int const EXIT = -999;
bool lectView = true;
  
  struct Time //edge
{
int date, time;
string slotName = "NULL";
};
  
  struct IdentitySlot
{
Time slot;
IdentitySlot* nxtSlot = nullptr;
};

  struct Identity //vertex
{
string name, id;
IdentitySlot* SlotHead = nullptr;
vector<pair<int, int>> bookedSlots; //Store booked date and time slots from Student
}Lecturer[3]={{"Bridget","012"},{"Bob","345"},{"Ali Abu","678"}}, Student[3]={{"Justin", "012"}, {"Pravin", "345"}, {"Vimalan", "678"}};

bool dateTimeVerification(int date, int time)
{
    // Convert to integers after adding leading zeros
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    int hour = time / 100;
    int minute = time % 100;

  // Check validity of date and time
    if (year < 1970 || year > 9999)
        return false;
    if (month < 1 || month > 12)
        return false;


  
     // February month that only has 28 or 29 days according to leap year
    if (month == 2)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
            return (day >= 1 && day <= 29) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
        else
            return (day >= 1 && day <= 28) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
    }

    
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day >= 1 && day <= 30) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
    else
        return (day >= 1 && day <= 31) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

//https://stackoverflow.com/questions/69744982/how-to-tell-if-its-before-a-configured-time-in-c
bool pastDateTimeCheck(int date1, int time1)
{
  time_t now = time(0);
  tm *current = localtime(&now);

  int year = date1 / 10000;
  int month = (date1 / 100) % 100;
  int day = date1 % 100;
  int hour = time1 / 100;
  int minute = time1 % 100;

  int currentYear = current -> tm_year + 1900;
  int currentMonth = current -> tm_mon + 1;
  int currentDay = current -> tm_mday;
  int currentHour = current -> tm_hour;
  int currentMin = current -> tm_min;

  if (year > currentYear)
    return true;
    else if (year == currentYear && month > currentMonth)
      return true;
      else if (year == currentYear && month == currentMonth && day > currentDay)
        return true;
        else if (year == currentYear && month == currentMonth && day == currentDay && hour > currentHour)
          return true;
          else if (year == currentYear && month == currentMonth && day == currentDay && hour == currentHour && minute > currentMin)
            return true;
  //Hour and minute is not working and accurate
  return false;
}

int listOfLecturers(Identity lect[])
{
  int no;
  
    cout<<"LECTURER LIST"<<endl
        <<"============="<<endl;
  for(int i = 0; i < 3; i++)
  {
    cout<<"|"<<i+1<<"| - "<<lect[i].name<<endl;
  }
  cout<<"Please select the lecturer of your choice (1-3) or type -999 to return: ";
  while(!(cin>>no) ||(no != EXIT && (no < 1 || no > 3)))
  {
    if(no == EXIT)
    {
      cout<<"Back to student homepage..."<<endl<<endl;
      return EXIT;
    }
    cout<<"Invalid number. Please enter again."<<endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cout<<endl<<endl;
  return no;
}

bool lectViewSlots(Identity lect, bool lectView)
{
  int availableSlots = 0;
  
  for(int i = 0; i< 3; i++)
  {
    if(Lecturer[i].name == lect.name && Lecturer[i].id == lect.id)
    {
      if(lectView)
      {
      cout<<"View Consultation Slots set by Lecturer "<<lect.name<<":"<<endl   
          <<"*Slot is occupied when student name is registered*"<<endl<<endl;
      }
      IdentitySlot* lectSlotNavi = Lecturer[i].SlotHead;
      if(lectSlotNavi == NULL)
      {
        cout<<endl<<"There are currently no available consultation slots. Back to lecturer homepage menu..."<<endl<<endl;
        return false;
      }
      else
      {      
        if(lectView)
        {
        cout<<"\tDate\t|\tTime\t|\tStudent Name"<<endl
            <<"============================================"<<endl;
        }
        else
        {
        cout<<"\tDate\t|\tTime"<<endl
            <<"========================"<<endl;
        }
        while(lectSlotNavi != NULL)
        {          
          // https://stackoverflow.com/questions/225362/convert-a-number-to-a-string-with-specified-length-in-c
          //changing int to string for date and time to get the leading 0
          
          stringstream ss_time, ss_date;
          ss_time << setw(4) << setfill('0') << lectSlotNavi->slot.time;
          ss_date << setw(8) << setfill('0') << lectSlotNavi->slot.date;
          string timeStr = ss_time.str();
          string dateStr = ss_date.str();

          timeStr.insert(2, ":");
          dateStr.insert(4, "-");
          dateStr.insert(7, "-");
          
          if(lectView)
          {
            cout<<dateStr<<"\t|"<<timeStr<<"\t\t|"<<lectSlotNavi->slot.slotName<<endl
                <<"--------------------------------------------"<<endl;
           lectSlotNavi = lectSlotNavi->nxtSlot;
          }
          else 
          {
            
            if(lectSlotNavi->slot.slotName == "NULL")
            {
              cout<<dateStr<<"\t|\t"<<timeStr<<endl
                  <<"------------------------"<<endl;
              lectSlotNavi = lectSlotNavi->nxtSlot;
              availableSlots++;
            }
            else
            {
              lectSlotNavi = lectSlotNavi->nxtSlot;
            }
          }
        }
      if(!lectView && availableSlots == 0)
      {
        cout<<endl<<"**All slots have been booked. Back to student homepage..."<<endl<<endl;
        return false;
      }
      cout<<endl;
      return true;
    }
  }
 }
}

bool lectAddSlots(Identity &lect)
{
  for (int i = 0; i < 3; i++)
  {
    if (Lecturer[i].name == lect.name && Lecturer[i].id == lect.id)
    {
      bool dateTimeFuture;
      int date, time;
    
    cout << "Enter the date of consultation slot (YYYYMMDD, e.g., 20231130 for 2023/11/30) or type -999 to exit: ";
    while (!(cin >> date) || !dateTimeVerification(date, 0) || (date == EXIT))
    {
        if(date==EXIT)
        {
          cout<<"Back to lecturer Home Page..."<<endl<<endl;
          return false;
        }
        cout << "Invalid input format. Please enter again:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
    cout << "Enter the time of consultation slot (HHMM, e.g., 2000 for 20:00) or type -999 to exit: ";
    while (!(cin >> time) || !dateTimeVerification(date, time) || (time == EXIT))
    {
        if(date==EXIT)
        {
          cout<<"Back to lecturer Home Page..."<<endl<<endl;
          return false;
        }
        cout << "Invalid input format. Please enter again:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
      
      cout<<endl;

      //Check if date & time is in the past or not
      dateTimeFuture = pastDateTimeCheck(date, time);
      if(!dateTimeFuture)
      {
        cout << "The consultation slot is set in the past date and time. It has been automatically removed."<<endl<<endl;
        return false;
      }

      IdentitySlot* newSlot = new IdentitySlot;
      newSlot->slot.date = date;
      newSlot->slot.time = time;
      newSlot->nxtSlot = nullptr;

      // If the lecturer slot list is empty
      if (Lecturer[i].SlotHead == nullptr)
      {
        Lecturer[i].SlotHead = newSlot;
        return true;
      }

      // Check if new slot is the same as the lect slot head
      if (date == Lecturer[i].SlotHead->slot.date && time == Lecturer[i].SlotHead->slot.time)
      {
        cout << "A consultation slot with the same date and time has been set." << endl<<endl;
        newSlot = nullptr;
        return false;
      }
      else // Adjust the slots chronologically
      {
        // Deciding whether new slot will be placed before or after the head of slot based on the time & date
        if (date < Lecturer[i].SlotHead->slot.date || (date == Lecturer[i].SlotHead->slot.date && time < Lecturer[i].SlotHead->slot.time))
        { // AddToFirstNode method
          newSlot->nxtSlot = Lecturer[i].SlotHead;
          Lecturer[i].SlotHead = newSlot;
          return true;
        }

        // Navigating through nodes and placing newSlot based on time & date
        IdentitySlot* lectSlotNavi = Lecturer[i].SlotHead;
        while (lectSlotNavi->nxtSlot != nullptr)
        {
          if(date == lectSlotNavi->nxtSlot->slot.date && time == lectSlotNavi->nxtSlot->slot.time)
          {
            cout<<"A consultation slot with the same date and time has been set."<<endl<<endl;
            return false;
          }

          if((date < lectSlotNavi->nxtSlot->slot.date) || (date == lectSlotNavi->nxtSlot->slot.date && time < lectSlotNavi->nxtSlot->slot.time))
          { // AddAtPos method
            newSlot->nxtSlot = lectSlotNavi->nxtSlot;
            lectSlotNavi->nxtSlot = newSlot;
            return true;
          }
          lectSlotNavi = lectSlotNavi->nxtSlot;
        }
        // If condition is not met for both then it is placed at the last of the list
        lectSlotNavi->nxtSlot = newSlot;
        return true;
      }
    }
  }
}

bool lectDeleteSlots(Identity &lect)
{
  int date, time;
  lectView = true;

  if(!lectViewSlots(lect, lectView))
  {
    return false;
  }
  else
    cout<<endl<<"*Please delete a slot that is not booked.*"<<endl<<endl;
  
    cout << "Enter the date of consultation slot for deletion (YYYYMMDD, e.g., 20231130 for 2023/11/30) or type -999 to exit: ";
    while(!(cin >> date) || !dateTimeVerification(date, 0) || (date == EXIT))
    {
      if(date == EXIT)
      {
       cout<<"Back to lecturer Home Page..."<<endl<<endl;
       return false;
      }
    cout<<"Invalid input format. Please enter again:"<<endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }  

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Enter the time of consultation slot for deletion (HHMM, e.g., 2000 for 20:00) or type -999 to exit: ";
    while(!(cin>>time) || !dateTimeVerification(date, time) || (time == EXIT))
    {
      if(date == EXIT)
      {
        cout<<"Back to lecturer Home Page..."<<endl<<endl;
      return false;
    }
    cout<<"Invalid input format. Please enter again:"<<endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  for (int i = 0; i < 3; i++)
  {
    if (Lecturer[i].name == lect.name && Lecturer[i].id == lect.id)
    {
      IdentitySlot *lectSlotNavi = Lecturer[i].SlotHead;
      IdentitySlot *prevSlot = nullptr;

      // Search for the slot with the specified date and time
      while(lectSlotNavi != nullptr)
      {
        if(date == lectSlotNavi->slot.date && time == lectSlotNavi->slot.time)
        {
          if(lectSlotNavi->slot.slotName != "NULL") // If the slot is booked
          {
            cout<<endl<<"Student "<<lectSlotNavi->slot.slotName<<" has already booked the following consultation slot."<<endl<<endl;
            return false;
          }
          else // If the slot is not booked (unbooked)
          {
            if(lectSlotNavi == Lecturer[i].SlotHead)
            {
              Lecturer[i].SlotHead = lectSlotNavi->nxtSlot; // If slot deletion is the first node
            }
            else
            {
              prevSlot->nxtSlot = lectSlotNavi->nxtSlot; // If slot deletion is not the first node
            }
            delete lectSlotNavi; // Free up space
            return true;
          }
        }
        prevSlot = lectSlotNavi;
        lectSlotNavi = lectSlotNavi->nxtSlot;
      }
      cout << "Slot with the specified date and time is not found." << endl;
      return false;
    }
  }
  // Lecturer not found
  return false;
}

void lecturerHomePage(Identity lect)
{
  int code=0;
  do
  {
  cout<<"Welcome to the Lecturer Homepage!"<<endl
      <<"================================="<<endl
      <<"1 - View consultation slot"<<endl
      <<"2 - Add consultation slot"<<endl
      <<"3 - Delete consultation slot"<<endl
      <<"4 - Exit back to main menu"<<endl
      <<"================================="<<endl
      <<"Enter the number shown above: "<<endl;
    if (!(cin >> code) || code<1 || code>4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid number. Please try again." << endl;
        }
    else
    {
    cout<<endl;
    switch(code){
      case 1: 
        {
        lectView = true; 
        lectViewSlots(lect, lectView); break; 
        }
      case 2: 
      {
        if(lectAddSlots(lect))
        cout<<endl<<"You have successfully added a consultation slot!"<<endl<<endl;
        break;
      }
      case 3: 
      {
        if(lectDeleteSlots(lect))
        cout<<endl<<"You have successfully deleted a consultation slot."<<endl<<endl;
        break;
      }
      case 4: cout<<"--You have exited back to main menu--"<<endl; break;
      }
    } 
  }while(code!=4);
}

bool bookSlots(Identity lect[], Identity stud)
{ 
  int i, x;
  int date, time;
  lectView = false;
  
  int index = listOfLecturers(lect);  
  if(index == EXIT)
  {
    return false;
  }
  else
  {
    Identity LecturerList = lect[index-1];
  
    if(lectViewSlots(LecturerList, lectView))
    { 
      cout<<"Enter the date of consultation slot for booking (YYYYMMDD, e.g., 20231130 for 2023/11/30) or type -999 to exit: ";
    while (!(cin >> date) || !dateTimeVerification(date, 0) || (date == EXIT))
    {
      if(date==EXIT)
      {
        cout<<"Back to student Home Page..."<<endl<<endl;
        return false;
      }
        cout << "Invalid input format. Please enter again:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    cout<<"Enter the time of consultation slot for booking (HHMM, e.g., 2000 for 20:00) or type -999 to exit: ";
    while(!(cin >> time) || !dateTimeVerification(date, time) || (time == EXIT))
    {
      if(date==EXIT)
      {
        cout<<"Back to student Home Page..."<<endl<<endl;
        return false;
      }
        cout<<"Invalid input format. Please enter again:"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  
      // Check if the student has already booked a slot with similar date and time with any other lecturers (attempted)
      for (const auto& bookedSlot : stud.bookedSlots)
      {
          if (bookedSlot.first == date && bookedSlot.second == time)
          {
              cout<<endl<<"You already booked a slot at the same time and date with another lecturer."<<endl<<endl;
              return false;
          }
      }
      
      IdentitySlot *lectSlotNavi = LecturerList.SlotHead;

      // Search for the slot with the specified date and time
      while(lectSlotNavi != nullptr)
      {
        if(date == lectSlotNavi->slot.date && time == lectSlotNavi->slot.time)
        {
          if(lectSlotNavi->slot.slotName != "NULL") 
          {
            cout<<"Student "<<lectSlotNavi->slot.slotName<<" has already booked the following consultation slot."<<endl;
            return false;
          }
          else // If the slot is not booked (unbooked)
          {            
            // https://en.cppreference.com/w/cpp/language/range-for
            
            // Add the slot to the student's bookedSlots
            stud.bookedSlots.push_back({ date, time});
                      
            IdentitySlot* newSlot = new IdentitySlot;
            newSlot->slot.date = lectSlotNavi->slot.date;
            newSlot->slot.time = lectSlotNavi->slot.time;
            newSlot->slot.slotName = LecturerList.name;
            newSlot->nxtSlot = nullptr;
            
            lectSlotNavi->slot.slotName = stud.name; //store stud name in lect slotname
             for(i = 0; i<3; i++)
            {
              if(Student[i].name == stud.name)//find the array of the Student[]
              {
                // If the lecturer slot list is empty
                if (Student[i].SlotHead == nullptr)
                {
                  Student[i].SlotHead = newSlot;
                  return true;
                }
  
              if (date < Student[i].SlotHead->slot.date || (date == Student[i].SlotHead->slot.date && time < Student[i].SlotHead->slot.time))
              { // AddToFirstNode method
                newSlot->nxtSlot = Student[i].SlotHead;
                Student[i].SlotHead = newSlot;
                return true;
              }
  
              // Navigating through nodes and placing newSlot based on time & date
              IdentitySlot* studSlotNavi = Student[i].SlotHead;
              while (studSlotNavi->nxtSlot != nullptr)
              {  
                
                if((date < studSlotNavi->nxtSlot->slot.date) || (date == studSlotNavi->nxtSlot->slot.date && time < studSlotNavi->nxtSlot->slot.time))
                { // AddAtPos method
                  newSlot->nxtSlot = studSlotNavi->nxtSlot;
                  studSlotNavi->nxtSlot = newSlot;
                  return true;
                }
                studSlotNavi = studSlotNavi->nxtSlot;
              }
              // If condition is not met for both then it is placed at the last of the list
              studSlotNavi->nxtSlot = newSlot;
              return true;
              }
            }
          return true;
          }
        }
        lectSlotNavi = lectSlotNavi->nxtSlot;
      }
    cout<<endl<<"Slot with the specified date and time is not found."<<endl<<endl;
    return false;
    }
    else
      return false;
    }
}

bool ActiveSlots(Identity stud)
{
  for(int i = 0; i< 3; i++)
  {
    if(Student[i].name == stud.name)
    {
      cout<<"View all active consultation Slots for student "<<stud.name<<":"<<endl<<endl;
      
      IdentitySlot* studSlotNavi = Student[i].SlotHead;
      if(studSlotNavi == NULL)
      {
        cout<<endl<<"You have not booked any consultation slots."<<endl<<endl;
        return false;
      }
      else
      {      
        cout<<"\tDate\t|\tTime\t|\tLecturer name"<<endl
            <<"============================================"<<endl;

        while(studSlotNavi != NULL)
        {          
          // https://stackoverflow.com/questions/225362/convert-a-number-to-a-string-with-specified-length-in-c
          //changing int to string for date and time to get the leading 0
          
          stringstream ss_time, ss_date;
          ss_time << setw(4) << setfill('0') << studSlotNavi->slot.time;
          ss_date << setw(8) << setfill('0') << studSlotNavi->slot.date;
          string timeStr = ss_time.str();
          string dateStr = ss_date.str();

          timeStr.insert(2, ":");
          dateStr.insert(4, "-");
          dateStr.insert(7, "-");
          
          cout<<dateStr<<"\t|"<<timeStr<<"\t\t|"<<studSlotNavi->slot.slotName<<endl
              <<"--------------------------------------------"<<endl;
          studSlotNavi = studSlotNavi->nxtSlot;
        }
      cout<<endl;
      return true;
    }
  }
 }
}

bool unbookSlots(Identity lect[], Identity stud)
{
  int i, x, date, time;
  
  if(!ActiveSlots(stud))
  {
    return false;
  }
  else
  {
    cout << "Enter the date of consultation slot for deletion (YYYYMMDD, e.g., 20231130 for 2023/11/30) or type -999 to exit: ";
    while(!(cin >> date) || !dateTimeVerification(date, 0) || (date == EXIT))
    {
      if(date == EXIT)
      {
       cout<<"Back to lecturer Home Page..."<<endl<<endl;
       return false;
      }
    cout<<"Invalid input format. Please enter again:" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }  

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Enter the time of consultation slot for deletion (HHMM, e.g., 2000 for 20:00) or type -999 to exit: ";
    while(!(cin>>time) || !dateTimeVerification(date, time) || (time == EXIT))
    {
      if(date == EXIT)
      {
        cout<<"Back to lecturer Home Page..."<<endl<<endl;
        return false;
      }
    cout<<"Invalid input format. Please enter again:"<<endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  for(i = 0; i<3; i++)
    if(Student[i].name == stud.name)
    {
      IdentitySlot *studSlotNavi = Student[i].SlotHead;
      IdentitySlot *prevSlot = nullptr;
      
      while(studSlotNavi != nullptr)
      {
       if(date == studSlotNavi->slot.date && time == studSlotNavi->slot.time)
       {
        for(x = 0; x<3; x++)
        {
          if(lect[x].name == studSlotNavi->slot.slotName)
          {
            IdentitySlot *lectSlotNavi = lect[x].SlotHead;
            while(lectSlotNavi != NULL)
            {
              if(date == lectSlotNavi->slot.date && time == lectSlotNavi->slot.time)
              {
                lectSlotNavi->slot.slotName = "NULL";
              }
              lectSlotNavi = lectSlotNavi->nxtSlot;
            }
          }
        }
          if(studSlotNavi == Student[i].SlotHead)
          {
            Student[i].SlotHead = studSlotNavi->nxtSlot; 
          }
          else
          {
            prevSlot->nxtSlot = studSlotNavi->nxtSlot; 
          }
            delete studSlotNavi; 
            return true;
         }
          prevSlot = studSlotNavi;
          studSlotNavi = studSlotNavi->nxtSlot;
      }
    }
  }
  return 0;
}

void studentHomePage(Identity lect[], Identity stud)
{
  int code=0;
  do
  {
  cout<<"Welcome to the Student Homepage!"<<endl
      <<"================================="<<endl         
      <<"1 - Book an appointment"<<endl
      <<"2 - Active appointment"<<endl
      <<"3 - Cancel an appointment"<<endl
      <<"4 - Exit to main menu"<<endl
      <<"================================="<<endl
      <<"Enter the number shown above: "<<endl;
    if (!(cin >> code) || code<1 || code>4)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << endl << "Invalid number. Please try again." << endl;
    }
    else
    {
      cout<<endl;
      switch(code){
        case 1: 
        {
          if(bookSlots(lect, stud))
          cout<<endl<<"You have successfully booked an appointment!"<<endl<<endl;
          break;
        }
        case 2: ActiveSlots(stud); break; 
        case 3:
        {
          if(unbookSlots(lect, stud))
          cout<<endl<<"You have successfully unbooked an appointment."<<endl<<endl;
          break;
        }
        case 4: cout<<endl<<"--You have exited back to main menu--"<<endl; break;
      }
    }
  }while(code != 4);
}

int main()
{
  int code = 0;
  bool login =false; //condition for do while loop
  Identity info; 
  
  do {
    cout << "============================" << endl
         << "LECTURER CONSULTATION SYSTEM" << endl
         << "============================" << endl
         << "|1|--Lecturer" << endl
         << "|2|--Student" << endl
         << "|3|--Exit" << endl
         << "Enter the number according to your role:" << endl;

    if (!(cin >> code) || code<1 || code>3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid number. Please try again." << endl;
        }
    else {
      cout<<endl;
      switch (code) {
        case 1: {
          int attempt = 0; //number of input attempts
          do {
            cout << "=====================" << endl
                 << "Lecturer's Login Page" << endl
                 << "=====================" << endl;
            cout << "Username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, info.name);
            cout << "Password: ";
            cin >> info.id;
            cout << endl;
              
              for(int i =0; i<3; i++)
                {
                  if(info.name==Lecturer[i].name && info.id==Lecturer[i].id)
                  {
                    login = true;
                    cout << "Login Successful." << endl<<endl;                          
                    lecturerHomePage(info);
                    break;              
                  } 
                }
              if(!login)
                cout << "Invalid lecturer username or password." << endl;
              attempt++;
              if (attempt == 3) {
                cout << "The maximum number of input has been reached. Returning to main menu." << endl;
                break;
              }
          } while (!login);
          break;
        }  
        case 2: {
          int attempt2 = 0, i;
          bool login = false;
          do { 
            cout << "===================" << endl
                 << "Student Login Page" << endl
                 << "===================" << endl
                 << "Please enter the following" << endl;
            cout << "Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //prevent data from main menu interferring with input info.name
            getline(cin, info.name);
            cout << "ID: ";
            cin >> info.id;
            cout << endl;

            for (i = 0; i < 3; i++) {
              if (info.name == Student[i].name && info.id == Student[i].id){
                login = true;
                cout<<"Login Successful."<<endl<<endl;
                studentHomePage(Lecturer, info);
                break;
              }
            } 
              if(!login)
              cout << "Invalid student name or ID." << endl;
              attempt2++;
              if (attempt2 == 3) {
                cout << "The maximum number of input has been reached. Returning to main menu." << endl;
                break;
              }
            } while (!login);
          break; 
        }
        case 3:
          cout << "You have exited the program." << endl;
          break;
      }
    }
    cout<<endl;
  } while (code != 3);

  return 0;
}
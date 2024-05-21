#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

int const SIZE = 3;

  struct Time //edge
{
int time;
int date;
};
  
  struct LecturerSlot
{
Time slot;
LecturerSlot* nxtSlot;
};

  struct Identity //vertex
{
string name, id;
LecturerSlot* lectSlotHead;
}arrStud[3]={{"Justin", "012"}, {"Pravin", "345"}, {"Vimalan", "678"}}, arrMan[3]={{"Lee","111"},{"Maria","222"},{"Ave","333"}};

Identity Lecturer[SIZE]={{"Bridget","012"},{"Bob","345"},{"Ali Abu","678"}};

void lecturerHomePage();

void lectViewSlots(Identity lect);
void lectAddSlots(Identity &lect);
int cancelAppointment();

void studentHomePage();
int ActiveHistorySlots();
int editSlots();

void managementHomePage();

int mainMenu()
{
  int code=0;
    do
   {
    cout<<"============================"<<endl
        <<"LECTURER CONSULTATION SYSTEM"<<endl
        <<"============================"<<endl
        <<"|1|--Lecturer"<<endl
        <<"|2|--Student"<<endl
        <<"|3|--Management"<<endl
        <<"|4|--Exit"<<endl
        <<"Enter the number according to your role:"<<endl;

    cin>>code;

    if(code<1 or code>4)
    {
      cout<<"Invalid input. Please try again with the numbers above."<<endl;
    }
  }while(code<1 || code>4);   
  
  return code;  
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
      <<"3 - Cancel appointment"<<endl
      <<"4 - Exit back to main menu"<<endl
      <<"================================="<<endl
      <<"Enter the number shown above: "<<endl;

      cin>>code;

    switch(code){
      case 1: lectViewSlots(lect); break; 
      case 2: 
      {
        lectAddSlots(lect);
        break;
      }
      case 3: cancelAppointment(); break;
      case 4: cout<<"--You have exited back to main menu--"<<endl; break;
      default: cout<<"Invalid Code. Please try again."<<endl;
    }
  }while(code!=4 || code<1 || code>4);
}

void lectViewSlots(Identity lect)
{
  for(int i = 0; i< SIZE; i++)
  {
    if(Lecturer[i].name == lect.name && Lecturer[i].id == lect.id)
    {
      cout<<"View Consultation Slots for Lecturer "<<lect.name<<":"<<endl;
      LecturerSlot* lectSlotNavi = Lecturer[i].lectSlotHead;
      while(lectSlotNavi != NULL)
        {
           cout<<"|\tTime\t|\tDate\t|"<<endl
               <<"==================="<< endl
               <<"|"<<lectSlotNavi->slot.time<<"\t|"<<lectSlotNavi->slot.date<<"\t|"<<endl;
                lectSlotNavi = lectSlotNavi->nxtSlot;
        }
      cout<<endl;
    }
  }
  cout<<"Lecturer is not found."<<endl;
}

void lectAddSlots(Identity &lect)
{
  for (int i = 0; i < SIZE; i++)
  {
    if (Lecturer[i].name == lect.name && Lecturer[i].id == lect.id)
    {
      string time, date;
      cout << "Adding Consultation Slots for Lecturer " << lect.name << endl;
      cout << "Enter the time of consultation slot (HHMM, e.g., 2000 for 20:00): ";
      cin >> time;
      cout << "Enter the date of consultation slot (DDMMYYYY, e.g., 30112023): ";
      cin >> date;

      // Convert string into integer for time & date in "LecturerSlot" struct
      int timeInt = stoi(time);
      int dateInt = stoi(date);

      LecturerSlot* newSlot = new LecturerSlot;
      newSlot->slot.time = timeInt;
      newSlot->slot.date = dateInt;
      newSlot->nxtSlot = nullptr;

      // If the lecturer slot list is empty
      if (Lecturer[i].lectSlotHead == nullptr)
      {
        Lecturer[i].lectSlotHead = newSlot;
        return;
      }

      // Check if new slot is the same as the lect slot head
      if (timeInt == Lecturer[i].lectSlotHead->slot.time && dateInt == Lecturer[i].lectSlotHead->slot.date)
      {
        cout << "A consultation slot with the same date and time has been set." << endl;
        newSlot = nullptr;
      }
      else // Adjust the slots chronologically
      {
        // Deciding whether new slot will be placed before or after the head of slot based on the time & date
        if (timeInt < Lecturer[i].lectSlotHead->slot.time || (timeInt == Lecturer[i].lectSlotHead->slot.time && dateInt > Lecturer[i].lectSlotHead->slot.date))
        { // AddToFirstNode method
          newSlot->nxtSlot = Lecturer[i].lectSlotHead;
          Lecturer[i].lectSlotHead = newSlot;
          return;
        }

        // Navigating through nodes and placing newSlot based on time & date
        LecturerSlot* lectSlotNavi = Lecturer[i].lectSlotHead;
        while (lectSlotNavi->nxtSlot != nullptr)
        {
          if (timeInt < lectSlotNavi->nxtSlot->slot.time || (timeInt == lectSlotNavi->nxtSlot->slot.time && dateInt < lectSlotNavi->nxtSlot->slot.date))
          { // AddAtPos method
            newSlot->nxtSlot = lectSlotNavi->nxtSlot;
            lectSlotNavi->nxtSlot = newSlot;
            return;
          }
          lectSlotNavi = lectSlotNavi->nxtSlot;
        }
        // If condition is not met for both then it is placed at the last of the list
        lectSlotNavi->nxtSlot = newSlot;
        return;
      }
    }
  }
  cout << "Lecturer is not found." << endl; // Shouldn't happen but just in case
}

int cancelAppointment()
{

}

void studentHomePage(Identity stud)
{
  int code=0;
  do
  {
  cout<<"Welcome to the Student Homepage!"<<endl
      <<"================================="<<endl         
      <<"1 - Active/History appointment"<<endl
      <<"2 - Book or unbook appointment"<<endl
      <<"3 - Exit to main menu"<<endl
      <<"================================="<<endl
      <<"Enter the number shown above: "<<endl;

    cin>>code;

    switch(code){
      case 1: ActiveHistorySlots(); break; 
      case 2: editSlots(); break;
      case 3: cout<<"--You have exited back to main menu--"<<endl; break;
      default: cout<<"Invalid Code. Please try again."<<endl;
    }
  }while(code!=3 || code<1 || code>3);
}

int ActiveHistorySlots()
{
  return 0;
}

int editSlots()
{
  return 0;
}

void managementHomePage(Identity staff)
{
  int code=0;
  do
  {
  cout<<"Welcome to the Management Homepage!"<<endl
      <<"================================="<<endl        
      <<"1 - View lecturer's consultation status"<<endl
      <<"2 - Exit to main menu"<<endl
      <<"================================="<<endl
      <<"Enter the number shown above: "<<endl;

    cin>>code;

    switch(code){
      case 1: break;
      case 2: cout<<"--You have exited back to main menu--"<<endl; break;
      default: cout<<"Invalid Code. Please try again."<<endl;
    }
  }while(code!=2 || code<1 || code>2);
}

int main()
{
  int code = 0;
  bool login; //condition for do while loop
  Identity info; 
  
  do {
    cout << "============================" << endl
         << "LECTURER CONSULTATION SYSTEM" << endl
         << "============================" << endl
         << "|1|--Lecturer" << endl
         << "|2|--Student" << endl
         << "|3|--Management" << endl
         << "|4|--Exit" << endl
         << "Enter the number according to your role:" << endl;

    if (!(cin >> code) || code<1 || code>4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid number. Please try again." << endl;
        }
    else {
      switch (code) {
        case 1: {
          int attempt = 0; //number of input attempts
          bool login = false; 
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
                  if(info.name==Lecturer[i].name && info.id==Lecturer[i].id){
              cout << "You have successfully entered the lecturer's Homepage!" << endl;
              lecturerHomePage(info);
              login = true;
              break;
                  }
                }
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
              if (info.name == arrStud[i].name && info.id == arrStud[i].id) {
                login = true;
                studentHomePage(info);
                break;
              }
            } 
              cout << "Invalid student name or ID." << endl;
              attempt2++;
              if (attempt2 == 3) {
                cout << "The maximum number of input has been reached. Returning to main menu." << endl;
                break;
              }
            } while (!login);
          break; 
        }
        case 3: {
          int attempt2 = 0, i;
          bool login = false;
          do { 
            cout << "===================" << endl
                 << "Management Login Page" << endl
                 << "===================" << endl
                 << "Please enter the following" << endl;
            cout << "Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, info.name);
            cout << "Password: ";
            cin >> info.id;
            cout << endl;

            for (i = 0; i < 3; i++) {
              if (info.name == arrMan[i].name && info.id == arrMan[i].id) {
                login = true;
                managementHomePage(info);
                break;
              }
            }
              cout << "Invalid staff name or ID." << endl;
              attempt2++;
              if (attempt2 == 3) {
                cout << "The maximum number of input has been reached. Returning to main menu." << endl;
                break;
              }
          } while (!login);
          break;
        }
        case 4:
          cout << "You have exited the program." << endl;
          break;
      }
    }
    cout<<endl;
  } while (code != 4 || code < 1 || code > 4);

  return 0;
}
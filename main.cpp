#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "include/event.cpp"
void ShowHomeScreen();
using namespace std;
void ClearScreen(){cout << string( 100, '\n' );}
bool IsIn(string keyword, string line){return (line.find (keyword) != string::npos);}
void ShowEventsPage(Profile);
string toLower(string data){
    return data;
}

void SetupKeywords(string First,string Last){
  string keyword;
  string introMsg = "PLEASE READ: \n vfgesvwebgqtgrsfdvcbgrefsv";
  ofstream o("user_profiles/" + First + "-" + Last + ".txt", ios::app);
  cout << introMsg << endl;
  o << "Keywords:";
  while (keyword != "exit"){
      cin >> keyword;
      o << " " + toLower(keyword);
  }
  ClearScreen();
  ShowHomeScreen();
}

void SignUp(){
  string First; 
  string Last; 
  cout << "Enter your first name:\n";
  cin >> First;
  cout << "Enter your last name:\n";
  cin >> Last;
  ofstream o("user_profiles/" + First + "-" + Last + ".txt");
  o << "First Name: " << First << "\n";
  o << "Last Name: " << Last << "\n";

  string password = " "; 
  string temp;
  while (temp!=password){
  cout << "Enter your password\n";
  cin >> password;
  cout << "Confirm your password\n";
  cin >> temp;
  }
  o << "Password: " << password << "\n";
  cout << "User Profile Created \n Press Enter to Return to Home";
  o.close();
  cin.ignore();
  ClearScreen();
  SetupKeywords(First, Last);
}

string getline_num(string filename, int num){
    ifstream o(filename);
    std::string line;
    for(int i = 0; i < num; i++){
        getline(o, line);
    }
    o.close();
    return line;
}

void Login(){
    string First; 
    string Last; 
    cout << "Enter your first name:\n";
    cin >> First;
    cout << "Enter your last name:\n";
    cin >> Last;

    // extract users actual password 
    string act_password = getline_num("user_profiles/" + First + "-" + Last + ".txt",3);; 
    string inp_password = "";
    bool LoggedIn = false;
    while (("Password: " + inp_password) != act_password){
        cout << "Enter your password\n";
        cin >> inp_password;
    }
Profile User(First,Last);
ShowEventsPage(User);
}

void ShowHomeScreen(){
    int option;
    cout << "(1) Sign Up\n(2) Login\nSelect a number to continue\n";
    cin >> option;
    switch (option){
        case 1: ClearScreen(); SignUp(); break;
        case 2: ClearScreen(); Login(); break;
        default:
        cout << "Invalid Entry";
        ShowHomeScreen();
        break;
    }
}

Event* FindReleventEvents(Profile User){
    Event Events[50];
    int curr_index = 0;
    ifstream o("email_samples/1.txt");
    std::string line;
    while (getline(o, line)){
        Event temp;
        temp.name = line.substr(0,20);
        temp.content = line;
        bool relevant = false;
        for (int i = 0; i > (sizeof(User.KeyWords)/sizeof(User.KeyWords[0])); i++){
            if (IsIn(User.KeyWords[0],toLower(line))){
                relevant = true;
            } 
        }
        if (relevant){
            Events[curr_index] = temp;
            curr_index += 1;
        }
    }
    return Events;
}

void ShowEventsPage(Profile User){
    Event* EventList = FindReleventEvents(User);
    for(int i = 0;i < (sizeof(EventList)/sizeof(EventList));i++){
        cout << EventList[i].name << endl;
        cout << "Is happening on" << EventList[i].date;
    }
}

int main() { 
    ShowHomeScreen();
    return 0;
}
 
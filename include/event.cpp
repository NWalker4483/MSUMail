#include<string>
using namespace std;
class Event 
{ 
    public: 
    string name; 
    string date;
    string content;
}; 

class Profile { 
    public: 
    string FirstName; 
    string LastName;
    string FullName;
    string KeyWords[25];
    
    string getline_num(string filename, int num){
    ifstream o(filename);
    std::string line;
    for(int i = 0; i < num; i++){
        getline(o, line);
    }
    o.close();
    return line;
}
    Profile(string First,string Last){
        FirstName = First;
        LastName = Last;
        FullName = First + " " + Last;
        int words = 0;
        string str_temp = getline_num("user_profiles/" + First + "-" + Last + ".txt",4); 
        char str[1024];
        strncpy(str, str_temp.c_str(), sizeof(str));
        str[sizeof(str) - 1] = 0;
        // Returns first token  
        char *token = strtok(str, " "); 
        // Keep printing tokens while one of the 
        // delimiters present in str[]. 
        while (token != NULL) 
        { 
            KeyWords[words] = token;
            words += 1; 
            token = strtok(NULL, " "); 
        } 
    }
}; 
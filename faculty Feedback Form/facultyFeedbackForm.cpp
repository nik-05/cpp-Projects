#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// Design Class to Provide Design to the Project
class Design{
    public:
//     This will Display Welcome Message
    void welcome(){
        std :: cout << "--------------------------------------------------------\n";
        std :: cout << "Welcome to Faculty Feedback form. Enter Your credentials\n";
        std :: cout << "--------------------------------------------------------\n";
    }
//     It will input Given String between Two Lines
    void box(string line){
        std :: cout << "--------------------------------------------------------\n";
        std :: cout << line << "\n";
        std :: cout << "--------------------------------------------------------\n";
    }
//     Add Extra Lines
    void addLine(){
        std :: cout << "--------------------------------------------------------\n";
    }
};
// Admin Class, Contains all Admin Functions
class Admin: virtual public Design{
    bool isAdmin = false, isLogin = false;
    public:
//     Check if the User is an Admin
    bool validateUser(string username, string password){
        int count=0;
        fstream newFile;
        newFile.open("admin.txt", ios_base :: in);
        string admin;
        if(newFile.is_open()){
            while(getline(newFile, admin)){
                count++;
                if(admin == username)
                    break;
            }
        }
        newFile.close();
        newFile.open("adminPassword.txt", ios_base :: in);
        if(newFile.is_open()){
            string adminPassword;
            while(getline(newFile, adminPassword) && --count){
            }
            if(adminPassword == password && admin == username){
                isAdmin = true;
                isLogin = true;
                return true;
            }
        }
        return false;
    }
// View Feedback Form
    void viewFeedBackForm(){
        fstream newFile;
        newFile.open("questionList.txt", ios_base :: in);
        if(newFile.is_open()){
            string questions;
            Design :: box("These are the Following Questions");
            int i=1;
            while(getline(newFile, questions)){
                std :: cout << i << ". " << questions << "\n";
                i++;
            }
            newFile.close();
            string temp;
            std :: cout << "Enter Any Key To Continue...\n";
            Design :: addLine();
            std :: cin >> temp;
        }
    }
// Add questions in the Feedback Form
    void addQuestion(){
        fstream newFile;
        newFile.open("questionList.txt", ios_base :: app);
        if(newFile.is_open()){
            string question;
            Design :: box("Enter Your Question: ");
            cin.ignore();
            getline(cin, question);
            question += "\n";
            newFile.write(question.data(), question.size());
        }
        Design :: addLine();
        std :: cout << "Question Added Sucessfully\n";
        newFile.close();
    }
    //View Teacher List
    void viewTeacherList(){
        fstream newFile;
        newFile.open("teacherlist.txt", ios :: in);
        if(newFile.is_open()){
            string teacher;
            Design :: box("These are the Following Teachers");
            while(getline(newFile, teacher)){
                std :: cout << teacher << "\n";
            }
        }
        newFile.close();
        string temp;
        std :: cout << "Enter Any Key To Continue...\n";
        Design :: addLine();
        std :: cin >> temp;
    }
// Add Teacher to the List
    void addTeacher(){
        fstream newFile;
        newFile.open("teacherlist.txt", ios_base :: app);
        if(newFile.is_open()){
            string teacher;
            Design :: box("Enter Your Question: ");
            cin.ignore();
            getline(cin, teacher);
            teacher += "\n";
            newFile.write(teacher.data(), teacher.size());
        }
        Design :: addLine();
        std :: cout << "Teacher Added Sucessfully\n";
        newFile.close();
    }

    void exitMainMenu(){
        
    }
};
// Student Class, Contains functions of Admin and As well as User
class Student: public Admin{
    bool isStudent = false, isLogin = false;
    string responses[100];
    int response_count=0;
    public:
    bool validateUser(string username, string password){
        int count=0;
        fstream newFile;
        newFile.open("student.txt", ios_base :: in);
        string student;
        if(newFile.is_open()){
            while(getline(newFile, student)){
                count++;
                if(student == username)
                    break;
            }
        }
        newFile.close();
        newFile.open("studentPassword.txt", ios_base :: in);
        if(newFile.is_open()){
            string studentPassword;
            while(getline(newFile, studentPassword) && --count);
            if(studentPassword == password && student == username){
                isStudent = true;
                isLogin = true;
                return true;
            }
        }
        newFile.close();
        return false;
    }
    
    void fillForm(){
        response_count=0;
        fstream newFile;
        newFile.open("questionList.txt", ios_base :: in);
        if(newFile.is_open()){
            string questions;
            Design :: box("Enter Your Responses");
            int i=1;
            while(getline(newFile, questions)){
                std :: cout << i << ". " << questions << "\n";
                std :: cin >>responses[response_count];
                i++;
                response_count++;
            }
            newFile.close();
            string temp;
            std :: cout << "Enter Any Key To Continue...\n";
            Design :: addLine();
            std :: cin >> temp;
        }
    }

    void viewResponse(){
        fstream newFile;
        newFile.open("questionList.txt", ios_base :: in);
        if(newFile.is_open()){
            string questions;
            Design :: box("Enter Your Responses");
            int i=1;
            while(getline(newFile, questions)){
                std :: cout << i << ". " << questions << "\n";
                std :: cout << responses[i-1] << "\n";
                i++;
            }
            newFile.close();
            string temp;
            std :: cout << "Enter Any Key To Continue...\n";
            Design :: addLine();
            std :: cin >> temp;
        }
    }
};

class Login: private Student, virtual public Design{
    bool isLogin = false, isAdmin = false, isStudent = false;
    string username, password;
    public:

    void authenticate(){

        while(true){
            askInfo();
            isAdmin = Admin :: validateUser(username, password);
            
            if(!isAdmin){
                isStudent = Student :: validateUser(username, password);
            }
            else break;
            
            if(!isStudent){
                Design :: box("Error!!! Incorrect Username or Password");
                continue;
            }
            else break;
        }
        isLogin = true;
        Design :: box("Welcome "+username);
    }
    
    void mainMenu(){
        char input;
        if(isAdmin){
            while(input!='5'){
                Design :: box("Enter Numbers To Select Menu");
                std :: cout << "1. View Feedback Form\n";
                std :: cout << "2. Add a New Question\n";
                std :: cout << "3. View Teachers List\n";
                std :: cout << "4. Add Teacher\n";
                std :: cout << "5. Exit\n";
                Design :: addLine();

                std :: cin >> input;

                switch(input){
                    case '1': viewFeedBackForm();
                            break;
                    case '2': addQuestion();
                            break;
                    case '3': viewTeacherList();
                            break;
                    case '4': addTeacher();
                            break;
                    case '5': exitMainMenu();
                            break;
                    default:std :: cout << "Enter Correct Number Only\n";
                            break;
                }
            }
        }
        else{
            while(input!='5'){
                Design :: box("Enter Numbers to Select Menu");
                std :: cout << "1. View Feedback Form\n";
                std :: cout << "2. Fill feedback Form\n";
                std :: cout << "3. View Teachers List\n";
                std :: cout << "4. View Your Response\n";
                std :: cout << "5. Exit\n";
                Design :: addLine();

                std :: cin >> input;

                switch(input){
                    case '1': viewFeedBackForm();
                            break;
                    case '2': fillForm();
                            break;
                    case '3': viewTeacherList();
                            break;
                    case '4': viewResponse();
                            break;
                    case '5': exitMainMenu();
                            break;
                    default:std :: cout << "Enter Correct Number Only\n";
                            break;
                }

            }
        }
    }
    
    void askInfo(){

        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
    }
};

int main(){
    Login LOGIN;
    LOGIN.welcome();
    LOGIN.authenticate();
    LOGIN.mainMenu();
    return 0;
}

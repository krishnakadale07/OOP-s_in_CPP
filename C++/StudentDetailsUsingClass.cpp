# include <iostream>
using namespace std;

    class students{
    public:
        string name;
        int age;

        void input(){
            cout << " Enter Name : ";
            cin >> name;
            
            cout << " Enter Age :";
            cin >> age;

        }
        void show(){
            cout << "Name : " << name << endl;
            cout << "Age : " << age << endl;
        }
        
    };
    int main(){
        int n;
        cout << "Enter the number of students :";
        cin >> n;
        students* s = new students[n];

        for(int i = 0; i < n; i++){
            cout << "Enter the details of students : " << i + 1 << endl;
            s[i].input();
        }
        cout << "\n------The details of students------ \n";
        for(int i = 0 ; i < n; i++){
            s[i].show();
        }
        delete[] s;
        return 0;
    }
    


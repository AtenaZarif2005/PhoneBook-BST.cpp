#include <iostream>
#include <string>
using namespace std;
//_______________________________________________________
struct Person {
    string name;
    string phone;
    Person* left;
    Person* right;
};
//_______________________________________________________
struct Stack{
    Person *path[100];
    int top;
};
//_______________________________________________________
class PhoneBookBST{
    public:
        Person *root;
        PhoneBookBST(){ root = nullptr;}
        void insert(string name, string phone);
        Person *SearchByName(string name);
        Person *SearchByPhone(string phone);
        void RemoveContact(string name);
        void inorder();
};
//_______________________________________________________
int main(){
    PhoneBookBST phoneBook;
    return 0;
}


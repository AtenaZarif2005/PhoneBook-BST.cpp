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
void PhoneBookBST::insert(string name, string phone){
    if (name == ""){
        cout << "plz enter name: ";
        getline(cin, name);
    }
    if (SearchByName(name)){
        cout << "Name already exists.\n";
        return;
    }
    if (phone == ""){
        cout << "plz enter phone number here: ";
        getline(cin, phone);
    }
    if (SearchByPhone(phone)){
        cout << "Phone already exists.\n"; 
        return;
    }
    Person *newPerson = new Person{name, phone, nullptr, nullptr};
    if (!root){
        root = newPerson;
        cout << "Added as root!\n";
        return;
    }
    Person *current = root;
    Person *parent = nullptr;
    Stack path;
    path.top = -1;
    while (current){
        parent = current;
        path.path[++path.top] = current;
        if (name < current->name)
            current = current->left;
        else
            current = current->right;
    }
    if (name < parent->name)
        parent->left = newPerson;
    else
        parent->right = newPerson;
    cout << "Contact added.\n";
}
//_____________________________________________________________
Person *PhoneBookBST::SearchByName(string name) {
    Person *current = root;
    Stack path;
    path.top = -1;
    while (current != nullptr) {
        path.path[++path.top] = current;
        if (current->name == name) {return current;} 
        else if (name < current->name) {current = current->left;} 
        else {current = current->right;}
    }
    return nullptr;
}
//_______________________________________________________________
Person *PhoneBookBST::SearchByPhone(string phone) {
    if (!root) return nullptr;
    Stack s;
    s.top = -1;
    s.path[++s.top] = root;
    while (s.top != -1) {
        Person* current = s.path[s.top--];
        if (current->phone == phone) return current;
        if (current->right) s.path[++s.top] = current->right;
        if (current->left)  s.path[++s.top] = current->left;
    }
    return nullptr;
}
//_________________________________________________________________
void PhoneBookBST::RemoveContact(string name) {
    if (!root) {
        cout << "Phonebook is empty.\n";
        return;
    }
    Person *current = root;
    Person *parent = nullptr;
    Stack path;
    path.top = -1;
    while (current && current->name != name) {
        parent = current;
        path.path[++path.top] = current;
        if (name < current->name) current = current->left;
        else current = current->right;
    }
    if (!current) {cout << "Contact not found.\n"; return;}
    if (!current->left && !current->right) {
        if (!parent) {root = nullptr;}
        else if (parent->left == current) {parent->left = nullptr;}
        else {parent->right = nullptr;}
        delete current;
        cout << "Contact deleted.\n";
        return;
    }
    if (!current->left || !current->right) {
        Person* child = (current->left) ? current->left : current->right;
        if (!parent) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
        cout << "Contact deleted.\n";
        return;
    Person* succParent = current;
    Person* succ = current->right;
    while (succ->left) {
        succParent = succ;
        succ = succ->left;
    }
    current->name = succ->name;
    current->phone = succ->phone;
    if (succParent->left == succ) succParent->left = succ->right;
    else succParent->right = succ->right;
    delete succ;
    cout << "Contact deleted.\n";
    }
}
//_____________________________________________________________________
void PhoneBookBST::inorder() {
    if (!root) {
        cout << "Phonebook is empty.\n";
        return;
    }
    Stack s;
    s.top = -1;
    Person* current = root;
    while (current || s.top != -1) {
        while (current) {
            s.path[++s.top] = current;
            current = current->left;
        }
        current = s.path[s.top--];
        cout << "Name: " << current->name << ", Phone: " << current->phone << endl;
        current = current->right;
    }
}
//_______________________________________________________________________
int main() {
    PhoneBookBST phoneBook;
    int choice;
    do {
        cout << "\n====== *Phone Book* ======\n";
        cout << "1. Add contact\n";
        cout << "2. Search by name\n";
        cout << "3. Search by phone\n";
        cout << "4. Show sorted list\n";
        cout << "5. Delete contact\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string name, phone;
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone: ";
                getline(cin, phone);
                phoneBook.insert(name, phone);
                cout << "\n*Press Enter to return to menu*";
                cin.get();
                break;
            }
            case 2: {
                string name;
                cout << "Enter name to search: ";
                getline(cin, name);
                Person* result = phoneBook.SearchByName(name);
                if (result)
                    cout << "Found: Name: " << result->name << ", Phone: " << result->phone << endl;
                else
                    cout << "Contact not found.\n";
                cout << "\n*Press Enter to return to menu*";
                cin.get();
                break;
            }
            case 3: {
                string phone;
                cout << "Enter phone to search: ";
                getline(cin, phone);
                Person* result = phoneBook.SearchByPhone(phone);
                if (result)
                    cout << "Found: Name: " << result->name << ", Phone: " << result->phone << endl;
                else
                    cout << "Contact not found.\n";
                cout << "\n*Press Enter to return to menu*";
                cin.get();
                break;
            }
            case 4:
                phoneBook.inorder();
                cout << "\n*Press Enter to return to menu*";
                cin.get();
                break;
            case 5: {
                string name;
                cout << "Enter name to delete: ";
                getline(cin, name);
                phoneBook.RemoveContact(name);

                cout << "\n*Press Enter to return to menu*";
                cin.get();
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                cout << "\n*Press Enter to return to menu*";
                cin.get();
        }
    } while (choice != 0);
    return 0;
}
//________________________________________________________________FINISH______________________________________________________________________//

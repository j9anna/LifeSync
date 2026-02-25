#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <iomanip>
#include<fstream>
#include<sstream>
using namespace std;



class tasknode {
public:
    string title, cate;
    int pri;
    tasknode* next;
    tasknode* prev;
    tasknode(string t = "", string c = "", int p = 0) {
        title = t;
        cate = c;
        pri = p;
        next = NULL;
        prev = NULL;
    }

};

class tasklinkedlist {
private:
    tasknode* head;

public:
    tasklinkedlist() {
        head = nullptr;
    }


    void addtask(string t, string c, int p) {
        tasknode* newNode = new tasknode(t, c, p);

        if (head == NULL || p < head->pri) {
            newNode->next = head;
            if (head != NULL) {
                head->prev = newNode;
            }
            head = newNode;
            return;
        }

        tasknode* curr = head;
        while (curr->next != NULL && curr->next->pri <= p) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        if (curr->next != NULL) {
            curr->next->prev = newNode;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }




    void removetask(string title) {
        if (head == nullptr) {
            cout << "List is empty. Cannot remove task." << endl;
            return;
        }
        if (head->title == title) {
            tasknode* temp = head;
            head = head->next;
            delete temp;
            cout << "Task \"" << title << "\" removed." << endl;
            return;
        }

        tasknode* current = head;
        tasknode* prev = nullptr;
        while (current != nullptr && current->title != title) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Task \"" << title << "\" not found." << endl;
            return;
        }
        prev->next = current->next;
        delete current;
        cout << "Task \"" << title << "\" removed." << endl;
    }
    void searchbytitle(string t) {
        tasknode* ptr = head;

        while (ptr != NULL) {
            if (ptr->title == t) {
                cout << "Title: " << ptr->title << endl << "Category: " << ptr->cate << endl << "Priority: " << ptr->pri << endl;
                return;
            }
            ptr = ptr->next;
        }

        cout << "Task not found" << endl;

    }
    void searchtaskcat(string cate) {
        tasknode* current = head;
        bool found = false;
        cout << " Tasks in Category: " << cate << endl;
        while (current != nullptr) {
            if (current->cate == cate) {
                cout << " - " << current->title << " (Priority: " << current->pri << ")" << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No tasks found in this category." << endl;
        }
    }
    void displaytasks() {
        if (head == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }
        tasknode* current = head;
        cout << "All Tasks : " << endl;
        while (current != nullptr) {
            cout << " - Task:  " << current->title << endl << "  Priority : " << current->pri << endl << "  category" << " [" << current->cate << "]" << endl;
            current = current->next;
        }
    }
    void loadtasksfile(string c) {
        ifstream inputFile(c);
        if (!inputFile.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }
        string line;
        cout << "Loaded: " << endl;
        while (getline(inputFile, line)) {
            if (line.empty()) continue;
            string t, c, pstr;
            int p;
            stringstream ss(line);
            getline(ss, t, ',');       // title
            getline(ss, c, ',');    // category
            getline(ss, pstr);      // priority
            p = stoi(pstr);
            addtask(t, c, p);
            cout << t << endl;
        }
        inputFile.close();
    }
};


class event {
protected:
    string name, desc;
    float time;
public:
    event(string n = " ", string d = " ", float t = 0.0) {
        name = n; desc = d; time = t;
    }

    float getTime() { return time; }
    string getName() { return name; }
    string getDesc() { return desc; }

    friend ostream& operator<<(ostream&, const event&);

};


class AllEvents {
private:
    event* events;
    int capacity;
    int numEvents;
public:
    AllEvents(int num = 0) {
        capacity = 100; 
        numEvents = num; 
        events = new event[capacity];
    }
    ~AllEvents() { delete[] events; }


    //helper functions
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }

    void minHeapify(int i, int s) {
        int l = left(i), r = right(i), smallest = i;
        if (l < s && events[l].getTime() < events[i].getTime()) smallest = l;
        if (r < s && events[r].getTime() < events[smallest].getTime()) smallest = r;
        if (smallest == i) return;
        swap(events[smallest], events[i]);
        minHeapify(smallest, s);
    }

    event removeEvent() { /*remove and return root -- extract min*/
        event temp = events[0]; numEvents--;
        swap(events[0], events[numEvents]);
        minHeapify(0, numEvents-1);
        return temp;
    }
    event getNextEvent() {   /*return root but don't remove*/
        return events[0];
    }


    void addEvent(const event& val) { /*insertFn*/
        int i = numEvents;
        events[i] = val;int p = parent(i); numEvents++;
        while (i > 0 && events[i].getTime() < events[p].getTime()) {
            swap(events[i], events[p]);
            i = p; p = parent(i);
        }


    }
    void displayAllEvents() {
        heapSort();
        for (int i = 0; i < numEvents; i++) {
            cout << events[i] << endl;
        }
    }

    bool isFull() {
        return capacity == numEvents;
    }
    bool isEmpty() {
        return numEvents == 0;
    }

    void heapSort() {
        buildMinHeap();
        for (int i = numEvents - 1; i > 0; i--) {
            swap(events[i], events[0]);
            minHeapify(0, i);
        }
        for (int i = numEvents - 1, j=0; i >= numEvents / 2; j++, i--) {
            swap(events[i], events[j]);
        }
    }

    void buildMinHeap() {
        for (int i = (numEvents / 2) - 1; i >= 0;i--) {
            minHeapify(i, numEvents);
        }
    }
    void loadeventsfile(string c) {
        ifstream inputFile(c);
        if (!inputFile.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }
        string line;
        cout << "Loaded: " << endl;
        while (getline(inputFile, line)) {
            if (line.empty()) continue;
            string t, fstr, d = "";
            float f;
            stringstream ss(line);
            getline(ss, t, ',');       // title
            getline(ss, fstr);      // time
            f = stof(fstr);
            addEvent(event(t, d, f));
        }
        displayAllEvents();
        inputFile.close();
    }

};

ostream& operator<<(ostream& o, const event& e) {
    o << "Title: " << e.name << endl;
    if (e.desc != "") o << "Description: " << e.desc << endl;
    o << "Time: " << fixed << setprecision(2) <<e.time << endl;
    return o;
}

template <class T>
bool inputValidation(T start, T endd, T val) {
    return val >= start && val <= endd;
}




class Stack
{
    list<string> l;
public:

    void clearStack() {
        l.clear();
    }

    bool isEmpty() {
        return l.empty();
    }

    string top() {
        if (l.empty()) { return ""; }
        return l.back();
    }

    string pop() {
        if (l.empty()) { return ""; }
        string elem = l.back();
        l.pop_back();
        return elem;
    }

    void push(string elem)
    {
        l.push_back(elem);
    }
};


class note {
private:
    string title;
    string content;
    Stack prevC;
public:
    note() {
        title = "";
        content = "";
    }

    note(string t, string c) {
        title = t;
        content = c;
    }

    void update(string c) {
        prevC.push(content);
        content = c;
    }

    bool undo() {
        if (prevC.isEmpty()) {
            cout << "No previous note version." << endl;
            return false;
        }
        content = prevC.pop();
        return true;
    }

    string getTitle() {
        return title;
    }

    void viewTitle() {
        cout << title << endl;
    }

    void viewContent() {
        cout << content << endl;
    }
};

class notes {
private:
    note l[101];
    int elem;
public:
    notes() {
        for (int i = 0; i < 101; i++) {
            l[i] = note();
        }
        elem = 0;
    }

    int hashValue(const string& t) {
        int sum = 0;
        for (char ch : t) {
            sum += ch;
        }
        return sum % 101;
    }

    void insertNote(string t, string c) {
        int value = hashValue(t);
        for (int i = 0; i < 101; i++) {
            if (l[(value + (i * i)) % 101].getTitle() == "") {
                l[(value + (i * i)) % 101] = note(t, c);
                cout << "Note \"" << t << "\"added." << endl;
                elem++;
                return;
            }
        }
    }

    void displayNotes() {
        for (int i = 0; i < 101; i++) {
            if (l[i].getTitle() == "") {
                continue;
            }
            cout << "Title:  ";
            l[i].viewTitle();
            cout << "Content:  ";
            l[i].viewContent();
        }
    }

    void updateNote(string t, string uc) {
        int value = hashValue(t);
        for (int i = 0; i < 101; i++) {
            if (l[(value + (i * i)) % 101].getTitle() == t) {
                l[(value + (i * i)) % 101].update(uc);
                cout << "Note \"" << t << "\" updated." << endl;
            }
        }
    }

    void undoUpdate(string t) {
        bool result;
        int value = hashValue(t);
        for (int i = 0; i < 101; i++) {
            if (l[(value + (i * i)) % 101].getTitle() == t) {
                result = l[(value + (i * i)) % 101].undo();
                if (result) cout << "update removed." << endl;
            }
        }
    }

    bool titleCheck(string t) {
        int value = hashValue(t);
        for (int i = 0; i < 101;i++) {
            if (l[(value + (i * i)) % 101].getTitle() == t) {
                return true;
            }
        }
        return false;
    }

    bool isEmptyN() {
        if (elem == 0)return true;
        return false;
    }

    bool isFullN() {
        if (elem == 101) {
            cout << "New note can not be added , Storage is full." << endl;
            return true;
        }
        return false;
    }


    void loadnotesfile(string c) {
        ifstream inputFile(c);
        if (!inputFile.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }
        string line;
        cout << "Loaded: " <<endl;
        while (getline(inputFile, line)) {
            if (line.empty()) continue;
            string t, c;
            float f;
            stringstream ss(line);
            getline(ss, t, ',');       // title
            getline(ss, c);      // content
            insertNote(t, c);
        }
        inputFile.close();
    }

};



int main()
{
    notes n;  AllEvents Events;  tasklinkedlist x;
    cout << "Welcome To LifeSync!" << endl << "Please enter your name: ";
    string name; getline(cin, name);
    cout << "Hello " << name << endl;
    bool l = true;
    while (l) {
        cout << "Choose the section you'd like to go to" << endl;
        cout << "1. Tasks" << endl << "2. Events" << endl << "3. Notes" << endl << "4. Exit LifeSync" << endl;
        int optn;
        cin >> optn;
        while (cin.fail() || !inputValidation(1, 4, optn)) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Invalid Input, Enter a number between 1 - 4: ";
            cin >> optn;
        }
        switch (optn) {
        case 1: {
            bool loop = true;
            while (loop) {
                int ch;
                cout << "Choose Operation: " << endl;
                cout << "1. Add a task" <<
                    endl << "2. Remove a task" <<
                    endl << "3. Search by title" <<
                    endl << "4. Search by category" <<
                    endl << "5. Display all tasks" <<
                    endl << "6. Read tasks from file" <<
                    endl << "7. Exit tasks" << endl;
                cin >> ch;
                while (cin.fail() || !inputValidation(1, 7, ch)) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cout << "Invalid Input, Enter a number between 1 - 6: ";
                    cin >> ch;
                }

                switch (ch) {
                case 1: {
                    string t; string c; int p;cin.ignore();
                    cout << "Enter title: " << endl; getline(cin, t);cout << endl;
                    cout << "Enter category: " << endl; getline(cin, c);cout << endl;
                    cout << "Enter priority: " << endl;
                    cin >> p;cout << endl;
                    x.addtask(t, c, p);
                    break;

                }
                case 2: {
                    string t; string c; int p;cin.ignore();
                    cout << "Enter title: " << endl; getline(cin, t);cout << endl;
                    x.removetask(t);
                    break;
                }
                case 3: {
                    string t; string c; int p;cin.ignore();
                    cout << "Enter title: " << endl; getline(cin, t);cout << endl;
                    x.searchbytitle(t);
                    break;
                }
                case 4: {
                    string t; string c; int p;cin.ignore();
                    cout << "Enter category: " << endl; getline(cin, c);cout << endl;
                    x.searchtaskcat(c);
                    break;
                }
                case 5: {
                    x.displaytasks();
                    break;
                }
                case 6: {
                    string n;cin.ignore();
                    cout << "Enter file name : " << endl; getline(cin, n);cout << endl;
                    x.loadtasksfile(n);
                    
                }
                case 7: {
                    loop = false;
                    break;
                }
                }
            }
            break;
        }


        case 2: {

            int ch; bool cont = true;
            while (cont) {
                cout << "Enter Number Of Operation You'd like to complete: " << endl
                    << "1. Add Event" << endl 
                    << "2. Show Next Event" << endl
                    << "3. Remove Closest Event" << endl 
                    << "4. Display All Saved Events" << endl
                    << "5. Read events from a file" << endl 
                    << "6. Exit" << endl;

                cin >> ch;
                while (cin.fail() || !inputValidation(1, 6, ch)) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cout << "Invalid Input, Enter a number between 1 - 6: ";
                    cin >> ch;
                }


                switch (ch) {
                case 1: { //add an event
                    if (Events.isFull()) {
                        cout << "Your events are full, remove an event to add a new one!" << endl;
                        break;
                    }
                    string n, d; float t; cin.ignore();
                    cout << "Name of Event: "; getline(cin, n); cout << endl;
                    cout << "Description of Event: "; getline(cin, d); cout << endl;
                    cout << "Time of Event (enter in 24h format HH.MM): "; cin >> t; cout << endl;
                    int x = t; float y = t - x;
                    while (!inputValidation<int>(0, 23, x)||!inputValidation<float>(0.00, 0.59, y)) {
                        cout << "Please enter a valid time in 24h format HH.MM: ";
                        cin >> t; x = t; y = t - x;
                    }
                    event e(n, d, t);
                    Events.addEvent(e);
                    break;
                }
                case 2: { //display next event
                    if (Events.isEmpty()) {
                        cout << "You don't have any saved events!" << endl;
                        break;
                    }
                    cout << "Your next Event: " << endl << Events.getNextEvent();
                    break;
                }
                case 3: { //display next event and remove it
                    if (Events.isEmpty()) {
                        cout << "You don't have any saved events!" << endl; 
                        break;
                    }
                    event temp = Events.removeEvent();
                    cout << "Successfully Removed!" << endl;
                    cout << temp;
                    break;
                }
                case 4: { //display all events
                    if (Events.isEmpty()) {
                        cout << "You don't have any saved events!" << endl; 
                        break;
                    }
                    cout << "Your Events: " << endl;
                    Events.displayAllEvents();
                    break;
                }
                case 5: {
                    string n;cin.ignore();
                    cout << "Enter file name : " << endl; getline(cin, n);cout << endl;
                    Events.loadeventsfile(n);
                    
                }
                case 6: {
                    cont = false; break;
                }
                }

            }
            break;
        }

        case 3: {
            bool loop = true;
            int chn;
            while (loop) {
                cout << "Choose the Operation you want: " << endl;
                cout << "1. Add a note" <<
                    endl << "2. Update a note" <<
                    endl << "3. Undo an update" <<
                    endl << "4. Display all notes" <<
                    endl << "5. Read files from notes" <<
                    endl << "6. Exit notes" << endl;
                cin >> chn;
                while (cin.fail() || !inputValidation(1, 6, chn)) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cout << "Invalid Input, Enter a number between 1 - 6: " << endl;
                    cin >> chn;
                }

                switch (chn) {
                case 1: {
                    if (n.isFullN()) { break; }
                    string title;cin.ignore();
                    cout << "Enter a title for your note: " << endl;
                    getline(cin, title);
                    while (n.titleCheck(title)) {
                        cout << "A note with this title already exists, Enter another title." << endl;
                        getline(cin, title);
                    }
                    string content;
                    cout << "Enter the content of your note :" << endl;
                    getline(cin, content);
                    n.insertNote(title, content);
                    break;
                }

                case 2: {
                    if (n.isEmptyN()) {
                        cout << "You have no notes to update." << endl;
                        break;
                    }
                    string title;cin.ignore();
                    cout << "Enter a title for the note you want to update: ";
                    getline(cin, title);
                    if (!n.titleCheck(title)) {
                        cout << "This note does not exist." << endl;
                        break;
                    }
                    string content;
                    cout << "Enter the content of your note : ";
                    getline(cin, content);
                    n.updateNote(title, content);
                    break;
                }

                case 3: {
                    if (n.isEmptyN()) {
                        cout << "You have no notes to undo their update." << endl;
                        break;
                    }
                    string title;cin.ignore();
                    cout << "Enter a title for the note you want to undo its update: ";
                    getline(cin, title);
                    if (!n.titleCheck(title)) {
                        cout << "This note does not exist." << endl;
                        break;
                    }
                    n.undoUpdate(title);
                    break;
                }

                case 4: {
                    if (n.isEmptyN()) {
                        cout << "You have no notes to display." << endl;
                        break;
                    }
                    n.displayNotes();
                    break;
                }

                case 5: {
                    string c;cin.ignore();
                    cout << "Enter file name : " << endl; getline(cin, c);cout << endl;
                    n.loadnotesfile(c);
                }

                case 6: {
                    loop = false;
                    break;
                }
                }
            } break;
        }

        case 4: {
            cout << "We are sad to see you go :(" << endl << "See you next time " << name << endl;
            l = false;
        }
        }
    }

    return 0;
}
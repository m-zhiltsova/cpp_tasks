#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// You have asked me to add linked list for map sorting. I just add current element from the map to the linked list in needed order and get a sorted linked list.

struct Node {
    string word;
    int fre;
    Node* next;

    Node(string word, int fre, Node* next) : word(word), fre(fre), next(next) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void append(string word, int value) {
        if (!head) {
            head = new Node(word, value, nullptr);
            return;
        }
        Node* prev = nullptr;
        Node* current = head;

        while ((current->fre > value) && (current->next)){
            prev = current;
            current = current->next;
        }
        if (prev == nullptr) {
            Node* nw = new Node(word, value, current);
            head = nw;
        }
        else {
            Node* nw = new Node(word, value, current);
            prev->next = nw;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc > 3) {
        cout << "Too much arguments" << endl;
        return 0;
    }
    else if (argc < 3) {
        cout << "Too little arguments" << endl;
        return 0; 
    }
    
    // reading from file
    
    ifstream in(argv[1]);
    string line;
    map <string, int> m;
    int i,n;
    string word = "";
    int num = 0;

    if (in.is_open()) {
       while (getline(in, line)) {
         i = 0;
         n = line.length();
         while (i != n) {
             if ((('a' <= line[i]) && (line[i]  <= 'z')) 
                         || (('A' <= line[i]) && (line[i] <= 'Z'))
                         || (('0' <= line[i]) && (line[i] <= '9'))) {
                         word += line[i];
                         }
             else if (word != "" && m.find(word) == m.end()) {
                     m[word] = 1;
                     word = "";
                     num += 1;
             }
             else if (word != ""){
                     m[word] += 1;
                     word = "";
                     num += 1;
             }
             i += 1;
         }
         if (word != "" && m.find(word) == m.end()) {
             m[word] = 1;
             word = "";
             num += 1;
         }
         else if (word != ""){
             m[word] += 1;
             word = "";
             num += 1;
         }
       }
    }
    in.close();

    // add from map to sorted linked list 
    
    LinkedList ll = LinkedList();
    
    for (auto [first, second] : m) {
        ll.append(first, second);
    }

    // writing to csv file

    ofstream out;
    out.open(argv[2]);
    
    if (out.is_open()) {
         Node* current = ll.head;
         while (current) {
            out << current->word << "," << current->fre << "," << (current->fre / float(num) * 100) << "%" << endl;
            current = current->next;
        }
    }
    out.close();
}

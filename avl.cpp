#include <iostream>
#include "Tree.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
vector<string> extract(string line);
void printRange(Tree t, string s);
void printRangeHelper(vector<pair<int, int>> s, string n);



int main(int argc, char* argv[]) {
    ifstream inFIle;
    string filename = argv[1];
    //string f = filename.substr(16, filename.length()-16);
    inFIle.open(filename);
    Tree t;

    if(!inFIle){
        cout << "failed" << endl;
    }
    for(string line; getline(inFIle, line);){
        vector<string> elements = extract(line);
        if(elements.size() >= 1){
            if(elements[0] == "insert"){
                //cout << "f" << endl;
                elements.erase(elements.begin());
                for(size_t i = 0; i < elements.size(); i++){
                    t.insert(stoi(elements[i]));
                    //cout << elements[i] << endl;

                }
                //t.reset();
                t.getThree();
                cout << endl;
                t.reset();
            }
            else if(elements[0] == "lookup"){
                elements.erase(elements.begin());
                for(size_t i = 0; i < elements.size(); i++){
                    t.lookUp(stoi(elements[i]));
                
                }
                t.getLookUpThree();
                cout << endl;
                t.reset();
            }
            else if(elements[0] == "print"){
                if(elements[1] == "tree"){
                    t.printTree();
                    cout << endl;
                }
                else
                   printRange(t, elements[1]);
            }
        }
    }
    return 0;
}

vector<string> extract(string line){
    string temp;
    vector<string> elements;
    istringstream stringLine(line);
    while(getline(stringLine, temp, ' ')){
        elements.push_back(temp);
    }
    return elements;
}
void printRangeHelper(vector<pair<int, int>> s, string n){
    if(s.size() == 0){
        cout << "No inserts would cause a " << n << " rotation." << endl << endl;
        return;
    }
    cout << "The following inserts would cause a " << n << " rotation:" << endl;

    for(size_t i = 0; i < s.size(); i++){
        pair<int, int> range = s[i];
        if(i != 0)
            cout << ", ";
        if(range.first == range.second)
            cout << range.first << endl;
        else
            cout << range.first << " to " << range.second << endl;
    }
    cout << endl;
}

void printRange(Tree t, string s){
    vector<pair<int, int>> ll;
    vector<pair<int, int>> lr;
    vector<pair<int, int>> rl;
    vector<pair<int, int>> rr;
    t.findRotation(ll, lr, rl, rr);
    if(s == "left-left")
        printRangeHelper(ll, s);
    else if(s =="left-right")
        printRangeHelper(lr, s);
    else if(s == "right-left")
        printRangeHelper(rl, s);
    else if(s == "right-right")
        printRangeHelper(rr, s);
}



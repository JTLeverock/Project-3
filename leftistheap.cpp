#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


// node structure
class Node{
    public:
        int key; // cases, in this scenario
        Node *left;
        Node *right;
        int svalue;

        int day;
        int month;
        int year;
        string country;
        string code;
        string continent;
        int deaths;
        int population;
        int rate;

        // constructor
        Node(int _day, int _month, int _year, 
        string _country, string _code, string _continent, 
        int _cases, int _deaths, int _population, int _rate, 
        Node *_left = nullptr, Node *_right = nullptr, int _svalue = 0){

            this->key = _cases;
            right = _right;
            left = _left,
            svalue =  _svalue;

            day = _day;
            month = _month;
            year = _year;
            country = _country;
            code = _code;
            continent = _continent;
            deaths = _deaths;
            population = _population;
            rate = _rate;
            
    }

};


class LeftistHeap{
    public:
        LeftistHeap();
        ~LeftistHeap();
        void delete_helper(Node *del);

        void Insert(int _day, int _month, int _year, 
        string _country, string _code, string _continent, 
        int _cases, int _deaths, int _population, int _rate);

        Node *Merge(Node *node1, Node *node2);
        int extractMax();
        Node *root;
        void PrintCountries(int n); 
};
 
// constructor
LeftistHeap::LeftistHeap(){
    root = nullptr;
}
 
// destructor - calls helper method
LeftistHeap::~LeftistHeap(){
    delete_helper(root);
}

// move through the tree and delete each node recursively
void LeftistHeap::delete_helper(Node *del){
    if (del == nullptr){
        return;
    }
    delete_helper(del->left);
    delete_helper(del->right);
    delete del;
}
 
 
// the primary function of the leftist heap, 
Node *LeftistHeap::Merge(Node * node1, Node * node2){

    // if either input is null, then result is that node
    if (node1 == nullptr)
        return node2;
    if (node2 == nullptr)
        return node1;

    // if node1 smaller than node2
    if (node1->key > node2->key){
        
        // if nothing on left subtree, add node2
        if (node1->left == nullptr)
            node1->left = node2;

        else{ // else add onto right subtree
            node1->right = Merge(node1->right, node2);

            // // if sval left < sval right --> no longer leftist tree, fix
            if (node1->left->svalue < node1->right->svalue){
                Node *tmp = node1->left;
                node1->left = node1->right;
                node1->right = tmp;
            }
            node1->svalue = node1->right->svalue + 1; //sval++
        }

        return node1;
    }

    
    else{ // node2->key < node1->key
        if (node2->left == nullptr)
            node2->left = node1;
        else
        {
            node2->right = Merge(node2->right, node1);

            // if sval left < sval right --> no longer leftist tree, fix
            if (node2->left->svalue < node2->right->svalue){
                Node *tmp = node2->left;
                node2->left = node2->right;
                node2->right = tmp;
            }
            node2->svalue = node2->right->svalue + 1; //sval++
        }

        return node2;
    }
}
 
 
// insert nodes, runs merge function
void LeftistHeap::Insert(int _day, int _month, int _year, 
    string _country, string _code, string _continent, 
    int _cases, int _deaths, int _population, int _rate)
{

    Node* temp = new Node(_day, _month, _year, _country,
    _code, _continent, _cases, _deaths, _population, _rate);

    root = Merge(temp, root);
}
 
// find min value, remove from tree and return
int LeftistHeap::extractMax(){

    // if empty heap return -1
    if (root == nullptr){
        return -1;
    }

    // get current min, then replace root with Merge of left and right branch
    int min = root->key;
    Node *temp = root;
    root = Merge(root->left, root->right);
    delete temp;
    return min;
}

// funciton to print top 50 countries by total case count
void LeftistHeap::PrintCountries(int n){
    cout << "Top "<< n << " Highest Case/Death Counts by Country: " << endl;
    for (int i=0; i<n; i++){
        cout << i+1 << ": " << root->month << "/" << root->day << "/" << root->year << " " << root->country << ": Cases: " << root->key << " Deaths: " << root->deaths << endl;
        extractMax();
    }
}




int main() {

    clock_t time;

    LeftistHeap heap;

    string line, day, month, year, country, code, continent, cases, deaths, population, rate = "";

    int _day, _month, _year, _cases, _deaths, _population = 0;
    
    float _rate;

    int count = 0;

    ifstream file;
    file.open("covid.csv");

    getline(file, line);

    while(count != 53629) {

        getline(file, day, ',');        
        day = day.substr(1, day.size() - 2);
        _day = stoi(day);

        getline(file, month, ',');
        month = month.substr(1, month.size() - 2);
        _month = stoi(month);

        getline(file, year, ',');
        year = year.substr(1, year.size() - 2);
        _year = stoi(year);

        getline(file, cases, ',');
        cases = cases.substr(1, cases.size() - 2);
        _cases = stoi(cases);

        getline(file, deaths, ',');
        deaths = deaths.substr(1, deaths.size() - 2);
        _deaths = stoi(deaths);

        getline(file, country, ',');
        if (country == "\"Bonaire")
        {
            getline(file, country, ',');
            country = "Bonaire, Saint Eustatius and Saba";
        }
        else 
        {
        country = country.substr(1, country.size() - 2);
        }

        getline(file, code, ',');
        code = code.substr(1, code.size() - 2);

        getline(file, population, ',');
        population = population.substr(1, population.size() - 2);
        _population = stoi(population);

        getline(file, continent, ',');
        continent = continent.substr(1, continent.size() - 2);

        getline(file, rate);
        rate = rate.substr(1, rate.size() - 2);
        _rate = stof(rate);

        heap.Insert(_day, _month, _year, country, code, continent, _cases, _deaths, _population, _rate);

        count++;
    }
    
    heap.PrintCountries(100);

    time = clock() - time;

    cout << "Time to run program: ." << time << " seconds" << endl;

    return 0;

}
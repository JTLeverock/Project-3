#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Node {
    private:
    int day; // 1 - 31
    int month; // 1 - 12
    int year; // 2019 - 2020
    int cases;
    int deaths;
    string country;
    string countrycode;
    int population;
    string continent;
    float rate;

    public:
    Node() {
        this->day = 0; this->month = 0; this->year = 0; this->cases = 0; this->deaths = 0; this->country = "", this->countrycode = ""; this->population = 0; this->continent = ""; this->rate = 0.0;
    }
    Node(int da, int m, int y, int ca, int de, string co, string coco, int p, string con, float r) {
        this->day = da; this->month = m; this->year = y; this->cases = ca; this->deaths = de; this->country = co, this->countrycode = coco; this->population = p; this->continent = con; this->rate = r;
    }
    int getCases() { return cases; }
    int getDeaths() { return deaths; }
    string getCountry() { return country; }
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }
};

class MaxHeap {
    private:
    vector<Node> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);
    
    public:
    void insert(int day, int month, int year, int cases, int deaths, string country, string countrycode, int population, string continent, float rate);
    Node extractMax();
    void printCases();
};

void MaxHeap::heapifyDown(int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;
    if (l < heap.size() && heap[l].getCases() > heap[max].getCases()) {
        max = l;
    }
    if (r < heap.size() &&  heap[r].getCases() > heap[max].getCases()) {
        max = r;
    }
    if (max != i) {
        swap(heap[i], heap[max]);
        heapifyDown(max);
    }
}

void MaxHeap::heapifyUp(int i) {
    int p = (i - 1) / 2;
    if (p >= 0 && heap[i].getCases() > heap[p].getCases()) {
        swap(heap[i], heap[p]);
        heapifyUp(p);
    }
}

Node MaxHeap::extractMax() {
    Node max = heap[0];
    Node t = heap.back();
    heap[0] = t;
    heap.pop_back();
    heapifyDown(0);
    return max;
}

void MaxHeap::insert(int day, int month, int year, int cases, int deaths, string country, string countrycode, int population, string continent, float rate) {
    heap.push_back(Node(day, month, year, cases, deaths, country, countrycode, population, continent, rate));
    heapifyUp(heap.size() - 1);
}

void MaxHeap::printCases() { // prints 100 highest cases
    cout << "Top 100 Highest Case/Death Counts by Country:" << endl;
    int count = 0;
    while (count < 100)
    {
        cout << count + 1 << ". " << heap[0].getMonth() << "/" << heap[0].getDay() << "/" << heap[0].getYear() << " " << heap[0].getCountry() << " Cases:" << heap[0].getCases() << " Deaths:" << heap[0].getDeaths() << endl;
        extractMax();
        count++;
    }
    
}

int main() {

    clock_t time;
    time = clock();

    MaxHeap heap;

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

        //cout << count << " " << day << " " << month << " " << year << " " << cases << " " << deaths << " " << country << " " << code << " " << population << " " << continent << " " << rate << endl;
        heap.insert(_day, _month, _year, _cases, _deaths, country, code, _population, continent, _rate);
        count++;
        
    }
    
    heap.printCases();

    time = clock() - time;

    cout << "Time to run program: " << "." << time << " seconds";

    return 0;

}
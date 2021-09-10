
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>

using namespace std;

class AdjacencyList {
private:
    map<string, vector<pair<string, float>>> maps;
    map<string, vector<pair<string, float>>> fromAtoB;
    map<string, float> pfList;
    int counts;
public:
    void pushPage(string from, string to);
    void PageRank(int n);
    void setPFList();
    AdjacencyList();
};


AdjacencyList::AdjacencyList() {
    counts = 0;
    maps;
    fromAtoB;
    pfList;
}

//Function maps out the graph. Sets paired values to 1. Pushes in "from" and "to" into the graph to include all vertices.
void AdjacencyList::pushPage(string from, string to) {
    if (maps.find(to) == maps.end()) {
        vector<pair<string, float>> temp;
        temp.push_back(make_pair(from, 1));
        maps.emplace(to, temp);
        counts++;
    }
    else {
        maps.at(to).push_back(make_pair(from, 1));
    }

    if (maps.find(from) == maps.end()) {
        vector<pair<string, float>> temp1;
        maps.emplace(from, temp1);
        counts++;
    }

    if (fromAtoB.find(from) == fromAtoB.end()) {
        vector<pair<string, float>> temp;
        temp.push_back(make_pair(to, 1));
        fromAtoB.emplace(from, temp);
    }
    else {
        fromAtoB.at(from).push_back(make_pair(to, 1));
    }
    if (fromAtoB.find(to) == fromAtoB.end()) {
        vector<pair<string, float>> temp1;
        fromAtoB.emplace(to, temp1);
    }
}

//Function prints the PageRank of all pages afater p power iterations in ascending alphabetical order of webpages and rounding rank to two decimal places.
void AdjacencyList::PageRank(int n) {
    map<string, float> temp;

    for (int k = 0; k < n-1; k++) {
        temp = pfList;
        map<string, vector<pair<string, float>>>::iterator it = maps.begin();

        while (it != maps.end()) {
            float sum = 0;
            for (int i = 0; i < it->second.size(); i++) {
                sum += it->second.at(i).second *pfList.at(it->second.at(i).first);
            }
            temp.at(it->first) = sum;
            it++;
        }
        pfList = temp;
    }

    map<string, float>::iterator it1 = pfList.begin();
    while (it1 != pfList.end()) {
        cout << fixed << std::setprecision(2) << it1->first << " "  <<it1->second<<endl;
        it1++;
    }
    
}


//Function sets the initial r(0) value of adjacency list. 1/counts_of_vertices. Sets the M (matrix?) value to 1/counts_of_inputs.
void AdjacencyList::setPFList() {
    map<string, vector<pair<string, float>>>::iterator it = maps.begin();
    while (it != maps.end()) {

        pfList.emplace(it->first,(float)1 / counts);
            for (int i = 0; i < it->second.size(); i++) {
                it->second.at(i).second = (float)1 / fromAtoB.at(it->second.at(i).first).size();         //Sets 1/number_of_out_vertices
            }
        it++;
    }
  
}

int main()
{
    AdjacencyList ans;
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    for (int i = 0; i < no_of_lines; i++) {
        cin >> from;
        cin >> to;
        ans.pushPage(from, to);
    }
    ans.setPFList();
    ans.PageRank(power_iterations);

}


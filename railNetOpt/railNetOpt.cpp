// railNetOpt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include< cstdlib >
using namespace std;

struct Station 
{
    int id;
    string name;
    vector<pair<int, int>>neighbors; //destination and distance
};

void generateMap(vector<Station>& railwayNetwork, int numberOfStations) 
{
    for (int i = 0; i < numberOfStations; i++) {
        railwayNetwork[i].id = i;
        cout << "Enter station name: " << endl;
        string name;
        cin >> name;
        railwayNetwork[i].name = name;
        int numNiegh;
        cout << endl << "Enter number of neighbours: " << endl;
        cin >> numNiegh;
        for (int j = 0; j < numNiegh; j++) {
            int dist, neig;
            cout << "Enter distance and neighbour id: " << endl;
            cin >> dist;
            cin >> neig;
            railwayNetwork[i].neighbors.push_back(make_pair(dist, neig));
        }//for-2 loop
    }//for-1 loop
}

void djikstraAlgo(vector<Station>& railwayNetwork, int source, int destination)
{
    int numStation = railwayNetwork.size();
    vector<int> distance(numStation);
    vector<int>previous(numStation, -1);

    //store infinity in distance
    for (int i = 0; i < numStation; i++) distance[i] = INT_MAX;

    set<pair<int, int>> s;

    //to reach source to source it will take 0 distance only
    distance[source] = 0;

    //add it in set, distance to reach from source to source
    s.insert(make_pair(0, source));

    while (!s.empty())
    {
        // the * helps to return the value of first element in the set, if not * than the pointin iterator or address.
        auto top = *(s.begin());

        int currDist = top.first;
        int currStation = top.second;

        s.erase(s.begin());

        //traverse neighbour of top node
        for (int i = 0; i < numStation; i++)
        {
            if (currStation == railwayNetwork[i].id) 
            {
                for (auto neighbor: railwayNetwork[i].neighbors) 
                {
                    if (currDist + neighbor.first < distance[neighbor.second]) {
                        s.erase({ distance[neighbor.second], neighbor.second });
                        distance[neighbor.second] = currDist + neighbor.first;
                        previous[neighbor.second] = currStation;
                        s.insert({ distance[neighbor.second], neighbor.second });
                    }
                }
                break;
            } //if end
        }//for ends
    }//while ends
    cout << endl << endl;

    if (distance[destination] == INT_MAX) {
        cout << "No path from " << source << " to " << destination << " exists." << endl;
    }
    else {
        cout << "Shortest path from " << source << " to " << destination << " is: " << endl << endl;
        int current = destination;
        vector<int> path;
        while (current != -1) {
            path.push_back(current);
            current = previous[current];
        }
        for (int i = path.size() - 1; i >= 0; --i) {
            if (i != path.size() - 1)
                cout << " -> ";
            cout << railwayNetwork[path[i]].name;
        }
        cout << endl << endl;
        cout << "Total distance: " << distance[destination] << endl;
    }// else end

}//function ends

int main()
{
    cout << "Railway Network OPtimization: \n";
    int numberOfStations = 10;
    vector <Station> railwayNetwork(numberOfStations);

    //call generateMap() to fill railway network or define manually 
    // generateMap(railwayNetwork, numberOfStations);
    
    vector<string>stationNames = { "CSMT", "churchgate", "Mumbai Central", "Dadar", "Vadala", "Kurla", "Bandra", "Borivali", "Thane", "Vashi" };

    for (int i = 0; i < numberOfStations; i++) {
        railwayNetwork[i].id = i;
        railwayNetwork[i].name = stationNames[i];
    }

    railwayNetwork[0].neighbors = { {10, 3}, {9, 4} };
    railwayNetwork[1].neighbors = { {5, 2} };
    railwayNetwork[2].neighbors = { {7, 3}, {5, 1} };
    railwayNetwork[3].neighbors = { {10, 0}, {7 ,2}, {8, 5}, {7, 6} };
    railwayNetwork[4].neighbors = { {9, 0}, {8, 5}, {8, 6} };
    railwayNetwork[5].neighbors = { {8, 3}, {8, 4}, {21, 8}, {26, 9} };
    railwayNetwork[6].neighbors = { {7, 3}, {8, 4}, {20, 7} };
    railwayNetwork[7].neighbors = { {20, 6} };
    railwayNetwork[8].neighbors = { {21, 5} };
    railwayNetwork[9].neighbors = { {26, 5} };


    //MARK: printing Adjacency list
    /*
    for (int i = 0; i < numberOfStations; i++) {

        cout << endl << "ID: " << railwayNetwork[i].id << " Name: " << railwayNetwork[i].name << endl;
        int n = railwayNetwork[i].neighbors.size();
        cout << "number of neighbours: " << n << endl;

        for (int j = 0; j < n; j++) {
            cout <<"{ " << railwayNetwork[i].neighbors[j].first << " " << railwayNetwork[i].neighbors[j].second <<"} " << ", ";
        }//for-2
    }//for-1
    */
    cout << endl;
    int source;
    cout << "Please enter source: ";
    cin >> source;

    int destination;
    cout << "Please enter your destination: ";
    cin >> destination;

    djikstraAlgo(railwayNetwork, source, destination);
    
}



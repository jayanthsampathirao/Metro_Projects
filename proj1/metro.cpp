#include <iostream>
#include <unordered_map>
#include <queue>
#include <limits>
using namespace std ;

// Structure to represent a station in the metro graph
struct Station {
    std::string name;
    std::unordered_map<Station*, int> neighbors;
    int distance;
    Station* previous;

    Station(const std::string& stationName) : name(stationName), distance(std::numeric_limits<int>::max()), previous(nullptr) {}

    void addNeighbor(Station* neighbor, int distance) {
        neighbors[neighbor] = distance;
    }
};

// Function to add an edge between two stations
void addEdge(Station* station1, Station* station2, int distance) {
    station1->addNeighbor(station2, distance);
    station2->addNeighbor(station1, distance);
}

// Function to perform Dijkstra's algorithm
void dijkstra(Station* source) {
    source->distance = 0;
    std::priority_queue<std::pair<int, Station*>, std::vector<std::pair<int, Station*>>, std::greater<std::pair<int, Station*>>> pq;
    pq.push(std::make_pair(0, source));

    while (!pq.empty()) {
        Station* currentStation = pq.top().second;
        pq.pop();

        for (const auto& neighbor : currentStation->neighbors) {
            Station* adjacentStation = neighbor.first;
            int weight = neighbor.second;
            int distance = currentStation->distance + weight;

            if (distance < adjacentStation->distance) {
                adjacentStation->distance = distance;
                adjacentStation->previous = currentStation;
                pq.push(std::make_pair(distance, adjacentStation));
            }
        }
    }
}

// Function to print the shortest path and fare amount between two stations
void printShortestPath(Station* destination) {
    std::cout << "Shortest path from Chennai Central to " << destination->name << ":\n";
    Station* currentStation = destination;
    std::vector<std::string> path;
    int fareAmount = 0;

    while (currentStation) {
        path.push_back(currentStation->name);
        fareAmount += 10;
        currentStation = currentStation->previous;
    }

    std::cout << "Stations: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i != 0) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nTotal Fare: $" << fareAmount << std::endl;
}

int main() {
    // Create stations
    Station thiruvottiyur("Thiruvottiyur");
    Station waherman("Waherman Metro");
    Station mannadi("Mannadi");
    Station highcourt("High Court");
    Station governament("Government Estate");
    Station lic("LIC");
    Station thousand_lights("Thousand Lights");
    Station ag_dms("AG-DMS");
    Station teynampet("Teynampet");
    Station nandanam("Nandanam");
    Station saidapet("Saidapet Metro");
    Station little_mount("Little Mount");
    Station guindy("Guindy Metro");
    Station egmore("Egmore Metro");
    Station nehru_park("Nehru Park");
    Station kilpauk("Kilpauk");
    Station shenoy_nagar("Shenoy Nagar");
    Station anna_nagar_east("Anna Nagar East");
    Station anna_nagar_tower("Anna Nagar Tower");
    Station thirumangalam("Thirumangalam");
    Station koyambedu("Koyambedu");
    Station cmbt("CMBT");
    Station arumbakkam("Arumbakkam");
    Station vadapalani("Vadapalani");
    Station ashok_nagar("Ashok Nagar");
    Station ekkattuthangal("Ekkattuthangal");
    Station st_thomas_metro("St. Thomas Metro");
    Station nanganallur_road("Nanganallur Road");
    Station menambakkam("Menambakkam Metro");
    Station airport("Airport");
    Station chennai_central("Chennai Central");
    Station alandur("Alandur");

    // Add edges between stations
    addEdge(&thiruvottiyur, &waherman, 10);
    addEdge(&waherman, &mannadi, 10);
    addEdge(&mannadi, &highcourt, 10);
    addEdge(&highcourt, &chennai_central, 10);
    addEdge(&governament, &lic, 10);
    addEdge(&lic, &thousand_lights, 10);
    addEdge(&thousand_lights, &ag_dms, 10);
    addEdge(&ag_dms, &teynampet, 10);
    addEdge(&teynampet, &nandanam, 10);
    addEdge(&nandanam, &saidapet, 10);
    addEdge(&saidapet, &little_mount, 10);
    addEdge(&little_mount, &guindy, 10);
    addEdge(&chennai_central, &egmore, 10);
    addEdge(&egmore, &nehru_park, 10);
    addEdge(&nehru_park, &kilpauk, 10);
    addEdge(&kilpauk, &shenoy_nagar, 10);
    addEdge(&shenoy_nagar, &anna_nagar_east, 10);
    addEdge(&anna_nagar_east, &anna_nagar_tower, 10);
    addEdge(&anna_nagar_tower, &thirumangalam, 10);
    addEdge(&thirumangalam, &koyambedu, 10);
    addEdge(&koyambedu, &cmbt, 10);
    addEdge(&cmbt, &arumbakkam, 10);
    addEdge(&arumbakkam, &vadapalani, 10);
    addEdge(&vadapalani, &ashok_nagar, 10);
    addEdge(&ashok_nagar, &ekkattuthangal, 10);
    addEdge(&chennai_central, &governament, 10);
    addEdge(&guindy, &ekkattuthangal, 10);
    addEdge(&alandur, &st_thomas_metro, 10);
    addEdge(&alandur, &guindy, 10);
    addEdge(&alandur, &ekkattuthangal, 10);
    addEdge(&alandur, &nanganallur_road, 10);
    addEdge(&nanganallur_road, &menambakkam, 10);
    addEdge(&menambakkam, &airport, 10);
    
    // User input for source and destination stations
    string source, destination;
    cout << "Enter the source station: ";
    getline(cin, source);
    cout << "Enter the destination station: ";
    getline(cin, destination);

    // Find the corresponding stations
    Station* sourceStation = nullptr;
    Station* destinationStation = nullptr;

    vector<Station*> stations = {
        &thiruvottiyur, &waherman, &mannadi, &highcourt, &chennai_central, &governament, &lic, &thousand_lights, &ag_dms,
        &teynampet, &nandanam, &saidapet, &little_mount, &guindy, &egmore, &nehru_park, &kilpauk, &shenoy_nagar,
        &anna_nagar_east, &anna_nagar_tower, &thirumangalam, &koyambedu, &cmbt, &arumbakkam, &vadapalani,
        &ashok_nagar, &ekkattuthangal, &alandur, &st_thomas_metro, &nanganallur_road, &menambakkam, &airport
    };

    for (Station* station : stations) {
        if (station->name == source) {
            sourceStation = station;
        }
        if (station->name == destination) {
            destinationStation = station;
        }
    }

    if (sourceStation == nullptr || destinationStation == nullptr) {
        cout << "Invalid source or destination station." << endl;
        return 0;
    }

    // Run Dijkstra's algorithm
    dijkstra(sourceStation);

    // Print the shortest path and fare amount
    printShortestPath(destinationStation);

    return 0;


}

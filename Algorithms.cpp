//ID -324246651
//GMAIL- sapirblumshtein@gmail.com



#include "Algorithms.hpp" 
#include "Graph.hpp"
#include <iostream>  
#include <vector> 
#include <queue> 
#include <limits>
#include <stack> 
#include <algorithm>


using namespace std;

namespace ariel { 
//statement of the function
bool negativeCycle(const Graph& g); 
void dfsSecond(const vector<vector<int>>& transpose, size_t  v, vector<bool>& visited) ;
void dfsFirst(const vector<vector<int>>& matrix, size_t  v, vector<bool>& visited, stack<int>& finishOrder) ;
vector<int> bellmanFord(const Graph& graph, size_t source, vector<int>& dist, vector<int>& prev) ;

bool Algorithms::isConnected(const Graph& graph) {
    const vector<vector<int>>& matrix = graph.getAdjMatrix();
    size_t n = graph.getNVertices();
    if (graph.getNVertices() == 0) { //empty graph as not connected 
        return false;
    }

    // Step 1: Perform a DFS to get the finish order.
    vector<bool> visited(n, false);
    stack<int> finishOrder;
    for (size_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsFirst(matrix, i, visited, finishOrder);
        }
    }

    // Step 2: Create the transpose of the graph.
    vector<vector<int>> transpose(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                transpose[j].push_back(i);
            }
        }
    }

    // Step 3: Perform a DFS based on the vertex finish order in the original DFS.
    fill(visited.begin(), visited.end(), false);
    size_t componentCount = 0; // This counts how many strong components are found

    while (!finishOrder.empty()) {
        int v = finishOrder.top();
        finishOrder.pop();
        if (!visited[v]) {
            stack<int> component;
            dfsSecond(transpose, v, visited);
            componentCount++;
            if (componentCount > 1) { // If more than one component is found, the graph is not strongly connected.
                return false;
            }
        }
    }

    // If exactly one strong component that includes all vertices is found:
    return true;
}

void Algorithms:: dfsFirst(const vector<vector<int>>& matrix, size_t v, vector<bool>& visited, stack<int>& finishOrder) {
    visited[v] = true;

    for (size_t neighbor = 0; neighbor < matrix[v].size(); ++neighbor) {
        if (!visited[neighbor]) {
            dfsFirst(matrix, neighbor, visited, finishOrder);
        }
    }

    finishOrder.push(v);
}

void Algorithms:: dfsSecond(const vector<vector<int>>& transpose, size_t v, vector<bool>& visited) {
    visited[v] = true;

    for (size_t neighbor : transpose[v]) {
        if (!visited[neighbor]) {
            dfsSecond(transpose, neighbor, visited);
        }
    }
}

// if there is a negative cycle
    bool Algorithms :: negativeCycle(const Graph& g) {  // according to bellman ford n-1 times
    size_t n = g.getNVertices();
    vector<int> dist(n, 0);
    vector<int> prev(n, -1);
    
        // Get the distances after V-1 iterations
        vector<int> distance = bellmanFord(g, 0 , dist ,prev);
        
        // Now check if additional relaxation is possible
        for (size_t u = 0; u < n; u++) {  // loop iterates over all possible source vertices u for the edges in the graph
            for (size_t v = 0; v < n; v++) { // loop iterates over all possible destination vertices v for the edges in the graph.
                if (g.getAdjMatrix()[u][v] != 0) { // If there's an edge from u to v
                    int weight = g.getAdjMatrix()[u][v];
            // Check for negative cycles - if there is a relax again (n times) there is a  negative cycles
                    if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                        return true; // there a negative cycle
                    }
                }
            }
        }
    
    return false; //There is no negative cycle
}


vector<int> Algorithms :: bellmanFord(const Graph& graph, size_t source, vector<int>& dist, vector<int>& prev) {
    size_t n = graph.getNVertices();
    dist.assign(n, numeric_limits<int>::max()); // Init distances with infinity
    prev.assign(n, -1); //Contains the previous vertices in the shortest path.

    dist[source] = 0; // we start to put 0

    for (size_t i = 0; i < n - 1; i++) {     // Relax edges repeatedly
        for (size_t u = 0; u < n; u++) {
            for (size_t v = 0; v < n; v++) {
                int weight = graph.getAdjMatrix()[u][v];
                if (weight != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + graph.getAdjMatrix()[u][v] < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }

    return dist; 
}

string Algorithms::shortestPath(const Graph& graph, int source, int destination) {
    size_t n = graph.getNVertices();
    vector<int> dist; // Initialize vectors for distance
    vector<int> prev; // Initialize vectors for previous vertex

    // Run Bellman-Ford to detect negative cycles and find shortest paths
    dist = bellmanFord(graph, source, dist, prev);

    // Check if there is a negative cycle
    if (negativeCycle(graph)) {
        return "-1"; // There is no path due to negative cycle
    }

    // Check if there is no path from source to destination
    if (dist[destination] == numeric_limits<int>::max()) {
        return "-1"; // There is no path
    }

    if (source == destination) {
        return to_string(source);  // Path from a node to itself is the node
    }

    vector<int> path;
    int current = destination;
    path.push_back(current);
    while (current != source) {
        current = prev[current];
        path.push_back(current);
    }
    reverse(path.begin(), path.end()); // Reverse the path to get correct order

    // return the string of the path
    string pathStr;
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) {
            pathStr += "->";
        }
        pathStr += to_string(path[i]);
    }
    return pathStr;
}


string Algorithms::isContainsHelper(const Graph& g, int source, vector<int>& visited, vector<int>& stack_of_cycle, int parent) {
    int n = g.getNVertices();

    visited[source] = 1; 
    stack_of_cycle.push_back(source);

    for (int v = 0; v < n; v++) {
        int weight = g.getAdjMatrix()[source][v]; // to know what have in the matrix
        if (weight != 0) {
            if (visited[v] == 0) { // we dont visit the v
                string path = isContainsHelper(g, v, visited, stack_of_cycle,-1);
                if (path != "-1") {
                    return path;
                }
            } else if (visited[v] == 1) { // Back edge, negative cycle detected
                string path = to_string(v);
                while (stack_of_cycle.back() != v) { 
                    path = to_string(stack_of_cycle.back()) + "->" + path;
                    stack_of_cycle.pop_back();
                }
                path = to_string(v) + "->" + path;
                return path;
            }
        }
    }

    visited[source] = 2; // do like visited and finish
    stack_of_cycle.pop_back();

    return "-1"; // there isnt cycle
}

string Algorithms::isContainsCycle(const Graph& graph) {
    size_t n = graph.getNVertices();
    const vector<vector<int>>& adjMatrix = graph.getAdjMatrix();
    vector<int> visited(n, 0); // put o every area
    vector<int> stack_of_cycle;

    for (int source = 0; source < n; source++) {
        if (visited[source] == 0) {
            vector<int> dist(n, numeric_limits<int>::max());
            vector<int> prev(n, -1);   
            string path = isContainsHelper(graph, source, visited, stack_of_cycle,-1);
            if (path != "-1") {
                return path;
            }
        }
    }

    return "0";
}

bool  Algorithms:: isBipartiteHelper(const vector<vector<int>>& graph, int current, vector<int>& visited, vector<int>& side1, vector<int>& side2, int group_num) {
    visited[current] = group_num; 

    if (group_num == 0) { 
        side1.push_back(current);
    } else {
        side2.push_back(current);
    }

    for (int neighbor = 0; neighbor < graph.size(); neighbor++) {
        if (graph[current][neighbor] != 0) {
            if (visited[neighbor] == -1) { //  chack if has not been visit
                if (!isBipartiteHelper(graph, neighbor, visited, side1, side2, 1 - group_num)) {
                    return false; // if the dfs return false so isnt bipartite
                }
            } else if (visited[neighbor] == visited[current]) { // if there is the same color of the neighbor
                return false;
            }
        }
    }

    return true;
}

string Algorithms::isBipartite(const Graph& g) {
    const vector<vector<int>>& graph = g.getAdjMatrix();
    int n = g.getNVertices();

    vector<int> side1; // the first side
    vector<int> side2; // the second side
    vector<int> visited(n, -1);

    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            if (!isBipartiteHelper(graph, i, visited, side1, side2, 0)) {
                return "0"; // not bipartite

            }
        }
    }

    string sides = "The graph is bipartite: A={";
    for (size_t i = 0; i < side1.size(); i++) {
        sides += to_string(side1[i]);
        if (i < side1.size() - 1) {
            sides += ",";
        }
    }
    sides += "}, B={";
    for (size_t i = 0; i < side2.size(); i++) {
        sides += to_string(side2[i]);
        if (i < side2.size() - 1) {
            sides += ",";
        }
    }
    sides += "}";

    return sides;
}

} // namespace ariel  
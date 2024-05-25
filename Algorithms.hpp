//ID -324246651
//GMAIL- sapirblumshtein@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.hpp"
#include <string>
#include <stack>

using namespace std;

namespace ariel {

class Algorithms {
public:
    // Return if the graph is connected
    static bool isConnected(const Graph& graph);

    // Returns the shortest path between start and end
    static string shortestPath(const Graph& graph, int start, int end);

    // Helper function for isBipartite
    static bool isBipartiteHelper(const vector<vector<int>>& graph, int current, vector<int>& visited, vector<int>& side1, vector<int>& side2, int group_num);

    // Checks if the graph is bipartite
    static string isBipartite(const Graph& g);
 
    // Checks if the graph contains a cycle
    static string isContainsCycle(const Graph& graph);

    // Checks if the graph contains a negative cycle
    static bool negativeCycle(const Graph& graph);

    // Helper function for isContainsCycle
    static string isContainsHelper(const Graph& g, int source, vector<int>& visited, vector<int>& stack_of_cycle, int parent);

    // Bellman-Ford algorithm for shortest paths
    static vector<int> bellmanFord(const Graph& graph, size_t source, vector<int>& dist, vector<int>& prev);

    // DFS helper function for isConnected
    static void dfsSecond(const vector<vector<int>>& transpose, size_t v, vector<bool>& visited);

    // DFS helper function for isConnected
    static void dfsFirst(const vector<vector<int>>& matrix, size_t v, vector<bool>& visited, stack<int>& finishOrder);
};

}

#endif // ALGORITHMS_HPP

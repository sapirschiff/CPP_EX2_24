#pragma once

#include <vector>
#include <iostream>

namespace ariel {

class Graph {
private:
    std::vector<std::vector<int>> adjMatrix;
    int nVertices;
    int edges;
    bool weighted;

public:
    Graph();
    void loadGraph(const std::vector<std::vector<int>>& matrix);
    void printGraph() const;
    int getNVertices() const;
    int getEdges() const;
    const std::vector<std::vector<int>>& getAdjMatrix() const;
    bool isProperSubsetOf(const Graph& other) const;


    // Binary operators
    Graph operator+(const Graph& other) const;
    Graph& operator+=(const Graph& other);
    Graph operator+() const;
    Graph operator-(const Graph& other) const;
    Graph& operator-=(const Graph& other);
    Graph operator-() const;

    // Comparison operators
    bool operator==(const Graph& other) const;
    bool operator!=(const Graph& other) const;
    bool operator<(const Graph& other) const;
    bool operator<=(const Graph& other) const;
    bool operator>(const Graph& other) const;
    bool operator>=(const Graph& other) const;

    // Increment and Decrement
    Graph& operator++();
    Graph operator++(int);
    Graph& operator--();
    Graph operator--(int);

    // Scalar multiplication and division
    Graph operator*(int scalar) const;
    Graph& operator*=(int scalar);
    Graph& operator/=(int scalar);

    // Matrix multiplication
    Graph operator*(const Graph& other) const;

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

} // namespace ariel

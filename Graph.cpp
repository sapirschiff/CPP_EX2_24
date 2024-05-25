#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel {

Graph::Graph() : nVertices(0), edges(0), weighted(false) {}

void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
    size_t n = matrix.size();
    for(const auto& row : matrix) {
        if (row.size() != n) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }

    this->adjMatrix = matrix;
    this->nVertices = n;
    this->edges = 0;

    // Set diagonal elements to zero
    for (size_t i = 0; i < n; ++i) {
        this->adjMatrix[i][i] = 0;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0) {
                this->edges++;
            }
        }
    }
}

void Graph::printGraph() const {
    for (const auto& row : adjMatrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

int Graph::getNVertices() const { 
    return this->nVertices;
}

int Graph::getEdges() const { 
    return this->edges; 
}

const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
    return this->adjMatrix;
}

// Binary operators
Graph Graph::operator+(const Graph& other) const {

    if (other.getAdjMatrix().size() != this->getAdjMatrix().size())
    {
        throw std::invalid_argument("Matrices need to be of the same size for +");
    }
    size_t size = this->getAdjMatrix().size();

    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0)); // new mateix for resulr
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[i][j] = this->adjMatrix[i][j] + other.adjMatrix[i][j]; // do the +
        }
    }

    Graph res;
    res.loadGraph(result);
    return res;
}

Graph& Graph::operator+=(const Graph& other) {

    if (other.getAdjMatrix().size() != this->getAdjMatrix().size())
    {
        throw std::invalid_argument("Matrices need to be of the same size for +=");
    }
    size_t size = this->getAdjMatrix().size();

    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0)); // new mateix for resulr 
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
            result[i][j] = this->adjMatrix[i][j] + other.adjMatrix[i][j]; // do the +
            }
        }

    this->loadGraph(result);
    return *this;
}

Graph Graph::operator+() const {
    return *this;
}

Graph Graph::operator-(const Graph& other) const {
    if (other.getAdjMatrix().size() != this->getAdjMatrix().size())
    {
        throw std::invalid_argument("Matrices need to be of the same size for -");
    }
    size_t size = this->getAdjMatrix().size();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0)); // new mateix for resulr

    
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[i][j] = this->adjMatrix[i][j] - other.adjMatrix[i][j];
        }
    }

    Graph res;
    res.loadGraph(result);
    return res;
}

Graph& Graph::operator-=(const Graph& other) {

    if (other.getAdjMatrix().size() != this->getAdjMatrix().size())
    {
        throw std::invalid_argument("Matrices need to be of the same size for -=.");
    }
    size_t size = this->getAdjMatrix().size();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            adjMatrix[i][j] -= other.adjMatrix[i][j]; // add the function -=
        }
    }

    return *this;
}

Graph Graph::operator-() const {
    std::vector<std::vector<int>> result(this->adjMatrix);
    for (auto& row : result) {
        for (auto& val : row) {
            if (val != 0) {
                val = -val;
            }
        }
    }

    Graph res;
    res.loadGraph(result);
    return res;
}

// Comparison operators
bool Graph::operator==(const Graph& other) const {

    bool equals = true;
    if (other.getAdjMatrix().size() != this->getAdjMatrix().size())
    {
        return equals;
    }
    size_t size = this->getAdjMatrix().size();


    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {

            if (adjMatrix[i][j] != other.adjMatrix[i][j]) // if one of them is not equals
            {
                equals=false;
            }
        }
     }
    return equals;

     if (!(*this > other) && !(*this < other))
        {
            return true;
        }
        return false;
}

bool Graph::operator!=(const Graph& other) const {

    if (*this == other)
        
        return false;
        
    return true;

}


// Similarly refactor operator>
bool Graph::operator>(const Graph& other) const {
    bool bigger = true;
    size_t size = this->getAdjMatrix().size();
    size_t size2 = other.getAdjMatrix().size();

    if(other == *this) return false; // if the matrix is the same so is cant be

    if(size == size2){
        bigger = false;
    }
    if(size>size2){

    for (size_t i = 0; i < size-size2; ++i) {
        for (size_t j = 0; j < size-size2; ++j) {
        bool bigger2 = true;  
        for (size_t k = 0; k < size2 && bigger2; k++)
            {
                for (size_t l = 0; l < size && bigger2; l++)
                    {
                        bigger2 = this->getAdjMatrix()[i + k][j + l] == other.getAdjMatrix()[k][l];
                    }
                }
                    if (bigger2)
                    {
                        return true;
                    }
                }
            
        }
    }// end if
    if (this->getEdges() > other.getEdges())
        {
            return true;
        }
        
    if (this->getEdges() == other.getEdges())
        {
            if (size > size2)
            {
                return true;
            }
        }
        return bigger;
    }



bool Graph::operator<(const Graph& other) const {
    return other > *this;
}

bool Graph::operator<=(const Graph& other) const {
    return *this < other || *this == other;
}


bool Graph::operator>=(const Graph& other) const {
     return *this == other || *this > other;
}

Graph& Graph::operator++() {
    for (auto& row : adjMatrix) {
        for (auto& val : row) {
            val++;
        }
    }
    return *this;
}


//Graph Graph::operator++(int) {
//    Graph tmp = *this;
//    ++(*this);
//    return tmp;
//}

Graph& Graph::operator--() {
    for (auto& row : adjMatrix) {
        for (auto& val : row) {
            val--;
        }
    }
    return *this;
}

//Graph Graph::operator--(int) {
//    Graph tmp = *this;
//    --(*this);
//    return tmp;
//}

// Scalar multiplication and division
Graph Graph::operator*(int scalar) const {
    size_t size = this->getAdjMatrix().size();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0)); // new mateix for resulr


    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[i][j] = this->adjMatrix[i][j] * scalar;

        }
    }


    Graph res;
    res.loadGraph(result);
    return res;
}

Graph& Graph::operator*=(int scalar) {
    for (auto& row : adjMatrix) {
        for (auto& val : row) {
            val *= scalar;
        }
    }
    return *this;
}

Graph& Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    size_t size = this->getAdjMatrix().size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            adjMatrix[i][j] /= scalar; // Perform the division
        }
    }
    
    return *this;
}

// Matrix multiplication
Graph Graph::operator*(const Graph& other) const {
    if (this->getAdjMatrix().size()!= other.getAdjMatrix().size()) {
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    size_t size = other.getAdjMatrix().size();

    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                result[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];

            }
        }
    }
    for (int i=0; i<size; i++){ // check if the multiplication return number that is not 0
            result[i][i]=0;
    }

    Graph res;
    res.loadGraph(result);
    return res;
}

// Stream output
std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (const auto& row : graph.adjMatrix) {
        for (int val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}
}// namespace
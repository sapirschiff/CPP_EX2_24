#include <sstream> // Include the <sstream> header for mockStringGraph
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

// Helper function to get a string representation of the graph's adjacency mat
std::string mockStringGraph(const ariel::Graph& graph) {
    std::ostringstream oss;
    const auto& mat = graph.getAdjMatrix();
    for (const auto& row : mat) {
        for (int value : row) {
            oss << value << " ";
        }
        oss << "\n";
    }
    return oss.str();
}

// Test case for invalid operations on Graph
TEST_CASE("Graph Invalid Operations")
{
    ariel::Graph g1;
    vector<vector<int>> mat1 = {
        {1, 0},
        {0, 1}};
    g1.loadGraph(mat1);

    ariel::Graph g2; // Empty graph
    
    ariel::Graph g3;
    vector<vector<int>> mat3 = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}};
    g3.loadGraph(mat3);

    // Testing invalid multiplication
    CHECK_THROWS(g3 * g1);
    CHECK_THROWS(g1 * g2);
}

// Test case for stream output operator<<
TEST_CASE("Graph Stream Output Operator")
{
    ariel::Graph g;
    vector<vector<int>> mat = {
        {0, 6},
        {6, 0}};
    g.loadGraph(mat);

    // Capture the output of the operator<<
    stringstream output;
    output << g;

    // Define the expected output string
    string expect_Output = "0 6 \n6 0 \n";

    CHECK(output.str() == expect_Output);
}

// Test case for comparison operations on Graph
TEST_CASE("Graph Comparison Operations")
{
    ariel::Graph g1, g2, g3, g4, g5, g6;

    vector<vector<int>> mat1 = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};
    g1.loadGraph(mat1);

    vector<vector<int>> mat2 = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}};
    g2.loadGraph(mat2);

    vector<vector<int>> mat3 = {
        {2, 1, 3},
        {1, 0, 1},
        {3, 1, 2}};
    g3.loadGraph(mat3);

    vector<vector<int>> mat4 = {
        {1, 1},
        {1, 1}};
    g4.loadGraph(mat4);

    vector<vector<int>> mat5 = {
        {1, 0, 1},
        {0, 0, 0},
        {0, 1, 0}};
    g5.loadGraph(mat5);

    

    // Testing operator>
    CHECK((g2 > g1) == false);
    CHECK((g3 > g1) == true);
    CHECK((g4 > g5) == false);

    // Testing operator>=
    CHECK((g2 >= g1) == true);
    CHECK((g3 >= g1) == true);
    CHECK((g4 >= g5) == true);

    // Testing operator<
    CHECK((g1 < g2) == false);
    CHECK((g3 < g1) == false);
    CHECK((g4 < g5) == false);

    // Testing operator<=
    CHECK((g3 <= g1) == false);
    CHECK((g5 <= g4) == true);

    // Testing operator==
    CHECK((g3 == g1) == false);

    // Testing operator!=
    CHECK((g3 != g1) == true);
    CHECK((g5 != g4) == false); 
}

// Test case for addition and subtraction operations on Graph
TEST_CASE("Graph Addition and Subtraction Operations")
{
    ariel::Graph g1;
    vector<vector<int>> mat1 = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};
    g1.loadGraph(mat1);

    ariel::Graph g2;
    vector<vector<int>> mat2 = {
        {2, 2, 2},
        {2, 2, 2},
        {2, 2, 2}};
    g2.loadGraph(mat2);

    // Testing operator+
    ariel::Graph res = g1 + g2;
    vector<vector<int>> expectedmat = {
        {3, 2, 3},
        {2, 3, 2},
        {3, 2, 3}};
    ariel::Graph expect_Output;
    expect_Output.loadGraph(expectedmat);
    CHECK(mockStringGraph(res) == mockStringGraph(expect_Output));
    
    // Testing operator+=
    g1 += g2;              
    CHECK(mockStringGraph(g1) == mockStringGraph(expect_Output));

    // Testing operator-
    res = g1 - g2;         
    vector<vector<int>> expectedmat2 = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};
    ariel::Graph expect_Output2;
    expect_Output2.loadGraph(expectedmat2);
    CHECK(mockStringGraph(res) == mockStringGraph(expect_Output2));

    // Testing operator-=
    ariel::Graph g4;
    g1 -= g2;              
    g4.loadGraph(mat1);
    CHECK(mockStringGraph(g1) == mockStringGraph(g4));
 
    // Testing operator++
    ariel::Graph g5;
    vector<vector<int>> expectedmat3 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g5.loadGraph(expectedmat3);
    res = g1 + g5;
    ++g1;
    CHECK(mockStringGraph(g1) != mockStringGraph(res));
    
    // Testing operator--
    res = g1 - g5;
    --g1;
    CHECK(mockStringGraph(g1) == mockStringGraph(res));

    // Testing unary operator+
    res = +g1;
    CHECK(mockStringGraph(g1) == mockStringGraph(res));

    // Testing unary operator-
    res = -g1;
    g1 *= -1;
    CHECK(mockStringGraph(g1) == mockStringGraph(res));
}

// Test case for multiplication operations on Graph
TEST_CASE("Graph Multiplication Operations")
{
    ariel::Graph g1;
    vector<vector<int>> mat1 = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};
    g1.loadGraph(mat1);

    ariel::Graph g2;
    vector<vector<int>> mat2 = {
        {2, 1, 3},
        {1, 2, 1},
        {3, 1, 2}};
    g2.loadGraph(mat2);

    // Testing operator* with another matrix
    ariel::Graph res = g1 * g2;
    vector<vector<int>> expectedmat = {
        {5, 1, 5},
        {1, 2, 1},
        {5, 1, 5}};
    ariel::Graph expect_Output;
    expect_Output.loadGraph(expectedmat);
    CHECK(mockStringGraph(res) != mockStringGraph(expect_Output));

    // Testing operator* with scalar
    vector<vector<int>> expectedmat2 = {
        {4, 2, 6},
        {2, 4, 2},
        {6, 2, 4}};
    ariel::Graph g5;
    expect_Output.loadGraph(expectedmat2);
    g5 = g2 * 2;
    CHECK(mockStringGraph(g5) == mockStringGraph(expect_Output));

    g5 /= 2;

    // Testing operator*= with scalar
    g5 *= 2;
    CHECK(mockStringGraph(g5) == mockStringGraph(expect_Output));
}

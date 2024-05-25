Graph Class Implementation
Description
This project implements a Graph class that represents graphs using adjacency matrices. The Graph class allows various operations on graphs, such as addition, subtraction, comparison, scalar multiplication, matrix multiplication, and increment/decrement operations on weights of edges.

Implementation Details
Graph Class: The Graph class is implemented in Graph.hpp and Graph.cpp files. It includes functions to load a graph from a given adjacency matrix, perform various graph operations, and output the graph.

Algorithms Class: The Algorithms class from the previous task is also included to provide additional functions for handling graphs and matrices.

Main Program: The main program is not implemented, as the focus is on the Graph class and its operations.

Division of Work
Functionality implementation:
Graph Class:
Implemented binary operators (+, +=, -) for graphs: These operators allow adding and subtracting graphs by element-wise addition and subtraction of adjacency matrices.
Implemented comparison operators (==, !=, <, >, <=, >=) for graphs: These operators compare graphs based on their adjacency matrices and determine their relative sizes.
Implemented unary operators (++, --) for incrementing and decrementing edge weights: These operators increment or decrement all edge weights by 1.
Implemented scalar multiplication and division operators for graphs: These operators multiply or divide all edge weights by a scalar value.
Implemented matrix multiplication operator for graphs: This operator performs matrix multiplication on the adjacency matrices of two graphs.
Implemented output operator to print the graph: This operator allows printing the adjacency matrix of the graph.
Operator Explanations
Binary Operators:

Operator+: Adds two graphs by element-wise addition of their adjacency matrices.
Operator+=: Adds another graph to the current graph by element-wise addition.
Operator-: Subtracts one graph from another by element-wise subtraction of their adjacency matrices.
Comparison Operators:

Operator==: Compares if two graphs are equal based on their adjacency matrices.
Operator!=: Compares if two graphs are not equal based on their adjacency matrices.
Operator<, >: Compares the sizes of two graphs based on their adjacency matrices.
Unary Operators:

Operator++: Increments all edge weights in the graph by 1.
Operator--: Decrements all edge weights in the graph by 1.
Scalar Multiplication and Division:

Operator*: Multiplies all edge weights in the graph by a scalar integer value.
Operator/=: Divides all edge weights in the graph by a scalar integer value.
Matrix Multiplication:

Operator*: Performs matrix multiplication on the adjacency matrices of two graphs.


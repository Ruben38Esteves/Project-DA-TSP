/**
 * @file Manager.h
 * @brief This file contains the implementation of user interface.
 */

#ifndef DAPROJECT2_MANAGER_H
#define DAPROJECT2_MANAGER_H

#include "Graph.h"

class Manager
{
private:
    Graph graph;

public:
    Manager();
    /**
     * @brief Reads a graph from a file and sets it as the current graph.
     *
     * This function reads a graph from the specified file path and sets it as the current graph
     * in the Manager class. It can read both toy graphs and real-world graphs based on the `real` flag.
     *
     * Time complexity: O(V + E) being V the number of vertexes and E the number of edges
     *
     * @param filePath The file path of the graph file.
     * @param real A flag indicating whether the graph is a real-world graph (true) or a toy graph (false).
     */
    void readGraph(const std::string &filePath, bool real);

    /**
     * @brief Displays the main menu and handles user input for various options.
     *
     * Time complexity: O(1)
     *
     * This function displays the main menu with different options and handles user input
     * to perform various operations based on the selected option.
     */
    void mainMenu();

    /**
     * @brief Prompts the user to input a node based on a given message.
     *
     * This function prompts the user to input a node ID based on the given message.
     * It returns a pointer to the corresponding vertex if found, or nullptr if canceled or not found.
     *
     * Time complexity: O(1)
     *
     * @param message The message displayed to the user.
     * @return A pointer to the input node vertex or nullptr if canceled or not found.
     */
    Vertex *inputNode(const std::string &message);

    /**
     * @brief Displays the read graph menu and handles user input for graph selection.
     *
     * This function displays the read graph menu with different options and handles user input
     * to select a graph to read and set as the current graph in the Manager class.
     *
     * Time complexity: O(1)
     */
    void readGraphMenu();

    /**
     * @brief Displays the toy graph menu and handles user input for toy graph selection.
     *
     * This function displays the toy graph menu with different options and handles user input
     * to select a toy graph to read and set as the current graph in the Manager class.
     *
     * Time complexity: O(1)
     */
    void toyGraphMenu();

    /**
     * @brief Displays the fully connected graph menu and handles user input for fully connected graph selection.
     *
     * This function displays the fully connected graph menu with different options and handles user input
     * to select a fully connected graph to read and set as the current graph in the Manager class.
     *
     * Time complexity: O(1)
     */
    void fullyConnectedGraphMenu();

    /**
     * @brief Displays the real-world graph menu and handles user input for real-world graph selection.
     *
     * This function displays the real-world graph menu with different options and handles user input
     * to select a real-world graph to read and set as the current graph in the Manager class.
     *
     * Time complexity: O(1)
     */
    void realWorldGraphMenu();

    /**
     * @brief Calculates the Traveling Salesman Problem (TSP) solution using backtracking.
     *
     * This function calculates the TSP solution using backtracking and displays the optimal path and total distance.
     * It starts from the vertex with ID 0 as the initial node.
     *
     * Time complexity: O(2^V * V^2) being V the number of vertexes
     */
    void TSPBacktracking();

    /**
     * @brief Recursive helper function for TSPBacktracking.
     *
     * This function is a recursive helper function for TSPBacktracking. It explores all possible paths
     * starting from the given `currNode` and updates the `minCost` and `bestPath` variables with the optimal path.
     *
     * Time complexity: O(2^V * V^2) being V the number of vertexes
     *
     * @param currNode The current node being explored.
     * @param visited A boolean array indicating whether a node has been visited or not.
     * @param currPath The current path being explored.
     * @param currCost The current cost of the path.
     * @param minCost The minimum cost found so far.
     * @param bestPath The best path found so far.
     */
    void TSPBacktrackingRecursive(Vertex *currNode, std::vector<Vertex *> &visitedNodes, double currCost, double &minCost, std::vector<Vertex *> &bestPath);

    /**
     *
     * @brief Performs the Triangular Approximation for the Traveling Salesman Problem (TSP).
     *
     * This function applies the Triangular Approximation algorithm to find an initial solution for the TSP.
     * It uses the Prim's algorithm to construct a minimum spanning tree of the graph, and then performs a depth-first search (DFS)
     * starting from the first vertex to obtain a path that visits all vertices. The last vertex in the path is connected back to the first vertex
     * to complete the cycle. The total distance of the path is calculated by summing the distances between consecutive vertices.
     * The execution time of the function is also measured.
     *
     * Time complexity: O(E * log(V) + V) being V the number of vertexes  and E the number of edges
     */
    void TSPTriangularApproximation();

    /**
     *
     * @brief Performs the 2-opt optimization for the Traveling Salesman Problem (TSP).
     *
     * This function applies the 2-opt optimization algorithm to improve the solution obtained from the Triangular Approximation.
     * It starts by finding an initial solution using the Triangular Approximation algorithm.
     * Then, it repeatedly iterates over pairs of edges in the path and checks if swapping them can reduce the total distance.
     * If a swap improves the solution, the path is modified accordingly, and the process is repeated until no further improvement is found.
     * The execution time of the function is measured and divided into two parts: the time spent on path creation and the time spent on path improvement.
     *
     * Time complexity: O(E * log(V) + V^2) being V the number of vertexes and E the number of edges
     */
    void twoOpt();
};

/**
 * Reads a field from a cvs file
 *
 * Time complexity: O(1)
 * 
 * @param line istringstream variable
 * @param delim until which character should the line be read
 */
std::string getField(std::istringstream &line, char delim);

#endif // DAPROJECT2_MANAGER_H

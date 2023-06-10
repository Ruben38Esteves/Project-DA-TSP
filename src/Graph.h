/**
 * @file Graph.h
 * @brief This file contains the implementation of the Graph class.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <unordered_map>
#include <vector>
#include "VertexEdge.h"
#include "MutablePriorityQueue.h"

#define M_PI 3.14159265358979323846
#define INF INT32_MAX

/**
 * @class Graph
 * @brief Represents a graph data structure.
 */
class Graph
{
private:
    std::unordered_map<int, Vertex *> vertexMap; /**< Map of vertex IDs to Vertex pointers. */
    bool real;                                   /**< Flag indicating whether the graph represents real-world locations. */

public:
    /**
     * @brief Gets the number of vertices in the graph.
     *
     * Time complexity: O(1)
     *
     * @return The number of vertices.
     */
    int getNumVertex() const;

    /**
     * @brief Gets the map of vertex IDs to Vertex pointers.
     *
     * Time complexity: O(1)
     *
     * @return The vertex map.
     */
    std::unordered_map<int, Vertex *> getVertexMap() const;

    /**
     * @brief Resets the graph by removing all vertices.
     *
     * Time complexity: O(1)
     */
    void resetGraph();

    /**
     * @brief Finds a vertex with a given ID.
     *
     * Time complexity: O(1)
     *
     * @param id The ID of the vertex to find.
     * @return A pointer to the found vertex, or nullptr if not found.
     */
    Vertex *findVertex(const int &id) const;

    /**
     * @brief Adds a vertex to the graph.
     *
     * Time complexity: O(1)
     *
     * @param id The ID of the vertex to add.
     * @return True if the vertex was added successfully, false if a vertex with the same ID already exists.
     */
    bool addVertex(const int &id);

    /**
     * @brief Adds an edge to the graph.
     *
     * Time complexity: O(1)
     *
     * @param sourc The ID of the source vertex.
     * @param dest The ID of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the edge was added successfully, false if either the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);

    /**
     * @brief Adds a bidirectional edge to the graph.
     *
     * Time complexity: O(1)
     *
     * @param sourc The ID of the source vertex.
     * @param dest The ID of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the edge was added successfully, false if either the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    /**
     * @brief Calculates the distance between two vertices.
     * And adds a new edge between them if there is none with the weight returned by haversine function
     *
     * Time complexity: O(1)
     *
     * @param v1 Pointer to the first vertex.
     * @param v2 Pointer to the second vertex.
     * @return The distance between the two vertices.
     */
    double getDistance(Vertex *v1, Vertex *v2);

    /**
     * @brief Sets the graph to represent real-world locations or not.
     *
     * Time complexity: O(1)
     *
     * @param real Flag indicating whether the graph represents real-world locations.
     */
    void setReal(bool real);

    // Algorithms

    /**
     * @brief Applies the Prim's algorithm to find the minimum spanning tree of the graph.
     *
     * Time complexity: O(E * log(V)) being E the number of edges and V the number of vertexes
     */
    void prim();

    /**
     * @brief Performs a depth-first search (DFS) on the graph, calculating the total distance and storing the path.
     *
     * Time complexity: O(V) being V the number of vertexes
     *
     * @param vertex Pointer to the current vertex being visited.
     * @param lastVertex Pointer to the last visited vertex.
     * @param path Vector to store the path.
     * @return The total distance of the path.
     */
    double dfs(Vertex *vertex, Vertex **lastVertex, std::vector<Vertex *> &path);
};

/**
 * @brief Calculates the haversine distance between two sets of latitude and longitude coordinates.
 *
 * Time complexity: O(1)
 *
 * @param lat1 The latitude of the first point.
 * @param lon1 The longitude of the first point.
 * @param lat2 The latitude of the second point.
 * @param lon2 The longitude of the second point.
 * @return The haversine distance between the two points.
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Deletes a dynamically allocated 2D integer matrix.
 *
 * Time complexity: O(1)
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */
void deleteMatrix(int **m, int n);

/**
 * @brief Deletes a dynamically allocated 2D double matrix.
 *
 * Time complexity: O(1)
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */
void deleteMatrix(double **m, int n);

#endif /* GRAPH_H */

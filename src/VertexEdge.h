/**
 * @file VertexEdge.h
 * @brief This file contains the implementation of the Vertex and Edge classes.
 */

#ifndef VERTEXEDGE_H
#define VERTEXEDGE_H

#include <unordered_map>
#include "MutablePriorityQueue.h"

class Edge;

/************************* Vertex  **************************/

/**
 * @class Vertex
 * @brief Represents a Vertex data structure.
 */
class Vertex
{
private:
    int id;
    std::unordered_map<int, Edge *> adj; // Outgoing edges
    bool visited;
    bool processing;
    unsigned int indegree;
    double dist;
    double latitude;
    double longitude;
    Edge *path;

public:
    /**
     * @brief Constructs a vertex with the given ID.
     *
     * @param id The ID of the vertex.
     */
    explicit Vertex(int id);

    /**
     * @brief Adds an outgoing edge from this vertex to a destination vertex with a given weight.
     *
     * Time complexity: O(1)
     *
     * @param d The destination vertex.
     * @param w The weight of the edge.
     * @return The newly created edge.
     */
    Edge *addEdge(Vertex *d, double w);

    /**
     * @brief Removes an outgoing edge with the given destination ID from this vertex.
     *
     * Time complexity: O(1)
     *
     * @param destID The ID of the destination vertex.
     * @return True if the edge was successfully removed, false if the edge does not exist.
     */
    bool removeEdge(int destID);

    /**
     * @brief Removes all outgoing edges from this vertex.
     *
     * Time complexity: O(E), where E is the number of outgoing edges.
     */
    void removeOutgoingEdges();

    /**
     * @brief Checks if this vertex is less than another vertex. Used for sorting purposes.
     *
     * Time complexity: O(1)
     *
     * @param vertex The vertex to compare with.
     * @return True if this vertex is less than the other vertex, false otherwise.
     */
    bool operator<(Vertex &vertex) const;

    /**
     * @brief Returns the ID of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The ID of this vertex.
     */
    int getId() const;

    /**
     * @brief Returns the outgoing edges of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The outgoing edges of this vertex.
     */
    std::unordered_map<int, Edge *> getAdj() const;

    /**
     * @brief Checks if this vertex has been visited.
     *
     * Time complexity: O(1)
     *
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Checks if this vertex is being processed.
     *
     * Time complexity: O(1)
     *
     * @return True if the vertex is being processed, false otherwise.
     */
    bool isProcessing() const;

    /**
     * @brief Returns the indegree of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The indegree of this vertex.
     */
    unsigned int getIndegree() const;

    /**
     * @brief Returns the distance of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The distance of this vertex.
     */
    double getDist() const;

    /**
     * @brief Returns the latitude of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The latitude of this vertex.
     */
    double getLatitude() const;

    /**
     * @brief Returns the longitude of this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The longitude of this vertex.
     */
    double getLongitude() const;

    /**
     * @brief Returns the path (edge) to this vertex.
     *
     * Time complexity: O(1)
     *
     * @return The path (edge) to this vertex.
     */
    Edge *getPath() const;

    /**
     * @brief Returns the distance to a specific vertex.
     *
     * Time complexity: O(1)
     *
     * @param v The destination vertex.
     * @return The distance to the destination vertex, or -1 if there is no edge to the destination.
     */
    double getDistTo(Vertex *v);

    /**
     * @brief Sets the ID of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param id The ID to set.
     */
    void setId(int id);

    /**
     * @brief Sets the visited status of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param visited The visited status to set.
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the processing status of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param processing The processing status to set.
     */
    void setProcessing(bool processing);

    /**
     * @brief Sets the indegree of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param indegree The indegree to set.
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Sets the latitude of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param latitude The latitude to set.
     */
    void setLatitude(double latitude);

    /**
     * @brief Sets the longitude of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param longitude The longitude to set.
     */
    void setLongitude(double longitude);

    /**
     * @brief Sets the distance of this vertex.
     *
     * Time complexity: O(1)
     *
     * @param dist The distance to set.
     */
    void setDist(double dist);

    /**
     * @brief Sets the path (edge) to this vertex.
     *
     * Time complexity: O(1)
     *
     * @param path The path (edge) to set.
     */
    void setPath(Edge *path);

    /**
     * @brief Find an edge connecting this vertex to the specified destination vertex.
     *
     * This function searches for an edge in the adjacency list of the current vertex
     * that connects it to the specified destination vertex. If an edge is found, it
     * is returned; otherwise, nullptr is returned.
     *
     * Time complexity: O(1)
     *
     * @param dest A pointer to the destination vertex.
     * @return A pointer to the found edge, or nullptr if no edge is found.
     */
    Edge *findEdge(Vertex *dest) const;

    friend class MutablePriorityQueue<Vertex>;
protected:
    int queueIndex = 0;         // required by MutablePriorityQueue and UFDS
private:
    /**
     * @brief Deletes an edge from the memory.
     *
     * Time complexity: O(1)
     *
     * @param edge The edge to delete.
     */
    void deleteEdge(Edge *edge);

    friend class Edge;
};

/********************** Edge  ****************************/

/**
 * @class Edge
 * @brief Represents an Edge data structure.
 */
class Edge
{
private:
    Vertex *orig;
    Vertex *dest;
    double weight;
    Edge *reverse;
    bool selected;
    double flow;

public:
    /**
     * @brief Constructs an edge from an origin vertex to a destination vertex with a given weight.
     *
     * @param orig The origin vertex.
     * @param dest The destination vertex.
     * @param w The weight of the edge.
     */
    Edge(Vertex *orig, Vertex *dest, double w);

    /**
     * @brief Returns the destination vertex of this edge.
     *
     * Time complexity: O(1)
     *
     * @return The destination vertex of this edge.
     */
    Vertex *getDest() const;

    /**
     * @brief Returns the weight of this edge.
     *
     * Time complexity: O(1)
     *
     * @return The weight of this edge.
     */
    double getWeight() const;

    /**
     * @brief Returns the origin vertex of this edge.
     *
     * Time complexity: O(1)
     *
     * @return The origin vertex of this edge.
     */
    Vertex *getOrig() const;

    /**
     * @brief Returns the reverse edge of this edge.
     *
     * Time complexity: O(1)
     *
     * @return The reverse edge of this edge.
     */
    Edge *getReverse() const;

    /**
     * @brief Checks if this edge is selected.
     *
     * Time complexity: O(1)
     *
     * @return True if the edge is selected, false otherwise.
     */
    bool isSelected() const;

    /**
     * @brief Returns the flow of this edge.
     *
     * Time complexity: O(1)
     *
     * @return The flow of this edge.
     */
    double getFlow() const;

    /**
     * @brief Sets the selected status of this edge.
     *
     * Time complexity: O(1)
     *
     * @param selected The selected status to set.
     */
    void setSelected(bool selected);

    /**
     * @brief Sets the reverse edge of this edge.
     *
     * Time complexity: O(1)
     *
     * @param reverse The reverse edge to set.
     */
    void setReverse(Edge *reverse);

    /**
     * @brief Sets the flow of this edge.
     *
     * Time complexity: O(1)
     *
     * @param flow The flow to set.
     */
    void setFlow(double flow);

    friend class Vertex;
};

#endif // VERTEXEDGE_H

// By: Gonçalo Leão

#include "Graph.h"

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    lat1 *= (M_PI / 180.0);
    lat2 *= (M_PI / 180.0);

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371000 * c;
}

int Graph::getNumVertex() const
{
    return vertexMap.size();
}

std::unordered_map<int, Vertex *> Graph::getVertexMap() const
{
    return this->vertexMap;
}

void Graph::resetGraph()
{
    this->vertexMap.erase(this->vertexMap.begin(), this->vertexMap.end());
}


Vertex *Graph::findVertex(const int &id) const
{
    if (vertexMap.find(id) == vertexMap.end())
    {
        return nullptr;
    }
    return vertexMap.at(id);
}

bool Graph::addVertex(const int &id)
{
    if (findVertex(id) != nullptr)
    {
        return false;
    }
    vertexMap[id] = new Vertex(id);
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, double w)
{
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w)
{
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

double Graph::getDistance(Vertex *v1, Vertex *v2)
{
    double d = v1->getDistTo(v2);
    if (this->real && d == -1)
    {
        d = haversine(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
        this->addBidirectionalEdge(v1->getId(), v2->getId(), d);
    }
    return d;
}

void Graph::setReal(bool real)
{
    this->real = real;
}

void deleteMatrix(int **m, int n)
{
    if (m != nullptr)
    {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

void deleteMatrix(double **m, int n)
{
    if (m != nullptr)
    {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}
// algoritms

void Graph::prim()
{
    for (auto a : vertexMap)
    {
        a.second->setVisited(false);
        a.second->setDist(INF);
        a.second->setPath(nullptr);
    }

    Vertex *start = findVertex(0);
    start->setDist(0);

    MutablePriorityQueue<Vertex> queue;
    queue.insert(start);

    while (!queue.empty())
    {
        Vertex *v = queue.extractMin();
        v->setVisited(true);
        for (auto e : v->getAdj())
        {
            Vertex *w = e.second->getDest();
            if (!w->isVisited())
            {
                double prevDist = w->getDist();
                if (e.second->getWeight() < prevDist)
                {
                    w->setDist(e.second->getWeight());
                    w->setPath(e.second);
                    if (prevDist == INF)
                    {
                        queue.insert(w);
                    }
                    else
                    {
                        queue.decreaseKey(w);
                    }
                }
            }
        }
    }
}

double Graph::dfs(Vertex *vertex, Vertex **lastVertex, std::vector<Vertex *> &path)
{
    path.push_back(vertex);

    double total = 0;

    if (*lastVertex != nullptr)
        total = this->getDistance(*lastVertex, vertex);
    *lastVertex = vertex;

    for (auto e : vertex->getAdj())
    {
        if (e.second->getDest()->getPath() != e.second)
            continue;
        total += dfs(e.second->getDest(), lastVertex, path);
    }

    return total;
}

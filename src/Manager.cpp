#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Manager.h"

#ifdef _WIN32
const std::string file_path = "";
#else
const std::string file_path = "src/";
#endif

using namespace std;

Manager::Manager() = default;

std::string getField(std::istringstream &line, char delim)
{
    std::string string1, string2;
    getline(line, string1, delim);
    if (string1.front() == '"' && string1.back() != '"')
    {
        getline(line, string2, '"');
        string1 += string2;
        getline(line, string2, ',');
        return string1.substr(1);
    }
    else
        return string1;
}

void Manager::readGraph(const string &filePath, bool real)
{
    if (this->graph.getNumVertex() > 0)
        this->graph.resetGraph();
    this->graph.setReal(real);
    bool f = true;
    string path = file_path + filePath;
    if (!real)
    {
        ifstream file(path);
        string line;
        while (getline(file, line))
        {
            if (f)
            {
                f = false;
            }
            else
            {
                string start, end, distancia;
                istringstream s(line);

                start = getField(s, ',');
                end = getField(s, ',');
                distancia = getField(s, ',');

                this->graph.addVertex(stoi(start));
                this->graph.addVertex(stoi(end));

                this->graph.addBidirectionalEdge(stoi(start), stoi(end), stod(distancia));
            }
        }
    }
    else
    {
        ifstream file(path + "nodes.csv");
        string line;
        while (getline(file, line))
        {
            if (f)
            {
                f = false;
            }
            else
            {
                string start, longi, lati;
                istringstream s(line);

                start = getField(s, ',');
                longi = getField(s, ',');
                lati = getField(s, ',');

                this->graph.addVertex(stoi(start));

                graph.findVertex(stoi(start))->setLatitude(stod(lati));
                graph.findVertex(stoi(start))->setLongitude(stod(longi));
            }
        }
        f = true;
        file = ifstream(path + "edges.csv");
        while (getline(file, line))
        {
            if (f)
            {
                f = false;
            }
            else
            {
                string orig, dest, dist;
                istringstream s(line);

                orig = getField(s, ',');
                dest = getField(s, ',');
                dist = getField(s, ',');

                this->graph.addBidirectionalEdge(stoi(orig), stoi(dest), stod(dist));
            }
        }
    }
}

void Manager::mainMenu()
{
    int i = 0, n;
    while (i != 5)
    {
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "Selecione uma opcao: \n";
        cout << "1: Escolher grafo\n";
        if (this->graph.getNumVertex() > 0)
        {
            cout << "2: Calcular TSP usando Backtracking \n";
            cout << "3: Calcular TSP usando aproximação triangular \n";
            cout << "4: Calcular TSP usando aproximação triangular e otimizado por 2-opt\n";
        }
        cout << "5: Sair \n";
        n = (int)this->graph.getNumVertex();
        cout << "Numero de vertices carregados: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i)
        {
        case 1:
            this->readGraphMenu();
            break;
        case 2:
            if(this->graph.getNumVertex() > 0)
                this->TSPBacktracking();
            break;
        case 3:
            if(this->graph.getNumVertex() > 0)
                this->TSPTriangularApproximation();
            break;
        case 4:
            if(this->graph.getNumVertex() > 0)
                this->twoOpt();
            break;
        case 5:
            cout << "A sair..." << endl;
            break;
        default:
            cout << "Selecione uma opcao valida!" << endl;
        }
    }
}

Vertex *Manager::inputNode(const string &message)
{
    unsigned int i = -1;
    Vertex *temp;
    cout << message << endl;
    while (true)
    {
        cout << "Digite: '-1' se desejar cancelar a operacao" << endl;
        cout << "ID do vertice: ";
        cin >> i;
        if (i == -1)
        {
            return nullptr;
        }
        temp = this->graph.findVertex(i);
        if (temp != nullptr)
        {
            return temp;
        }
        else
            cout << "Vertice não encontrado insira um ID diferente" << endl;
    }
}

void Manager::readGraphMenu()
{
    int i = 0, n;
    while (i != 4)
    {
        cout << "------------MENU ESCOLHA DE GRAFO----------" << endl;
        cout << "Selecione uma opcao: \n";
        cout << "1: Grafos de brinquedo\n";
        cout << "2: Grafos totalmente conectados\n";
        cout << "3: Grafos do mundo real\n";
        cout << "4: Sair \n";
        n = (int)this->graph.getNumVertex();
        cout << "Numero de vertices carregados: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i)
        {
        case 1:
            toyGraphMenu();
            i = 4;
            break;
        case 2:
            fullyConnectedGraphMenu();
            i = 4;
            break;
        case 3:
            realWorldGraphMenu();
            i = 4;
            break;
        case 4:
            cout << "A sair..." << endl;
            break;
        default:
            cout << "Selecione uma opcao valida!" << endl;
        }
    }
}

void Manager::toyGraphMenu()
{
    int i = 0, n;
    while (i != 4)
    {
        cout << "------------MENU GRAFOS DE BRINQUEDO----------" << endl;
        cout << "Selecione uma opcao: \n";
        cout << "1: Grafo de envio\n";
        cout << "2: Grafo de estadios\n";
        cout << "3: Grafo de turismo\n";
        cout << "4: Sair \n";
        n = (int)this->graph.getNumVertex();
        cout << "Numero de vertices carregados: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i)
        {
        case 1:
            this->readGraph("datasets/toy-graphs/shipping.csv", false);
            i = 4;
            break;
        case 2:
            this->readGraph("datasets/toy-graphs/stadiums.csv", false);
            i = 4;
            break;
        case 3:
            this->readGraph("datasets/toy-graphs/tourism.csv", false);
            i = 4;
            break;
        case 4:
            cout << "A sair..." << endl;
            break;
        default:
            cout << "Selecione uma opcao valida!" << endl;
        }
    }
}

void Manager::fullyConnectedGraphMenu()
{
    int i = 0, n;
    while (i != 13)
    {
        cout << "------------MENU GRAFOS TOTALMENTE CONEXOS----------" << endl;
        cout << "Selecione uma opcao: \n";
        cout << "1: Grafo de 25 vertices\n";
        cout << "2: Grafo de 50 vertices\n";
        cout << "3: Grafo de 75 vertices\n";
        cout << "4: Grafo de 100 vertices\n";
        cout << "5: Grafo de 200 vertices\n";
        cout << "6: Grafo de 300 vertices\n";
        cout << "7: Grafo de 400 vertices\n";
        cout << "8: Grafo de 500 vertices\n";
        cout << "9: Grafo de 600 vertices\n";
        cout << "10: Grafo de 700 vertices\n";
        cout << "11: Grafo de 800 vertices\n";
        cout << "12: Grafo de 900 vertices\n";
        cout << "13: Sair \n";
        n = (int)this->graph.getNumVertex();
        cout << "Numero de vertices carregados: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i)
        {
        case 1:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_25.csv", false);
            i = 13;
            break;
        case 2:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_50.csv", false);
            i = 13;
            break;
        case 3:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_75.csv", false);
            i = 13;
            break;
        case 4:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_100.csv", false);
            i = 13;
            break;
        case 5:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_200.csv", false);
            i = 13;
            break;
        case 6:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_300.csv", false);
            i = 13;
            break;
        case 7:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_400.csv", false);
            i = 13;
            break;
        case 8:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_500.csv", false);
            i = 13;
            break;
        case 9:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_600.csv", false);
            i = 13;
            break;
        case 10:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_700.csv", false);
            i = 13;
            break;
        case 11:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_800.csv", false);
            i = 13;
            break;
        case 12:
            this->readGraph("datasets/extra-fully-connected-graphs/edges_900.csv", false);
            i = 13;
            break;
        case 13:
            cout << "A sair..." << endl;
            break;
        default:
            cout << "Selecione uma opcao valida!" << endl;
        }
    }
}

void Manager::realWorldGraphMenu()
{
    int i = 0, n;
    while (i != 4)
    {
        cout << "------------MENU GRAFOS REAIS----------" << endl;
        cout << "Selecione uma opcao: \n";
        cout << "1: Grafo 1\n";
        cout << "2: Grafo 2\n";
        cout << "3: Grafo 3\n";
        cout << "4: Sair \n";
        n = (int)this->graph.getNumVertex();
        cout << "Numero de vertices carregados: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i)
        {
        case 1:
            this->readGraph("datasets/real-world-graphs/graph1/", true);
            i = 4;
            break;
        case 2:
            this->readGraph("datasets/real-world-graphs/graph2/", true);
            i = 4;
            break;
        case 3:
            this->readGraph("datasets/real-world-graphs/graph3/", true);
            i = 4;
            break;
        case 4:
            cout << "A sair..." << endl;
            break;
        default:
            cout << "Selecione uma opcao valida!" << endl;
            break;
        }
    }
}

void Manager::TSPBacktracking() {
    Vertex* startNode = graph.findVertex(0);
    if (startNode == nullptr) {
        std::cout << "Node 0 does not exist." << std::endl;
        return;
    }
    std::vector<Vertex*> visitedNodes;
    visitedNodes.push_back(startNode);

    double minCost = std::numeric_limits<double>::max();
    std::vector<Vertex *> bestPath;

    auto start = chrono::high_resolution_clock::now();
    TSPBacktrackingRecursive(startNode, visitedNodes, 0, minCost, bestPath);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    std::cout << "The TSP path is: ";
    for (int i = 0; i < bestPath.size() - 1; i++)
    {
        std::cout << bestPath[i]->getId() << " -> ";
    }
    std::cout << bestPath.front()->getId() << std::endl;
    std::cout << "The total distance is: " << minCost << std::endl;
    cout << "The execution time was: " << duration.count() << " microseconds" << endl;
}

void Manager::TSPBacktrackingRecursive(Vertex *currNode, std::vector<Vertex *> &visitedNodes, double currCost,
                                       double &minCost, std::vector<Vertex *> &bestPath)
{
    if (visitedNodes.size() == graph.getNumVertex())
    {
        double pathCost = currCost;
        Edge *edge = currNode->findEdge(visitedNodes.front());
        if (edge)
        {
            pathCost += edge->getWeight();
        }
        if (pathCost < minCost)
        {
            if (edge)
            {
                minCost = pathCost;
                bestPath = visitedNodes;
                bestPath.push_back(visitedNodes.front());
            }
        }
        return;
    }
    for (auto a : currNode->getAdj()) {
        Vertex* nextNode = a.second->getDest();
        if (std::find(visitedNodes.begin(), visitedNodes.end(), nextNode) == visitedNodes.end()) {
            visitedNodes.push_back(nextNode);
            double pathCost = currCost;
            if (a.second) {
                pathCost += a.second->getWeight();
            }
            if (pathCost < minCost)
            {
                TSPBacktrackingRecursive(nextNode, visitedNodes, pathCost, minCost, bestPath);
            }
            visitedNodes.pop_back();
        }
    }
}

void Manager::TSPTriangularApproximation()
{
    Vertex *lastVertex = nullptr;
    auto start = chrono::high_resolution_clock::now();
    graph.prim();

    cout << "\nThe TSP path is: ";
    vector<Vertex *> path;
    double total = graph.dfs(graph.findVertex(0), &lastVertex, path);
    total += lastVertex->getDistTo(this->graph.findVertex(0));

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "The TSP path is: ";
    if (this->graph.getNumVertex() <= 100)
    {
        for (auto v : path)
        {
            cout << v->getId() << " -> ";
        }
        cout << "0" << endl;
    }
    cout << "The total distance is: " << total << endl;
    cout << "The execution time was: " << duration.count() << " microseconds" << endl;
}

void Manager::twoOpt()
{
    vector<Vertex *> path;
    Vertex *lastVertex = nullptr;

    auto start = chrono::high_resolution_clock::now();

    graph.prim();
    double total = graph.dfs(graph.findVertex(0), &lastVertex, path);
    total += lastVertex->getDistTo(this->graph.findVertex(0));
    double oldTotal = total;

    auto middle = chrono::high_resolution_clock::now();

    bool foundImprovement = true;
    int n = path.size();
    double epsilon = 1e-9;
    while (foundImprovement)
    {
        foundImprovement = false;
        for (int i = 0; i <= n - 2; i++)
        {
            for (int j = i + 1; j <= n - 1; j++)
            {
                double lengthDelta =
                    this->graph.getDistance(path[i], path[j]) + this->graph.getDistance(path[(i + 1) % n], path[(j + 1) % n]) - this->graph.getDistance(path[i], path[(i + 1) % n]) - this->graph.getDistance(path[j], path[(j + 1) % n]);
                if (lengthDelta < -epsilon)
                {
                    reverse(path.begin() + i + 1, path.begin() + j + 1);
                    total += lengthDelta;
                    foundImprovement = true;
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(middle - start);
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - middle);

    if (this->graph.getNumVertex() <= 100)
    {
        cout << "The TSP path is: ";
        for (auto v : path)
        {
            cout << v->getId() << " -> ";
        }
        cout << "0" << endl;
    }

    cout << "The total distance without 2-opt was: " << oldTotal << endl;
    cout << "The total distance with 2-opt is: " << total << endl;
    cout << "2-opt reduced the path cost in: " << oldTotal - total << endl;

    cout << "The path creation with triangular approximation took: " << duration1.count() << " microseconds" << endl;
    cout << "The path improvement took with 2-opt: " << duration2.count() << " microseconds" << endl;
}

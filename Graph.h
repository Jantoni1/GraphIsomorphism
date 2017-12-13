#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
#include <random>
class Graph
{
private:
    std::vector<std::vector<bool> > matrix;
    std::vector<std::vector<int>  > cycles;
    std::vector<short> Vertex_num;
    std::vector<short> degree;
    std::vector<int> subset;
    size_t Vertices;
    size_t Edges;
    int unique_degrees;
    int n;
    int k;
public:
    long long int recursion_counter;
    Graph(std::istream& s);
    void Cycles();
    bool isIsomorphic(const Graph& other);
    bool permute(const Graph& other);
    bool match(const Graph& other);
    void show();
    void addDegree(std::vector<bool>& ifused);

};


#endif // GRAPH_H_INCLUDED









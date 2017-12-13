#include <iostream>
#include <fstream>
#include "Graph.h"

#ifdef TEST
#define MAX_VERTICES 15
#define MIN_VERTICES 8
#define NUMBER_OF_TESTS 10000
bool Test()
{
    bool check;
    std::vector<int> vec;
    std::string tmp;
    std::stringstream ss1, ss2;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> rnd1(MIN_VERTICES, MAX_VERTICES);
    int vertexcount = rnd1(g);
    std::uniform_int_distribution<> rnd2(0, vertexcount * (vertexcount-1) /2 );
    int edgecount = rnd2(g);
    for(int i=0; i<vertexcount; ++i)
        vec.push_back(i);

    std::shuffle( vec.begin(), vec.end(), g);
    ss1 << vertexcount << std::endl;
    ss2 << vertexcount << std::endl;
    int a,b;
    std::uniform_int_distribution<> dis(0, vertexcount-1);
    for(int i=0; i<edgecount ; ++i)
    {
       a = dis(g);
       b = dis(g);
       ss1 << a <<" "<< b << std::endl;
       ss2 << vec[a] <<" "<< vec[b] << std::endl;
    }
    Graph graph1(ss1);
    Graph graph2(ss2);
    check = graph1.isIsomorphic(graph2);
    return check;
}
#endif // TEST

using namespace std;

int main(int argc, char **argv)
{
#ifdef TEST
    double TICKNUM = 31, counter = 0, NOfTESTS = NUMBER_OF_TESTS,k=1;
    std::cout<<"UNIT TESTS."<<std::endl<<"[";
    for(int i=0;i<NUMBER_OF_TESTS;++i)
     {

         if(Test())
            ++counter;
         if(k/ TICKNUM < (double)i / NOfTESTS)
         {
             std::cout<<"=";
             std::cout.flush();
             k=k+1.0;
         }
     }
     std::cout<<"]"<<std::endl;
     std::cout<<counter<<"/"<<NUMBER_OF_TESTS<<" tests passed."<<std::endl;
#else

    if(argc<3)
    {
        std::cout<<"Wrong number of arguments. Aborted."<<std::endl;
        return -1;
    }
    std::fstream file1, file2;
    file1.open( argv[1], std::ios::in );
    file2.open( argv[2], std::ios::in );
    if( file1.fail() )
    {
        std::cout<<"Could not open first file."<<std::endl;
        return -1;
    }
    if( file2.fail() )
    {
        std::cout<<"Could not open second file."<<std::endl;
        return -1;
    }
    Graph graph1(file2);
    Graph graph(file1);
    file1.close();
    file2.close();
    std::chrono::high_resolution_clock::time_point begin, end;
    begin = std::chrono::high_resolution_clock::now();
    bool check = graph.isIsomorphic(graph1);
    end = std::chrono::high_resolution_clock::now();
    if(!check)
        std::cout<<"Graphs are not isomorphic."<<std::endl;
	std::cout << std::chrono::duration<double, std::milli>(end - begin).count()<<" ms."<<std::endl;
    //std::cout<<"Recursion counter: "<<graph.recursion_counter<<std::endl;


    return 0;
#endif //TEST
}

#include "Graph.h"
inline void swap(std::vector<short> &Vertex_num, int i, int k)
{
  short c;
     c = Vertex_num[i];
  Vertex_num[i]=Vertex_num[k];
  Vertex_num[k]=c;
}
inline void MultipleMatrix(std::vector<std::vector<int> >& first, std::vector<std::vector<int> >& second, std::vector<std::vector<int> >& third, int Vertices)
{
  for(int i=0; i<Vertices; i++)
  {
   for(int j=0; j<Vertices; j++)
   {
         third[i][j]=0;
         for(int k=0; k<Vertices; k++)
         {
            third[i][j]+= first[i][k] * second[k][j];
         }
    }
  }
}
Graph::Graph(std::istream& s): Vertices(0), Edges(0), unique_degrees(2), n(1), k(0), recursion_counter(0)
{
    std::stringstream ss;
    unsigned a=0 , b=0;
    std::string cp, check="";
    std::vector<bool> ifused;
    s >> Vertices;
    ifused.resize(Vertices);
    degree.resize(Vertices);
    matrix.resize(Vertices);
    for(unsigned i=0; i<Vertices; ++i)
        matrix[i].resize(Vertices);
    std::getline(s, cp);
    while(std::getline(s, cp))
    {
        ss.clear();
        ss << cp;
        ss >> a >> b >> check;
        if(check.size() == 0)
        {
            if(a >= Vertices || b >= Vertices)
            {
                std::cout<<"Invalid vertex number in file. Aborted."<<std::endl;
                return;
            }
            if(matrix[a][b] == true)
                continue;
            matrix[a][b] = true;
            matrix[b][a] = true;
            ++degree[a];
            if(a!=b)
                ++degree[b];
            ++Edges;
        }
        else
        {
            std::cout<<"Found unknown expression in file: "<<check<<". The rest of the line is ignored." <<std::endl;
            check="";
        }
    }
    Cycles();
    addDegree(ifused);
}
void Graph::addDegree(std::vector<bool> &ifused)
{
    std::vector<int> temp;
    temp.resize(3);
    temp[0]=-1;
    temp[2]=0;
    for(unsigned i=0; i<Vertices; ++i)
    {
        for(unsigned k=0; k<Vertices; ++k)
        {
            if( !ifused[k] && (temp[0] == -1 || (temp[0] > degree[k] || (temp[0] == degree[k] &&  temp[2] > cycles[k][k] ) ) ) )
            {
                temp[0] = degree[k];
                temp[1] = k;
                temp[2] = cycles[k][k];
            }
        }
        ifused[temp[1]] = true;
        Vertex_num.push_back(temp[1]);
        temp[0] = -1;
        temp[2]=-1;
    }
    subset.push_back(0);
    for(unsigned i=1; i<Vertices; ++i)
        if(degree[Vertex_num[i]] != degree[Vertex_num[i-1]] || ( degree[Vertex_num[i]] == degree[Vertex_num[i-1]] && cycles[Vertex_num[i] ][Vertex_num[i] ] != cycles[ Vertex_num[i-1] ][ Vertex_num[i-1] ] ) )
        {
            ++unique_degrees;
            subset.push_back(i);
        }
    subset.push_back(Vertices);
}

void Graph::Cycles()
{
    cycles.resize(Vertices);
    for(unsigned i=0; i<Vertices; ++i)
    {
        cycles[i].resize(Vertices);
        for(unsigned j=0;j<Vertices; ++j)
            if(i!=j)
                cycles[i][j] = matrix[i][j];
            else
                cycles[i][j] = 0;
    }
    std::vector<std::vector<int> > first = cycles, third = cycles;
    MultipleMatrix(first, cycles, third, Vertices);
    MultipleMatrix(third, first, cycles, Vertices);
}

bool Graph::isIsomorphic(const Graph& other)
{
    if(Vertices != other.Vertices || Edges != other.Edges || unique_degrees != other.unique_degrees)
        return false;
    for(unsigned i=0;i<Vertices; ++i)
        if(degree[ Vertex_num[i] ] != other.degree[ other.Vertex_num[i] ])
              return false;
    return permute(other);
}
bool Graph::permute(const Graph& other)
{
        if( n < unique_degrees )
        {
                if( k < subset[n] )
                {
                    for(int i = k ; i < subset[n]; i++)
                    {
                        swap(Vertex_num, i, k);
                        ++k;
                        if(permute(other) == true)
                            return true;
                        --k;
                        swap(Vertex_num, i, k);
                    }
                }
                else if( n+1<unique_degrees )
                {
                      ++n;
                      if(permute(other) == true)
                        return true;
                      --n;
                }
                else return match(other);

        }
        else  return match(other);
    return false;
}
bool Graph::match(const Graph& other)
{
    ++recursion_counter;
    for(unsigned i=0; i<Vertices; ++i)
        for(unsigned j=i ; j<Vertices; ++j)
            if(matrix[ Vertex_num[i] ][ Vertex_num[j] ] != other.matrix[ other.Vertex_num[i] ][ other.Vertex_num[j] ] )
                return false;
#ifndef TEST
    std::cout<<"Graphs are isomorphic."<<std::endl;
    int vertices=Vertices;
    for(int i=0; i<vertices; ++i)
        for(int j=0; j<vertices; ++j)
            if(Vertex_num[j] == i)
                std::cout<<Vertex_num[j]<<" --> "<<other.Vertex_num[j]<<std::endl;
    std::cout << std::endl;
#endif // TEST
    return true;
}
void Graph::show()
{
    for(unsigned i=0; i<Vertices; ++i)
    {
        for(unsigned j=0; j<Vertices; ++j)
            std::cout<<matrix[i][j]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

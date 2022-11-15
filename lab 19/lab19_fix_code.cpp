// A C++ Program to detect cycle in a graph
#include <iostream>
#include <vector>

class Graph
{
  int V;                                              // No. of vertices
  std::vector<int> *adj;                              // Pointer to an array containing adjacency lists
  bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic()
public:
  Graph(int V);               // Constructor
  void addEdge(int v, int w); // to add an edge to graph
  bool isCyclic();            // returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new std::vector<int>[V]; // where does this get deleted????
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w); // Add w to v’s list.
}

// This function is a variation of DFSUtil() in
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
  if (visited[v] == false)
  {
    // Mark the current node as visited and part of recursion stack
    visited[v] = true;
    recStack[v] = true;

    // Recur for all the vertices adjacent to this vertex
    std::vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
      if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
      {
        return true;
      }
      else if (recStack[*i])
      {
        return true;
      }
    }
  }
  recStack[v] = false; // remove the vertex from recursion stack
  return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
  // Mark all the vertices as not visited and not part of recursion
  // stack
  bool *visited = new bool[V];  // where does this get deleted????
  bool *recStack = new bool[V]; // where does this get deleted????
  for (int i = 0; i < V; i++)
  {
    visited[i] = false;
    recStack[i] = false;
  }

  // Call the recursive helper function to detect cycle in different
  // DFS trees
  for (int i = 0; i < V; i++)
  {

    if (!visited[i] && isCyclicUtil(i, visited, recStack))
    {
      return true;
    }
  }

  delete[] visited;
  delete[] recStack;

  return false;
}

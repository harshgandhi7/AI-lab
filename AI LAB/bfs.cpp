#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph
{
  int V;
  list<int> *adj;

public:
  Graph(int V); // Constructor

  void addEdge(int v, int w);
  void BFS(int s);
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w);
}

void Graph::BFS(int s)
{

  vector<bool> visited(V, false);

  queue<int> queue;

  visited[s] = true;
  queue.push(s);

  while (!queue.empty())
  {

    s = queue.front();
    cout << s << " ";
    queue.pop();

    for (auto adjVertex : adj[s])
    {
      if (!visited[adjVertex])
      {
        visited[adjVertex] = true;
        queue.push(adjVertex);
      }
    }
  }
}

int main()
{
  Graph g(4);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(2, 0);
  g.addEdge(2, 3);
  g.addEdge(3, 3);

  cout << "Breadth First Traversal (starting from vertex 2): ";
  g.BFS(2);

  return 0;
}

#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include<queue>
using namespace std;

class FromToDivisible {
  public:
    int shortest(int N, int S, int T, vector <int> a, vector <int> b);
};

//Finds the LCM of two numbers 
int FindLCM(int i, int j, int N)
{
  int z, x, y, a, GCD, s, t;
  long long LCM;

  x = i;
  y = j; 
  while (y != 0)
  {
    a = x % y;
    x = y;
    y = a;
  }
  
  GCD = x;
  LCM = (((long long)i / GCD) * j); //Calculates LCM and prevents integer overflow
  
  if (LCM > N) LCM = -1; 
  return (int)LCM;
}

//Finds shortest path between S and T, if none exists, returns -1
int FromToDivisible::shortest(int N, int S, int T, vector <int> a, vector <int> b)
{
  vector<int> as, bs, distances, backlinks, links; //Parallel vectors for nodes, node i = {a(i), b(i)}
  vector<vector<int>> edges; //Stores edges for each node
  queue <int> bfs; 
  int M, LCM, bi, aj, size, node, edge, distance; 

  M = a.size(); 

  //Creates nodes 
  for (int i = 0; i < M; i++)
  {
    as.push_back(a.at(i)); //a(i)
    bs.push_back(b.at(i)); //b(i)  
  }
  
  //total nodes = M + 2; 
  edges.resize(M + 2); //Resizes outer vector

  //Creates links from S to node i and from T to node i
  for (int i = 0; i < M; i++)
  {
    if (S % as.at(i) == 0) edges[0].push_back(i+1); //S = edges[0], connects nodes from S
    if (T % bs.at(i) == 0) edges[i+1].push_back(M+1); //T = edges[last], connects nodes to T
  }


  //Iterate through all other nodes a(i) and b(j) and connect edges 
  for (int i = 0; i < M; i++)
  {
    bi = bs.at(i);  //Node i
    for (int j = 0; j < M; j++)
    {
      if (i == j) continue; //Prevents checking same node
      aj = as.at(j);
      if (FindLCM(bi, aj, N) != -1)
      {
        edges[i+1].push_back(j+1); 
      }
    }   
  }
  
  //Resizes distances and backlinks
  distances.resize(M+2, -1); 
  backlinks.resize(M+2, -1); 
  
  bfs.push(0);  //Pushes first node on, S
  distances.at(0) = 0; 

  //Carries out the BFS
  while (!bfs.empty())  //Change back to while loop, I want to test for loop 
  {
    node = bfs.front();
    bfs.pop();
    links = edges.at(node); //Gets edges
    size = links.size();
    for (int j = 0; j < size; j++)  //Iterate through edges and carry out BFS
    {
      edge = links.at(j);
      if (distances.at(edge) != -1) continue; //Skips if link has already been found

      distances.at(edge) = distances.at(node) + 1;
      backlinks.at(edge) = node; 
      bfs.push(edge); 
    }
  }

  distance = distances.at(distances.size() -1); //Grabs distance as distance from S to final node T

  if (distance != -1) distance--; //Adjusts distance 
  return distance;
}

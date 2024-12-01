/****************************
Templated created by Kazumi Slott
CS311

Your name: Scott Leyden
Your programmer number: 20
Hours spent: 4
Any difficulties?:
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
using namespace std;

class edge
{
  friend class graph;  //What do you need here if you want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w;};
  int getNeighbor() const {return neighbor;};
  int getWt() const {return wt;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  int getNumVer() const {return num_ver;}; 
  list<edge*>* getVerAr() const {return ver_ar;};
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object
  ver_ar = new list<edge*>[num];
  num_ver = num;
}

graph::~graph()
{
  for (int i = 0; i < num_ver; i++)
  {
    for (list<edge*>::iterator u = ver_ar[i].begin(); u != ver_ar[i].end(); u++)
    {
      delete *u;
    }
    ver_ar[i].clear();
  }
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
  ver_ar[v].push_back(new edge(u, w));
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.
  for (int i = s; i < num_ver; i++)
  {
    if (num[i] == 0){ return i; }
  }
  for (int i = 1; i < start; i++)
  {
    if (num[i] == 0){ return i; }
  }
  return -1;
}

//start Traversal at start
void graph::DFT(int start)
{
  queue<string> edges;
  int* num = new int[num_ver];
  for (int i = 0; i < num_ver; i++)
  {
    num[i] = 0;
  }
  int i = 1;
  int vert = start;
  do
  {
    DFT_helper(vert, i, num, edges);
    vert = (nextUnvisitedNodes(num, vert, vert + 1));
  } while (nextUnvisitedNodes(num, start, start + 1) != -1);
  displayQueue(edges);
  delete num;
}



void graph::DFT_helper(int vert, int& i, int* num, queue<string>& q)
{
  num[vert] = i++;
  cout << vert << " ";
  
  for (list<edge*>::iterator u = ver_ar[vert].begin(); u != ver_ar[vert].end(); u++)
  {
    if (num[(*u)->neighbor] == 0)
    {
      q.push(to_string(vert) + "->" + to_string((*u)->neighbor));
      DFT_helper((*u)->neighbor, i, num, q);
    } 
  }
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  queue<int> q;
  queue<string> edges;
  int* num = new int[num_ver];
  for (int i = 0; i < num_ver; i++)
  {
    num[i] = 0;
  }
  int i = 1;
  int vert = start;
  while (nextUnvisitedNodes(num, start, start + 1) != -1)
  {
    num[vert] = i++;
    q.push(vert);
    while (!q.empty())
    {
      vert = q.front();
      q.pop();
      cout << vert << " ";
      for (list<edge*>::iterator u = ver_ar[vert].begin(); u != ver_ar[vert].end(); u++)
      {
        if (num[(*u)->neighbor] == 0)
        {
          num[(*u)->neighbor] = i++;
          q.push((*u)->neighbor);
          edges.push(to_string(vert) + "->" + to_string((*u)->neighbor));
        }
        
      }
    }
    vert = nextUnvisitedNodes(num, start, start + 1);
  }
  displayQueue(edges);
  delete num;
}

#endif

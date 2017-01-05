#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>

using namespace std;

typedef int WeightType;
typedef int NodeType;

int const MaxNumNodex = 9999;

typedef int NodeWeight;
typedef int EdgeWeight;

class node
{
public:
   node();
   node(const node &);
   node &operator=(const node &);
   
   void setId(int i);
   int getId() const;
   
   void setPred(int);
   int getPred() const;
   
   void setWeight(NodeWeight);
   NodeWeight getWeight() const;
   
   void setNode(int, NodeWeight, bool, bool,int);
   
   void mark();
   void unMark();
   bool isMarked() const;
   
   void visit();
   void unVisit();
   bool isVisited() const;
   
private:
   int id;
   NodeWeight weight;
   bool marked;
   bool visited;
   int pred;
};

node::node()
// Constructor, creates a new, uninitialized node. Id is initialized
// elsewhere (by the graph constructor).
{
   unMark();
   unVisit();
   setWeight(0);
}

node::node(const node &n)
// Copy constructor
{
   setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited(),
           n.getPred());
}

node &node::operator=(const node &n)
// Overloaded assignment operator.
{
   setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited(),
           n.getPred());
   return *this;
}

NodeWeight node::getWeight() const
// Return node's weight
{
   return weight;
}

void node::setWeight(NodeWeight w)
// Set node's weight to w.
{
   weight = w;
}
   
void node::setId(int i)
// Set node's id to i.  Throws an exception if i < 0.
{
   if (i < 0)
      throw rangeError("Bad value in node::setId");
   
   id = i;
}
   
int node::getId() const
// Return node's id
{
   return id;
}

void node::setNode(int id, NodeWeight w = 0, bool m = false, bool v = false, int p=0)
// Initialize a node;
{
   setId(id);
   setWeight(w);
   setPred(p);
   
   if (m)
      mark();
   else
      unMark();
   
   if (v)
      visit();
   else
      unVisit();
}

int node::getPred() const
// Return node's predecessor
{
   return pred;
}

void node::setPred(int val)
// Set node's predecessor to val
{
   pred = val;
}

void node::mark()
   // Mark node.
{
   marked = true;
}

void node::unMark()
   // Un-mark node.
{
   marked = false;
}

bool node::isMarked() const
   // Return true if node is marked, and false otherwise.
{
   return marked;
}

void node::visit()
   // Set visited to true;
{
   visited = true;
}

void node::unVisit()
   // Set visited to false;
{
   visited = false;
}

bool node::isVisited() const
   // Return true if node is visited, and false otherwise.
{
   return visited;
}


ostream &operator<<(ostream &ostr, const node &n)
{
   ostr << "node: " << n.getId() << " weight: " << n.getWeight()
   << " visited: " << n.isVisited() << " marked " << n.isMarked()
   << " predecessor: " << n.getPred() << endl;
   return ostr;
}

bool operator<(const node &n1, const node &n2)
// Compare nodes based on weights.
{
   return n1.getWeight() < n2.getWeight();
}

bool operator>(const node &n1, const node &n2)
// Compare nodes based on weights.
{
   return n1.getWeight() > n2.getWeight();
}

bool operator==(const node &n1, const node &n2)
// Compare nodes based on weights.
{
   return n1.getWeight() == n2.getWeight();
}

#endif


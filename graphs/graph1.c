#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <functional>
#include <algorithm>
#include <limits.h>
using namespace std;

const unsigned int MAXKEY = 2048;
const int INFINITY = INT_MAX/2;
template <typename VertexType, typename EdgeType>
class Graph
{
 public:
     Graph(int num = 0)
         : nodenum(num)
     {
     }

     void insertArc(int begin, int end, int weight=-1)
     {
         EdgeList &adj = nodevec[begin-1].adj;
         EdgeNode enode(begin-1, end-1, weight);
         edgevec.push_back(enode);
         adj.push_back(enode);
     }

     void create376()
     {
         nodevec.push_back(VertexNode('s'));
         nodevec.push_back(VertexNode('t'));
         for (int i = 0; i < 3; i++)
             nodevec.push_back(VertexNode('x'+i));
         insertArc(1, 2, 6);
         insertArc(1, 4, 7);
         insertArc(2, 3, 5);
         insertArc(2, 4, 8);
         insertArc(2, 5, -4);
         insertArc(3, 2, -2);
         insertArc(4, 3, -3);
         insertArc(4, 5, 9);
         insertArc(5, 1, 2);
         insertArc(5, 3, 7);
     }

     void create367()
     {
         nodevec.push_back(VertexNode('s'));
         nodevec.push_back(VertexNode('t'));
         for (int i = 0; i < 3; i++)
             nodevec.push_back(VertexNode('x'+i));
         insertArc(1, 2, 10);
         insertArc(1, 4, 5);
         insertArc(2, 3, 1);
         insertArc(2, 4, 2);
         insertArc(3, 5, 4);
         insertArc(4, 2, 3);
         insertArc(4, 3, 9);
         insertArc(4, 5, 2);
         insertArc(5, 1, 7);
         insertArc(5, 3, 6);
     }

     void display()
     {
         cout << "输出图的邻接表：" << endl;
         for (int i = 0; i < nodevec.size(); i++)
         {
              cout << nodevec[i].data << "->"; 
              EdgeList adj = nodevec[i].adj;
              typename EdgeList::iterator it;
              for (it = adj.begin(); it != adj.end(); it++)
              {
                  int index = (*it).adjvex;
                  cout << nodevec[index].data << "("
                      << it->weight << ")->";
              }
              cout << endl;
         }
     }

     void printPath()
     {
         int si;
         cout << "please input the source node:";
         cin >> si;
         for (int i = 0; i < nodenum; i++)
         {
             if (i != si-1)
             {
                printPath(nodevec[si-1], &nodevec[i]);
                cout << endl;
             }
         }
     }

     bool BELLMAN_FORD(int index)
     {
         nodevec[index-1].dist = 0;
         VertexNode *node;
         VertexNode *dnode;
         for (int i = 0; i < nodevec.size()-1; i++)
         {
             for (int j = 0; j < nodevec.size(); j++)
             {
                 node = &nodevec[j];
                 typename EdgeList::iterator it;
                 for (it = node->adj.begin(); it != node->adj.end();
                         it++)
                 {
                     dnode = &nodevec[(*it).adjvex];
                     if (node->dist + (*it).weight < dnode->dist)
                     {
                         dnode->dist = node->dist + (*it).weight;
                         dnode->path = node;
                     }
                 }
             }
         }

         for (int i = 0; i < edgevec.size(); i++)
         {
             EdgeNode enode = edgevec[i];
             if (nodevec[enode.adjvex].dist >
                     nodevec[enode.source].dist + enode.weight)
                 return false;
         }

         cout << "Bellman-ford:" << endl;
	 for (int i = 0; i < nodevec.size(); i++)
	 {
	     cout << nodevec[index-1].data << "->" << nodevec[i].data 
	          << "(" << nodevec[i].dist << ")" << endl;
	 }
	 return true;
     }

     void dijkstra(int index)
     {
         nodevec[index-1].dist = 0;
         vector<VertexNode *> s, q;
	 //vector<VertexNode *> q;

	 for (int i = 0; i < nodevec.size(); i++)
	     q.push_back(&nodevec[i]);
	 make_heap(q.begin(), q.end(), VertexNodeSort());
 
         cout << "dijkstra:" << endl;
         VertexNode *node;
	 VertexNode *dnode;
	 while (!q.empty())
	 {
	     node = q.front();
	     cout << nodevec[index-1].data << "->" << node->data 
	          << "(" << node->dist << ")" << endl;
	     pop_heap(q.begin(), q.end(), VertexNodeSort());
	     q.pop_back();
	     s.push_back(node);
	     typename EdgeList::iterator it;
	     for (it = node->adj.begin(); it != node->adj.end(); it++)
	     {
	         dnode = &nodevec[(*it).adjvex];
		 if (node->dist + (*it).weight < dnode->dist)
		 {
		     dnode->dist = node->dist + (*it).weight;
		     dnode->path = node;
		 }
	     }
             make_heap(q.begin(), q.end(), VertexNodeSort());
	 }
     }
     
 private:
     struct EdgeNode
     {
         int source;
         int adjvex;
         EdgeType weight;
         EdgeNode *next;

         EdgeNode() : source(-1), adjvex(-1), weight(-1), next(NULL)
         {}
         EdgeNode(int src, int adj, int wei = -1, EdgeNode *n = NULL)
             : source(src), adjvex(adj), weight(wei), next(n)
         {}

         friend bool operator<(const EdgeNode &enode1, 
                 const EdgeNode &enode2)
         {
             return enode1.weight < enode2.weight;
         }
     };

     enum VertexColor {WHITE, GRAY, BLACK};
     typedef list<EdgeNode> EdgeList;
     struct VertexNode
     {
         VertexType data;
         EdgeList adj;
         int dist;
         VertexColor color;
         VertexNode *path;
	 int key;
         VertexNode(VertexType d) : data(d), dist(INFINITY), 
             path(NULL), color(WHITE)
         {}
         VertexNode() : data(-1), dist(INFINITY), path(NULL),
            color(WHITE)
         {}
     };

     void printPath(VertexNode &s, VertexNode *v)
     {
         if (&s == v)
             cout << s.data << "->";
         else if (v->path == NULL)
             cout << "no path from " << s.data << " to " << v->data << endl;
         else
         {
             printPath(s, v->path);
             cout << v->data << "->";
         }
     }

     //定义prim时堆的内容的大小，堆中存储的是指向VertexNode的指针，
     //比较准则是根据这个结构中的dist的大小比较，建小顶堆，
     class VertexNodeSort
     {
     public:
         bool operator()(const VertexNode *node1, 
	     const VertexNode *node2) const
         {
             return node1->dist > node2->dist;
         }
     };
     vector<VertexNode> nodevec;
     vector<EdgeNode> edgevec;
     int nodenum;
};

int main()
{
    Graph<char, int> g, g1;
    g.create376();
    g.display();
    if (!g.BELLMAN_FORD(1))
        cout << "不存在最短路径" << endl;
    g1.create367();
    g1.display();
    g1.dijkstra(1);
    return 0;
}

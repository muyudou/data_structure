#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <functional>
#include <algorithm>
#include <stdio.h>
#include "disjset.h"
using namespace std;

const unsigned int MAXKEY = 2048;
const int INFINITY = -1;
template <typename VertexType, typename EdgeType>
class Graph
{
 public:
     Graph(int num = 0)
         : nodenum(num)
     {
     }

     void create()
     {
         VertexType data; 
         while (cin >> data && data != EOF)
         {
             VertexNode node(data);
   
             int index, weight;
                 while (cin >> index && index != -1)
                 {
                     EdgeNode enode(index);
                     (node.adj).push_back(enode);
                 }
             nodevec.push_back(node);
             nodenum++;
         }
     }

     void createW()
     {
         VertexType data; 
         while (cin >> data && data != EOF)
         {
             VertexNode node(data);
   
             int index, weight;
             while (cin >> index >> weight && index != -1)
             {
                 EdgeNode enode(index, weight);
                 (node.adj).push_back(enode);
             }
             nodevec.push_back(node);
             nodenum++;
         }
     }

     void create94()
     {
         vector<int> vec;
         for (int i = 1; i <= 7; i++)
         {
             nodevec.push_back(VertexNode(i));
             nodenum++;
         }
         int index;
         for (int i = 0; i < nodevec.size(); i++)
         {
             while (cin >> index && index != -1)
             {
                 EdgeNode enode(index);
                 nodevec[i].adj.push_back(enode);
                 nodevec[index].indegree++;
             }
         }
     }

     void insertArc(int begin, int end, int weight=-1)
     {
         EdgeList &adj = nodevec[begin-1].adj;
         nodevec[end-1].indegree++;
         EdgeNode enode(begin-1, end-1, weight);
         adj.push_back(enode);
     }

     void create368()
     {
         for (int i = 0; i < 9; i++)
             nodevec.push_back(VertexNode('a'+i));
         insertArc(1, 2, 4);
         insertArc(1, 8, 8);
         insertArc(2, 3, 8);
         insertArc(2, 8, 11);
         insertArc(3, 2, 8);
         insertArc(3, 4, 7);
         insertArc(3, 6, 4);
         insertArc(3, 9, 2);
         insertArc(4, 3, 7);
         insertArc(4, 5, 9);
         insertArc(4, 6, 14);
         insertArc(5, 4, 9);
         insertArc(5, 6, 10);
         insertArc(6, 3, 4);
         insertArc(6, 4, 14);
         insertArc(6, 5, 10);
         insertArc(6, 7, 2);
         insertArc(7, 6, 2);
         insertArc(7, 8, 1);
         insertArc(7, 9, 6);
         insertArc(8, 7, 1);
         insertArc(8, 1, 8);
         insertArc(8, 9, 7);
         insertArc(9, 3, 2);
         insertArc(9, 7, 6);
         insertArc(9, 8, 7);
     }

     void getindegree()
     {
         EdgeList adjlist;
         typename EdgeList::iterator it;
         for (it = adjlist.begin(); it != adjlist.end(); it++)
             nodevec[(*it).adjvex].indegree++;
     }

     void display()
     {
         cout << "输出图的邻接表：" << endl;
         for (int i = 0; i < nodevec.size(); i++)
         {
              cout << nodevec[i].data << "[" 
                  << nodevec[i].indegree << "]->";
              EdgeList adj = nodevec[i].adj;
             // cout << adj.size() << endl;
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

         void topSort()
         {
             deque<VertexNode> deq;
             for (int i = 0; i < nodenum; i++)
                 if (nodevec[i].indegree == 0)
                     deq.push_back(nodevec[i]);

             int counter = 0;
             VertexNode node;
             while (!deq.empty())
             {
                 node = deq.front();
                 deq.pop_front();
                 cout << node.data << " ";
                 counter++;
                 typename EdgeList::iterator it;
                 for (it = node.adj.begin(); it != node.adj.end(); it++)
                 {
                     VertexNode &adjnode = nodevec[(*it).adjvex];
                     if (--adjnode.indegree == 0)
                         deq.push_back(adjnode);
                 }
             }
             cout << endl;
             if (counter != nodenum)
                 cout << "circle exists" << endl;
         }

     void BFS(int index)
     {
         nodevec[index-1].dist = 0;
         deque<VertexNode*> deq;  //因为要记录上一个节点，所以用指针
         deq.push_back(&nodevec[index-1]);
         
         while (!deq.empty())
         {
             VertexNode *node = deq.front();
             cout << node->data << " ";
             deq.pop_front();
             typename EdgeList::iterator it;
             //将该节点的邻接点的距离改为该节点的距离加1，并将邻接点的path
             //设置为该节点，并进队
             EdgeList adj = node->adj;
             for (it = adj.begin(); it != adj.end(); it++)
             {
                 VertexNode &adjnode = nodevec[(*it).adjvex];
                 if (adjnode.dist == INFINITY)
                 {
                // cout << "adj:" << adjnode.data << endl;
                 adjnode.dist = node->dist+1;
                 adjnode.path = node;
                 deq.push_back(&adjnode);
                 }
             }
         }
         cout << endl;
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

     //递归实现深度优先搜索
     void DFS()
     {
         int time = 0;
         for (int i = 0; i < nodenum; i++)
             if (nodevec[i].color == WHITE)
             {
                 cout << endl;
                 DFS(nodevec[i], time);
                 cout << endl;
             }
     }

     //首先将所有节点入优先队列，源节点的key设置为0, 其余是infinite,
     //之后判断队列是否为空，将key最小的元素出队，并依次遍历邻接点，
     //对于每个邻接点v，判断该w(u,v)是否小于当前v的key,小于的话则改变当前的
     //key,并将path设置为源节点

     void PRIM(int index)
     {
         nodevec[index-1].key = 0;
         vector<VertexNode*> prique;
         for (int i = 0; i < nodevec.size(); i++)
             prique.push_back(&nodevec[i]);
         make_heap(prique.begin(), prique.end(), 
	     VertexNodeSort());
         
         VertexNode *node;
         VertexNode *vex;
         int sumw = 0, i=0;
         cout << "PRIM生成的最小生成树是: "; 
         while (!prique.empty())
         {
             node = prique.front();
             cout << node->data << " ";
             sumw += node->key;
             pop_heap(prique.begin(), prique.end(), VertexNodeSort());
	     prique.pop_back();
	     i++;
             typename EdgeList::iterator it;
             EdgeList adj = node->adj;
             for (it = adj.begin(); it != adj.end(); it++)
             {
	         vex = &nodevec[(*it).adjvex];
                 if (find(prique.begin(), prique.end(), vex) != prique.end()
                      && it->weight < vex->key)
                 {
                     vex->path = node;
                     vex->key = it->weight;
                 }
             }
             make_heap(prique.begin(), prique.end(), 
                     VertexNodeSort());
         }
         cout << endl;
         cout << "最小生成树的总权重是: " << sumw << endl;
     }

     void KRUSKAL()
     {
         DisjSets d(nodevec.size());
         vector<EdgeNode> edgevec, edgetree;

         VertexNode node;
         for(int i = 0; i < nodevec.size(); i++)
         {
             node = nodevec[i];
             typename EdgeList::iterator it;
             for (it = node.adj.begin(); it != node.adj.end(); it++)
                 edgevec.push_back(*it);
         }
         sort(edgevec.begin(), edgevec.end());
         for (typename vector<EdgeNode>::iterator it = edgevec.begin();
                 it != edgevec.end(); it++)
         {
             int ps = d.find((*it).source);
             int pa = d.find((*it).adjvex);
             if (ps != pa)
             {
                 edgetree.push_back(*it);
                 d.unionSets(ps, pa);
             }
         }

         int sumw = 0;
         for (int i = 0; i < edgetree.size(); i++)
         {
             cout << "第 " << i << " 条边（" 
                 << nodevec[edgetree[i].source].data << "->"
                 << nodevec[edgetree[i].adjvex].data << ")权重是"
                 << edgetree[i].weight << endl;
             sumw += edgetree[i].weight;
         }
         cout << "最小生成树的总权重是:" << sumw << endl;
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
         int indegree;
         int dist;
         VertexColor color;
         int start;
         int end;
         VertexNode *path;
	 int key;
         VertexNode(VertexType d) : data(d), indegree(0)
            , dist(INFINITY), path(NULL), color(WHITE), 
	    start(0), end(0), key(MAXKEY)
         {}
         VertexNode() : data(-1), indegree(0), dist(INFINITY), path(NULL),
            color(WHITE), start(0), end(0), key(MAXKEY)
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

     void DFS(VertexNode &v, int time)
     {
         cout << v.data << "->";
         v.start = ++time;
         v.color = GRAY;
         typename EdgeList::iterator it;
         for (it = v.adj.begin(); it != v.adj.end(); it++)
         {
             VertexNode &node = nodevec[(*it).adjvex];
             if (node.color == WHITE)
             {
                 node.path = &v; 
                 DFS(node, time);
             }
         }
         v.color = BLACK;
         v.end = ++time;
     }

     //定义prim时堆的内容的大小，堆中存储的是指向VertexNode的指针，
     //比较准则是根据这个结构中的dist的大小比较，建小顶堆，
     class VertexNodeSort
     {
     public:
         bool operator()(const VertexNode *node1, 
	     const VertexNode *node2) const
         {
             return node1->key > node2->key;
         }
     };
     vector<VertexNode> nodevec;
     int nodenum;
};

int main()
{
    Graph<char, int> g;
    g.create368();
    g.display();
    //g.topSort();
    //g.BFS(3);
    //g.printPath();
    //g.DFS();
    //g.printPath();
    g.PRIM(1);
    g.printPath();
    g.KRUSKAL();
    return 0;
}

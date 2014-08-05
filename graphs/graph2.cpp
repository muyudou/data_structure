#include <vector>
#include <iostream>
#include <limits.h>
using namespace std;

template <typename Comparable>
class Graph
{
public:
    Graph(int ndnum) : nodenum(ndnum)
    {
        nodevec.reserve(nodenum);
        wmat.reserve(nodenum);
        for (int i = 0; i < nodenum; i++)
        {
            wmat.push_back(vector<int>(nodenum)); 
            for (int j = 0; j < nodenum; j++)
            {
                if (i == j)
                    wmat[i][j] = 0;
                else
                    wmat[i][j] = INT_MAX/2;
            }
        }
    }

    void insertArc(int begin, int end, int weight = -1)
    {
        wmat[begin][end] = weight;
    }

    void create402()
    {
        for (int i = 0; i < nodenum; i++)
            nodevec[i] = i+1;
        insertArc(0, 1, 3);
        insertArc(0, 2, 8);
        insertArc(0, 4, -4);
        insertArc(1, 3, 1);
        insertArc(1, 4, 7);
        insertArc(2, 1, 4);
        insertArc(3, 0, 2);
        insertArc(3, 2, -5);
        insertArc(4, 3, 6);
    }

    void displayGraph()
    {
        for (int i = 0; i < nodenum; i++)
            cout << nodevec[i] << " ";
        cout << endl;
        displaymat(wmat);
    }

    void displaymat(vector<vector<int> > &mat)
    {
        for (int i = 0; i < nodenum; i++)
        {
            for (int j = 0; j < nodenum; j++)
            {
                if (mat[i][j] == INT_MAX/2)
                    cout << "@ ";
                else
                    cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void extend_shortest_paths(vector<vector<int> > &preL, 
         vector<vector<int> > &L)
    {
        matinit(L);
        for (int i = 0; i < nodenum; i++)
            for (int j = 0; j < nodenum; j++)
                for (int k = 0; k < nodenum; k++)
                     L[i][j] = min(L[i][j], preL[i][k] + wmat[k][j]);
        displaymat(L);
    }

    void slow_shortest_paths()
    {
        vector<vector<int> > preL;
        for (int i = 0; i < nodenum; i++)
            preL.push_back(wmat[i]);

        vector<vector<int> > L(nodenum);
        for (int i = 0; i < nodenum; i++)
            L[i].resize(nodenum, INT_MAX/2);

        vector<vector<int> > &ppL = preL;
        vector<vector<int> > &pL = L;
        for (int m = 1; m < nodenum-1; m++)
        {
            extend_shortest_paths(ppL, pL);
            ppL = pL;
        }
        displaymat(L);
    }
   
    void matinit(vector<vector<int> > &mat)
    {
        for (int i = 0; i < nodenum; i++)
            for (int j = 0; j < nodenum; j++)
            {
                if (i == j)
                    mat[i][j] = 0;
                else
                    mat[i][j] = INT_MAX/2;
            }
    }

    void floyd()
    {
        vector<vector<int> > pred; //保存上一个d
        for (int i = 0; i < nodenum; i++)
            pred.push_back(wmat[i]);

        vector<vector<int> > d(nodenum); //保存计算出来的d
        vector<vector<int> > prep(nodenum); //保存上一个p
        vector<vector<int> > p(nodenum);    //保存计算出来的p
        //初始化
        for (int i = 0; i < nodenum; i++)
        {
            vector<int> vec(nodenum, -1);
            d[i] = prep[i] = p[i] = vec;
            for (int j = 0; j < nodenum; j++)
            {
                if (i != j && wmat[i][j] < INT_MAX/2)
                    prep[i][j] = i+1;
            }
        }

        cout << "prep: " << endl;
        displaymat(prep);

        vector<vector<int> > &ppd = pred;
        vector<vector<int> > &pd = d;
        vector<vector<int> > &ppp = prep;
        vector<vector<int> > &pp = p;
        for (int k = 0; k < nodenum; k++)
        {
            for (int i = 0; i < nodenum; i++)
                for (int j = 0; j < nodenum; j++)
                {
                    pd[i][j] = min(ppd[i][j], ppd[i][k] + ppd[k][j]);
                    if (ppd[i][j] == INT_MAX/2 && (ppd[i][k] == INT_MAX/2
                                || ppd[k][j] == INT_MAX/2))
                        pd[i][j] = INT_MAX/2;
                    if (pd[i][j] == ppd[i][j])
                        pp[i][j] = ppp[i][j];
                    else
                        pp[i][j] = ppp[k][j];
                }
            cout << "距离矩阵d" << endl;
            displaymat(pd);
            cout << "路径矩阵p" << endl;
            displaymat(pp);
            ppd = pd;
            ppp = pp;
            pd.clear();
            pp.clear();
        }
    }

private:
    vector<vector<int> > wmat;
    vector<Comparable> nodevec;
    int nodenum;
};

int main()
{
    Graph<int> g(5);
    g.create402();
    g.displayGraph();
    //g.slow_shortest_paths();
    g.floyd();
    return 0;
}

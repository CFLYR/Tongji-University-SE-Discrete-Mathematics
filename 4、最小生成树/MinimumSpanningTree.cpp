#include <conio.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

const int MAX_SIZE = 100000;

using namespace std;
void InputChoice(int& value)
{
    char invalue;
    while (1) {
        invalue = _getch();
        if (invalue == 'y') {
            cout << invalue << endl;
            value = 1;
            break;
        } else if (invalue == 'n') {
            cout << invalue << endl;
            value = 0;
            break;
        }
    }

    return;
}

struct Road {
    string first;
    string second;
    int length;
    Road()
        : first("")
        , second("")
        , length(0)
    {
    }
    Road(string f, string s, int l)
        : first(f)
        , second(s)
        , length(l)
    {
    }
};

typedef struct ArcNode {
    int adjvex;
    struct ArcNode* nextarc;
    string sec_name;
    ArcNode()
        : adjvex(0)
        , nextarc(nullptr)
        , sec_name("")
    {
    }
} ArcNode;

typedef struct VNode {
    string Name;
    ArcNode* firstarc;
    VNode()
        : Name("")
        , firstarc(nullptr)
    {
    }
} VNode;

class ALGraph {
private:
    vector<VNode> vertices;
    int vexnum, arcnum;
    set<pair<string, string>> edges;

public:
    ALGraph()
        : vexnum(0)
        , arcnum(0)
    {
    }
    int SearchMost(ArcNode* firstarc, string& second)
    {
        int smallest = MAX_SIZE + 1;
        ArcNode* newNode = new ArcNode();
        while (firstarc->nextarc != nullptr) {
            if (firstarc->adjvex < smallest) {
                smallest = firstarc->adjvex;
                second = firstarc->sec_name;
            }
            firstarc = firstarc->nextarc;
        }
        return smallest;
    }

    unsigned int SearchVex(const string Name)
    {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (Name == vertices[i].Name) {
                return i + 1;
            }
        }
        return 0;
    }
    void CreatGraph()
    {
        cout << "请输入节点数和边数（以空格分隔）\n";
        while (1) {
            cin >> vexnum >> arcnum;
            if (cin.fail() || vexnum < 1 || vexnum > MAX_SIZE || arcnum < 0 || arcnum > vexnum * (vexnum - 1) / 2) {
                cout << "输入错误，请重输" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else {
                break;
            }
        }

        cout << "请依次输入各节点名称\n";
        for (int i = 0; i < vexnum; i++) {
            VNode Alpha;
            vertices.push_back(Alpha);
            string avl_name;
            cin >> avl_name;
            if (!SearchVex(avl_name)) {
                vertices[i].Name = avl_name;
            } else {
                cout << "输入错误，请重输\n";
                i--;
                continue;
            }
        }
        cout << "节点创建完成\n";
    }

    void AddEdges()
    {
        cout << "请输入边的信息，格式为：起点 终点 权重\n";
        for (int i = 0; i < arcnum; i++) {
            string start, end;
            int weight;
            while (1) {
                cin >> start >> end >> weight;
                if (cin.fail() || weight < 1 || weight > MAX_SIZE || !SearchVex(start) || !SearchVex(end) || start == end) {
                    cout << "输入错误，请重输" << endl;
                    cin.clear();
                    cin.ignore(MAX_SIZE, '\n');
                } else if (edges.find({ start, end }) != edges.end() || edges.find({ end, start }) != edges.end()) {
                    cout << "该边已存在，请重输" << endl;
                } else {
                    break;
                }
            }

            edges.insert({ start, end });
            edges.insert({ end, start });

            // 添加从start到end的边
            ArcNode* newNode1 = new ArcNode();
            newNode1->adjvex = weight;
            newNode1->sec_name = end;
            newNode1->nextarc = vertices[SearchVex(start) - 1].firstarc;
            vertices[SearchVex(start) - 1].firstarc = newNode1;

            // 添加从end到start的边
            ArcNode* newNode2 = new ArcNode();
            newNode2->adjvex = weight;
            newNode2->sec_name = start;
            newNode2->nextarc = vertices[SearchVex(end) - 1].firstarc;
            vertices[SearchVex(end) - 1].firstarc = newNode2;
        }
        cout << "边创建完成\n";
    }

    void CreatMST()
    {
        vector<bool> visited(vexnum, false);
        vector<Road> mst;
        priority_queue<Road, vector<Road>, CompareRoad> pq;
        int totalWeight = 0;

        // Start from the first vertex
        int startIndex = 0;
        visited[startIndex] = true;

        addEdgesToPQ(startIndex, pq, visited);

        while (!pq.empty() && mst.size() < size_t(vexnum - 1)) {
            Road minRoad = pq.top();
            pq.pop();

            int secondIndex = SearchVex(minRoad.second) - 1;
            if (!visited[secondIndex]) {
                visited[secondIndex] = true;
                mst.push_back(minRoad);
                totalWeight += minRoad.length;

                addEdgesToPQ(secondIndex, pq, visited);
            }
        }

        if (mst.size() == size_t(vexnum - 1)) {
            cout << "最小生成树构建成功！\n";
            cout << "最小权重和为: " << totalWeight << endl;
            cout << "最小生成树的边如下：\n";
            for (const Road& road : mst) {
                cout << road.first << " - " << road.second << ": " << road.length << endl;
            }
        } else {
            cout << "无法构建连通所有节点的最小生成树，图可能不是连通的。\n";
        }
    }

    struct CompareRoad {
        bool operator()(const Road& r1, const Road& r2)
        {
            return r1.length > r2.length;
        }
    };

    void addEdgesToPQ(int nodeIndex, priority_queue<Road, vector<Road>, CompareRoad>& pq, const vector<bool>& visited)
    {
        ArcNode* arc = vertices[nodeIndex].firstarc;
        while (arc != nullptr) {
            int adjIndex = SearchVex(arc->sec_name) - 1;
            if (!visited[adjIndex]) {
                pq.push(Road(vertices[nodeIndex].Name, arc->sec_name, arc->adjvex));
            }
            arc = arc->nextarc;
        }
    }
};

int main()
{
    char op;
    ALGraph grapher;
    while (1) {
        system("cls");
        cout << "+-------------------------+" << endl;
        cout << "|       最小生成树        |" << endl;
        cout << "+-------------------------+" << endl;
        grapher.CreatGraph();
        grapher.AddEdges();
        grapher.CreatMST();

        int continue_value;
        cout << "是否继续运算？ （y/n）: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }

    return 0;
}
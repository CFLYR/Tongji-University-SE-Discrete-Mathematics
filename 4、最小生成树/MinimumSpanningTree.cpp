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
        cout << "������ڵ����ͱ������Կո�ָ���\n";
        while (1) {
            cin >> vexnum >> arcnum;
            if (cin.fail() || vexnum < 1 || vexnum > MAX_SIZE || arcnum < 0 || arcnum > vexnum * (vexnum - 1) / 2) {
                cout << "�������������" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else {
                break;
            }
        }

        cout << "������������ڵ�����\n";
        for (int i = 0; i < vexnum; i++) {
            VNode Alpha;
            vertices.push_back(Alpha);
            string avl_name;
            cin >> avl_name;
            if (!SearchVex(avl_name)) {
                vertices[i].Name = avl_name;
            } else {
                cout << "�������������\n";
                i--;
                continue;
            }
        }
        cout << "�ڵ㴴�����\n";
    }

    void AddEdges()
    {
        cout << "������ߵ���Ϣ����ʽΪ����� �յ� Ȩ��\n";
        for (int i = 0; i < arcnum; i++) {
            string start, end;
            int weight;
            while (1) {
                cin >> start >> end >> weight;
                if (cin.fail() || weight < 1 || weight > MAX_SIZE || !SearchVex(start) || !SearchVex(end) || start == end) {
                    cout << "�������������" << endl;
                    cin.clear();
                    cin.ignore(MAX_SIZE, '\n');
                } else if (edges.find({ start, end }) != edges.end() || edges.find({ end, start }) != edges.end()) {
                    cout << "�ñ��Ѵ��ڣ�������" << endl;
                } else {
                    break;
                }
            }

            edges.insert({ start, end });
            edges.insert({ end, start });

            // ��Ӵ�start��end�ı�
            ArcNode* newNode1 = new ArcNode();
            newNode1->adjvex = weight;
            newNode1->sec_name = end;
            newNode1->nextarc = vertices[SearchVex(start) - 1].firstarc;
            vertices[SearchVex(start) - 1].firstarc = newNode1;

            // ��Ӵ�end��start�ı�
            ArcNode* newNode2 = new ArcNode();
            newNode2->adjvex = weight;
            newNode2->sec_name = start;
            newNode2->nextarc = vertices[SearchVex(end) - 1].firstarc;
            vertices[SearchVex(end) - 1].firstarc = newNode2;
        }
        cout << "�ߴ������\n";
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
            cout << "��С�����������ɹ���\n";
            cout << "��СȨ�غ�Ϊ: " << totalWeight << endl;
            cout << "��С�������ı����£�\n";
            for (const Road& road : mst) {
                cout << road.first << " - " << road.second << ": " << road.length << endl;
            }
        } else {
            cout << "�޷�������ͨ���нڵ����С��������ͼ���ܲ�����ͨ�ġ�\n";
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
        cout << "|       ��С������        |" << endl;
        cout << "+-------------------------+" << endl;
        grapher.CreatGraph();
        grapher.AddEdges();
        grapher.CreatMST();

        int continue_value;
        cout << "�Ƿ�������㣿 ��y/n��: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }

    return 0;
}
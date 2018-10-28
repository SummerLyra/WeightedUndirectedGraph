#include"Graph.h"

using namespace std;

const int MAX = 1000;
int g[100][100], x[100], bestx[100];
int cl = 0, bestl = MAX, n;

void title()
{
	cout << "--------------------------------------------------" << endl;
	cout << "---------------欢迎使用景点管理系统---------------" << endl;
}

void mainMenu()
{
	cout << "--------------------------------------------------" << endl;
	cout << "[1]修改数据" << endl;
	cout << "[2]最短路径" << endl;
	cout << "[3]景点周边" << endl;
	cout << "[4]线路规划" << endl;
	cout << "[5]退出系统" << endl;
}

void subMenu()
{
	cout << "--------------------------------------------------" << endl;
	cout << "[1]添加景点" << endl;
	cout << "[2]添加路径" << endl;
	cout << "[3]删除景点" << endl;
	cout << "[4]删除路径" << endl;
	cout << "[5]修改路径" << endl;
	cout << "[6]退出系统" << endl;
}

int main()
{
	int mainChoice = 0;
	int subChoice = 0;
	int mainLoop = 1;
	int subLoop = 1;
	string dept, arrv;
	double dist;
	int num;
	string* array = nullptr;
	Graph g;
	g.readFile();
	title();
	while (mainLoop == 1)
	{
		mainLoop = 0;
		mainMenu();
		cin >> mainChoice;
		switch (mainChoice)
		{
		case 1:
			subLoop = 1;
			while (subLoop == 1)
			{
				subLoop = 0;
				subMenu();
				cin >> subChoice;
				switch (subChoice)
				{
				case 1:
					cout << "请输入要添加的景点名称：" << endl;
					cin >> dept;
					g.addVertex(dept);
					break;
				case 2:
					cout << "请输入要添加路径的两端点及距离：" << endl;
					cin >> dept >> arrv >> dist;
					g.addEdge(dept, arrv, dist);
					break;
				case 3:
					cout << "请输入要删除的景点名称：" << endl;
					cin >> dept;
					g.removeVertex(dept);
					break;
				case 4:
					cout << "请输入要删除路径的两端点及距离：" << endl;
					cin >> dept >> arrv;
					g.removeEdge(dept, arrv);
					break;
				case 5:
					cout << "请输入要修改路径的两端点及距离：" << endl;
					cin >> dept >> arrv >> dist;
					g.updateWeight(dept, arrv, dist);
					break;
				case 6:
					break;
				default:
					cout << "选项错误，请重新输入：" << endl;
					subLoop = 1;
					break;
				}
				if (subChoice >= 1 && subChoice <= 5)
				{
					cout << "是否继续修改?" << endl;
					cout << "[1]确定" << endl;
					cout << "[2]返回" << endl;
					cin >> subLoop;
				}
				if (subLoop == 1)
				{
					mainLoop = 1;
					continue;
				}
				else
				{
					mainLoop = 1;
					break;
				}
			}
			break;
		case 2:
			cout << "请输入要寻找最短路径的两端点：" << endl;
			cin >> dept >> arrv;
			g.dijkstra(dept, arrv);
			break;
		case 3:
			cout << "请输入要寻找周边景点的端点及范围：" << endl;
			cin >> dept >> dist;
			g.dijkstra(dept, dist);
			break;
		case 4:
			cout << "请输入感兴趣的景点数量：" << endl;
			cin >> num;
			array = new string[num];
			cout << "请输入感兴趣的" << num << "个景点名称：" << endl;
			for (int i = 0; i < num; i++)
			{
				cin >> array[i];
			}
			g.kruskal(array, num);
			break;
		case 5:
			return 0;
		default:
			cout << "选项错误，请重新输入：" << endl;
			mainLoop = 1;
			break;
		}
		if (mainChoice >= 2 && mainChoice <= 4)
		{
			cout << "是否继续?" << endl;
			cout << "[1]确定" << endl;
			cout << "[2]退出" << endl;
			cin >> mainLoop;
		}
		if (mainLoop == 1)
		{
			continue;
		}
	}
	return 0;
}

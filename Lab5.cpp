#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;
char buff[10];
string strng;
int temp, selectedVertex = 0;

class Graph
{
	int indic, vertexAmount, edgesAmount;
	bool orient, mass;
	vector<vector<pair<int, int>>> list;
	vector<vector<tuple<int, int, int>>> listm;
	vector<pair<int, int>> vectPairs;
	vector<tuple<int, int, int>> vectTuples;
	vector<vector<int>> matrix;
public:
	void ReadGraph(string fileName)
	{
		ifstream input(fileName);
		input >> buff;
		switch (buff[0])
		{
		case 'C':
		{
			indic = 1;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			for (int j = 2; j < strng.length(); j++)
				vertexAmount = vertexAmount * 10 + (strng[j] - '0');
			break;
		}
		case 'L':
		{
			indic = 2;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			for (int j = 2; j < strng.length(); j++)
				vertexAmount = vertexAmount * 10 + (strng[j] - '0');
			break;
		}
		case 'E':
		{
			indic = 3;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			int i = 2;
			while (strng[i] != ' ')
			{
				vertexAmount = vertexAmount * 10 + (strng[i] - '0');
				i++;
			}
			i++;
			edgesAmount = strng[i] - '0';
			i++;
			while (i < strng.length())
			{
				edgesAmount = edgesAmount * 10 + (strng[i] - '0');
				i++;
			}
			break;
		}
		}
		input >> buff;
		if (buff[0] == '0') orient = false; else orient = true;
		input >> buff;
		if (buff[0] == '0') mass = false; else mass = true;

		if (indic == 1)
		{
			getline(input, strng);
			int linenum = 0;
			while (getline(input, strng))
			{
				matrix.push_back(vector<int>());
				temp = strng[0] - '0';
				for (int i = 1; i < strng.length(); i++)
					if (strng[i] != ' ')
					{
						temp *= 10; temp += strng[i] - '0';
					}
					else
					{
						matrix[linenum].push_back(temp);
						temp = strng[i + 1] - '0';
						i++;
					}
				matrix[linenum].push_back(temp);
				linenum++;
			}
		}
		if (indic == 2)
		{
			if (!mass)
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					list.push_back(vector<pair<int, int>>());
					temp = strng[0] - '0';
					for (int i = 1; i < strng.length(); i++)
						if (strng[i] != ' ')
						{
							temp *= 10; temp += strng[i] - '0';
						}
						else
						{
							list[linenum].push_back(make_pair(linenum + 1, temp));
							temp = strng[i + 1] - '0';
							i++;
						}
					list[linenum].push_back(make_pair(linenum + 1, temp));
					linenum++;
				}
			}
			else
			{
				int tempTwo;
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					listm.push_back(vector<tuple<int, int, int>>());
					temp = strng[0] - '0';
					for (int i = 1; i < strng.length(); i++)
						if (strng[i] != ' ')
						{
							if (strng[i] != ',')
							{
								temp *= 10;
								temp += strng[i] - '0';
							}
							else
							{
								tempTwo = temp;
								temp = strng[i + 1] - '0';
								i++;
								continue;
							}
						}
						else
						{
							listm[linenum].push_back(make_tuple(linenum + 1, tempTwo, temp));
							temp = strng[i + 1] - '0';
							i++;
						}
					listm[linenum].push_back(make_tuple(linenum + 1, tempTwo, temp));
					linenum++;
				}
			}
		}

		if (indic == 3)
		{
			if (!mass)
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					vectPairs.push_back(pair<int, int>());
					vectPairs[linenum].first = strng[0] - '0';
					int i = 1;
					while (strng[i] != ' ')
					{
						vectPairs[linenum].first = vectPairs[linenum].first * 10 + strng[i] - '0';
						i++;
					}
					i++;
					vectPairs[linenum].second = strng[i] - '0';
					i++;
					while (i < strng.length())
					{
						vectPairs[linenum].second = vectPairs[linenum].second * 10 + strng[i] - '0';
						i++;
					}
					linenum++;
				}
			}
			else
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					vectTuples.push_back(tuple<int, int, int>());
					get<0>(vectTuples[linenum]) = strng[0] - '0';
					int i = 1;
					while (strng[i] != ' ')
					{
						get<0>(vectTuples[linenum]) = get<0>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					i++;
					get<1>(vectTuples[linenum]) = strng[i] - '0';
					i++;
					while (strng[i] != ' ')
					{
						get<1>(vectTuples[linenum]) = get<1>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					i++;
					get<2>(vectTuples[linenum]) = strng[i] - '0';
					i++;
					while (i < strng.length())
					{
						get<2>(vectTuples[linenum]) = get<2>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					linenum++;
				}
			}
		}
	}
	void WriteGraph(string fileName)
	{
		ofstream output(fileName);
		if (indic == 1)
		{
			for (int i = 0; i < matrix.size(); i++)
			{
				output << matrix[i][0];
				for (int j = 1; j < matrix[i].size(); j++)
					output << ' ' << matrix[i][j];
				output << endl;
			}
		}
		if (indic == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < list.size(); i++)
				{
					if (list[i].size() != 0) output << list[i][0].second;
					for (int j = 1; j < list[i].size(); j++)
						output << ' ' << list[i][j].second;
					output << endl;
				}
			}
			else
			{
				for (int i = 0; i < listm.size(); i++)
				{
					if (listm[i].size() != 0) output << get<1>(listm[i][0]) << ',' << get<2>(listm[i][0]);
					for (int j = 1; j < listm[i].size(); j++)
						output << ' ' << get<1>(listm[i][j]) << ',' << get<2>(listm[i][j]);
					output << endl;
				}
			}
		}
		if (indic == 3)
		{
			if (!mass)
				for (int i = 0; i < vectPairs.size(); i++)
					output << vectPairs[i].first << ' ' << vectPairs[i].second << endl;
			else
				for (int i = 0; i < vectTuples.size(); i++)
					output << get<0>(vectTuples[i]) << ' ' << get<1>(vectTuples[i]) << ' ' << get<2>(vectTuples[i]) << endl;
		}
	}
	void AddEdge(int from, int to, int weight = 1)
	{
		if (indic == 1)
			matrix[from - 1][to - 1] = weight;
		if (indic == 2)
		{
			if (!mass)
			{
				list[from - 1].push_back(make_pair(from, to));
				if (!orient)
					list[to - 1].push_back(make_pair(to, from));
			}
			else
			{
				listm[from - 1].push_back(make_tuple(from, to, weight));
				if (!orient)
					listm[to - 1].push_back(make_tuple(to, from, weight));
			}
		}
		if (indic == 3)
		{
			if (!mass)
				vectPairs.push_back(make_pair(from, to));
			else
				vectTuples.push_back(tuple<int, int, int>(from, to, weight));
		}
	}
	void RemoveEdge(int from, int to)
	{
		if (indic == 1)
			matrix[from - 1][to - 1] = 0;
		if (indic == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < list[from - 1].size(); i++)
					if (list[from - 1][i].second == to) list[from - 1].erase(list[from - 1].begin() + i);
				if (!orient)
					for (int i = 0; i < list[to - 1].size(); i++)
						if (list[to - 1][i].second == from) list[to - 1].erase(list[to - 1].begin() + i);
			}
			else
			{
				for (int i = 0; i < listm[from - 1].size(); i++)
					if (get<1>(listm[from - 1][i]) == to) listm[from - 1].erase(listm[from - 1].begin() + i);
				if (!orient)
					for (int i = 0; i < listm[to - 1].size(); i++)
						if (get<1>(listm[to - 1][i]) == from) listm[to - 1].erase(listm[to - 1].begin() + i);
			}
		}
		if (indic == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vectPairs.size(); i++)
					if (vectPairs[i].first == from && vectPairs[i].second == to)
						vectPairs.erase(vectPairs.begin() + i);
			}
			else
			{
				for (int i = 0; i < vectTuples.size(); i++)
					if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
						vectTuples.erase(vectTuples.begin() + i);
			}
		}
	}
	int ChangeEdge(int from, int to, int newWeight)
	{
		int oldWeight;
		if (indic == 1)
		{
			oldWeight = matrix[from - 1][to - 1];
			matrix[from - 1][to - 1] = newWeight;
		}
		if (indic == 2)
		{
			for (int i = 0; i < listm[from - 1].size(); i++)
				if (get<1>(listm[from - 1][i]) == to)
				{
					oldWeight = get<2>(listm[from - 1][i]);
					get<2>(listm[from - 1][i]) = newWeight;
				}
			if (!orient)
			{
				for (int i = 0; i < listm[to - 1].size(); i++)
					if (get<1>(listm[to - 1][i]) == from)
					{
						oldWeight = get<2>(listm[to - 1][i]);
						get<2>(listm[to - 1][i]) = newWeight;
					}
			}
		}
		if (indic == 3)
			for (int i = 0; i < vectTuples.size(); i++)
				if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
				{
					oldWeight = get<2>(vectTuples[i]);
					get<2>(vectTuples[i]) = newWeight;
				}
		return oldWeight;
	}
	void TransformToAdjList()
	{
		if (indic == 1)
		{
			if (!mass)
				for (int i = 0; i < matrix.size(); i++)
				{
					list.push_back(vector<pair<int, int>>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							list[i].push_back(make_pair(i + 1, j + 1));
				}
			else
				for (int i = 0; i < matrix.size(); i++)
				{
					listm.push_back(vector<tuple<int, int, int>>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							listm[i].push_back(tuple<int, int, int>(i + 1, j + 1, matrix[i][j]));
				}
			matrix = vector<vector<int>>();
		}
		if (indic == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vertexAmount; i++)
					list.push_back(vector<pair<int, int>>()); // CHECK THIS
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectPairs.size(); j++)
						if (vectPairs[j].first == i + 1)
						{
							list[i].push_back(make_pair(i + 1, vectPairs[j].second));
							if (!orient)
								list[vectPairs[j].second - 1].push_back(make_pair(vectPairs[j].second, i + 1));
						}
				}
			}
			else
			{
				for (int i = 0; i < vertexAmount; i++)
					listm.push_back(vector<tuple<int, int, int>>());
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectTuples.size(); j++)
						if (get<0>(vectTuples[j]) == i + 1)
						{
							listm[i].push_back(tuple<int, int, int>(get<0>(vectTuples[j]), get<1>(vectTuples[j]), get<2>(vectTuples[j])));
							if (!orient)
								listm[get<1>(vectTuples[j]) - 1].push_back(tuple<int, int, int>(get<1>(vectTuples[j]), get<0>(vectTuples[j]), get<2>(vectTuples[j])));
						}
				}
			}
			vectPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indic = 2;
	}
	void TransformToListOfEdges()
	{
		if (indic == 1)
		{
			if (!mass)
				for (int i = 0; i < matrix.size(); i++)
				{
					vectPairs.push_back(pair<int, int>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							vectPairs.push_back(make_pair(i + 1, j + 1));
				}
			else
				for (int i = 0; i < matrix.size(); i++)
				{
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							vectTuples.push_back(tuple<int, int, int>(i + 1, j + 1, matrix[i][j]));
				}
			matrix = vector<vector<int>>();
		}
		if (indic == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < list.size(); i++)
					for (int j = 0; j < list[i].size(); j++)
					{
						bool next = false;
						if (!orient && list[i][j].first < list[i][j].second)
							for (int k = 0; k < list[list[i][j].second - 1].size(); k++)
								if (list[list[i][j].second - 1][k].second == list[i][j].first) next = true;
						if (next) continue;
						else vectPairs.push_back(make_pair(list[i][j].first, list[i][j].second));
					}
			}
			else
			{
				for (int i = 0; i < listm.size(); i++)
					for (int j = 0; j < listm[i].size(); j++)
					{
						bool next = false;
						if (!orient && get<0>(listm[i][j]) < get<1>(listm[i][j]))
							for (int k = 0; k < listm[get<1>(listm[i][j]) - 1].size(); k++)
								if (get<1>(listm[get<1>(list[i][j])][k]) == get<0>(listm[i][j])) next = true;
						if (next) continue;
						else vectTuples.push_back(tuple<int, int, int>(get<0>(listm[i][j]), get<1>(listm[i][j]), get<2>(listm[i][j])));
					}
			}
			list = vector<vector<pair<int, int>>>();
			listm = vector<vector<tuple<int, int, int>>>();
		}
		indic = 3;
	}
	void TransformToAdjMatrix()
	{
		if (indic == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < list.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < list.size(); i++)
					for (int j = 0; j < list[i].size(); j++)
						matrix[i][list[i][j].second - 1] = 1;
			}
			else
			{
				for (int i = 0; i < listm.size(); i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < listm.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < listm.size(); i++)
					for (int j = 0; j < listm[i].size(); j++)
						matrix[i][get<1>(listm[i][j]) - 1] = get<2>(listm[i][j]);
			}
			list = vector<vector<pair<int, int>>>();
			listm = vector<vector<tuple<int, int, int>>>();
		}
		if (indic == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vertexAmount; j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectPairs.size(); i++)
				{
					matrix[vectPairs[i].first - 1][vectPairs[i].second - 1] = 1;
					if (!orient)
						matrix[vectPairs[i].second - 1][vectPairs[i].first - 1] = 1;
				}
			}
			else
			{
				for (int i = 0; i < vectTuples.size(); i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vectTuples.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectTuples.size(); i++)
				{
					matrix[get<0>(vectTuples[i]) - 1][get<1>(vectTuples[i]) - 1] = get<2>(vectTuples[i]);
					if (!orient)
						matrix[get<1>(vectTuples[i]) - 1][get<0>(vectTuples[i]) - 1] = get<2>(vectTuples[i]);
				}
			}
			vectPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indic = 1;
	}
	void WidthWay(int &vertex, vector<pair<int, int>> &marks, int sink, bool &markedSink, Graph &result, bool &searching, vector<int> &path)
	{
		bool last = false, marked = false;
		searching = false;
		if (selectedVertex + 1 == path.size()) return;
		int goingTo = path[selectedVertex+1];
		cout << goingTo << endl;
		for (int i = 0; i < listm[vertex - 1].size(); i++)
		{
			if (get<1>(result.listm[vertex - 1][i]) == goingTo)
			{
				marked = true;
				//cout << vertex << endl;
				/*system("pause");
				listm[vertex - 1];
				system("pause");*/
				marks[get<1>(listm[vertex - 1][i]) - 1].first = vertex;
				marks[get<1>(listm[vertex - 1][i]) - 1].second = min(marks[vertex - 1].second, get<2>(listm[vertex - 1][i]) - get<2>(result.listm[vertex - 1][i]));
				if (get<1>(listm[vertex - 1][i]) == sink)
				{
					searching = true;
					last = true;
					markedSink = true;
				}
			}
			//cout << "AAAAAAAAAAAAAAAAA";
		}
		if (!marked)
			return;
		selectedVertex++;
			//WidthWay(get<1>(listm[vertex - 1][i]), marks, sink, markedSink, result, searching, path);
		WidthWay(goingTo, marks, sink, markedSink, result, searching, path);
		int i = sink;
		if (last)
		while (marks[i-1].first != 0)
		{
			for (int j = 0; j < result.listm[marks[i - 1].first-1].size(); j++)
			{
				if (get<1>(result.listm[marks[i - 1].first - 1][j]) == i)
				{
					get<2>(result.listm[marks[i - 1].first - 1][j]) += marks[sink - 1].second;
				}
			}
			i = marks[i - 1].first;
		}
		return;
	}

	void flowFordFulkerson(int sourse, int sink)
	{
		Graph result;
		result.listm = listm;
		for (int i = 0; i < result.listm.size(); i++)
			for (int j = 0; j < result.listm[i].size(); j++)
				get<2>(result.listm[i][j]) = 0;
		if (indic != 2) TransformToAdjList();
		bool searching=true, markedSink;
		markedSink = false;
		vector<pair<int, int>> marks, marksEmpty;
		for (int i = 0; i < vertexAmount; i++)
			marksEmpty.push_back(make_pair(0, 0));
		marksEmpty[sourse - 1].second = 1488;
		int vertex = sourse;
		marks = marksEmpty;
		while (1>0)
		{
			selectedVertex = 0;
			vector<int> path = Deikstra(sourse, sink, sink, result);
			if (path.size() == 0) return;
			for (int t = 0; t < path.size(); t++)
				cout << path[t] << " ";
			cout << endl;
			WidthWay(vertex, marks, sink, markedSink, result, searching, path);
			marks = marksEmpty;
			markedSink = false;
			for (int i = 0; i < result.listm.size(); i++)
			{
				if (listm[i].size() != 0) cout << get<1>(result.listm[i][0]) << ',' << get<2>(result.listm[i][0]);
				for (int j = 1; j < result.listm[i].size(); j++)
					cout << ' ' << get<1>(result.listm[i][j]) << ',' << get<2>(result.listm[i][j]);
				cout << endl;
			}
			system("pause");
		}
		for (int i = 0; i < result.listm.size(); i++)
		{
			if (listm[i].size() != 0) cout << get<1>(result.listm[i][0]) << ',' << get<2>(result.listm[i][0]);
			for (int j = 1; j < result.listm[i].size(); j++)
				cout << ' ' << get<1>(result.listm[i][j]) << ',' << get<2>(result.listm[i][j]);
			cout << endl;
		}
		system("pause");
	}
	vector<int> Deikstra(int source, int sink, int current, Graph &result)
	{
		unsigned int a = 1488, b=1488;
		int nextVert=1;
		vector<int> path, marks, visited;
		for (int i = 0; i < vertexAmount; i++)
		{
			path.push_back(0);
			visited.push_back(0);
			if(i+1!=source) marks.push_back(a);
			else marks.push_back(0);
		}
		DeikstraMain(source, sink, nextVert, result, path, marks, visited);
		vector<int> way;
		if (path[sink - 1] == 0) return vector<int>();
		for (int v = sink; v != source; v = path[v - 1])
			way.push_back(v);
		way.push_back(source);
		reverse(way.begin(), way.end());
		return way;
	}

	void DeikstraMain(int source, int sink, int current, Graph &result, vector<int> &path, vector<int> &marks, vector<int> &visited)
	{
		//cout << "a" << endl;
		unsigned int a = -1, b = -1;
		int nextVert;
		visited[current - 1] = 1;
		if (current - 1 >= listm.size()) return;
		for (int i = 0; i < listm[current - 1].size(); i++)
		{
			//cout << marks[get<1>(result.listm[current - 1][i]) - 1] << "*" << marks[current - 1] + get<2>(result.listm[current - 1][i])<<endl;
			if ((marks[get<1>(result.listm[current - 1][i]) - 1] > marks[current-1] + get<2>(result.listm[current - 1][i]))
				&& get<2>(listm[current - 1][i])>get<2>(result.listm[current - 1][i]))
			{
				//cout << "AYE";
				marks[get<1>(result.listm[current - 1][i]) - 1] = marks[current - 1] + get<2>(result.listm[current - 1][i]);
				path[get<1>(result.listm[current - 1][i]) - 1] = current;
			}
		}
		for (int i = 0; i < vertexAmount; i++)
		{
			//cout << visited[i] << " " << marks[i] << endl;
			if (visited[i] == 0 && marks[i] < a)
			{
				nextVert = i + 1;
				a = marks[i];
			}
		}
		if (a != b)
		{
			//cout << nextVert << endl;
			DeikstraMain(source, sink, nextVert, result, path, marks, visited);
		}
	}
};

int main(void)
{
	Graph something;
	something.ReadGraph("input.txt");
	something.flowFordFulkerson(1, 6);
	//something.Deikstra(1, 6, 1, something);
	system("pause");
}
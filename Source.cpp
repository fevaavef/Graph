#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
char buff[10];
string strng;
int temp;
vector<vector<pair<int, int>>> list;
vector<vector<tuple<int, int, int>>> listm;
vector<pair<int, int>> vectPairs;
vector<tuple<int, int, int>> vectTuples;
vector<vector<int>> matrix;

class DSU
{
private:
public:
	vector<int> p, rank;
	bool victory = true;
	DSU(int N)
	{
		for (int i = 0; i < N; i++)
		{
			p.push_back(i + 1);
			rank.push_back(0);
		}
	}
	int find(int x)
	{
		if (x == 0) return -1;
		return (x == p[x - 1] ? x : p[x - 1] = find(p[x - 1]));
	}

	void unite(int x, int y)
	{
		if ((x = find(x)) == (y = find(y)))
		{
			victory = false;
			return;
		}

		if (rank[x - 1] <  rank[y - 1])
			p[x - 1] = y;
		else
			p[y - 1] = x;

		if (rank[x - 1] == rank[y - 1])
			++rank[x - 1];
	}
};

class Graph
{
	int indic, vertexAmount, edgesAmount;
	bool orient, mass;
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
	bool SecondCondit()
	{
		DSU dsu(vertexAmount);
		for (int i = 0; i < list.size(); i++)
		{
			for (int j=0; j<list[i].size();j++)
			if (dsu.find(list[i][j].first) != dsu.find(list[i][j].second))
				dsu.unite(list[i][j].first, list[i][j].second);
		}
		int special,regular=0;
		special = dsu.p[0];
		for (int i = 1; i < dsu.p.size(); i++)
		{
			if (dsu.p[i - 1] == dsu.p[i])
			{
				if (regular == 0)
					swap(regular, special);
				if (regular != dsu.p[i]) return false;
			}
			else
				if (special == 0)
					special = dsu.p[i];
				else
					return false;
		}
		return true;
	}

	bool CircleExists()
	{
		if (indic != 2) TransformToAdjList();
		for (int i = 0; i < list.size(); i++)
			if (list[i].size() % 2 != 0) return false;
		if (!SecondCondit()) return false;
		return true;
	}

	int checkEuler(bool &circleExist)
	{
		int result = 0;
		if (indic != 2) TransformToAdjList();
		if (circleExist)
			return 1;
		else
		{
			for (int i = 0; i < list.size(); i++)
				if (list[i].size() % 2 != 0) result = i+1;
			if (!SecondCondit()) result = 0;
		}
		return result;
	}

	vector<int> getEuleranTourEffective()
	{
		if (indic != 2) TransformToAdjList();
		edgesAmount = 0;
		vector<vector<pair<int, int>>> listCl = list;
		vector<int> result, stack; 
		bool isCircle = CircleExists();
		int from;
		if (checkEuler(isCircle) != 0) stack.push_back(checkEuler(isCircle));
		else return result;
		while (stack.size() != 0)
		{
			from = stack.back();
			if (listCl[from - 1].size() != 0)
			{
				int to = listCl[from - 1][0].second;
				stack.push_back(listCl[from - 1][0].second);
				listCl[from - 1].erase(listCl[from-1].begin());
				for (int i = 0; i < listCl[to - 1].size(); i++)
					if (listCl[to - 1][i].second == from)
						listCl[to - 1].erase(listCl[to - 1].begin() + i);
			}
			if (from == stack.back())
			{
				stack.erase(stack.end() - 1);
				cout << from << ' ';
			}
		}
		return stack;
	}

	vector<int> getEuleranTourFleri()
	{
		if (indic != 2) TransformToAdjList();
		edgesAmount = 0;
		for (int i = 0; i < list.size(); i++)
			edgesAmount += list[i].size();
		edgesAmount /= 2;
		vector<vector<pair<int, int>>> listCl = list;
		vector<int> result;
		bool isCircle = CircleExists();
		if (checkEuler(isCircle) != 0) result.push_back(checkEuler(isCircle));
		else return result;
     	return RecBase(result[result.size() - 1], result, listCl);
	}

	vector<int> RecBase(int currentVert, vector<int> result, vector<vector<pair<int, int>>> listCl)
	{
		bool added = false;
		for (int i = 0; i < listCl[currentVert - 1].size(); i++)
		{
			if (!IfBridge(listCl[currentVert - 1][i],listCl) || ((i == listCl[currentVert - 1].size()-1) && !added))
			{
					int oldVert = currentVert;
					result.push_back(listCl[currentVert - 1][i].second);
					currentVert = listCl[currentVert - 1][i].second;
					listCl[oldVert - 1].erase(listCl[oldVert - 1].begin() + i);
					for (int j = 0; j < listCl[currentVert - 1].size(); j++)
						if (listCl[currentVert - 1][j].second == oldVert)
							listCl[currentVert - 1].erase(listCl[currentVert - 1].begin() + j);
					added = true;
					break;
			}
		}
		if (result.size()<edgesAmount)result=RecBase(currentVert, result, listCl);
		else if (CircleExists()) result.push_back(result[0]);
		return result;
	}

	bool IfBridge(pair<int,int> edge, vector<vector<pair<int, int>>> listCl)
	{
		vector<int> queue, visited, visitedStart;
		queue.push_back(edge.first);
		while (queue.size()!=0)
		{
			for (int i = 0; i<listCl[queue.back() - 1].size(); i++)
				if (!((listCl[queue.back() - 1][i].first == edge.first && listCl[queue.back() - 1][i].second == edge.second) ||
					(listCl[queue.back() - 1][i].first == edge.second && listCl[queue.back() - 1][i].second == edge.first)) 
					&& find(visited.begin(), visited.end(), listCl[queue.back() - 1][i].second) == visited.end()
					&& find(queue.begin(), queue.end(), listCl[queue.back() - 1][i].second) == queue.end())
					queue.insert(queue.begin(), listCl[queue.back() - 1][i].second);
			visited.push_back(queue.back());
			queue.erase(queue.end() - 1, queue.end());
		}
		queue.push_back(edge.first);
		while (queue.size() != 0)
		{
			for (int i = 0; i<listCl[queue.back() - 1].size(); i++)
				if (find(visitedStart.begin(), visitedStart.end(), listCl[queue.back() - 1][i].second) == visitedStart.end()
					&& find(queue.begin(), queue.end(), listCl[queue.back() - 1][i].second) == queue.end())
					queue.insert(queue.begin(), listCl[queue.back() - 1][i].second);
			visitedStart.push_back(queue.back());
			queue.erase(queue.end() - 1, queue.end());
		}
		return (visited.size() != visitedStart.size());
	}
};

int main(void)
{
	setlocale(LC_ALL, "rus");
	Graph something;
	something.ReadGraph("input.txt");
	something.WriteGraph("output.txt");
	//cout << something.CircleExists();
	vector<int> result= something.getEuleranTourEffective();
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << ' ';
	system("pause");
	//something.TransformToAdjList();
	//something.WriteGraph("output.txt");
}
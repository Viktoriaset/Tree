#include <iostream>
#include <vector>
#include <fstream>

struct node {
	int vertex; // always vertex = index in vector Graph + 1
	std::vector<int> transition;
	bool isChek = false;

	void addEdge(int edge) {
		for (int i = 0; i < transition.size(); i++) {
			if (transition[i] == edge) {
				return;
			}
		}
		transition.push_back(edge);
	}

	void deleteEdge(int edge) {
		std::vector<int> t;
		for (int i = 0; i < transition.size(); i++) {
			if (edge != transition[i]) {
				t.push_back(transition[i]);
			}
		}
		transition = t;
		return;
	}
};

bool dfs(std::vector<node>& graph, int vertex) {
	if (graph[vertex].isChek) {
		return false;
	}

	graph[vertex].isChek = true;

	for (int i = 0; i < graph[vertex].transition.size(); i++) {
		graph[graph[vertex].transition[i]].deleteEdge(vertex);
		if (!dfs(graph, graph[vertex].transition[i])) {
			return false;
		}
		graph[graph[vertex ].transition[i]].addEdge(vertex);
	}
	return true;
}

int main()
{
	std::ifstream inp("input.txt");
	std::ofstream out("output.txt");
	int n, m;
	inp >> n >> m;

	if (m >= n) {
		out << "NO";
		return 0;
	}
	std::vector<node> Graph(n+1);

	for (int i = 0; i < m; i++) {
		int vertex, edge;
		inp >> vertex >> edge;
		Graph[vertex].vertex = vertex;
		Graph[vertex].addEdge(edge);
		Graph[edge].vertex = edge;
		Graph[edge].addEdge(vertex);
	}

	bool answer = dfs(Graph, 1);

	for (int i = 1; i < Graph.size(); i++) {
		if (!Graph[i].isChek) {
			out << "NO";
			return 0;
		}
	}

	out <<  ((answer)? "YES" : "NO");
	return 0;
}


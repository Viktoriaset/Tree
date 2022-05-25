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
	if (graph[vertex - 1].isChek) {
		return false;
	}

	graph[vertex - 1].isChek = true;

	for (int i = 0; i < graph[vertex - 1].transition.size(); i++) {
		graph[graph[vertex - 1].transition[i] -1].deleteEdge(vertex);
		if (!dfs(graph, graph[vertex - 1].transition[i])) {
			return false;
		}
		graph[graph[vertex - 1].transition[i] - 1].addEdge(vertex);
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
	std::vector<node> Graph(n);

	for (int i = 0; i < m; i++) {
		int vertex, edge;
		inp >> vertex >> edge;
		Graph[vertex - 1].vertex = vertex;
		Graph[vertex - 1].addEdge(edge);
		Graph[edge - 1].vertex = edge;
		Graph[edge - 1].addEdge(vertex);
	}

	out <<  (dfs(Graph, 1)? "YES" : "NO");
	return 0;
}


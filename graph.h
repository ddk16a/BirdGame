#ifndef GRAPH_H
#define GRAPH_H

#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <functional>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>

template <class T, class weightType = unsigned int>
class graph {
	private:
		//matrix has a each vertex and a set containing all the edges
		// typedef std::pair<weightType, bool> edge;
		// std::map<T, std::map<T, edge>> data;
		std::map<T, std::map<T, weightType>> data;

		std::function<void(T,T, weightType)> addEdge;

		weightType weigh(std::vector<std::pair<T, weightType>> route) const;
		weightType defaultWeight;
	public:
		//defaults to undirected, but can be specified otherwise
		graph(weightType def = weightType(), bool directed = false);
		void direct(bool directed = true);

		//counting suffs
		int vertexCount() const;

		//vertex stuff
		void insert(T value); //adds a vertex to the graph
		void remove(T value); //removes a vertex from the graph, does nothing if the vertex does not exist
		bool hasNode(T value) const; //check for the vertex

		//edge stuff
		void connect(T a, T b, weightType weight = graph<T,weightType>::defaultWeight); //adds a connection from the a to b. if undirected, adds a connection from b to a
		weightType weight(T a, T b) const; //returns the edgeweight

		//path stuff
		std::vector<std::pair<T, weightType>> path(T a, T b, std::set<T> seen = std::set<T>()) const; //finds the shortest path and returns the weight of the path, or 0 if no path is found
		std::vector<std::pair<T, weightType>> adjacent(T value) const; //return all adjacent vetecies
		T descend(T val) const; //returns the value found after following the shortest path to the end
		T ascend(T val) const; //returns the value found after following the shortest path to the end

		void print(int size = 5) {
			std::cout << std::setw(size) << "graph" << '\n';
			for_each(data.begin(), data.end(), [size] (std::pair<const T, std::map<T, weightType>> val) {
				std::cout << std::setw(size) << val.first;
				std::for_each(val.second.begin(), val.second.end(), [size] (std::pair<const T, weightType> val) {
					std::cout << std::setw(size) << '(' << val.first << ',' << val.second << ')';
				});
				std::cout << '\n';
			});
		}
};

template <class T, class weightType>
graph<T ,weightType>::graph(weightType def, bool directed) {
	defaultWeight = def;
	direct(directed);
}

template <class T, class weightType>
weightType graph<T ,weightType>::weigh(std::vector<std::pair<T, weightType>> route) const {
	weightType sum = weightType();
	for_each(route.begin(), route.end(), [&] (std::pair<T, weightType> val) {
		sum += val.second;
	});
	return sum;
}

template <class T, class weightType>
void graph<T ,weightType>::direct(bool directed) {
	if (directed)
		addEdge = [this] (T a, T b, weightType weight) { data[a][b] = weight; };
	else
		addEdge = [this] (T a, T b, weightType weight) { data[a][b] = data[b][a] = weight; };
}

template <class T, class weightType>
int graph<T ,weightType>::vertexCount() const {
	return data.size();
}

template <class T, class weightType>
void graph<T ,weightType>::insert(T value) {
	if (hasNode(value))
		return;
	// std::for_each(data.begin(), data.end(), [&] (std::pair<const T, std::map<T, edge>>& val) {
	// 	val.second[value] = edge(weightType(), false);
	// });
	// std::for_each(data.begin(), data.end(), [&] (std::pair<const T, std::map<T, edge>>& val) {
	// 	data[value][val.first] = edge(weightType(), false);
	// });
	// data[value][value] = edge(weightType(), false);
	data.insert(make_pair(value, std::map<T, weightType>()));
}

template <class T, class weightType>
void graph<T ,weightType>::remove(T value) {
	data.erase(value);
	std::for_each(data.begin(), data.end(), [value] (std::pair<const T, std::map<T, weightType>>& edge) {
		edge.second.erase(value);
	});
}

template <class T, class weightType>
bool graph<T ,weightType>::hasNode(T value) const {
	return data.find(value) != data.end();
}

template <class T, class weightType>
void graph<T ,weightType>::connect(T a, T b, weightType weight) {
	addEdge(a, b, weight);
}

template <class T, class weightType>
weightType graph<T ,weightType>::weight(T a, T b) const {
	return weigh(path(a, b));
}

//finds the 'lightest' path from a to b
template <class T, class weightType>
std::vector<std::pair<T, weightType>> graph<T ,weightType>::path(T a, T b, std::set<T> seen) const {
	std::vector<std::pair<T, weightType>> returner;
	//if the vertecies don't exist or are the same

	if ((a == b) || !(hasNode(a) && hasNode(b)))
		return returner;

	seen.insert(a);
	auto adj = adjacent(a);

	//if a is directly connected to b
	if (std::find_if(adj.begin(), adj.end(), [b] (std::pair<T, weightType> val) { return val.first == b; }) != adj.end()) {
		returner.push_back(std::make_pair(a, data.at(a).at(b)));
		return returner;
	}

	//finds the shortest path to b
	for_each(adj.begin(), adj.end(), [&] (std::pair<T, weightType> val) {
		if (seen.find(val.first) != seen.end())
			return;
		seen.insert(val.first);
		auto temp = path(val.first, b, seen);
		if (returner.empty())
			returner = temp;
		else if (!temp.empty())
			returner = (weigh(returner) < weigh(temp) ? returner : temp);
		// returner = min(returner, path(val.first, b, seen), [&] (std::vector<std::pair<T, weightType>> a, std::vector<std::pair<T, weightType>> b) {
		// 	if (a.empty())
		// 		return true;
		// 	if (b.empty())
		// 		return false;
		// 	return weigh(a) < weigh(b);
		// });
	});

	if (!returner.empty())
		returner.push_back(std::make_pair(a, data.at(a).at(returner.back().first)));

	return returner;
}

//returns a priority queue with all the smallest edges
template <class T, class weightType>
std::vector<std::pair<T, weightType>> graph<T ,weightType>::adjacent(T value) const {
	if (!hasNode(value))
		return std::vector<std::pair<T, weightType>>();
	std::vector<std::pair<T, weightType>> returner(data.at(value).begin(), data.at(value).end());
	sort(returner.begin(), returner.end(), [] (std::pair<T, weightType> a, std::pair<T, weightType> b) { return a.second < b.second; });
	return returner;
	// std::vector<std::pair<T, weightType>> vec.;
	// if (!hasNode(value))
	// 	return vec;
	// for_each(data.at(value).begin(), data.at(value).end(), [&] (const std::pair<const T, edge> val) {
	// 	if (val.second.second)
	// 		vec.push_back(std::pair<T, weightType>(val.first, val.second.first));
	// });
	// sort(vec.begin(), vec.end(), [] (std::pair<T, weightType> a, std::pair<T, weightType> b) { return a.second < b.second; });
	// return vec;
}

//follows the 'lightest' edge until that edge leads to a value already seen
template <class T, class weightType>
T graph<T ,weightType>::descend(T val) const {
	if (!hasNode(val))
		return val;

	std::set<T> fall;
	auto down = adjacent(val);
	fall.insert(val);
	while (!down.empty()) {
		T temp = down.back().first;
		if (fall.find(temp) !=  fall.end())
			break;
		fall.insert(temp);
		down = adjacent(val = temp);
	}
	return val;
}

template <class T, class weightType>
T graph<T ,weightType>::ascend(T val) const {
	if (!hasNode(val))
		return val;

	std::set<T> climb;
	auto up = adjacent(val);
	climb.insert(val);
	while (!up.empty()) {
		T temp = up.back().first;
		if (climb.find(temp) !=  climb.end())
			break;
		climb.insert(temp);
		up = adjacent(val = temp);
	}
	return val;
}

#endif
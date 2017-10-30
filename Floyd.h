#include<string>
using namespace std;

class Graph_DG {
private:
	unsigned vexnum;   //number of vertices
	unsigned edge;     //number of edges
	unsigned **arc;   // adjacency matrix 
	unsigned ** dis;   // D matrix
	unsigned ** path;  //P matrix
public:

	Graph_DG(unsigned vexnum);

	~Graph_DG();

	//create graph
	void createGraph(unsigned start, unsigned end);

	//calulate the shortest path
	void Floyd();

	//print the shortest path
	void print_path(unsigned startv, unsigned endv);
};

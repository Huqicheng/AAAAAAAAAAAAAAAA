#include"Floyd.h"
#include <iostream>
#include <sstream>
#include <vector>

int checkarray(unsigned myarray[]) {
	int k = 0;
	for (int i = 0; i < 500; i++) {
		if (myarray[i] != 500) {
			k++;
		}
	}
	return k;
}

void resetarray(unsigned myarray[]) {
	for (int i = 0; i < 500; i++) {
		myarray[i] = 500;
	}
}

Graph_DG::Graph_DG(unsigned vexnum) {
	//intitialize the number of vertices
	this->vexnum = vexnum;
	//create adjacency matrix 
	arc = new unsigned*[this->vexnum];
	dis = new unsigned*[this->vexnum];
	path = new unsigned*[this->vexnum];
	for (unsigned i = 0; i < this->vexnum; i++) {
		arc[i] = new unsigned[this->vexnum];
		dis[i] = new unsigned[this->vexnum];
		path[i] = new unsigned[this->vexnum];
		for (unsigned k = 0; k < this->vexnum; k++) {
			arc[i][k] = 500;
		}
	}
}
//destructor
Graph_DG::~Graph_DG() {

	for (unsigned i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
		delete this->dis[i];
		delete this->path[i];

	}
	delete dis;
	delete arc;
	delete path;
}

void Graph_DG::createGraph(unsigned start, unsigned end) {
	
	unsigned weight=1;
	unsigned count = 1;

	arc[start][end] = weight;
	arc[end][start] = weight;
}

void Graph_DG::Floyd() {
	unsigned row = 0;
	unsigned col = 0;

	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			//Initialize the value of D with adjacency matrix value
			this->dis[row][col] = this->arc[row][col];
			//Initialize the value of P with vertex index  
			this->path[row][col] = col;
		}
	}

	//calculate the shortest path
	unsigned temp = 0;
	unsigned select = 0;
	for (temp = 0; temp < this->vexnum; temp++) {
		for (row = 0; row < this->vexnum; row++) {
			for (col = 0; col < this->vexnum; col++) {
				select = (dis[row][temp] == 500 || dis[temp][col] == 500) ? 500 : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select) {
					//update the D matrix
					this->dis[row][col] = select;
					//update the P matrix
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}

void Graph_DG::print_path(unsigned startv, unsigned endv) {

	unsigned row = 0;
	unsigned col = 0;
	unsigned temp = 0;
	temp = path[startv][endv];
	if (dis[startv][endv] == 500) {
		std::cerr << "Error:the path doesn't exist\n";
	}

	else {
		std::cout << to_string(startv);
		while (temp != endv) {
			std::cout << "-" << to_string(temp);
			temp = path[temp][endv];
		}
		std::cout << "-" << to_string(endv) << endl;
	}
		
}

int main() {

	unsigned vexnum = 0;
	const char comma = ',';
	unsigned array[500] = {500};

	while (!std::cin.eof()) {
		Graph_DG graph(vexnum);
		std::string line;
		std::getline(std::cin, line);
		size_t i;

		// use 'V' to define a new graph
		if (line[0] == 'V') {
			//memset(array, 1000, sizeof(array));
			resetarray(array);
			line.erase(0, 1);
			std::istringstream input(line);

			while (!input.eof()) {
				string num;
				input >> num;

				if (stoi(num) < 0) {
					std::cerr << "Error:Invalid number of vertex\n";
					break;
				}

				else {
					vexnum = stoi(num);
				}
			}
		}
		// use 'E' to add edges to the graph
		else if (line[0] == 'E') {

			int k = checkarray(array);
			if (k > 0)
				std::cerr << "Error:A valid edge set already exisits\n";

			else {
				line.erase(0, 1);
				unsigned num;
				std::string::iterator it;
				//leave all the numbers and clear other characters
				for (it = line.begin(); it != line.end(); it) {
					if (*it == '<') {
						line.erase(it);
					}
					else if (*it == '>') {
						line.erase(it);
					}
					else if (*it == '{') {
						line.erase(it);
					}
					else if (*it == '}') {
						line.erase(it);
					}
					else if (*it == ' ') {
						line.erase(it);
					}
					else
						++it;
				}

				if (!line.empty()) {
					std::istringstream input(line);
					std::vector<unsigned> nums;

					while (!input.eof()) {
						input >> num;
						nums.push_back(num);

						if (input.eof())
							break;

						char separator;
						input >> separator;
					}

					if (!nums.empty()) {
						i = 0;
						int count = 0;

						for (unsigned x : nums) {
							if (x >= vexnum) {
								count++;
							}
							else {
								array[i] = x;
								i++;
							}
						}
                                     std::vector<unsigned>(nums).swap(nums);
						//check whether there is invalid vertex index in the command
						if (count > 0) {
							resetarray(array);
							//memset(array, 1000, sizeof(array));
							std::cerr << "Error:Invalid vertex index\n";
						}
					}
				}
			    else {
				   array[0] = 0;
				   array[1] = 0;
				   i = 2;
				}
			}
		}
		else if (line[0] == 's') {

			int k = checkarray(array);
			line.erase(0, 1);
			unsigned num;
			std::istringstream input(line);
			std::vector<unsigned> nums;
			unsigned path[3];

			while (!input.eof()) {
				input >> num;
				nums.push_back(num);
				if (input.eof())
					break;
			}

			if (!nums.empty()) {
				size_t n = 0;
				for (unsigned x : nums) {
					path[n] = x;
					n++;
				}
                         std::vector<unsigned>(nums).swap(nums);

				if (path[0] >= vexnum || path[1] >= vexnum) {
					std::cerr << "Error:Invalid vertex idex\n";
				}
				// print one num if we want to check the self-loop
				else if (path[0] == path[1])
					std::cout << path[0] << endl;

				else if (k == 0)
					std::cerr << "Error:the path doesn't exist\n";

				else {
					for (int j = 0; j < i - 1; j) {
						graph.createGraph(array[j], array[j + 1]);
						j += 2;
					}
					graph.Floyd();
					graph.print_path(path[0], path[1]);
				}
			}
		}
	}
   return EXIT_SUCCESS;
}

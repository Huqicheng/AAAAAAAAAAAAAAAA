#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct Point
{
	int x, y;
};



int GenerateStreet(int upper_limit) {
	int street_number = upper_limit;
	int random;
	std::ifstream urandom("/dev/urandom");
	if (urandom.fail()) {
		//std::cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

	urandom.read((char*)&street_number, sizeof(int));
	if (street_number < 0)
		street_number = -street_number;
	random = street_number % (upper_limit - 1) + 2;
	//std::cout << "Random character: " << random << "\n";
	urandom.close();
	return random;
}

int GenerateSegement(int upper_limit) {

	int street_segement = upper_limit;
	int random;
	std::ifstream urandom("/dev/urandom");
	if (urandom.fail()) {
		//std::cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

	urandom.read((char*)&street_segement, sizeof(int));
	if (street_segement < 0)
		street_segement = -street_segement;
	random = street_segement % upper_limit + 2;
	//std::cout << "Random character: " << random << "\n";
	urandom.close();
	return random;
}

void WaitTime(int upper_limit) {

	int wait_sec = upper_limit;
	int random;fflush(stdout);
	std::ifstream urandom("/dev/urandom");
	if (urandom.fail()) {
		std::cerr << "Error: cannot open /dev/urandom\n";
	}

	urandom.read((char*)&wait_sec, sizeof(int));
	if (wait_sec < 0)
		wait_sec = -wait_sec;
	random = wait_sec % (upper_limit - 4) + 5;
	//std::cout << "Random character: " << random << "\n";
	urandom.close();
	sleep(random);
}

int GenerateCoord(int upper_limit) {

	int coord = upper_limit;
	int random;
	std::ifstream urandom("/dev/urandom");
	if (urandom.fail()) {
		std::cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

	urandom.read((char*)&coord, sizeof(int));
	random = coord % (upper_limit + 1);
	urandom.close();
	return random;
}

bool IsValid(Point street_def[], int j) {
	for (int a = 0; a < j - 1; a++) {
		for (int b = a + 1; b < j; b++) {
			if (street_def[a].x == street_def[b].x) {
				if (street_def[a].y == street_def[b].y) {
					return false;

				}
			}
		}
	}
	return true;
}

int pt_cmp(const void* val_l, const void* val_r)
{
	Point* left = (Point*)val_l;
	Point* right = (Point*)val_r;

	if (left->x > right->x) {
		return 1;
	}
	else if (left->x == right->x) {
		if (left->y > right->y) {
			return 1;
		}
		else if (left->y == right->y) {
			return 0;
		}
		else
			return -1;
	}
	return -1;
}


void OutputCommand(std::map<std::string, Point*> StreetMap, std::string array_name, int count) {
	std::cout << "a \"" << array_name << "\" ";
	for (int k = 0; k< count; k++) {
		std::cout << "(" << StreetMap[array_name][k].x << "," << StreetMap[array_name][k].y << ")";
	}
	std::cout << "\n";
      fflush(stdout);
}

void RemoveStreet(int count) {
	if (count > 0) {
		std::string name = "s";
		for (int i = 0; i < count; i++) {
			name.append("s");
			std::cout << "r " << "\"" << name << "\"\n";
		}
            fflush(stdout);
	}
}


int main(int argc, char * argv[]) {

	int command_line;
	int i = 0;
	int street_number, street_limit = 10;
	int street_segement, segement_limit = 5;
	int wait_sec, wait_limit = 5;
	int coord, coord_limit = 20;
	//std::map<std::string, Point> MyMap;
	//std::vector<Point> verices;


	while ((command_line = getopt(argc, argv, "s:n:l:c:")) != -1)
	{

		switch (command_line)
		{
		case 's':
			if (atoi(optarg) <2) {
				std::cerr << "Error: Invalid number of streets.\n";
				exit(1);
			}
			street_limit = atoi(optarg);
			break;
		case 'n':
			if (atoi(optarg) < 1) {
				std::cerr << "Error: Invalid number of segements.\n";
				exit(1);
			}
			segement_limit = atoi(optarg);
			break;
		case 'l':
			if (atoi(optarg) < 5) {
				std::cerr << "Error: Invalid waiting time.\n";
				exit(1);
			}
			wait_limit = atoi(optarg);
			break;
		case 'c':
			if (atoi(optarg) <1) {
				std::cerr << "Error: Invalid coordinates.\n";
				exit(1);
			}
			coord_limit = atoi(optarg);
			break;
		case '?':
			std::cerr << "Error: Invalid commad\n";
			exit(1);
		}

	}

	while (1) {

		int count = 0;
		RemoveStreet(i);
		i = 0;
		std::string name = "s";
		std::map<std::string, Point*> MyMap;
		//street_number = GenerateStreet(street_limit);
             street_number = GenerateStreet(5);
		for (i; i < street_number; i++) {
			int j = 0;
            Point* pointer = new Point[500];
			//street_segement = GenerateSegement(segement_limit);
                  street_segement = GenerateSegement(5);
			name.append("s");

			for (j; j < street_segement; j++) {
				
                pointer[j].x = GenerateCoord(coord_limit);
                pointer[j].y = GenerateCoord(coord_limit);
			}

			while (IsValid(street_def, j) == false) {
				count++;
				if (count >= 24) {
					std::cerr << "Error: failed to generate valid input for 25 attempts\n";
					exit(1);
				}
				j = 0;
				for (j; j < street_segement; j++) {
                    pointer[j].x = GenerateCoord(coord_limit);
                    pointer[j].y = GenerateCoord(coord_limit) };
				}

			}

			MyMap.insert(std::pair<std::string, Point*>(name, pointer));

			qsort(MyMap[name], j, sizeof(Point), pt_cmp);

			OutputCommand(MyMap, name, j);

		}
        std::map<std::string,Point*>::iterator it;
        
        for(it=MyMap.begin();it!=MyMap.end();++it)
            delete(it->second);
        
		std::cout << "g\n";
        fflush(stdout);
        WaitTime(wait_limit);
	}
      //exit(0);
      return EXIT_SUCCESS;
}

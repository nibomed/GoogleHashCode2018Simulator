#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

int C, R, F, N, B, T;

class Ride {
public:
	int a, b, x, y, s, f;
};

std::vector<Ride> rides;

std::vector<std::vector<int>> plan;
std::set<int> usedRides;

int points = 0;

void readInFile(char* name) {
	std::ifstream fileIn;
	fileIn.open(name, std::ifstream::in);
	fileIn >> R >> C >> F >> N >> B >> T;
	for (int i = 0; i < N; i++) {
		Ride ride;
		fileIn >> ride.a >> ride.b >> ride.x >> ride.y >> ride.s >> ride.f;
		rides.push_back(ride);
	}
	fileIn.close();
}

void readOutFile(char* name) {
	std::ifstream fileOut;
	fileOut.open(name, std::ifstream::in);
	for (int i = 0; i < F; i++) {
		int n, tempInt;
		std::vector<int> tempVec;
		fileOut >> n;
		for (int j = 0; j < n; j++) {
			fileOut >> tempInt;
			tempVec.push_back(tempInt);
		}
		plan.push_back(tempVec);
	}
	fileOut.close();
}

int distance(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void process() {
	for (int vehicles = 0; vehicles < F; vehicles++) {
		int x = 0, y = 0, t = 0;
		std::vector<int> route = plan[vehicles];
		for each (int rideIdx in route)
		{
			Ride ride = rides[rideIdx];
			
			// gointg to start
			t += distance(x, y, ride.a, ride.b);
			
			// waiting for start and check bonus
			if (t <= ride.s) {
				t = ride.s;
				points += B;
			}

			// going to finish and check time
			x = ride.x;
			y = ride.y;
			t += distance(ride.a, ride.b, ride.x, ride.y);
			if (t <= ride.f) {
				points += distance(ride.a, ride.b, ride.x, ride.y);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		std::cout << "Please specify 'in' and 'out' files";
		return 0;
	}

	readInFile(argv[1]);
	readOutFile(argv[2]);
	
	process();
	std::cout << points;

	return 0;
}
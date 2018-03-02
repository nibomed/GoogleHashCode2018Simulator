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

int points = 0;
int pointsMax = 0;
int finishedRides = 0;
int earnedBonuses = 0;
int totalWaitingTime = 0;
int totalDistanceToRide = 0;


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
			totalDistanceToRide += distance(x, y, ride.a, ride.b);
			
			// waiting for start and check bonus
			if (t <= ride.s) {
				totalWaitingTime += ride.s - t;
				t = ride.s;
				points += B;
				earnedBonuses++;
			}

			// going to finish and check time
			x = ride.x;
			y = ride.y;
			t += distance(ride.a, ride.b, ride.x, ride.y);
			if (t <= ride.f) {
				points += distance(ride.a, ride.b, ride.x, ride.y);
				finishedRides++;
			}
		}
	}
}

void calculateMaxPoints() {
	pointsMax = N*B;
	for each (Ride ride in rides)
	{
		pointsMax += distance(ride.a, ride.b, ride.x, ride.y);
	}
}

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		std::cout << "Please specify 'in' and 'out' files";
		return 0;
	}

	readInFile(argv[1]);
	readOutFile(argv[2]);
	
	calculateMaxPoints();

	process();

	std::cout << "Data: " << argv[1] << std::endl;
	std::cout << "Proposed solution: " <<argv[2] << std::endl;
	std::cout << "Successfully finished " << finishedRides << " rides from " << rides.size() << " rides" << std::endl;
	std::cout << "   ... also " << earnedBonuses << " of them with bonuses" << std::endl;
	if (finishedRides != 0) {
		std::cout << "Average passenger waiting time: " << 1.0 * totalWaitingTime / finishedRides << std::endl;
		std::cout << "Average distance to new ride: " << 1.0 * totalDistanceToRide / finishedRides << std::endl;
	}
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::cout << "Earned: " << points << " points from theoretical maximum of " << pointsMax << " points" << std::endl;

	return 0;
}
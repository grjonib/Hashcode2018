#pragma once
#include <vector>

struct Pos
{
	int row;
	int column;
};

static int GetDistance(Pos a, Pos b)
{
	return abs(a.row - b.row) + abs(a.column - b.column);
}

struct Ride
{
	int rideID;
	Pos start;
	Pos end;
	int earliestStartTime;
	int latestFinishTime;

	int rideDistance;
};

struct Vehicle
{
	int index;
	Pos currentPos{ 0,0 };
	int availableTime{ 0 };
	std::vector<int> assignments;
};


struct AssignmentData
{
	int numberOfRows;
	int numberOfColumns;
	int numberOfVehicles;
	int numberOfRides;
	
	int bonusPerRide;

	int totalTimeSteps;

	std::vector<Ride> rides;
	std::vector<Vehicle> vehicles;
	
};

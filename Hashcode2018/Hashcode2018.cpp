// Hashcode2018.cpp : Defines the entry point for the console application.
//

#include "DataClasses.h"
#include "FileParser.h"
#include "FileWriter.h"

#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>

void MyAwsomeAlgorithm(AssignmentData &data);

int main()
{	
	std::vector<std::string> dataFiles{
		"datafiles/a_example.in",
		"datafiles/b_should_be_easy.in",
		"datafiles/c_no_hurry.in",
		"datafiles/d_metropolis.in",
		"datafiles/e_high_bonus.in",
	};

	std::chrono::high_resolution_clock clock;
	int totalScore{ 0 };

	//Loop through all the files
	for (auto&& fileName : dataFiles)
	{
		//Setup
		auto startTime = clock.now();
		AssignmentData data;
		FileParser fp{ data };
		fp.parseDataFile(fileName);

		//Run Algorithm
		MyAwsomeAlgorithm(data);

		//Cleanup
		FileWriter::writeFile(fileName.substr(0, fileName.size() - 2) + "out", data);
		std::cout << "Processing " << fileName << " took " << std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - startTime).count() << " ms." << std::endl;
		std::cout << "------------\n";
	}
			
	return 0;
}


int CalcRideScore(Vehicle &vehicle, Ride &ride, int bonus)
{
	int preRideDist = GetDistance(vehicle.currentPos, ride.start);
	int timeWhenAtStart = vehicle.availableTime + preRideDist;
	if (timeWhenAtStart + ride.rideDistance < ride.latestFinishTime)
	{
		int score{ 0 };
		if (timeWhenAtStart <= ride.earliestStartTime)
			score += bonus;

		score += ride.rideDistance;
		score -= preRideDist;

		if (timeWhenAtStart < ride.earliestStartTime)
			score -= (ride.earliestStartTime - timeWhenAtStart);

		
		return (score >= 0) ? score : 0;
	}

	return -1;

}

int GetMax(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

void OrderRides(AssignmentData &data)
{
	std::sort(data.rides.begin(), data.rides.end(), [](const Ride &a, const Ride &b) -> bool {

		if (abs(a.earliestStartTime - b.earliestStartTime) > 1)
			return a.earliestStartTime < b.earliestStartTime;


		if (abs(a.latestFinishTime - b.latestFinishTime) > 1)
			return a.latestFinishTime < b.latestFinishTime;



		return a.rideDistance > b.rideDistance;

	});
}

void InitalizeVehicles(AssignmentData &data)
{
	for (int i = 0; i < data.numberOfVehicles; i++)
	{
		data.vehicles.emplace_back(Vehicle{ i });
	}
}

void MyAwsomeAlgorithm(AssignmentData &data)
{
	OrderRides(data);
	InitalizeVehicles(data);

	int score{ 0 };
	int rideCounter{ 0 };
	int bonusCounter{ 0 };
	
	for (auto&& ride : data.rides)
	{

		int maxScore{ -1 };
		int maxVehicleId{ -1 };

		// Calculate score for all vehicles taking this ride
		for (auto&& vehicle : data.vehicles)
		{
			int score = CalcRideScore(vehicle, ride, data.bonusPerRide);
			if (score > maxScore)
			{
				maxScore = score;
				maxVehicleId = vehicle.index;
			}
		}

		//If a vehicle can to this ride, assign the ride to vehicle
		if (maxVehicleId >= 0)
		{
			//Assign ride
			data.vehicles[maxVehicleId].assignments.emplace_back(ride.rideID);

			//Update vehicle
			int timeForBonus = ride.earliestStartTime + ride.rideDistance;
			data.vehicles[maxVehicleId].availableTime = GetMax(timeForBonus, data.vehicles[maxVehicleId].availableTime + GetDistance(data.vehicles[maxVehicleId].currentPos, ride.start) + ride.rideDistance);
			data.vehicles[maxVehicleId].currentPos = ride.end;

			//Calc score
			if (data.vehicles[maxVehicleId].availableTime == timeForBonus)
			{
				bonusCounter++;
				score += data.bonusPerRide;
			}			

			score += ride.rideDistance;
			rideCounter++;
		}
	}

	std::cout << "Rides made " << rideCounter << " out of " << data.numberOfRides << ". Bonus rides " << bonusCounter << ". Score: " << score << std::endl;
}

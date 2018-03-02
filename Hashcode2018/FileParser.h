#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


/*

3 4 2 3 2 10
0 0 1 3 2 9
1 2 1 0 0 9
2 0 2 2 0 9

*/

class FileParser
{
public:
	FileParser(AssignmentData &data) : data(data){};
	~FileParser() = default;
	
	void parseDataFile(std::string filename)
	{
		std::ifstream infile(filename);

		std::string line;

		//Parsing first line
		std::getline(infile, line);
		parseFirstLine(line);

		for (int i = 0; i < data.numberOfRides; i++)
		{
			std::getline(infile, line);
			addRide(line, i);
			
		}
	}

private:

	AssignmentData &data;

	template<typename Out>
	void split(const std::string &s, char delim, Out result) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}

	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, std::back_inserter(elems));
		return elems;
	}

	void parseFirstLine(std::string &line)
	{
		auto elems = split(line, ' ');

		if (elems.size() != 6)
		{
			std::cout << "FATAL ERROR, wrong number of parameters in first line" << std::endl;
			return;
		}

		data.numberOfRows= std::stoi(elems[0]);
		data.numberOfColumns = std::stoi(elems[1]);
		data.numberOfVehicles = std::stoi(elems[2]);
		data.numberOfRides = std::stoi(elems[3]);
		data.bonusPerRide = std::stoi(elems[4]);
		data.totalTimeSteps = std::stoi(elems[5]);

	}

	void addRide(std::string &line, int rideID)
	{
		auto elems = split(line, ' ');

		if (elems.size() != 6)
		{
			std::cout << "FATAL ERROR, rides should have 6 elements" << std::endl;
			return;
		}

		auto r = Ride{ rideID, Pos{ std::stoi(elems[0]) , std::stoi(elems[1]) }, Pos{ std::stoi(elems[2]) , std::stoi(elems[3]) }, std::stoi(elems[4]), std::stoi(elems[5]) };
		r.rideDistance = GetDistance(r.start, r.end);

		data.rides.emplace_back(r);




		
		return;
	}
};
#pragma once

#include "DataClasses.h"

#include <string>
#include <iostream>
#include <fstream>



class FileWriter
{
public:
	static void writeFile(std::string outputFileName, AssignmentData &data)
	{
		if (data.numberOfVehicles != data.vehicles.size())
		{
			std::cout << "Not all vehicles are in the list";
			return;
		}

		//std::cout << "Writing to: " << outputFileName << std::endl;

		std::ofstream output;
		
		output.open(outputFileName);
		for (auto&& vehicle : data.vehicles)
		{
			output << vehicle.assignments.size();
			for (auto&& assignment : vehicle.assignments)
			{
				output << " " << assignment;
			}
			output << "\n";
		}
		output.close();

		return;
	}

private:
	// Disallow creating an instance of this object
	FileWriter() {}
};


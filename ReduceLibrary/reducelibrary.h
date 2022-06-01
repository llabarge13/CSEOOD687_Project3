// reduce.h
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Reduce class definition

#pragma once
#include "framework.h"
#include <vector>
#include <boost\filesystem.hpp>
#include <boost\container\map.hpp>

/*	Decorate with either dllexport or dllimport depending
	on whether REDUCELIBRARY_EXPORTS is defined
*/
#ifdef REDUCELIBRARY_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif


// Performs reduce operation on intermediate results.
// Given sorted data from the intermediate file, reduces the results 
// by aggregating the values and output result to a file.
// e.g. (word, [1, 1]) -> (word, 2)
// Example:
//		boost::filesystem::path ouput_directory = boost::filesystem::path{ ".\\tem" };
//		boost::container::map<std::string, std::vector<int>> map_data;
//		std::vector<int> one{ 1 };
//		std::vector<int> two{ 1, 1 };
//		map_data["the"] = two;
//		map_data["quick"] = one;
//		map_data["brown"] = one;
//		Reduce reducer = Reduce(ouput_directory);
//		for (auto const& pair : map_data) {
//		    success = reducer->reduce(pair.first, pair.second);
//		}
class Reduce : public IReduce<std::string, int>
{

public:
	Reduce(const boost::filesystem::path& directory);

	// Sort operation
	int sort(const boost::filesystem::path& file);

	// Get aggregate/sorted data.
	// Aggregate data is map of where the key is a word
	// and the values are word counts. 
	// e.g. (word, [1, 1])
	const boost::container::map<std::string,
		std::vector<int>>&getAggregateData();

	// Performs reduce operation on intermediate results.
	// Given sorted data from the intermediate file, reduces the results 
	// by aggregating the values and output result to a file.
	// e.g. (word, [1, 1]) -> (word, 2)
	// If reduce operation fails (cannot write to file), returns -1. 
	// If reduce operation succeeds, returns 0.
	int reduce(const std::string& key, const std::vector<int>& values);


private:
	// Stores the sorted/aggregate data in memory
	boost::container::map<std::string, std::vector<int>> aggregate_data_;
};

extern "C" REDUCELIBRARY_API Reduce * createReducer(const boost::filesystem::path & directory);
extern "C" REDUCELIBRARY_API void destoryReducer(const Reduce * reducer);
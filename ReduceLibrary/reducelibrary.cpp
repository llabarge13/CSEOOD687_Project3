// reduce.cpp
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Reduce class implementation
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "reducelibrary.h"
#include "framework.h"

Reduce::Reduce(const boost::filesystem::path& directory) : IReduce<std::string, int>(directory)
{
}

// Performs reduce operation on intermediate results.
// Given sorted data from the intermediate file, reduces the results 
// by aggregating the values and output result to a file.
// e.g. (word, [1, 1]) -> (word, 2)
// If reduce operation fails (cannot write to file), returns -1. 
// If reduce operation succeeds, returns 0.
int Reduce::reduce(const std::string& key, const std::vector<int>& values)
{
	// Run reduce
	int result = std::reduce(std::execution::seq, values.begin(), values.end());
	// Write reduced value
	return exportToDisk(key, result);
}

// Sort map output from an input file.
// Input file must have the following format
//		(word, 1)
//		(word, 1)
//		...
// If the file cannot be parsed, returns -1.
// If the sort operation succeeds, retuns 0.
int Reduce::sort(const boost::filesystem::path& file)
{
	boost::filesystem::ifstream map_output(file);
	// File could not be opened
	if (map_output.fail()) {
		return -1;
	}

	std::string line;
	while (getline(map_output, line)) {
		// Parse out the key and the value
		boost::tokenizer<> tok(line);
		boost::tokenizer<>::iterator beg = tok.begin();
		std::string key = *beg;
		beg++;
		std::string value = *beg;

		try {
			// Add the value to the key's container
			aggregate_data_[key].push_back(std::stoi(value));
		}
		catch ([[maybe_unused]] const std::invalid_argument& ia) {
			// Value could not be converted to an integer
			// File has incorrect format
			return -1;
		}
	}
	map_output.close();

	// Success
	return 0;
}

// Get aggregate/sorted data.
// Aggregate data is map of where the key is a word
// and the values are word counts. 
// e.g. (word, [1, 1])
const boost::container::map<std::string,
	std::vector<int>>&Reduce::getAggregateData()
{
	return aggregate_data_;
}

REDUCELIBRARY_API Reduce* createReducer(const boost::filesystem::path& directory)
{
	return new Reduce(directory);
}

REDUCELIBRARY_API void destoryReducer(const Reduce* reducer)
{
	delete reducer;
}

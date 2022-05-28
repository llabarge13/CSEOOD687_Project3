// workflow.h
// Todd Hricik
// CSE687 Object Oriented Design
// April 28, 2022 - Project 1
// 
//  Workflow class definition
// May 12, 2022 - Updated for project 2
//  Updated for reduce and map DLLs
#pragma once
#include "boost\filesystem.hpp"
#include "imap.h"
#include "sorting.h"
#include "ireduce.h"

typedef IMap<std::string, std::string>* (*buildMapper)(const boost::filesystem::path&);
typedef IReduce<std::string, int>* (*buildReducer)(const boost::filesystem::path&);

class Workflow
{
	public:
		Workflow(std::string input_dir_arg, 
			std::string inter_dir_arg, 
			std::string output_dir_arg, 
			std::string map_dll_path, 
			std::string reduce_dll_path);											// constructor
		~Workflow();																// destructor
		boost::filesystem::path getTargetDir();										// directory containing files to be fed to Map
		boost::filesystem::path getIntermediateDir();								// directory containing intermediate files from Map
		boost::filesystem::path getOutDir();										// directory containing output file(s) from reduce
		boost::filesystem::path getMapLibPath();									// path to map dll
		boost::filesystem::path getReduceLibPath();									// path to reduce dll
		void run();																	// Runs the map sort reduce workflow


	private:
		boost::filesystem::path target_dir_;
		boost::filesystem::path intermediate_dir_;
		boost::filesystem::path out_dir_;
		boost::filesystem::path map_lib_path_;
		boost::filesystem::path reduce_lib_path_;


		IMap<std::string, std::string> * map_;										// Map is aggregated by Workflow
		Sorting* sorter_;															// Sorting is aggregated by Workflow
		IReduce<std::string, int>* reduce_;											// Reduce is aggregated by Workflow

		// Interfaces to map and reduce librarys 
		buildMapper create_map_;
		buildReducer create_reduce_;

		// Handles to map and reduce DLLs
		HINSTANCE hDLL_map_;
		HINSTANCE hDLL_reduce_;

};


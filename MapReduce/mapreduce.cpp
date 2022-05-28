// mapreduce.cpp
// Todd Hricik
// CIS 687 Object Oriented Design
// Project 1
////////////////////////////////////////////////////////////////////////////////////
// This program acts as executor which will intantiate a workflow object and invoke 
// the workflow's run member function
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <boost\log\core.hpp>
#include <boost\log\expressions.hpp>
#include <boost\filesystem.hpp>
#include <boost\log\trivial.hpp>
#include "executive.h"
#include "workflow.h"

// Set the boost logging threshold to >= info
void init()
{
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
}

int main(int argc, char* argv[])
{
    init();

    // check that comand line input is valid
    if (argc != 6)
    {
        BOOST_LOG_TRIVIAL(fatal) << "MapReduce <path of dir containging input files> <path of dir for intermediate files> <path of dir for output files <path of map DLL> <path of reduce DLL>";
        return -1;
    }

    // declare strings to hold command line input values which should each be a path to a directory
    std::string target_dir = argv[1];
    std::string intermediate_dir = argv[2];
    std::string out_dir = argv[3];
    std::string map_dll = argv[4];
    std::string reduce_dll = argv[5];

    // Instantiate an executor
    Executive* executive = new Executive(target_dir, intermediate_dir, out_dir, map_dll, reduce_dll);

    // Use the executor to run the workflow
    executive->run();

    delete executive;
}
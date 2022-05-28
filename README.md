# CSE687 Project 2: Map Reduce
May 12, 2022

Authors: Todd Hricik, Lyndsay LaBarge

## Overview
The Visual Studio Solution contains five seperate projects. We are using Visual Studio 2022.

The MapReduce project contains the implementation of the primary command line application.

The UnitTests project contains our Google Unit tests.

The Interfaces project contains out map and reduce interfaces, IMap and IReduce. These are template abstract classes. Concrete classes must include a map and reduce class 
method respectively.

The MapLibrary project contains our DLL library with our concrete Map class implementation. It follows the factory method pattern and contains a single function,
createMapper that returns a pointer to a concrete Map class object. The createMapper function takes single parameter, the output directory the object writes its results to.

The ReduceLibrary project contains our DLL library with our concrete Reduce class implementation. It follows the factory method pattern and contains a single function,
createReducer that returns a pointer to a concrete Reduce class object. The createReducer function takes single parameter, the output directory the object writes its results to.

We used C++ 17 and the boost C++ library (version 1.79). We used the boost Filesystem as opposed to implementating our own file management class.

## Build
All projects use a properties sheet. To build the projects, you will need to change the values of the user macros BoostRoot and BoostLib in MapReduce > PropertySheet.props, UnitTests > PropertySheet.props, Interfaces > PropertySheet.props, MapLibrary > PropertySheet.props, and ReduceLibrary > PropertySheet.props. By default they are set to `C:\Program Files\boost\boost_ 1_79_0` and `C:\Program Files\boost\boost_1_79_0\stage\lib`. To build, use either the Debug or Release configuration for x64 platforms.

## Usage
```
MapReduce.exe <path of dir containging input files> <path of dir for intermediate files> <path of dir for output files <path of map DLL> <path of reduce DLL>
```
All command line requirements are required. 

The input directory must contain UTF-8 encoded text files. If the input directory contains a file that does not meet the requirements, that file will be skipped during processing.

If the intermediate directory or the output directory does not already exist, the application will create the directories.

## Expected Output
### Command
```
.\MapReduce.exe "..\..\MapReduce\shakespeare" ".\temp" ".\output" ".\MapLibrary.dll" ".\ReduceLibrary.dll"
```
### Command Line Output 
```
[2022-05-11 18:00:15.188198] [0x00006dbc] [info]    targetDir member has been set in Workflow constructor.
[2022-05-11 18:00:15.188698] [0x00006dbc] [warning] Warning in Workflow constructor: argv[2] is not a directory

[2022-05-11 18:00:15.189199] [0x00006dbc] [info]    Info in Workflow constructor: Creating directory at .\temp now...
[2022-05-11 18:00:15.189199] [0x00006dbc] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-11 18:00:15.189700] [0x00006dbc] [warning] Warning in Workflow constructor: argv[3] is not a directory

[2022-05-11 18:00:15.189700] [0x00006dbc] [info]    Info in Workflow constructor: Creating directory at .\temp now...
[2022-05-11 18:00:15.190192] [0x00006dbc] [info]    Info in Workflow constructor: Directory for output files created.
[2022-05-11 18:00:15.190699] [0x00006dbc] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-11 18:00:15.191690] [0x00006dbc] [info]    Info in Workflow constructor: Reduce DLL located.
[2022-05-11 18:00:15.989329] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-05-11 18:00:16.553427] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for AMidSummerNightsDream.txt
[2022-05-11 18:00:17.298251] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for AsYouLIkeIte.txt
[2022-05-11 18:00:18.241415] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for Cymbeline.txt
[2022-05-11 18:00:18.998048] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for Love'sLabourLost.txt
[2022-05-11 18:00:19.759180] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for MeasureForMeasure.txt
[2022-05-11 18:00:20.493307] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for MuchAdoAboutNothing.txt
[2022-05-11 18:00:21.139921] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for PericlesPrinceOfTyre.txt
[2022-05-11 18:00:21.866047] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TamingOfTheShrew.txt
[2022-05-11 18:00:22.391638] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheComedyOfErrors.txt
[2022-05-11 18:00:24.543288] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheMerchantOfVenice.txt
[2022-05-11 18:00:25.320423] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheMerryWivesOfWindsor.txt
[2022-05-11 18:00:25.888022] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheTempest.txt
[2022-05-11 18:00:26.578642] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheTwelthNight.txt
[2022-05-11 18:00:27.168745] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TheTwoGentlemenOfVerona.txt
[2022-05-11 18:00:28.065401] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for TroilusAndCressida .txt
[2022-05-11 18:00:28.902547] [0x00006dbc] [info]    Info in Workflow run(): Map process completed for Winter'sTale.txt
[2022-05-11 18:00:28.903548] [0x00006dbc] [info]    Running sort on All'sWellThatEndsWell.txt
[2022-05-11 18:00:29.435140] [0x00006dbc] [info]    Running sort on AMidSummerNightsDream.txt
[2022-05-11 18:00:29.808705] [0x00006dbc] [info]    Running sort on AsYouLIkeIte.txt
[2022-05-11 18:00:30.311793] [0x00006dbc] [info]    Running sort on Cymbeline.txt
[2022-05-11 18:00:30.943402] [0x00006dbc] [info]    Running sort on Love'sLabourLost.txt
[2022-05-11 18:00:31.455992] [0x00006dbc] [info]    Running sort on MeasureForMeasure.txt
[2022-05-11 18:00:31.959579] [0x00006dbc] [info]    Running sort on MuchAdoAboutNothing.txt
[2022-05-11 18:00:32.443664] [0x00006dbc] [info]    Running sort on PericlesPrinceOfTyre.txt
[2022-05-11 18:00:32.871238] [0x00006dbc] [info]    Running sort on TamingOfTheShrew.txt
[2022-05-11 18:00:33.352823] [0x00006dbc] [info]    Running sort on TheComedyOfErrors.txt
[2022-05-11 18:00:33.719886] [0x00006dbc] [info]    Running sort on TheMerchantOfVenice.txt
[2022-05-11 18:00:34.202970] [0x00006dbc] [info]    Running sort on TheMerryWivesOfWindsor.txt
[2022-05-11 18:00:34.719060] [0x00006dbc] [info]    Running sort on TheTempest.txt
[2022-05-11 18:00:35.103627] [0x00006dbc] [info]    Running sort on TheTwelthNight.txt
[2022-05-11 18:00:35.578710] [0x00006dbc] [info]    Running sort on TheTwoGentlemenOfVerona.txt
[2022-05-11 18:00:35.981280] [0x00006dbc] [info]    Running sort on TroilusAndCressida .txt
[2022-05-11 18:00:36.584885] [0x00006dbc] [info]    Running sort on Winter'sTale.txt
[2022-05-11 18:00:37.156984] [0x00006dbc] [info]    Running reduce operation...
[2022-05-11 18:00:41.511021] [0x00006dbc] [info]    Writing success file...
[2022-05-11 18:00:41.512022] [0x00006dbc] [info]    Removing intermediate files...
[2022-05-11 18:00:41.648603] [0x00006dbc] [info]    Map reduce process complete.
```

### File Output
Assuming the application completed with no errors, the results of the map reduce operation are located in the specified output directory. It will output 2 files.

`reduce.txt` - file containing the map reduce output

`SUCCESS` - file indicating the operation completed successfully


## Unit Test Results
The unit tests are defined in UnitTests\tests.cpp. There are unit tests for the Map, Sort, Reduce, and Workflow calsses. 

```
[==========] Running 12 tests from 4 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from mapTest
[ RUN      ] mapTest.checkOutputPath
[       OK ] mapTest.checkOutputPath (1 ms)
[ RUN      ] mapTest.checkMapResult
[       OK ] mapTest.checkMapResult (1 ms)
[ RUN      ] mapTest.badOutputDirectory
[       OK ] mapTest.badOutputDirectory (0 ms)
[----------] 3 tests from mapTest (3 ms total)

[----------] 3 tests from sortTest
[ RUN      ] sortTest.checkSortOutput
[       OK ] sortTest.checkSortOutput (0 ms)
[ RUN      ] sortTest.badInputFilePath
[       OK ] sortTest.badInputFilePath (0 ms)
[ RUN      ] sortTest.badInputFileFormat
[       OK ] sortTest.badInputFileFormat (1 ms)
[----------] 3 tests from sortTest (2 ms total)

[----------] 4 tests from reduceTest
[ RUN      ] reduceTest.checkOutputDirectory
[       OK ] reduceTest.checkOutputDirectory (1 ms)
[ RUN      ] reduceTest.checkOutputPath
[       OK ] reduceTest.checkOutputPath (1 ms)
[ RUN      ] reduceTest.checkBadDirectory
[       OK ] reduceTest.checkBadDirectory (0 ms)
[ RUN      ] reduceTest.checkReduceOutput
[       OK ] reduceTest.checkReduceOutput (4 ms)
[----------] 4 tests from reduceTest (6 ms total)

[----------] 2 tests from WorkflowTest
[ RUN      ] WorkflowTest.testConstructor
[2022-05-11 17:04:29.398128] [0x00002ef8] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-05-11 17:04:29.398628] [0x00002ef8] [info]    targetDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.399129] [0x00002ef8] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.401131] [0x00002ef8] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-11 17:04:29.401629] [0x00002ef8] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.402129] [0x00002ef8] [info]    Info in Workflow constructor: Directory for output files created.
[2022-05-11 17:04:29.405130] [0x00002ef8] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-11 17:04:29.407630] [0x00002ef8] [info]    Info in Workflow constructor: Reduce DLL located.
[       OK ] WorkflowTest.testConstructor (10 ms)
[ RUN      ] WorkflowTest.testRun
[2022-05-11 17:04:29.408631] [0x00002ef8] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-05-11 17:04:29.409131] [0x00002ef8] [info]    targetDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.409630] [0x00002ef8] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.410131] [0x00002ef8] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-11 17:04:29.410631] [0x00002ef8] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-05-11 17:04:29.411130] [0x00002ef8] [info]    Info in Workflow constructor: Directory for output files created.
[2022-05-11 17:04:29.414131] [0x00002ef8] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-11 17:04:29.416631] [0x00002ef8] [info]    Info in Workflow constructor: Reduce DLL located.
[2022-05-11 17:04:29.456138] [0x00002ef8] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-05-11 17:04:29.457138] [0x00002ef8] [info]    Running sort on All'sWellThatEndsWell.txt
[2022-05-11 17:04:29.469140] [0x00002ef8] [info]    Running reduce operation...
[2022-05-11 17:04:30.575334] [0x00002ef8] [info]    Writing success file...
[2022-05-11 17:04:30.576334] [0x00002ef8] [info]    Removing intermediate files...
[2022-05-11 17:04:30.577333] [0x00002ef8] [info]    Map reduce process complete.
[       OK ] WorkflowTest.testRun (1171 ms)
[----------] 2 tests from WorkflowTest (1181 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 4 test cases ran. (1195 ms total)
[  PASSED  ] 12 tests.
```
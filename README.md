# CSE687 Project 3: Map Reduce
June 2, 2022

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

## Threading
You can configure the number of map and reduce threads via the command line using the ```--mappers``` and ```--reducers``` arguments. Note that the number of map and reduce threads is capped at the number of input files e.g. if there are 20 input files, you cannot have more than 20 map or reduce threads. If you pass a larger number via the command line, only 20 threads will be created.

The application will first split all the input files equally amongst the map threads. Each map thread will then seperate its assigned input files into R partitions, where R is the number of reducers. Note if the map thread does not have > R input files to process,
not all of the partitions will contain data and will be skipped.

## Build
All projects use a properties sheet. To build the projects, you will need to change the values of the user macros BoostRoot and BoostLib in MapReduce > PropertySheet.props, UnitTests > PropertySheet.props, Interfaces > PropertySheet.props, MapLibrary > PropertySheet.props, and ReduceLibrary > PropertySheet.props. By default they are set to `C:\Program Files\boost\boost_ 1_79_0` and `C:\Program Files\boost\boost_1_79_0\stage\lib`. To build, use either the Debug or Release configuration for x64 platforms.

## Usage
```
.\MapReduce.exe --help
Allowed options:
  --help                Show options
  --version             Verison number
  --input arg           Input directory path. Required.
  --temp arg            Intermediate directory path. Required.
  --output arg          Output directory path. Required.
  --map-dll arg         Path to map DLL. Required.
  --reduce-dll arg      Path to reduce DLL. Required.
  --mappers arg (=2)    Number of map threads. Optional. Defaults to 2.
  --reducers arg (=3)   Number of reduce threads. Optional. Defaults to 3.
```
All command line requirements are required except for the configurable number of mappers and reducers. 

The input directory must contain UTF-8 encoded text files. If the input directory contains a file that does not meet the requirements, that file will be skipped during processing.

If the intermediate directory or the output directory does not already exist, the application will create the directories.

## Expected Output
### Command
```
.\MapReduce.exe --input "..\..\MapReduce\books" --temp ".\temp" --output ".\output" --map-dll ".\MapLibrary.dll" --reduce-dll ".\ReduceLibrary.dll"
```
### Command Line Output 
```
[2022-05-31 18:43:57.742238] [0x00000804] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-31 18:43:57.744072] [0x00000804] [info]    Info in Workflow constructor: Reduce DLL located.
[2022-05-31 18:43:57.744072] [0x00000804] [info]    targetDir member has been set in Workflow constructor.
[2022-05-31 18:43:57.744562] [0x00000804] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-05-31 18:43:57.744562] [0x00000804] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-31 18:43:57.745063] [0x00000804] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-05-31 18:43:57.747571] [0x00005754] [info]    Info in Workflow run(): Running map process for All'sWellThatEndsWell.txt
[2022-05-31 18:43:57.748064] [0x000047cc] [info]    Info in Workflow run(): Running map process for AliceInWonderland.txt
[2022-05-31 18:43:58.566206] [0x00005754] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-05-31 18:43:58.566706] [0x00005754] [info]    Info in Workflow run(): Running map process for MeasureForMeasure.txt
[2022-05-31 18:43:58.627717] [0x000047cc] [info]    Info in Workflow run(): Map process completed for AliceInWonderland.txt
[2022-05-31 18:43:58.628217] [0x000047cc] [info]    Info in Workflow run(): Running map process for Love'sLabourLost.txt
[2022-05-31 18:43:59.333340] [0x00005754] [info]    Info in Workflow run(): Map process completed for MeasureForMeasure.txt
[2022-05-31 18:43:59.333840] [0x00005754] [info]    Info in Workflow run(): Running map process for TheMerchantOfVenice.txt
[2022-05-31 18:43:59.388850] [0x000047cc] [info]    Info in Workflow run(): Map process completed for Love'sLabourLost.txt
[2022-05-31 18:43:59.388850] [0x000047cc] [info]    Info in Workflow run(): Running map process for TheComedyOfErrors.txt
[2022-05-31 18:43:59.931945] [0x000047cc] [info]    Info in Workflow run(): Map process completed for TheComedyOfErrors.txt
[2022-05-31 18:43:59.932445] [0x000047cc] [info]    Info in Workflow run(): Running map process for TroilusAndCressida .txt
[2022-05-31 18:44:00.074470] [0x00005754] [info]    Info in Workflow run(): Map process completed for TheMerchantOfVenice.txt
[2022-05-31 18:44:00.074970] [0x00005754] [info]    Info in Workflow run(): Running map process for Winter'sTale.txt
[2022-05-31 18:44:00.854106] [0x000047cc] [info]    Info in Workflow run(): Map process completed for TroilusAndCressida .txt
[2022-05-31 18:44:00.854606] [0x000047cc] [info]    Info in Workflow run(): Running map process for AMidSummerNightsDream.txt
[2022-05-31 18:44:00.942621] [0x00005754] [info]    Info in Workflow run(): Map process completed for Winter'sTale.txt
[2022-05-31 18:44:00.943122] [0x00005754] [info]    Info in Workflow run(): Running map process for AsYouLIkeIte.txt
[2022-05-31 18:44:01.428706] [0x000047cc] [info]    Info in Workflow run(): Map process completed for AMidSummerNightsDream.txt
[2022-05-31 18:44:01.429207] [0x000047cc] [info]    Info in Workflow run(): Running map process for MuchAdoAboutNothing.txt
[2022-05-31 18:44:01.707255] [0x00005754] [info]    Info in Workflow run(): Map process completed for AsYouLIkeIte.txt
[2022-05-31 18:44:01.707755] [0x00005754] [info]    Info in Workflow run(): Running map process for PericlesPrinceOfTyre.txt
[2022-05-31 18:44:02.191840] [0x000047cc] [info]    Info in Workflow run(): Map process completed for MuchAdoAboutNothing.txt
[2022-05-31 18:44:02.192340] [0x000047cc] [info]    Info in Workflow run(): Running map process for TheMerryWivesOfWindsor.txt
[2022-05-31 18:44:02.380873] [0x00005754] [info]    Info in Workflow run(): Map process completed for PericlesPrinceOfTyre.txt
[2022-05-31 18:44:02.381373] [0x00005754] [info]    Info in Workflow run(): Running map process for TheTempest.txt
[2022-05-31 18:44:02.968475] [0x00005754] [info]    Info in Workflow run(): Map process completed for TheTempest.txt
[2022-05-31 18:44:02.968976] [0x00005754] [info]    Info in Workflow run(): Running map process for Frankenstein.txt
[2022-05-31 18:44:02.978977] [0x000047cc] [info]    Info in Workflow run(): Map process completed for TheMerryWivesOfWindsor.txt
[2022-05-31 18:44:02.979478] [0x000047cc] [info]    Info in Workflow run(): Running map process for Cymbeline.txt
[2022-05-31 18:44:03.975151] [0x000047cc] [info]    Info in Workflow run(): Map process completed for Cymbeline.txt
[2022-05-31 18:44:03.975652] [0x000047cc] [info]    Info in Workflow run(): Running map process for PrideAndPrejudice.txt
[2022-05-31 18:44:05.394399] [0x00005754] [info]    Info in Workflow run(): Map process completed for Frankenstein.txt
[2022-05-31 18:44:05.394900] [0x00005754] [info]    Info in Workflow run(): Running map process for TamingOfTheShrew.txt
[2022-05-31 18:44:06.136029] [0x00005754] [info]    Info in Workflow run(): Map process completed for TamingOfTheShrew.txt
[2022-05-31 18:44:06.136529] [0x00005754] [info]    Info in Workflow run(): Running map process for TheTwoGentlemenOfVerona.txt
[2022-05-31 18:44:06.746636] [0x00005754] [info]    Info in Workflow run(): Map process completed for TheTwoGentlemenOfVerona.txt
[2022-05-31 18:44:07.774815] [0x000047cc] [info]    Info in Workflow run(): Map process completed for PrideAndPrejudice.txt
[2022-05-31 18:44:07.774815] [0x000047cc] [info]    Info in Workflow run(): Running map process for TheTwelthNight.txt
[2022-05-31 18:44:08.387423] [0x000047cc] [info]    Info in Workflow run(): Map process completed for TheTwelthNight.txt
[2022-05-31 18:44:08.389423] [0x00001a2c] [info]    Running sort on 18380p0
[2022-05-31 18:44:08.389423] [0x00006480] [info]    Running sort on 18380p1
[2022-05-31 18:44:08.389423] [0x000063c0] [info]    Running sort on 18380p2
[2022-05-31 18:44:10.313759] [0x00006480] [info]    Running sort on 22356p1
[2022-05-31 18:44:11.269926] [0x00001a2c] [info]    Running sort on 22356p0
[2022-05-31 18:44:12.176085] [0x00006480] [info]    Running reduce operation...
[2022-05-31 18:44:13.509818] [0x000063c0] [info]    Running sort on 22356p2
[2022-05-31 18:44:13.998403] [0x00001a2c] [info]    Running reduce operation...
[2022-05-31 18:44:16.338813] [0x000063c0] [info]    Running reduce operation...
[2022-05-31 18:44:20.645005] [0x00000804] [info]    Running sort on reduce0.txt
[2022-05-31 18:44:20.962559] [0x00000804] [info]    Running sort on reduce1.txt
[2022-05-31 18:44:21.185098] [0x00000804] [info]    Running sort on reduce2.txt
[2022-05-31 18:44:21.523157] [0x00000804] [info]    Running reduce operation...
[2022-05-31 18:44:27.903973] [0x00000804] [info]    Writing success file...
[2022-05-31 18:44:27.904974] [0x00000804] [info]    Map reduce process complete.
[2022-05-31 18:44:27.904974] [0x00000804] [info]    Removing intermediate files...
```

### File Output
Assuming the application completed with no errors, the results of the map reduce operation are located in the specified output directory. It will output 2 files.

`reduce.txt` - file containing the map reduce output

`SUCCESS` - file indicating the operation completed successfully


## Unit Test Results
The unit tests are defined in UnitTests\tests.cpp. There are unit tests for the Map, Sort, Reduce, and Workflow calsses. 

```
Running main() from c:\a\1\s\thirdparty\googletest\googletest\src\gtest_main.cc
[==========] Running 12 tests from 4 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from mapTest
[ RUN      ] mapTest.checkOutputPath
".\temp\test.txt"
[       OK ] mapTest.checkOutputPath (3 ms)
[ RUN      ] mapTest.checkMapResult
[       OK ] mapTest.checkMapResult (2 ms)
[ RUN      ] mapTest.badOutputDirectory
[       OK ] mapTest.badOutputDirectory (1 ms)
[----------] 3 tests from mapTest (7 ms total)

[----------] 3 tests from sortTest
[ RUN      ] sortTest.checkSortOutput
[       OK ] sortTest.checkSortOutput (1 ms)
[ RUN      ] sortTest.badInputFilePath
[       OK ] sortTest.badInputFilePath (0 ms)
[ RUN      ] sortTest.badInputFileFormat
[       OK ] sortTest.badInputFileFormat (2 ms)
[----------] 3 tests from sortTest (4 ms total)

[----------] 4 tests from reduceTest
[ RUN      ] reduceTest.checkOutputDirectory
[       OK ] reduceTest.checkOutputDirectory (1 ms)
[ RUN      ] reduceTest.checkOutputPath
[       OK ] reduceTest.checkOutputPath (0 ms)
[ RUN      ] reduceTest.checkBadDirectory
[       OK ] reduceTest.checkBadDirectory (0 ms)
[ RUN      ] reduceTest.checkReduceOutput
[       OK ] reduceTest.checkReduceOutput (5 ms)
[----------] 4 tests from reduceTest (7 ms total)

[----------] 2 tests from WorkflowTest
[ RUN      ] WorkflowTest.testConstructor
[2022-05-31 18:50:04.396951] [0x00002edc] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-05-31 18:50:04.400952] [0x00002edc] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-31 18:50:04.403952] [0x00002edc] [info]    Info in Workflow constructor: Reduce DLL located.
[2022-05-31 18:50:04.403952] [0x00002edc] [info]    targetDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.404453] [0x00002edc] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.404953] [0x00002edc] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-31 18:50:04.405953] [0x00002edc] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.406453] [0x00002edc] [info]    Removing intermediate files...
[       OK ] WorkflowTest.testConstructor (13 ms)
[ RUN      ] WorkflowTest.testRun
[2022-05-31 18:50:04.409953] [0x00002edc] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-05-31 18:50:04.412954] [0x00002edc] [info]    Info in Workflow constructor: Map DLL located.
[2022-05-31 18:50:04.415955] [0x00002edc] [info]    Info in Workflow constructor: Reduce DLL located.
[2022-05-31 18:50:04.415955] [0x00002edc] [info]    targetDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.416455] [0x00002edc] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.416956] [0x00002edc] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-05-31 18:50:04.417455] [0x00002edc] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-05-31 18:50:04.421956] [0x00005c6c] [info]    Info in Workflow run(): Running map process for All'sWellThatEndsWell.txt
[2022-05-31 18:50:05.250100] [0x00005c6c] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-05-31 18:50:05.252601] [0x000027f0] [info]    Running sort on 23660p0
[2022-05-31 18:50:05.843204] [0x000027f0] [info]    Running reduce operation...
[2022-05-31 18:50:07.085422] [0x00002edc] [info]    Running sort on reduce0.txt
[2022-05-31 18:50:07.180438] [0x00002edc] [info]    Running reduce operation...
[2022-05-31 18:50:08.401151] [0x00002edc] [info]    Writing success file...
[2022-05-31 18:50:08.402652] [0x00002edc] [info]    Map reduce process complete.
[2022-05-31 18:50:08.402652] [0x00002edc] [info]    Removing intermediate files...
[       OK ] WorkflowTest.testRun (4003 ms)
[----------] 2 tests from WorkflowTest (4017 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 4 test cases ran. (4037 ms total)
[  PASSED  ] 12 tests.
```
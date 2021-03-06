# User makefile generated by OptFrame MCT (Make a Compilable Thing!)

all: mctApp$project

mctApp$project:      main$project.o  $projectProblemInstance.o  $projectEvaluator.o $projectConstructive$constructive.o  $projectNSSeq$neighborhood.o  $projectProblemCommand.o  $projectScanner.o  
	g++ $(GCC_FLAGS) main$project.o  $projectProblemInstance.o  $projectEvaluator.o $projectConstructive$constructive.o  $projectNSSeq$neighborhood.o  $projectProblemCommand.o  $projectScanner.o -o app_$project

main$project.o: main$project.cpp
	g++ -c $(GCC_FLAGS) main$project.cpp -o main$project.o
	
$projectProblemInstance.o: $project/ProblemInstance.cpp
	g++ -c $(GCC_FLAGS) $project/ProblemInstance.cpp -o $projectProblemInstance.o
	
$projectEvaluator.o: $project/Evaluator.cpp
	g++ -c $(GCC_FLAGS) $project/Evaluator.cpp -o $projectEvaluator.o
	
$projectConstructive$constructive.o: $project/Constructive$constructive.cpp
	g++ -c $(GCC_FLAGS) $project/Constructive$constructive.cpp -o $projectConstructive$constructive.o

$projectNSSeq$neighborhood.o: $project/NSSeq$neighborhood.cpp
	g++ -c $(GCC_FLAGS) $project/NSSeq$neighborhood.cpp -o $projectNSSeq$neighborhood.o
	
$projectScanner.o: ../OptFrame/Scanner++/Scanner.cpp
	g++ -c $(GCC_FLAGS) ../OptFrame/Scanner++/Scanner.cpp -o $projectScanner.o

$projectProblemCommand.o: $project/ProblemCommand.cpp
	g++ -c $(GCC_FLAGS) $project/ProblemCommand.cpp -o $projectProblemCommand.o



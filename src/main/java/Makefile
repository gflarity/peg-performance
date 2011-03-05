all:
	javac ca/tjug/talks/performance/Coordinate.java
	javac ca/tjug/talks/performance/GameState.java
	javac ca/tjug/talks/performance/Move.java
	javac ca/tjug/talks/performance/SolutionFinder.java
	echo -e "#!/bin/bash\n java ca.tjug.talks.performance.SolutionFinder" > ./performance
	chmod +x ./performance

clean:  
	-rm -rf ca/tjug/talks/performance/*class
	-rm ./performance

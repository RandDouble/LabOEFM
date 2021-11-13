LIBS:= `root-config --libs`
INCS:= `root-config --cflags` 

compile: millikan.exe angleCorrect.exe
#PART OF MAKEFILE USED FOR MILLIKAN EXPERIMENT
millikan: millikan.exe
#	rm log.log
	./millikan.exe dataRealProva.dat 
#>>log.log

millikan.exe: millikan.cpp
	g++ -o millikan.exe millikan.cpp ${LIBS} ${INCS}
#compila:
#	g++ -o millikan.exe millikan.cpp ${LIBS} ${INCS}
#PART OF MAKEFILE USED FOR ANGLE CORRECTIOKN
angle: angleCorrect.exe
	./angleCorrect.exe 20 51 30 40
angleCorrect.exe: angleCorrection.cpp
	g++ -o angleCorrect.exe angleCorrection.cpp 



clean: 
	rm millikan.exe
	rm angleCorrect.exe
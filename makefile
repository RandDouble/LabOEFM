LIBS:= `root-config --libs`
INCS:= `root-config --cflags` 
CFLAGS= -Wall -O

compile: millikan.exe angleCorrect.exe
#PART OF MAKEFILE USED FOR MILLIKAN EXPERIMENT
millikan: millikan.exe
#	rm log.log
#	./millikan.exe dataRealProva.dat 
#	./millikan.exe data.dat >>log.log
	./millikan.exe prova.dat >>log.log

millikan.exe: millikan.cpp
	g++ -o $@ $^ ${LIBS} ${INCS} ${CFLAGS}
#compila:
#	g++ -o millikan.exe millikan.cpp ${LIBS} ${INCS}
#PART OF MAKEFILE USED FOR ANGLE CORRECTIOKN
angle: angleCorrect.exe
	./angleCorrect.exe 31 11 29 57
angleCorrect.exe: angleCorrection.cpp
	g++ -o $@ $^ ${CFLAGS}
#PART OF MAKEFILE FOR CREATING ROOT GRAFIC FOR RETICULE SPECTROMETER
reticolo.exe:
	g++ -o $@ $^ ${LIBS} ${INCS} ${CFLAGS}


clean: 
	rm millikan.exe
	rm angleCorrect.exe
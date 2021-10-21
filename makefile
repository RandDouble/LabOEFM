LIBS:= `root-config --libs`
INCS:= `root-config --cflags` 


esegui: millikan.exe
#	rm log.log
	./millikan.exe dataRealProva.dat 
#>>log.log

millikan.exe: millikan.cpp
	g++ -o millikan.exe millikan.cpp ${LIBS} ${INCS}
compila:
	g++ -o millikan.exe millikan.cpp ${LIBS} ${INCS}

clean: 
	rm millikan.exe

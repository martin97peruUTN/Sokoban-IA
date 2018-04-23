#Choix du compilateur.
CP = g++ -O2
SDL = `sdl-config --cflags --libs`
#choix des inclusions


sokoban:obj/JeuSokoban.o obj/IHMSokoban.o obj/main.o obj/SolutionSokoban.o obj/evaluateurSokoban.o  obj/CritereArretNombreIteration.o obj/dijsktra.o obj/SolutionSokobanPousse.o obj/evaluateurSokobanPousse.o
	$(CP) $(SDL) $^ -o $@ -lm

obj/main.o: src/main.cpp src/CroiseurMutateurSokoban.h src/SelecteurElitismeLoterie.h src/SolveurGenetique.h src/CroiseurMutateurSokobanListe.h
	$(CP) src/main.cpp -o $@ -c
obj/JeuSokoban.o: src/JeuSokoban.cpp
	$(CP) $^ -o $@ -c
obj/IHMSokoban.o: src/IHMSokoban.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/SolutionSokoban.o: src/SolutionSokoban.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/evaluateurSokoban.o: src/evaluateurSokoban.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/CritereArretNombreIteration.o: src/CritereArretNombreIteration.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/dijsktra.o: src/dijsktra.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/SolutionSokobanPousse.o: src/SolutionSokobanPousse.cpp
	$(CP) $(SDL) $^ -o $@ -c
obj/evaluateurSokobanPousse.o: src/evaluateurSokobanPousse.cpp
	$(CP) $(SDL) $^ -o $@ -c

clean:
	rm -vf obj/*
	rm -vf *~
	rm -vf src/*~
	rm -vf sokoban
 

Programme: src/TP2.o src/country.o	
		gcc src/TP2.o src/country.o -o bin/Programme -ljansson

main.o: src/TP2.c src/country.h
		gcc -c src/TP2.c -o src/TP2.o

country.o: src/country.c
		gcc -c src/country.c -o src/country.o

#supression des fichiers temporaires
clean:
		rm -rf src/*.o
		rm -rf test/*.o
#compilation fichiers de test

test: src/country.o src/test.o
		gcc src/country.o src/test.o -o test/Test -lcunit -ljansson	
		test/Test
		test/test.sh
		

src/test.o: src/test.c	
		gcc -c src/test.c -o src/test.o -lcunit -ljansson

	
#Supression de tous les fichiers, sauf les sources
#en vue d’une reconstruction complète
mrproper: clean
		rm -rf bin/Programme
		rm -rf test/Test
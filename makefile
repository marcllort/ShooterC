all: Shooter

main.o: main.c ./include/Utils.h
	gcc main.c -c -Wall -Wextra -g3

Utils.o: ./src/Utils.c ./include/Utils.h ./include/EXT2.h ./include/FAT16.h
	gcc ./src/Utils.c -c -Wall -Wextra -g3

EXT2.o: ./src/EXT2.c ./include/EXT2.h
	gcc ./src/EXT2.c -c -Wall -Wextra -g3

FAT16.o: ./src/FAT16.c ./include/FAT16.h
	gcc ./src/FAT16.c -c -Wall -Wextra -g3

Shooter: main.o Utils.o EXT2.o FAT16.o
	gcc main.o Utils.o EXT2.o FAT16.o -o shooter -Wall -Wextra -lm -g3

clean:
	rm *.o shooter

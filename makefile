all: Shooter

main.o: main.c ./include/MainUtils.h
	gcc main.c -c -Wall -Wextra -g3

MainUtils.o: ./src/MainUtils.c ./include/MainUtils.h ./include/EXT2.h ./include/FAT16.h
	gcc ./src/MainUtils.c -c -Wall -Wextra -g3

EXT2.o: ./src/EXT2.c ./include/EXT2.h ./include/Utils.h
	gcc ./src/EXT2.c -c -Wall -Wextra -g3

FAT16.o: ./src/FAT16.c ./include/FAT16.h ./include/Utils.h
	gcc ./src/FAT16.c -c -Wall -Wextra -g3

Utils.o: ./src/Utils.c ./include/Utils.h
	gcc ./src/Utils.c -c -Wall -Wextra -g3

Shooter: main.o MainUtils.o EXT2.o FAT16.o Utils.o
	gcc main.o MainUtils.o EXT2.o FAT16.o Utils.o -o shooter -Wall -Wextra -lm -g3

clean:
	rm *.o shooter

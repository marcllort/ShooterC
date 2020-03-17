all: Shooter

main.o: main.c Utils.h
	gcc main.c -c -Wall -Wextra -g3

Utils.o: Utils.c Utils.h EXT2.h
	gcc Utils.c -c -Wall -Wextra -g3

EXT2.o: EXT2.c EXT2.h
	gcc Ext4.c -c -Wall -Wextra -g3

FAT16.o: FAT16.c FAT16.h
	gcc FAT16.c -c -Wall -Wextra -g3

Shooter: main.o Utils.o EXT2.o FAT16.o
	gcc main.o Utils.o EXT2.o FAT16.o -o Shooter -Wall -Wextra -lm -g3

clean:
	rm *.o Shooter


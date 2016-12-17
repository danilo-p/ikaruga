OBJ_DIR=./
BIN_DIR=./

LIB_ALLEGRO=`pkg-config --cflags --libs allegro-5`
LIB_IMAGE=`pkg-config --cflags --libs allegro_image-5`
LIB_PRIMITIVES=`pkg-config --cflags --libs allegro_primitives-5`
LIB_TTF=`pkg-config --cflags --libs allegro_ttf-5`
LIB_MATH=-lm

all: ikaruga

ikaruga: ikaruga.o
	gcc -o $(BIN_DIR)ikaruga $(OBJ_DIR)ikaruga.o $(LIB_ALLEGRO) $(LIB_IMAGE) $(LIB_TTF) $(LIB_MATH)

ikaruga.o: ikaruga.c
	gcc -o $(OBJ_DIR)ikaruga.o -c ikaruga.c

clean:
	rm -f $(OBJ_DIR)*.o $(BIN_DIR)*

OBJ_DIR=obj/
BIN_DIR=bin/
HEADER_DIR=headers/

LIB_ALLEGRO=`pkg-config --cflags --libs allegro-5`
LIB_IMAGE=`pkg-config --cflags --libs allegro_image-5`
LIB_PRIMITIVES=`pkg-config --cflags --libs allegro_primitives-5`
LIB_TTF=`pkg-config --cflags --libs allegro_ttf-5`
LIB_MATH=-lm

all: ikaruga

ikaruga: ikaruga.o
	gcc -o $(BIN_DIR)ikaruga $(HEADER_DIR)config.c $(HEADER_DIR)common.c $(HEADER_DIR)element.c $(HEADER_DIR)ship.c $(HEADER_DIR)bullet.c $(HEADER_DIR)game.c $(OBJ_DIR)ikaruga.o $(LIB_ALLEGRO) $(LIB_PRIMITIVES) $(LIB_IMAGE) $(LIB_TTF) $(LIB_MATH)

ikaruga.o: ikaruga.c
	gcc -o $(OBJ_DIR)ikaruga.o -c ikaruga.c

clean:
	rm -f $(OBJ_DIR)*.o $(BIN_DIR)*

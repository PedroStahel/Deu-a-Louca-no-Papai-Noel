CC = gcc

# Flags de compilação.
CFLAGS = -Wall -Wextra -std=c11 \
	$(shell pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

# Bibliotecas do Allegro para a linkagem.
LIBS = \
	$(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

# Arquivos objeto que compõem o executável.
OBJ = main.o jogo.o personagem.o mapa.o interface.o

# Linka todos os objetos e gera o executável.
jogo: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# Compila cada .c.
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Remove os arquivos gerados pela compilação.
clean:
	rm -f *.o jogo

.PHONY: clean

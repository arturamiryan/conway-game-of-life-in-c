CC = gcc
CFLAGS = -Wall -pedantic -Wextra

EXEFILE = game_of_life
SOURCES = source/main.c
BUILDDIR = build

$(EXEFILE) : $(SOURCES)
	mkdir -p build;
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILDDIR)/$(EXEFILE)

run : $(EXEFILE)
	./$(BUILDDIR)/$(EXEFILE)

clean :
	rm -rf $(BUILDDIR)/*
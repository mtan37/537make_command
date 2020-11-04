#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -Wextra -pedantic -g -pthread
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/537make.o $(ODIR)/util.o $(ODIR)/parser.o $(ODIR)/graphBuilder.o $(ODIR)/structs.o 
HEADERS = $(SDIR)/util.h $(SDIR)/parser.h
537make:$(OBJECTS)
	$(CC) -Wall -pthread -Wextra $(OBJECTS) -o 537make
$(ODIR)/537make.o: $(SDIR)/537make.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/parser.o: $(SDIR)/parser.c $(SDIR)/parser.h $(SDIR)/graphBuilder.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/graphBuilder.o: $(SDIR)/graphBuilder.c $(SDIR)/graphBuilder.h $(SDIR)/structs.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/structs.o: $(SDIR)/structs.c $(SDIR)/structs.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/util.o: $(SDIR)/util.c $(SDIR)/util.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR):
	mkdir -p $(ODIR)
clean:
	rm $(ODIR)/*.o
	rm -r $(ODIR)
	rm 537make

#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -Wextra -pedantic -g -pthread
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/537make.o $(ODIR)/util.o $(ODIR)/parser.o $(ODIR)/validator.o 
HEADERS = $(SDIR)/util.h $(SDIR)/parser.h $(SDIR)/validator.h
537make:$(OBJECTS)
	$(CC) -Wall -pthread -Wextra $(OBJECTS) -o 537make
$(ODIR)/537make.o: $(SDIR)/537make.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/parser.o: $(SDIR)/parser.c $(SDIR)/parser.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/validator.o: $(SDIR)/validator.c $(SDIR)/validator.h $(SDIR)/parser.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/util.o: $(SDIR)/util.c $(SDIR)/util.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR):
	mkdir -p $(ODIR)
clean:
	rm $(ODIR)/*.o
	rm -r $(ODIR)
	rm 537make

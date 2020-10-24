#make file for assignment1 @CS537
CC = gcc
CFLAGS = -c -Wall -Wextra -pedantic -g -pthread
ODIR = ./obj
SDIR = ./src
OBJECTS = $(ODIR)/util.o 
HEADERS = $(SDIR)/util.h 
537make:$(OBJECTS)
	$(CC) -Wall -pthread -Wextra $(OBJECTS) -o run
$(ODIR)/537make.o: $(SDIR)/537make.c $(HEADERS) | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/executor.o: $(SDIR)/executor.c $(SDIR)/executor.h $(SDIR)/util.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/parser.o: $(SDIR)/parser.c $(SDIR)/parser.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/validator.o: $(SDIR)/validator.c $(SDIR)/validator.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR)/util.o: $(SDIR)/util.c $(SDIR)/util.h | $(ODIR)
	$(CC) $(CFLAGS) $< -o $@
$(ODIR):
	mkdir -p $(ODIR)
clean:
	rm $(ODIR)/*.o
	rm -r $(ODIR)
	rm 537make

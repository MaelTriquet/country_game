CC = gcc -Wall -g -Wextra -ggdb #necessary flags
PROG = exe	#name of executable
PROG_org = exe_org #name different than executable for organisation
SRC_org = $(wildcard *.c) #source files for organisation 
SRC = $(wildcard $(srcdir)*.c)#source files
HEAD_org = $(wildcard *.h) #head files
HEAD = $(wildcard $(srcdir)*.h) #head files
OBJ = $(subst $(srcdir), $(bindir), $(SRC:.c=.o)) #object files      
OBJ_org = $(subst $(srcdir), $(bindir), $(SRC_org:.c=.o))#object files for organisation                                                                                                                                                                     
srcdir = src/
bindir = bin/
docdir = doc/
savedir = save/

all:
#remove the existing executable, create the new one and move it in the right place
	rm -rf $(PROG)
	make $(PROG)
	mv $(PROG) $(bindir)

$(PROG) : $(OBJ) #compile the code
		$(CC) $^ -lm -o $@

./$(bindir)%.o : ./$(srcdir)%.c  #compile the objects                                                                                                                                                                          
		$(CC) -c $^ -o $@

.PHONY : precompile #only ran when organizing
precompile:$(PROG_org)
	mv $(PROG) $(bindir)

$(PROG_org) : $(OBJ_org) #compile the code for organisation
		$(CC) $^ -lm -o $(PROG)

.PHONY : clean
clean : #clean the objects and the executable
	rm -rf $(OBJ)
	rm -rf $(PROG)

.PHONY : createSave
createSave : #create the save directory
	mkdir -p $(savedir)

.PHONY : save
save: #saves the minimal information necessary
	rm -rf $(savedir)
	mkdir -p $(savedir)
	cp *$(SRC) $(savedir)
	cp *$(HEAD) $(savedir)

.PHONY : restore
restore: #saves the minimal information necessary
	rm -rf $(srcdir)
	mkdir -p $(srcdir)
	cp $(wildcard $(savedir)*.c) $(wildcard $(savedir)*.h) $(srcdir)


.PHONY : createFiles
createFiles : #create the necessary directories
	mkdir -p $(srcdir)
	mkdir -p $(bindir)
	mkdir -p $(docdir)
	mkdir -p $(savedir)

.PHONY : organise_h
organise: createFiles #organises all the files in the directories they are meant to be
	make clean
	make precompile
	make doxy
	cp *$(SRC_org) *$(HEAD_org) $(savedir)
	cp *$(SRC_org) *$(HEAD_org) $(srcdir)
	cp *.o $(bindir)
	cp DoxyFile $(docdir)
	cp -r html $(docdir)
	cp -r latex $(docdir)
	rm $(SRC_org)
	rm $(HEAD_org)
	rm $(OBJ_org)
	rm DoxyFile
	rm -r html
	rm -r latex

.PHONY : organise
organise: createFiles #organises all the files in the directories they are meant to be
	make clean
	make precompile
	make doxy
	cp *$(SRC_org) $(savedir)
	cp *$(SRC_org) $(srcdir)
	cp *.o $(bindir)
	cp DoxyFile $(docdir)
	cp -r html $(docdir)
	cp -r latex $(docdir)
	rm $(SRC_org)
	rm $(OBJ_org)
	rm DoxyFile
	rm -r html
	rm -r latex


doxy:  #documentation doxygen
		doxygen -g DoxyFile && doxygen DoxyFile

help: #make help prints out the commands
    @echo 'General targets: '
	@echo ' help      - display this help'
	@echo ' organize  - puts all the files in directories'
	@echo 'Building targets: '
	@echo ' all       - build the project'
	@echo ' doxy      - build documentation'
	@echo 'Cleaning targets: '
	@echo ' clean     - save all the .c and .h files and remove anything that can be generated'

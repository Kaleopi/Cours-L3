#
# CONFIGURATION GENERALE
#

EXEC = voiture controleur
OBJETS = ncurses.o
NOM_PROJET = Projet 2 GIGOUT DAUNIQUE

#
# SUFFIXES
#

.SUFFIXES: .c .o

#
# OBJETS
#

EXEC_O = $(EXEC:=.o)
OBJETS_O = $(OBJETS) $(EXEC_O)

#
# ARGUMENTS ET COMPILATEUR
#

CLE_MSG = 1056
CLE_SHM = 2056
CLE_SEM = 3056
CC = gcc
CCFLAGS = -Wall -O3 -Werror -ansi -pedantic -D _XOPEN_SOURCE -D CLE_MSG=$(CLE_MSG) -D CLE_SEM=$(CLE_SEM) -D CLE_SHM=$(CLE_SHM)
CCLIBS =  -lncurses

#
# REGLES
#

all: $(OBJETS) $(EXEC_O)
	@echo "Création des exécutables..."
	@for i in $(EXEC); do \
	$(CC) -o $$i $$i.o $(OBJETS) $(CCLIBS); \
	done
	@echo "Terminé."

#
# REGLES PAR DEFAUT
#

.c.o: .h
	@cd $(dir $<) && ${CC} ${CCFLAGS} -c $(notdir $<) -o $(notdir $@)

#
# REGLES GENERALES
#

clean:
	@echo "Suppresion des objets, des fichiers temporaires..."
	@rm -f $(OBJETS) $(EXEC_O)
	@rm -f *~ *#
	@rm -f $(EXEC)
	@rm -f dependances
	@echo "Terminé."

cleanIPC:
	@echo "Suppression de la file de messages..."
	@ipcrm -Q $(CLE_MSG) -M $(CLE_SHM) -S $(CLE_SEM)
	@echo "File supprimée."

depend:
	@echo "Création des dépendances..."
	@sed -e "/^# DEPENDANCES/,$$ d" makefile > dependances
	@echo "# DEPENDANCES" >> dependances
	@for i in $(OBJETS_O); do \
	$(CC) -MM -MT $$i $(CCFLAGS) `echo $$i | sed "s/\(.*\)\\.o$$/\1.c/"` >> dependances; \
	done
	@cat dependances > makefile
	@rm dependances
	@echo "Terminé."

#
# CREATION ARCHIVE
#

ARCHIVE_FILES = *

archive: clean
	@echo "Création de l'archive $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename $$PWD`; cd .. && tar zcf $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz') $(addprefix $$REP/,$(ARCHIVE_FILES))
	@echo "Termine."

# DEPENDANCES
ncurses.o: ncurses.c ncurses.h
fonctionsVoiture.o: fonctionsVoiture.c fonctionsVoiture.h
fonctionsControleur.o: fonctionsControleur.c fonctionsControleur.h
controleur.o: controleur.c ncurses.h fonctionsControleur.h
voiture.o: voiture.c fonctionsVoiture.h

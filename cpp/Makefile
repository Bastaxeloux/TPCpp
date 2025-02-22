# Nom du programme
PROG = Lecteur-multimedia
LIBLECTEUR = liblecteur.a

# Répertoires
SRCDIR = src
INCLUDEDIR = include
OBJDIR = obj

# Fichiers sources et objets
MAIN_SOURCES = src/main.cpp src/Database.cpp src/Multimedia.cpp src/Film.cpp src/Group.cpp
MAIN_OBJECTS = $(MAIN_SOURCES:src/%.cpp=obj/%.o)

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I$(INCLUDEDIR) -pthread # -pthread pour les sockets

# Règles
all: $(PROG) $(LIBLECTEUR)

# Création d'une librairie statique pour la lier au Makefile cliserv
$(LIBLECTEUR): $(MAIN_OBJECTS)
	ar rcs $(LIBLECTEUR) $(MAIN_OBJECTS)

# l'executable
$(PROG): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(PROG)

run: all
	./Lecteur-multimedia


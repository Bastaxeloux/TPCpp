# Nom du programme
PROG = Lecteur-multimedia

# Répertoires
SRCDIR = src
INCLUDEDIR = include
OBJDIR = obj

# Fichiers sources et objets
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJETS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -I$(INCLUDEDIR)

# Règles
all: $(PROG)

$(PROG): $(OBJETS)
	$(CXX) $(CXXFLAGS) $(OBJETS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@



clean:
	rm -rf $(OBJDIR) $(PROG)

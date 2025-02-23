# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude -pthread

# Répertoires
SRCDIR = .
INCLUDEDIR = include
OBJDIR = obj
BINDIR = bin

# Fichiers source et objets
SERVER_SOURCES = server.cpp tcpserver.cpp Database.cpp Film.cpp Group.cpp Multimedia.cpp ccsocket.cpp
CLIENT_SOURCES = client.cpp ccsocket.cpp

SERVER_OBJECTS = $(SERVER_SOURCES:%.cpp=$(OBJDIR)/%.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:%.cpp=$(OBJDIR)/%.o)

# Cibles
all: server client

# Compilation du serveur
server: $(SERVER_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJECTS) -o $(BINDIR)/server

# Compilation du client
client: $(CLIENT_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o $(BINDIR)/client

# Compilation des fichiers .cpp en .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Exécuter le serveur et le client
run: all
	@osascript -e 'tell application "Terminal" to do script "cd $(shell pwd) && $(BINDIR)/server"' 
	@sleep 2
	@osascript -e 'tell application "Terminal" to do script "cd $(shell pwd) && $(BINDIR)/client"'

# Nettoyage des fichiers compilés
clean:
	rm -rf $(OBJDIR) $(BINDIR)

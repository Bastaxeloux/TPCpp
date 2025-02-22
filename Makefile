# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Icpp/include -pthread

JC = javac
JFLAGS = -g

# Directories
CPPSRC = cpp/src
CPPINCLUDE = cpp/include
CPPOBJ = cpp/obj
CPPBIN = cpp/bin
JAVASRC = java/src

# C++ sources
SERVER_SOURCES = $(CPPSRC)/server.cpp $(CPPSRC)/tcpserver.cpp $(CPPSRC)/Database.cpp $(CPPSRC)/Film.cpp $(CPPSRC)/Group.cpp $(CPPSRC)/Multimedia.cpp $(CPPSRC)/ccsocket.cpp
CLIENT_SOURCES = $(CPPSRC)/client.cpp $(CPPSRC)/ccsocket.cpp

SERVER_OBJECTS = $(SERVER_SOURCES:$(CPPSRC)/%.cpp=$(CPPOBJ)/%.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:$(CPPSRC)/%.cpp=$(CPPOBJ)/%.o)

# Java sources
JAVA_SOURCES = $(wildcard $(JAVASRC)/*.java)
JAVA_CLASSES = $(JAVA_SOURCES:$(JAVASRC)/%.java=$(JAVASRC)/%.class)

# Targets
all: server client java

# Compile C++ server
server: $(SERVER_OBJECTS)
	@mkdir -p $(CPPBIN)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJECTS) -o $(CPPBIN)/server

# Compile C++ client
client: $(CLIENT_OBJECTS)
	@mkdir -p $(CPPBIN)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o $(CPPBIN)/client

# Compile Java client GUI
java: $(JAVA_CLASSES)

# Rule for compiling C++ objects
$(CPPOBJ)/%.o: $(CPPSRC)/%.cpp
	@mkdir -p $(CPPOBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling Java classes
$(JAVASRC)/%.class: $(JAVASRC)/%.java
	$(JC) $(JFLAGS) -cp java/src -d java/src $<

# Run everything
run: all
	@osascript -e 'tell application "Terminal" to do script "cd $(shell pwd) && $(CPPBIN)/server"' 
	@sleep 2
	@osascript -e 'tell application "Terminal" to do script "cd $(shell pwd)/java/src && java -cp . MainWindow"'

# Clean all
clean:
	rm -rf $(CPPOBJ) $(CPPBIN) $(JAVASRC)/*.class

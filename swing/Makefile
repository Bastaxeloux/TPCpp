# Compiler settings
JC = javac
JFLAGS = -g

# Répertoires
SRCDIR = .
BINDIR = bin

# Fichiers source et classes
JAVA_SOURCES = $(wildcard $(SRCDIR)/*.java)
JAVA_CLASSES = $(JAVA_SOURCES:$(SRCDIR)/%.java=$(BINDIR)/%.class)

# Compilation des fichiers Java
all: $(JAVA_CLASSES)

# Compilation d’un fichier Java
$(BINDIR)/%.class: $(SRCDIR)/%.java
	@mkdir -p $(BINDIR)
	$(JC) $(JFLAGS) -d $(BINDIR) $<

# Exécution de l'application
run: all
	@osascript -e 'tell application "Terminal" to do script "cd $(shell pwd)/$(BINDIR) && java MainWindow"'

# Nettoyage des fichiers compilés
clean:
	rm -rf $(BINDIR)

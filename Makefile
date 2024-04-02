# Definizione del compilatore
CC=g++

# Nome del file eseguibile
TARGET=main.exe

# File sorgente
SRCS=main.cpp

# File oggetto
OBJS=$(SRCS:.cpp=.o)

# Regola per creare l'eseguibile
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Regola per generare file oggetto da file sorgente
%.o: %.cpp
	$(CC) -c $(SRCS) -o $(OBJS)


.PHONY: clean

# Regola 'clean' per rimuovere i file generati
clean:
	rm -rf *.o *.exe


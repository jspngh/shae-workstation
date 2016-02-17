OBJS = tinyxml2.o XMLSerialization.o persistence.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
TARGET = xmltest

TARGET : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

persistence.o : persistence.cpp ./serialization/XMLSerialization.h ./serialization/tinyxml2.h
	$(CC) $(CFLAGS) persistence.cpp

tinyxml2.o : serialization/tinyxml2.h serialization/tinyxml2.cpp
	$(CC) $(CFLAGS) serialization/tinyxml2.cpp

XMLSerialization.o : serialization/tinyxml2.h serialization/XMLSerialization.cpp serialization/XMLSerialization.h
	$(CC) $(CFLAGS) serialization/XMLSerialization.cpp

clean:
	rm -f *.o $(TARGET)

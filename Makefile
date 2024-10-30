
all: compile link run clean

SFML_INCLUDE = C:/SFML-2.6.1/include
SFML_LIB = C:/SFML-2.6.1/lib

compile:
	g++ -c *.cpp gui/*.cpp -std=c++17 -g -Wall -m64 -I $(SFML_INCLUDE) -DSFML_STATIC 

link:
	g++ *.o -o main -L $(SFML_LIB) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 

clean:
	del *.o *.exe
	
run:
	./main
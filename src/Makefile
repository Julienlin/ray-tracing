##
# ray-tracing
#
# @file
# @version 0.1

CXX = clang++
CXXFLAGS = --std=c++11 -Wall -fdiagnostics-color=always
EXEC = rayTracing
SOURCES = types.o ray.o  light_source.o screen.o scene_sphere.o ray_engine.o main.o

%.o : %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^

rayTracing : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm -f $(SOURCES)
	rm -f $(EXEC)
# end

##
# ray-tracing
#
# @file
# @version 0.1

SRCDIR= src
BUILDDIR= build
TARGET = bin/rayTracing
SRCEXT = cpp

CXX = g++
CXXFLAGS = --std=c++11 -g -Wall -fdiagnostics-color=always
INC=-I include
SOURCES= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
EXEC = rayTracing
LIB=
MKDIR_P = mkdir -p
# SOURCES = types.o ray.o  light_source.o screen.o scene_base_object.o scene_sphere.o ray_engine.o

# %.o : %.c
# 	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $^

# clean :
# 	rm -f $(SOURCES)
# 	rm -f $(EXEC)


$(TARGET): $(OBJECTS) test/rayTracing.cpp
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	# @echo "$(SOURCES)"
  	#  mkdir -p $(BUILDDIR)
	$(shell mkdir -p $(BUILDDIR))
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

rayTracing : $(BUILDDIR)/%.o test/rayTracing.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^

clean:
	rm -rf $(BUILDDIR) $(TARGET)

# end

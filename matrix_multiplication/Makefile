# Compiler settings
CXX = g++

# ---------------------------------------------------------
# Optimization Flags (-O0 vs -O1/-O2 vs -O3)
# ---------------------------------------------------------
# -O0 : Disables all compiler optimizations. The compiler translates your C++ 
#       code into machine code exactly as written. This proves that manual 
#       SIMD logic is inherently faster than raw scalar loops.
#
# -O1 / -O2 : Intermediate optimization levels. They provide solid speed 
#             improvements without drastically increasing compile time or 
#             heavily altering the underlying code structure.
#
# -O3 : The highest and best level of optimization for raw performance. The 
#       compiler analyzes your code and aggressively rewrites it at the 
#       assembly level. It will auto-vectorize standard loops (injecting 
#       its own SIMD), unroll loops to process chunks of 16 or 32 floats 
#       at once, and replace index math with raw pointer increments.
# ---------------------------------------------------------
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra

# File names
TARGET = test_mult
SRC = test_mult.cpp matrix_mult.cpp
OBJ = test_mult.o matrix_mult.o

# Default rule to build the executable
all: $(TARGET)

# STEP 2: Link the object files into the final executable, then delete the .o files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

# STEP 1: Compile each .cpp file into a .o object file
# The -c flag tells the compiler to stop before linking.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the final compiled executable
clean:
	rm -f $(TARGET)
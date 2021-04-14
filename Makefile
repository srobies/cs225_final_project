EXE = main
TEST = test

EXE_OBJ = main.o
OBJS = main.o AirportsData.o Graph.o
OBJS += $(CPP_FILES:.cpp=.o)

include cs225/make/cs225.mk

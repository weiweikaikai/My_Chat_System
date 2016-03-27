ROOT_PATH=$(shell pwd)

CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
CONF=$(ROOT_PATH)/conf
DATA_POOL=$(ROOT_PATH)/data_pool
LIB=$(ROOT_PATH)/lib
LOG=$(ROOT_PATH)/log
PLUGIN=$(ROOT_PATH)/plugin
SERVER=$(ROOT_PATH)/service
WINDOW=$(ROOT_PATH)/window

CC=g++
FLAGS=-Wno-deprecated -g #-D_JSON_STYLE_ #-D_DEBUG
LDFLAGS=#-static
INCLUDE=-I$(CLIENT) -I$(COMM) -I$(DATA_POOL) -I$(LOG) -I$(SERVER) -I$(WINDOW) -I/usr/include 
LIB_PATH=-L/usr/lib
LINK_LIB=-lpthread -ljson_linux-gcc-4.4.7_libmt -lncurses

SER_BIN=udp_server
CLI_BIN=udp_client

all:$(SER_BIN) $(CLI_BIN)
.PHONY:all
SRC=$(shell ls -R | grep -E '.cpp' | grep -v 'libjsoncpp.a')
OBJ=$(SRC:.cpp=.o)
SER_OBJ=$(shell echo $(OBJ) | sed 's/client.o\|client_main.o\|window.o//g')
CLI_OBJ=$(shell echo $(OBJ) | sed 's/data_pool.o\|service.o\|service_main.o//g')
	
$(SER_BIN):$(SER_OBJ) 
	@echo "Linking [ $^ ] to [ $@ ] ... done"
	@$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS) $(LINK_LIB)
$(CLI_BIN):$(CLI_OBJ)
	@echo "Linking [ $^ ] to [ $@ ] ... done"
	@$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS) $(LINK_LIB)
%.o:$(CLIENT)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
%.o:$(COMM)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
%.o:$(DATA_POOL)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#%.o:$(LOG)/%.cpp
#	@echo "Compiling [ $< ] to [ $@ ] ... done"
#	@$(CC) -c $< $(INCLUDE) $(FLAGS)
%.o:$(SERVER)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(INCLUDE) $(FLAGS) 
%.o:$(WINDOW)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)

.PHONY:clean
clean:
	@echo "clean project ... done"
	rm -rf *.o ${SER_BIN} ${CLI_BIN} output 

.PHONY:output
output:
	mkdir -p output/server/log
	mkdir -p output/server/bin
	mkdir -p output/client/log
	mkdir -p output/client/bin
	cp -rf udp_server output/server/bin
#	cp -rf plugin/server_ctrl.sh output/server
	cp -rf udp_client  output/client/bin
#	cp -rf conf        output/server
#	cp -rf conf        output/client
#	cp -rf plugin/run_client.sh output/client
#	rm -f  output/client/conf/server.conf
#	rm -f  output/server/conf/client.conf



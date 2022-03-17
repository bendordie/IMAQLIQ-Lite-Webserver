
SERVER_EXE = server

CLIENT_EXE = client

SRC_SERVER =	server_main.cpp \
				WebServer.cpp \
				WebSession.cpp \
				FdHandler.cpp \
				EventSelector.cpp \
				global_variables.cpp

OBJ_SERVER = $(SRC_SERVER:.cpp=.o)

SRC_CLIENT = client_main.cpp \
			 Client.cpp

OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)

CXX = clang++ --no-warnings

#CXXFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(SERVER_EXE) $(CLIENT_EXE) clean

$(SERVER_EXE): $(SRC_SERVER) *.hpp $(OBJ_SERVER)
	$(CXX) $(OBJ_SERVER) -o $(SERVER_EXE)

$(CLIENT_EXE): $(SRC_CLIENT) *.hpp $(OBJ_CLIENT)
	$(CXX) $(OBJ_CLIENT) -o $(CLIENT_EXE)

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(SERVER_EXE) $(CLIENT_EXE)

re: fclean all

.PHONY: all clean fclean re

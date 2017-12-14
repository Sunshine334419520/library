# @Author: YangGuang
# @Date:   2017-12-14T17:42:42+08:00
# @Email:  guang334419520@126.com
# @Filename: Makefile
# @Last modified by:   YangGuang
# @Last modified time: 2017-12-14T19:15:56+08:00


RESULT = main
OBJ = Main.o login.o MysqlInterface.o
CC = g++
FLAGS = -Wall -g -std=c++11
INCLUDE = /usr/local/Cellar/mysql/5.7.20/include/mysql/
LIB = /usr/local/Cellar/mysql/5.7.20/lib/

$(RESULT): $(OBJ)
	$(CC) $(FLAGS) -o $(RESULT) $(OBJ) -I$(INCLUDE) -L$(LIB) -lmysqlclient

Main.o:Main.cc
	$(CC) $(FLAGS) -c $<


login.o:login.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

MysqlInterface.o:mysqlinterface/MysqlInterface.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)


.PHONY: clean cleanall
clean:
	rm -rf $(OBJ)
cleanall:
	rm -rf $(OBJ) $(RESULT)

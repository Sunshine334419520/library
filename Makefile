# @Author: YangGuang
# @Date:   2017-12-14T17:42:42+08:00
# @Email:  guang334419520@126.com
# @Filename: Makefile
# @Last modified by:   sunshine
# @Last modified time: 2017-12-23T22:39:01+08:00


RESULT = main
OBJ = Main.o login.o  StudentUser.o AdministerPerson.o MysqlInterface.o Book.o hash.o
CC = g++
FLAGS = -Wall -g -std=c++11 -Iinclude/ -Imysqlinterface/
INCLUDE = /usr/local/Cellar/mysql/5.7.20/include/mysql/
LIB = /usr/local/Cellar/mysql/5.7.20/lib/

$(RESULT): $(OBJ)
	$(CC) $(FLAGS) -o $(RESULT) $(OBJ) -L$(LIB) -lmysqlclient

Main.o:lib/Main.cc
	$(CC) $(FLAGS) -c $<


login.o:lib/login.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

MysqlInterface.o:mysqlinterface/MysqlInterface.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

Book.o: lib/Book.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

AdministerPerson.o: lib/AdministerPerson.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

StudentUser.o: lib/StudentUser.cc
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

hash.o: lib/hash.cc
	$(CC) $(FLAGS) -c $<


.PHONY: clean cleanall
clean:
	rm -rf $(OBJ)
cleanall:
	rm -rf $(OBJ) $(RESULT)

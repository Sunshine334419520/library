/**
 * @Author: YangGuang
 * @Date:   2017-12-14T14:07:27+08:00
 * @Email:  guang334419520@126.com
 * @Filename: login.cc
 * @Last modified by:   YangGuang
 * @Last modified time: 2017-12-14T19:29:49+08:00
 */



#include <iostream>
#include <string>
#include <vector>
#include "mysqlinterface/MysqlInterface.hpp"
#include "login.hpp"


using namespace std;

/**
 * 判断账号是否正确,管理员账号以字母开头，用户账户是学号
 * @param  username [description]
 * @param  password [description]
 * @return          [description]
 */
bool LoginLibrarySystem(const std::string& username,
                        const std::string& password) {

   MysqlInterface mysql;

   if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
     mysql.PrintErrorInfo();
     return false;
   }


   std::string sql;
   if(username[0] > '1' && username[0] <'9') {
      sql = "select * from users where number=" + username + " and " "password=" + password; 
   }

   std::vector<std::vector<std::string> > result;
   if(!mysql.ReadData(sql, result)){
     mysql.PrintErrorInfo();
     return false;
   }

   if(result.empty()) {
     return false;
   }

   return true;

}

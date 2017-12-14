/**
 * @Author: YangGuang
 * @Date:   2017-12-14T14:53:29+08:00
 * @Email:  guang334419520@126.com
 * @Filename: MysqlInterface.hpp
 * @Last modified by:   YangGuang
 * @Last modified time: 2017-12-14T19:01:57+08:00
 */


#ifndef MYSQL_MYSQLINTERFACE_H
#define MYSQL_MYSQLINTERFACE_H

#include <mysql.h>
#include <iostream>
#include <string>
#include <vector>


class MysqlInterface {
public:
  /*  构造器 */
  MysqlInterface();
  /* destructor */
  ~MysqlInterface() { CloseDatabase(); }

  /*  数据库连接函数 */
  bool ConnectDatabase(const char* sever, const char* user,
       const char* pass, const char* database, int port = 3306);

  /* 数据库创建  */
  bool CreateDatabase(std::string& data_name);

  /* 创建表  */
  bool CreateTable(const std::string& table_name);



  /* 错误信息打印 */
  void PrintErrorInfo() const;

  /* 关闭数据库连接 */
  void CloseDatabase();

  /* 写入数据 */
  bool WriteData(const std::string& query);

  /* 读取数据 */
  bool ReadData(const std::string& query,
       std::vector< std::vector<std::string> >& result);

  /* 删除数据 */
  bool DeleteData(const std::string& query);

  /* 修改数据 */
  bool ModifyData(const std::string& query);

private:
  /*  错误信息设置  */
  void ErrorMysqlInfo();

private:
  MYSQL mysqlinterface_;  // MYSQL对象
  MYSQL_RES* result_;      //用于存放结果

  int errno_num_;           //错误代号
  const char* error_info_;  //错误信息
};


#endif

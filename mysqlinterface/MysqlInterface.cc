/**
 * @Author: YangGuang
 * @Date:   2017-12-14T15:26:36+08:00
 * @Email:  guang334419520@126.com
 * @Filename: MysqlInterface.cc
 * @Last modified by:   YangGuang
 * @Last modified time: 2017-12-14T19:02:00+08:00
 */


#include "MysqlInterface.hpp"
#include <iostream>
using namespace std;

MysqlInterface::MysqlInterface():
  errno_num_(0),error_info_("ok")
{
    mysql_library_init(0, NULL, NULL);
    mysql_init(&mysqlinterface_);
    mysql_options(&mysqlinterface_,MYSQL_SET_CHARSET_NAME,"gbk");
}


bool MysqlInterface::ConnectDatabase(const char *sever, const char *user,
     const char *pass, const char *database, int port)
{
  if(mysql_real_connect(&mysqlinterface_, sever,
     user, pass, database, port, 0, 0) != NULL) {
       return true;
  } else {
    ErrorMysqlInfo();
  }

  return false;
}



bool MysqlInterface::CreateDatabase(std::string &data_name)
{
  std::string query_str = "create database if not exists";
  query_str += data_name;

  if(mysql_query(&mysqlinterface_, query_str.c_str()) == 0) {
    query_str = "use";
    query_str += data_name;

    if(mysql_query(&mysqlinterface_, query_str.c_str()) == 0) {
      return true;
    }
  }

  ErrorMysqlInfo();
  return false;
}


bool MysqlInterface::WriteData(const std::string &query)
{
  if(mysql_query(&mysqlinterface_, query.c_str()) != 0) {
    ErrorMysqlInfo();
    return false;
  }

  return true;
}


bool MysqlInterface::ReadData(const std::string &query,
     std::vector<std::vector<std::string> >& result)
{
  if(mysql_query(&mysqlinterface_, query.c_str()) != 0) {
    ErrorMysqlInfo();
    return false;
  }

  /* 保存结果集 */
  result_ = mysql_store_result(&mysqlinterface_);

  /* 获得列数 */
  int field = mysql_num_fields(result_);

  MYSQL_ROW line = NULL;

  /* 将结果保存到 result ,result 是一个vector<vector<string>> */
  while ( (line = mysql_fetch_row(result_)) != NULL) {
    std::vector<std::string> line_data;
    std::string tmp;

    for(int i = 0; i < field; i++) {
      if(line[i])
        tmp = line[i];
      else
        tmp = "";

      line_data.push_back(tmp);
    }

    result.push_back(line_data);
  }

  return true;

}


bool MysqlInterface::DeleteData(const std::string &query)
{
  if(mysql_query(&mysqlinterface_, query.c_str()) != 0) {
    ErrorMysqlInfo();
    return false;
  }

  return true;
}


bool MysqlInterface::ModifyData(const std::string &query)
{
  if(mysql_query(&mysqlinterface_, query.c_str()) != 0) {
    ErrorMysqlInfo();
    return false;
  }
  return true;
}

void MysqlInterface::ErrorMysqlInfo()
{
  errno_num_ = mysql_errno(&mysqlinterface_);
  error_info_ = mysql_error(&mysqlinterface_);
}

void MysqlInterface::PrintErrorInfo() const
{
  std::cout << "Error " << errno_num_ << error_info_ << '\n';

}

void MysqlInterface::CloseDatabase() 
{
  mysql_close(&mysqlinterface_);
}

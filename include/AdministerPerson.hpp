/**
 * this is the super user class
 * @Author: sunshine
 * @Date:   2017-12-15T22:10:44+08:00
 * @Email:  guang334419520@126.com
 * @Filename: AdministerPerson.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T17:52:03+08:00
 */

#ifndef LIBRARY_ADMINISTERPERSON_H
#define LIBRARY_ADMINISTERPERSON_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "Book.hpp"


class Book;
class MysqlInterface;

namespace admin {

  class AdministerPerson {
  public:
    AdministerPerson();
    ~AdministerPerson();

    void ShowBooks() const;
    void ShowPersonInfo() const;
    void ShowBrrowReturnInfo() const;
    bool SetPersonInfo(const std::string&);
    bool SetPassword(const std::string&);

    bool AddBook(const Book&);
    bool ModifyBook(const Book&);
    bool RemoveBook(const std::string&);
    bool SearchBook(const Book::name_type&, Book*) const;

  private:
    std::string alias_;

    MysqlInterface* mysql_;
    std::list<Book>* Books_;
  };

bool ReadAllBook(std::list<Book>* books);


//模板函数：将string类型变量转换为常用的数值类型
template <class Type>
Type StringToNumber(const string& str){
   istringstream iss(str);
   Type num;
   iss >> num;
   return num;
}
}


#endif

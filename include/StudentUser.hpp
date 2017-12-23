/**
* @Author: sunshine
* @Date:   2017-12-15T22:21:45+08:00
* @Email:  guang334419520@126.com
* @Filename: StudentUser.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T17:59:32+08:00
*/


#ifndef LIBRARY_STUDENTUSER_H
#define LIBRARY_STUDENTUSER_H

#include <iostream>
#include <vector>
#include <string>
#include "Book.hpp"

class Book;

namespace user {

  class StudentUser {
  public:

    StudentUser();
    /*  显示图书  */
    void ShowBooks() const;

    /*  搜索图书  */
    bool SearchBook(const Book::name_type&, Book*) const;
    bool SearchBook(const Book::author_type&, std::vector<Book>&) const;
    const std::vector<Book>* SearchBook(const Book::class_type&) const;


    /*  获得个人信息  */
    void GetPersonInfo() const;

    /*  设置个人信息  */
    void SetPersonInfo(const std::string&, const std::string&,
                       const std::string&, const std::string&);

    /*  设置密码  */
    bool SetPassword(const std::string&);


    /* 还书 */
    bool ReturnBook(const std::string& number);

    /*  借书  */
    bool BorrowingBook(const Book::name_type& number);


  private:
    std::string name_;
    std::string number_;
    std::string department_;
    std::string alias_;

    std::vector<Book>* Books_;


  };


  /*  查看帮助信息  */
  void GetHelpInfo();
  bool ReadAllBook(std::vector<Book>* books);
}

#endif

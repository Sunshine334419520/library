/**
 * @Author: sunshine
 * @Date:   2017-12-16T17:55:30+08:00
 * @Email:  guang334419520@126.com
 * @Filename: Book.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T23:05:44+08:00
 */


#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <iostream>
using namespace std;


class Book {
public:
using date_type = std::string;
using class_type = std::string;
using name_type = std::string;
using author_type = std::string;
using size_type = unsigned int;

public:
  Book(name_type name, author_type author, std::string creators,
       size_type money, date_type publication_data,
       class_type major, std::string number, size_type pages):
        name_(name), author_(author), creators_(creators),
        price_(money), publication_data_(publication_data),
        major_(major), number_(number), size_(pages) {}


  const name_type& GetBookName() const;
  const author_type& GetBookAuthor() const;
  const class_type& GetBookClass() const;
  std::string GetBookCreators() const;
  const date_type& GetBookData() const;
  size_type GetBookPrice() const;
  size_type GetBookSize() const;
  const std::string& GetBookNumber() const;


  void SetBookName(const name_type& theName);
  void SetBookAuthor(const author_type& theAuthor);
  void SetBookClass(const class_type& theClass);
  void SetBookCreators(const std::string& theCreators);
  void SetBookData(const date_type& theData);
  void SetBookNumber(const std::string& theNumber);
  void SetBookPrice(size_type thePrice);
  void SetBookSize(size_type theSize);


  friend ostream& operator<<(ostream &os, const Book& item);
  ~Book() {}
private:
  name_type name_;              // Book name
  author_type author_;              // 作者名
  std::string creators_;            // 出版社
  size_type price_;                    // 价格
  date_type publication_data_;      // 生产日期
  class_type major_;               // 类别
  std::string number_;              // 编号
  size_type size_;                    // 页数

};





#endif

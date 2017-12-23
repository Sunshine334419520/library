/**
 * @Author: sunshine
 * @Date:   2017-12-16T17:54:32+08:00
 * @Email:  guang334419520@126.com
 * @Filename: Person.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-16T17:54:32+08:00
 */


#ifndef LIBRARY_PERSON_H
#define LIBRARY_PERSON_H

#include <iostream>

class Book;

class Person {
public:
  Person() = default;

  virtual ~Person() {}


  /*  显示图书  */
  virtual void ShowBooks() const;

  /*  搜索图书  */
  virtual const Book& SearchBook();

  /*  获得个人信息  */
  virtual void GetPersonInfo() const;

  /*  设置个人信息  */
  virtual void SetPersonInfo();

  /*  设置密码  */
  virtual void SetPassword();

  /*  查看帮助信息  */
  virtual void GetHelpInfo() const;


};



#endif

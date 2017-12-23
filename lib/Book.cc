/**
 * @Author: sunshine
 * @Date:   2017-12-16T17:55:38+08:00
 * @Email:  guang334419520@126.com
 * @Filename: Book.c
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T15:55:21+08:00
 */


#include "Book.hpp"
#include <iostream>

inline
const Book::name_type& Book::GetBookName() const
{
  return this->name_;
}


inline
const Book::author_type& Book::GetBookAuthor() const
{
  return this->author_;
}


inline
const Book::class_type& Book::GetBookClass() const
{
  return this->major_;
}


inline
const std::string& Book::GetBookCreators() const
{
    return this->creators_;
}


inline
const Book::date_type& Book::GetBookData() const
{
  return this->publication_data_;
}

inline
Book::size_type Book::GetBookPrice() const
{
  return this->price_;
}


inline
Book::size_type Book::GetBookSize() const
{
  return this->size_;
}


inline
const std::string& Book::GetBookNumber() const
{
  return this->number_;
}

inline
void Book::SetBookName(const name_type& theName)
{
  this->name_ = theName;
}


inline
void Book::SetBookAuthor(const author_type& theAuthor)
{
  this->author_ = theAuthor;
}


inline
void Book::SetBookClass(const class_type& theClass)
{
  this->major_ = theClass;
}


inline
void Book::SetBookCreators(const std::string& theCreators)
{
  this->creators_ = theCreators;
}


inline
void Book::SetBookData(const date_type& theData)
{
  this->publication_data_ = theData;
}


inline
void Book::SetBookNumber(const std::string& theNumber)
{
  this->number_ = theNumber;
}

inline
void Book::SetBookPrice(size_type thePrice)
{
  this->price_ = thePrice;
}

inline
void Book::SetBookSize(size_type theSize)
{
  this->size_ = theSize;
}

/**
 * Book class << 操作符重载
 */
 ostream& operator<<(ostream &os, const Book& item)
 {
   os.setf(ios::left);
   os.width(18);
   os << item.name_ << '\t';
   os.width(12);
   os << item.author_ << '\t';
   os.width(18);
   os << item.creators_ << '\t';
   os.width(6);
   os << item.price_ << '\t';
   os.width(11);
   os << item.publication_data_ << '\t';
   os.width(12);
   os << item.major_ << '\t';
   os.width(6);
   os << item.number_ << '\t';
   os.width(6);
   os << item.size_;
 }

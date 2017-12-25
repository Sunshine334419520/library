/**
 * This is the super user class
 * @Author: sunshine
 * @Date:   2017-12-15T22:10:27+08:00
 * @Email:  guang334419520@126.com
 * @Filename: AdministerPerson.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-25T19:01:02+08:00
 */

#include "AdministerPerson.hpp"
#include <iostream>
#include <sstream>
#include "user.hpp"
using namespace std;
using namespace admin;

AdministerPerson::AdministerPerson()
{
  str_ = "\"";
  Books_ = new list<Book>();
  ReadAllBook(Books_);

  mysql_ = new MysqlInterface();

  if(!mysql_->ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql_->PrintErrorInfo();
    return ;
  }

}

AdministerPerson::~AdministerPerson()
{
  delete Books_;
  delete mysql_;
}


void AdministerPerson::ShowPersonInfo() const
{
  cout << "alias : " << this->alias_ << endl;
}

void AdministerPerson::ShowBrrowReturnInfo() const
{
  string sql = "select * from record";
  std::vector<std::vector<string> > query_results;
  if(!mysql_->ReadData(sql, query_results)) {
    mysql_->PrintErrorInfo();
    return ;
  }

  for(const auto& bw : query_results) {
    for(const auto& v : bw) {
      cout << v << endl;
    }
  }

}


bool AdministerPerson::SetPersonInfo(const std::string& theAlias)
{

  string sql = "update admin set alias = " + str_ + theAlias + str_ +
  "where username = " + str_ + "root" + str_;

  if(!mysql_->ModifyData(sql)) {
    mysql_->PrintErrorInfo();
    return false;
  }

  this->alias_ = theAlias;
  return true;
}


bool AdministerPerson::SetPassword(const std::string& thePassword)
{
  string sql = "update admin set password = " + str_ + thePassword +
                str_ + " " + "where alias = " + str_ + this->alias_ + str_;

  if(!mysql_->ModifyData(sql)) {
    mysql_->PrintErrorInfo();
    return false;
  }

  return true;
}

bool AdministerPerson::AddBook(const Book& theBook)
{
   string sql = "insert into Books(name, author, creators, price, publicdata, class, number, pages) values(" +
                 str_ + theBook.GetBookName() + str_ + "," +
                 str_ + theBook.GetBookAuthor() + str_ + "," +
                 str_ + theBook.GetBookCreators() + str_ + ",";

   ostringstream ostr_sql;

   ostr_sql << sql;
   ostr_sql << str_ << theBook.GetBookPrice() << str_ << ","        \
            << str_ << theBook.GetBookData() << str_ << ","         \
            << str_ << theBook.GetBookClass() << str_ << ","        \
            << str_ << theBook.GetBookNumber() << str_ << ","       \
            << str_ << theBook.GetBookSize() << str_ << ")";


   cout << ostr_sql.str() << endl;
   if(!mysql_->WriteData(ostr_sql.str())) {
     mysql_->PrintErrorInfo();
     return false;
   }

   return true;
 }


bool AdministerPerson::ModifyBook(const string& old_number, const Book& new_book)
{
   string sql = "update into Books set name = " +
                str_ + new_book.GetBookName() + str_ + " " +
                "author = " + str_ + new_book.GetBookAuthor() + str_ + " " +
                "creators = " + str_ + new_book.GetBookCreators() + str_;

  ostringstream ostr_sql(sql);
  ostr_sql << " price = "<< str_ << new_book.GetBookPrice() << str_          \
           << " publicdata = "<< str_ << new_book.GetBookData() << str_       \
           << " class = "<< str_ << new_book.GetBookClass() << str_          \
           << " number = "<< str_ << new_book.GetBookNumber() << str_        \
           << " pages = "<< str_ << new_book.GetBookSize() << str_           \
           << "where number = " << str_ << old_number << str_;



  if(!mysql_->ModifyData(ostr_sql.str())) {
    mysql_->PrintErrorInfo();
    return false;
  }

  return true;

}


 bool AdministerPerson::RemoveBook(const std::string& theNumber)
 {
   string sql = "delete from Books where number = " + str_ + theNumber + str_;

   if(!mysql_->ModifyData(sql)) {
     mysql_->PrintErrorInfo();
     return false;
   }

   return true;
 }


 bool AdministerPerson::SearchBook(const Book::name_type& theName, Book* theBook) const
 {
   for(auto& book : *Books_) {
     if(book.GetBookName() == theName) {
       theBook = new Book(book);
      return true;
     }
   }

   return false;
 }


 /**
  * show all books
  */
 void AdministerPerson::ShowBooks() const
 {
   /*
   if(Books_ == nullptr) {
     Books_ = new std::list<Book>;
     ReadAllBooks(Books_);

   }
   */

   cout.setf(ios::left);
   cout.width(18);
   cout << "BookName" << '\t';
   cout.width(12);
   cout << "Author" << '\t';
   cout.width(18);
   cout << "Creators" << '\t';
   cout.width(6);
   cout << "Price" << '\t';
   cout.width(11);
   cout << "Data" << '\t';
   cout.width(12);
   cout << "Class" << '\t';
   cout.width(6);
   cout << "ID" << '\t';
   cout.width(6);
   cout << "pages" << '\n';

   for(const auto& book : *Books_) {
     cout << book << endl;
   }


 }

 /**
  * read from the database and save to books
  * @param  books save data
  * @return       true , false
  */
 bool admin::ReadAllBook(std::list<Book>* books)
 {
   MysqlInterface mysql;

   if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
     mysql.PrintErrorInfo();
     return false;
   }

   string sql = "select * from Books";
   std::vector<std::vector<string> > results;
   if(!mysql.ReadData(sql, results)) {
     mysql.PrintErrorInfo();
     return false;
   }

   if(results.empty()) {
     return false;
   }

   mysql.CloseDatabase();

   for(const auto& book : results) {
     Book::size_type price = StringToNumber<int>(book[4]);
     Book::size_type pages = StringToNumber<int>(book[8]);
     Book tmpbook(book[1], book[2], book[3],
               price, book[5], book[6],
               book[7], pages);


     books->push_back(tmpbook);


   }

   return true;
 }

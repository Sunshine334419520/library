/**
 * This is the super user class
 * @Author: sunshine
 * @Date:   2017-12-15T22:10:27+08:00
 * @Email:  guang334419520@126.com
 * @Filename: AdministerPerson.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T17:57:06+08:00
 */

#include "AdministerPerson.hpp"
#include <iostream>
#include <sstream>
#include "user.hpp"
using namespace std;
using namespace admin;

AdministerPerson::AdministerPerson()
{
  Books_ = new list<Book>;
  ReadAllBook(Books_);

  mysql_ = new MysqlInterface;

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

  string sql = "update admin alias = " + theAlias +
  "where username = " + this->alias_;

  if(!mysql_->ModifyData(sql)) {
    mysql_->PrintErrorInfo();
    return false;
  }

  this->alias_ = theAlias;
  return true;
}


bool AdministerPerson::SetPassword(const std::string& thePassword)
{
  string sql = "update admin password = " + thePassword + " " +
  "where alias = " + this->alias_;

  if(!mysql_->ModifyData(sql)) {
    mysql_->PrintErrorInfo();
    return false;
  }

  return true;
}

bool AdministerPerson::AddBook(const Book& theBook)
{
   string sql = "insert into Books(alias, number) values(" +
                 theBook.GetBookName() + "," +
                 theBook.GetBookAuthor() + "," +
                 theBook.GetBookCreators() + ",";

   ostringstream ostr_sql(sql);

   ostr_sql << theBook.GetBookPrice() << "," << theBook.GetBookData() << "," \
            << theBook.GetBookClass() << "," << theBook.GetBookNumber() << "," \
            << theBook.GetBookSize() << ")";



   if(!mysql_->WriteData(ostr_sql.str())) {
     mysql_->PrintErrorInfo();
     return false;
   }

   return true;
 }


bool AdministerPerson::ModifyBook(const Book& theBook)
{
   string sql = "update into Books name = " + theBook.GetBookName() + " " +
                "author = " + theBook.GetBookAuthor() + " " +
                "creators = " + theBook.GetBookCreators() + " ";


   ostringstream ostr_sql;
   ostr_sql << sql;
   ostr_sql << theBook.GetBookPrice() << "," << theBook.GetBookData() << "," \
            << theBook.GetBookClass() << "," << theBook.GetBookNumber() << "," \
            << theBook.GetBookSize() << ")";

  if(!mysql_->ModifyData(ostr_sql.str())) {
    mysql_->PrintErrorInfo();
    return false;
  }

  return true;

}


 bool AdministerPerson::RemoveBook(const std::string& theNumber)
 {
   string sql = "delete from Books where number = " + theNumber;

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
 bool ReadAllBook(std::list<Book>* books)
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

   mysql.CloseDatabase();

   for(const auto& book : results) {
     Book::size_type price = StringToNumber<int>(book[3]);
     Book::size_type pages = StringToNumber<int>(book[7]);
     Book tmpbook(book[0], book[1], book[2],
               price, book[4], book[5],
               book[6], pages);


     books->push_back(tmpbook);


   }

   return true;
 }

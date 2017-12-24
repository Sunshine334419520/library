/**
 * @Author: sunshine
 * @Date:   2017-12-15T22:22:21+08:00
 * @Email:  guang334419520@126.com
 * @Filename: StudentUser.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-24T21:48:28+08:00
 */


#include "StudentUser.hpp"
#include "MysqlInterface.hpp"
#include "Book.hpp"
#include "user.hpp"
#include "AdministerPerson.hpp"
#include <iostream>

using namespace std;
using namespace user;

StudentUser::StudentUser()
  {
    //name_ = nullptr;
    //number_ =nullptr;
    //department_ = nullptr;
    Books_ = new std::vector<Book>();
  }

/**
 * Get person information
 * @return void
 */

void StudentUser::GetPersonInfo() const
{
  cout << "name: " << this->name_ << endl;
  cout << "number_: " << this->number_ << endl;
  cout << "department_: " << this->department_ << endl;
  cout << "alias: " << this->alias_ << endl;
}


/**
 * Set Person information
 * @param  theName       your name
 * @param  theNumber     your number
 * @param  theDepartment your department
 * @return               void
 */
//inline
void StudentUser::SetPersonInfo(const std::string& theName,
                                const std::string& theNumber,
                                const std::string& theDepartment,
                                const std::string& theAlias)
{
  this->name_ = theName;
  this->number_ = theNumber;
  this->department_ = theDepartment;
  this->alias_ = theAlias;
}


/**
 * change your password
 * @param  thePassword new password
 * @return             succeed true, esle false
 */
bool StudentUser::SetPassword(const std::string& thePassword)
{
  MysqlInterface mysql;
  if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql.PrintErrorInfo();
    return false;
  }

  string sql = "update users password = " + thePassword +
               "where username = " + this->number_;

  if(!mysql.ModifyData(sql)) {
    mysql.PrintErrorInfo();
    return false;
  }

  return true;
}


/**
 * Use the book name as keywords to search
 *
 * @param       name The book name
 * @return      yes return book object，else reutrn null object
 */
bool StudentUser::SearchBook(const Book::name_type& name, Book* theBook) const
{
  /*

  if(Books_ == nullptr) {
    Books_ = new std::vector<Book*>;
    if(ReadAllBooks(Books_))
      return false;
  }
  */

  for(auto& book : *Books_) {
    if(book.GetBookName() == name) {
      theBook = new Book(book);
      return true;
    }
  }

  return false;
}


/**
 * Use author as keywords to search
 *
 * @param     author The author name
 * @return    succeed to return search result, else return nullptr
 */
bool StudentUser::SearchBook(const Book::author_type& author,
                             std::vector<Book>& result_books) const
{
  /*
  if(Books_ == nullptr) {
    Books_ = new std::vector<Book*>;
    if(!ReadAllBooks(Books_))
      return false;
  }
  */

  /* 寻找所有author作者的书，保存在reuslt_Books_结构中  */
  for(const auto& book : *Books_) {
    if(book.GetBookAuthor() == author) {
      result_books.push_back(book);
    }
  }

  if(result_books.empty()) {
    return false;
  }

  return true;
}


/**
 * Use class as keywords to search
 * @param  book_class The class name
 * @return            succeed vector , else nullptr
 */
const std::vector<Book>* StudentUser::SearchBook(const Book::class_type& book_class) const
{
  /*
  if(Books_ == nullptr) {
    Books_ = new std::vector<Book*>;
    if(ReadAllBooks(Books_))
      return nullptr;
  }
  */
  std::vector<Book>* result_class = new std::vector<Book>;
  /* 寻找所有book_class类别的书，保存在reuslt_class结构中  */
  for(const auto& book : *Books_) {
    if (book.GetBookClass() == book_class) {
      result_class->push_back(book);
    }
  }

  if(result_class->empty()) {
    return nullptr;
  }

  return result_class;
}


bool StudentUser::BorrowingBook(const Book::name_type& name)
{
  Book* sear_result = nullptr;

  if(!SearchBook(name, sear_result))
    return false;

  if(sear_result == nullptr)
    return false;

  MysqlInterface mysql;
  if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql.PrintErrorInfo();
    return false;
  }

  string sql = "insert into record(alias, number) values(" +
                this->alias_ + "," +
                sear_result->GetBookNumber() + ")";

  if(!mysql.WriteData(sql)) {
    mysql.PrintErrorInfo();
    return false;
  }
  mysql.CloseDatabase();
  return true;

}

/**
 * return a book
 * @param  number book number
 * @return        succeed ture, else false
 */
bool StudentUser::ReturnBook(const std::string& number)
{
  MysqlInterface mysql;
  if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql.PrintErrorInfo();
    return false;
  }

  string sql = "delete from record where number=" + number;

  if(!mysql.DeleteData(sql)) {
    mysql.PrintErrorInfo();
    return false;
  }

  return true;
}


/**
 * show all books
 */
void StudentUser::ShowBooks() const
{
  /*
  if(Books_ == nullptr) {
    Books_ = new std::vector<Book*>;
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
 * show help information
 */
void user::GetHelpInfo()
{
  cout << "\t\t\t\t\t\t** Student Command **" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'ls' : " << "Show all books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'find' : " << "Find books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'bw' : " << "Brrowing books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'return' : " << "Return books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'show' : " << "Show Person info" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'password' : " << "Change your the password" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'set' : " << "Seting person info" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'help' : " << "Show help info" << endl;
  cout << "\t\t\t\t\t\t** Admin Command **" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'ls' : " << "Show all books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'find' : " << "Find books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'remove' : " << "Remove books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'modify' : " << "Modify books" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'add' : " << "add a book" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'show' : " << "Show Person info" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'password' : " << "Change your the password" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'set' : " << "Seting person info" << endl;
  cout << "\t\t\t~~" << "- - - - - - - - -- - - - - - - -" << endl;
  cout << "\t\t\t~~" << "'help' : " << "Show help info" << endl;

}

/**
 * read from the database and save to books
 * @param  books save data
 * @return       true , false
 */

bool user::ReadAllBook(std::vector<Book>* books)
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

    Book::size_type price = admin::StringToNumber<int>(book[3]);
    Book::size_type pages = admin::StringToNumber<int>(book[7]);

    Book tmpbook(book[0], book[1], book[2],
                 price, book[4], book[5],
                 book[6], pages);


    books->push_back(tmpbook);

    //delete book;
  }

  return true;
}

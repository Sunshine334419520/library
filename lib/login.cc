/**
 * @Author: YangGuang
 * @Date:   2017-12-14T14:07:27+08:00
 * @Email:  guang334419520@126.com
 * @Filename: login.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-25T22:09:26+08:00
 */



#include <iostream>
#include <string>
#include <vector>
#include "MysqlInterface.hpp"
#include "AdministerPerson.hpp"
#include "StudentUser.hpp"
#include "Book.hpp"
#include "hash.hpp"

#include "login.hpp"
#include "user.hpp"


using namespace std;
using namespace user;
using namespace admin;


static void
StudentCmdParse(const std::string& command, StudentUser& student);
static void
AdminCommandParse(const std::string& command, AdministerPerson& root);
static Book InputBookInfo();
static bool RemoveFirstLastSpace(std::string& str);

/**
 * 判断账号是否正确,管理员账号以字母开头，用户账户是学号
 * @param  username 用户名
 * @param  password 密码
 * @param  alias    别名
 * @return          -1 失败，0 管理员 1 学生
 */
int LoginLibrarySystem(const std::string& username,
                       const std::string& password,
                       std::string& alias)
{

   MysqlInterface mysql;

   if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
     mysql.PrintErrorInfo();
     return -1;
   }


   std::string sql;
   size_t return_value = -1;

   if(username[0] > '1' && username[0] <'9') {
      sql = "select * from users where number=" +
            username + " and password=" + password;

      return_value = 1;
   } else {
     std::string str = "\'";
     sql = "select * from admin where username=" +
            str + username + str + " and password=" + str + password + str;

     return_value = 0;
   }

   std::vector<std::vector<std::string> > result;
   if(!mysql.ReadData(sql, result)){
     mysql.PrintErrorInfo();
     return -1;
   }

   if(result.empty()) {
     return -1;
   }

   alias = result[0][3];

   mysql.CloseDatabase();

   return return_value;

}


/**
 * 主要的逻辑分析，执行用户或者管理员命令
 * @param alias 用户别名
 * @param flags 用户 false 管理员 true
 */
void InterfaceMain(const std::string& alias, bool flags)
{
  std::string str = "\"";

  if(flags == true) {

    /*
    MysqlInterface mysql;
    if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql.PrintErrorInfo();
    return ;
  }

  std::string sql = "select * from userinfo where alias=" + alias;
  std::vector<std::vector<std::string> > result;
  if(!mysql.ReadData(sql, result)) {
  mysql.PrintErrorInfo();
  return ;
}
*/

AdministerPerson root;
root.SetPersonInfo(alias);

cout << "%%[" << alias << "]> ";
std::string command;
while(cin >> command) {
  RemoveFirstLastSpace(command);    //去除行首和行尾空格
  AdminCommandParse(command, root);
  cout << "%%[" << alias << "]> ";
}


}
else {
  MysqlInterface mysql;

  if(!mysql.ConnectDatabase(kHostName, kUserName, kPassWord, kDataBase)) {
    mysql.PrintErrorInfo();
    return ;
  }


  std::string sql = "select * from userinfo where alias=" + str + alias + str;
  std::vector<std::vector<std::string> > result;
  if(!mysql.ReadData(sql, result)) {
    mysql.PrintErrorInfo();
    return ;
  }

  StudentUser student;

  if(result.empty()) {
    cout << "Please input your name : ";
    string name;
    cin >>  name;

    cout << "Please input your student id: ";
    string id;
    cin >> id;

    cout << "Please input your college: ";
    string college;
    cin >> college;

    student.SetPersonInfo(name, id, college, alias);
    sql = "insert into userinfo(alias, name, number, department) values(" +
    str + alias + str + "," + str + name + str + "," + str + id + str +
    "," + str + college + str + ")";
    if(!mysql.WriteData(sql)) {
      mysql.PrintErrorInfo();
      return ;
    }

  } else {
    student.SetPersonInfo(result[0][1],
      result[0][2], result[0][3], alias);
    }

    mysql.CloseDatabase();

    cout << "%%[" << alias << "]> ";
    std::string command;
    while(cin >> command) {
      RemoveFirstLastSpace(command);
      StudentCmdParse(command, student);
      cout << "%%[" << alias << "]> ";
    }

  }





}


/**
 *              去除前后空格
 * @param  str 需要去除的字符串
 * @return     成功 true， 失败 false
 */
static bool RemoveFirstLastSpace(std::string& str)
{
  string::size_type first_pos = str.find_first_not_of(" ");

  if(first_pos == std::string::npos) {
    return false;
  }

  string::size_type last_pos = str.find_last_not_of(" ");

  if(last_pos == std::string::npos) {
    return false;
  }

  str = str.substr(first_pos, last_pos - first_pos + 1);

  return true;

}


/**
 * 管理员命令解析function
 * @param command 需要解析的命令
 * @param root    管理员对象
 */
static void
AdminCommandParse(const std::string& command, AdministerPerson& root)
{
  string::size_type pos = command.find(" ");
  std::string command_main;
  if(pos != string::npos)
    command_main = command.substr(0, pos);
  else
    command_main = command;

  switch (hashit(command_main)) {
    case  eLs:
    {
      pos = command.find("-");



      if(pos == string::npos || command[pos + 1] == 'p') {
        root.ShowPersonInfo();
      } else if(command[pos + 1] == 'b') {
        root.ShowBooks();
      } else if(command[pos + 1] == 'r') {
        root.ShowBrrowReturnInfo();
      } else {
        std::cout << command[pos + 1] << "：Without this option" << '\n';
      }

      break;
    }
    case eAdd:
    {


      Book book = InputBookInfo();


      root.AddBook(book);
      break;
    }
    case eRemove:
    {
      std::string number;
      std::cout << "Please input the number of the book : ";
      cin >> number;

      root.RemoveBook(number);
      break;
    }
    case eModify:
    {
      const Book book = InputBookInfo();
      std::cout << "Please input number of the need change " << '\n';
      std::string number;
      cin >> number;
      root.ModifyBook(number, book);
      break;
    }
    case eFind:
    {
      Book::name_type name;
      std::cout << "Please input [ name ] for search books : ";
      cin.ignore();
      getline(cin, name);
      Book* book = nullptr;
      root.SearchBook(name, book);
      cout << *book << endl;
      delete book;
      break;
    }
    case eHelp:
    {
      GetHelpInfo();
      break;
    }
    case ePassword:
    {
      std::string password;
      cin >> password;
      root.SetPassword(password);
    }
    case eSeting:
    {
      std::string new_alias;
      std::cout << "Please input new alias : ";
      std::cin >> new_alias;



      root.SetPersonInfo(new_alias);

      break;
    }
    case eExit:
      std::cout << "Bye" << '\n';
      exit(0);
    case eDefault:
    {
      std::cerr << command_main << ": without this command,"
                "Please input the \"help\" view the help info " << '\n';

      break;

    }
    default:
    {
      std::cerr << command_main << ": without this command,"
                "Please input the \"help\" view the help info " << '\n';

      break;
    }
  }

}


/**
 * 学生命令解析
 * @param command 需要解析的命令
 * @param student 学生对象
 */
static void
StudentCmdParse(const std::string& command,StudentUser& student)
{

  switch (hashit(command)) {
    case eLs:
    {
      student.ShowBooks();
      break;
    }
    case eFind:
    {
    search:
      std::cout << "\t\t- - - - - - - Search - - - - - - -" << '\n';
      std::cout << "\t\t\tSearch by title，Please input [1]! " << '\n';
      std::cout << "\t\t\tSearch by class，Please input [2]! " << '\n';
      std::cout << "\t\t\tSearch by author，Please input [3]! " << '\n';
      std::cout << "\t\t- - - - - - - - - - - - - - - - - " << '\n';
      int n;
      cin >> n;
      switch (n) {
        case 1:
        {
          std::cout << "Please input [ name ] for search books : ";
          Book::name_type name;
          cin.ignore();                 // 清除cin留下的\n让getline正常运作
          std::getline(std::cin, name);
          Book* book = nullptr;
          /* false 代表没有查询结果 */
          if(!student.SearchBook(name, &book)) {
            std::cout << "Without book name !!! " << name << endl;
            break;
          }
          cout << *book << endl;
          delete book;
          break;
        }
        case 2:
        {
          std::cout << "Please input [ class ] for search books : ";
          Book::class_type class_name;

          cin.ignore();                     // 清除cin留下的\n让getline正常运作

          std::getline(std::cin, class_name);

          std::vector<Book>* find_result = student.SearchBook(class_name);
          /* nullptr就是没有查询结果 */
          if(find_result == nullptr) {
            std::cout << "Without book name !!! " << class_name << endl;

          }
          /* 遍历结果并输出  */
          for(const auto& book : *find_result) {
            cout << book << endl;
          }

          delete find_result;
          break;
        }
        case 3:
        {
          std::cout << "Please input [ author ] for search books : ";
          Book::author_type author_name;
          cin.ignore();
          std::getline(std::cin, author_name);
          std::vector<Book> author_result;      //用于存放查询结果

          if(!student.SearchBook(author_name, author_result)) {
            std::cout << "Without book name !!! " << author_name << endl;
          }

          for(const auto& book : author_result) {
            cout << book << endl;
          }

          break;
        }
        default:
          goto search;
      }


      break;

    }
    case eBorrowing:
    {
      Book::name_type name;
      std::cout << "Please input [ name ] for borrowing books : ";
      cin.ignore();
      std::getline(cin, name);
      student.BorrowingBook(name);
      break;
    }
    case eReturn:
    {
      std::string number;
      std::cout << "Please input [ number ] for return books : ";
      cin.ignore();
      std::getline(cin, number);
      student.ReturnBook(number);
      break;
    }
    case eShow:
    {
      student.GetPersonInfo();
      break;
    }
    case ePassword:
    {
      std::string password;
      std::cout << "Please input [ password ] for change password : ";
      cin.ignore();
      std::getline(cin, password);
      student.SetPassword(password);
      break;
    }
    case eSeting:
    {
      std::string name;
      std::cout << "Please input your name : ";
      std::cin >> name;

      std::string number;
      std::cout << "Please input your number : ";
      std::cin >> number;

      std::string department;
      std::cout << "Please input your department : ";
      std::cin >> department;

      std::string new_alias;
      std::cout << "Please input your new alias : ";
      cin >> new_alias;
      student.SetPersonInfo(name, number, department, new_alias);
      break;
    }
    case eHelp:
    {
      GetHelpInfo();
      break;
    }
    case eExit:
      std::cout << "Bye" << '\n';
      exit(0);
    case eDefault:
    {
      std::cerr << command << ": without this command," <<
                "Please input the 'help' view the help info " << '\n';

      break;

    }
    default:
    {
      std::cerr << command << ": without this command,"
                "Please input the \"help\" view the help info " << '\n';

      break;
    }

  }
}


static Book InputBookInfo()
{
  Book::name_type name;
  std::cout << "Please input the name of a book : ";
  cin.ignore();
  getline(cin, name);

  Book::author_type author;
  std::cout << "Please input the name of the author : ";
  getline(cin, author);

  std::string creators;
  std::cout << "Please input the Publishing house of the book : ";
  getline(cin, creators);


  Book::size_type price;
  std::cout << "Please input the price of the book : ";
  cin >> price;

  Book::date_type data;
  std::cout << "Please input the production date of the book : ";
  getline(cin, data);


  Book::class_type book_class;
  std::cout << "Please input the type of the book : ";
  getline(cin, book_class);

  std::string number;
  std::cout << "Please input the number of the book : ";
  getline(cin, number);

  Book::size_type pages;
  std::cout << "Please input number of pages of the book : ";
  cin >> pages;

  return  Book(name, author, creators, price, data,
               book_class, number, pages);
}

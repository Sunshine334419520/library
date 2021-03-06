/**
 * @Author: YangGuang
 * @Date:   2017-12-13T21:58:30+08:00
 * @Email:  guang334419520@126.com
 * @Filename: Main.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-25T22:06:24+08:00
 */


#include "login.hpp"
//#include "Password.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

const char* kHostName = "localhost";
const char* kUserName = "root";
const char* kPassWord = "12345";
const char* kDataBase = "library";




int main(int argc, char const *argv[]) {

  /** 清屏 **/
  system("clear");


  std::string username,password;

  std::cout << "Please enter your number or admin account : ";
  std::cin >> username;


   password = getpass("Please enter your password : ");
  /*
  cout << "Please enter your password : ";
  cin >> password;
  */
  //passwd.InputPassword();

  //password = passwd.GetPassword();

  std::string alias;
  int n;

  if( (n = LoginLibrarySystem(static_cast<const std::string>(username),
   static_cast<const std::string>(password), alias)) < 0) {

    std::cout << "username or password error !" << '\n';
    return 0;
  } else if(n == 0){    //管理员账号登录

    InterfaceMain(alias, true);

  } else {      //学生登录
    InterfaceMain(alias, false);
  }


  return 0;
}

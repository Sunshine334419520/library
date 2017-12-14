/**
 * @Author: YangGuang
 * @Date:   2017-12-13T21:58:30+08:00
 * @Email:  guang334419520@126.com
 * @Filename: Main.cc
 * @Last modified by:   YangGuang
 * @Last modified time: 2017-12-14T19:19:38+08:00
 */


#include "login.hpp"
#include <iostream>
#include <string>
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

  std::cout << "Please enter your number or admin account : " << '\n';
  std::cin >> username;

  std::cout << "Please enter your password : " << '\n';
  std::cin >> password;

  if(LoginLibrarySystem(static_cast<const std::string>(username),
   static_cast<const std::string>(password))) {
    std::cout << "OK" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }


  return 0;
}

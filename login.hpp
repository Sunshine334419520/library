/**
 * @Author: YangGuang
 * @Date:   2017-12-14T17:17:17+08:00
 * @Email:  guang334419520@126.com
 * @Filename: login.hpp
 * @Last modified by:   YangGuang
 * @Last modified time: 2017-12-14T18:27:23+08:00
 */

#ifndef LIBRARY_LOGIN_H
#define LIBRARY_LOGIN_H


#include <iostream>
#include "user.hpp"

extern const char* kHostName;
extern const char* kUserName;
extern const char* kPassWord;
extern const char* kDataBase;


bool LoginLibrarySystem(const std::string& username,
                        const std::string& password);


#endif

/**
 * @Author: YangGuang
 * @Date:   2017-12-14T17:17:17+08:00
 * @Email:  guang334419520@126.com
 * @Filename: login.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-22T17:10:25+08:00
 */

#ifndef LIBRARY_LOGIN_H
#define LIBRARY_LOGIN_H


#include <iostream>



int LoginLibrarySystem(const std::string& username,
                       const std::string& password,
                       std::string& alias);

void InterfaceMain(const std::string& alias, bool flags);

#endif

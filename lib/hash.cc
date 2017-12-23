/**
 * @Author: sunshine
 * @Date:   2017-12-23T14:55:45+08:00
 * @Email:  guang334419520@126.com
 * @Filename: hash.cc
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T15:18:12+08:00
 */

#include <iostream>
#include "hash.hpp"


hash_t hashit(std::string const& inString)
{
  if(inString == "ls") return eLs;
  if(inString == "add") return eAdd;
  if(inString == "remove") return eRemove;
  if(inString == "modify") return eModify;
  if(inString == "find") return eFind;
  if(inString == "password") return ePassword;
  if(inString == "set") return eSeting;
  if(inString == "help") return eHelp;
  if(inString == "bw") return eBorrowing;
  if(inString == "return") return eReturn;
  if(inString == "show") return eShow;
}

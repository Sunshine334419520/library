/**
 * @Author: sunshine
 * @Date:   2017-12-22T20:39:42+08:00
 * @Email:  guang334419520@126.com
 * @Filename: hash.hpp
 * @Last modified by:   sunshine
 * @Last modified time: 2017-12-23T15:29:04+08:00
 */

#ifndef LIBRARY_HASH_H
#define LIBRARY_HASH_H

enum string_code {
  eAdd,
  eRemove,
  eModify,
  eFind,
  eShow,
  eHelp,
  eLs,
  ePassword,
  eSeting,
  eBorrowing,
  eReturn,
};

typedef string_code hash_t;
hash_t hashit(std::string const& inString);

#endif

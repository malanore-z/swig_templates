//
// Created by malanore on 11/13/21.
//

#include <malanore/c_api.h>

#include <string>

inline int APIHandleException(const std::exception& e) {
  SetLastError(e.what());
  return -1;
}

inline int APIHandleException(const std::string& s) {
  SetLastError(s.c_str());
  return -1;
}

#define API_BEGIN() try {
#define API_END()                                   \
  } catch (std::exception& e) {                     \
    return APIHandleException(e);                   \
  } catch (std::string& s) {                        \
    return APIHandleException(s);                   \
  } catch (...) {                                   \
    return APIHandleException("unknown exception"); \
  }                                                 \
  return 0;



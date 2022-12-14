//
// Created by mike yang on 10/3/2021.
//

#ifndef PDM_PDM_NETWORK_H
#define PDM_PDM_NETWORK_H

//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//#include <winsock2.h>
//#include <windows.h>
//#else
//#include <iostream>
//#endif

#include <string>
//#include <curl/curl.h>

class pdm_network{
public:
  explicit pdm_network(std::string a){user_nm=a;}
  static void upload_sync(std::string fname);
  void upload_sync_multi(const std::string& fname);
  void download_sync(std::string fname);
  void download_sync(std::string fname, std::string fpath);
  static int post(const std::string &a, const std::string &url);
  pdm_network();
  ~pdm_network();
private:
    static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
    std::string user_nm;

};

#endif //PDM_PDM_NETWORK_H

//
// Created by mike yang on 10/3/2021.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#include <windows.h>
#else
#include <iostream>
#endif

#include "pdm-network.h"
#include <stdio.h>
#include <string>
#include <asio.hpp>

/**
 * From https://curl.se/libcurl/c/ftpget.html
 * */
struct FtpFile {
    const char *filename;
    FILE *stream;
};



pdm_network::pdm_network() {
  curl_global_init(CURL_GLOBAL_ALL);
}

int pdm_network::post(const std::string &a, const std::string& url) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl){

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, a.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    /* Now run off and do what you have been told! */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      curl_easy_cleanup(curl);
      return 0;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  return 1;
}

pdm_network::~pdm_network() {
  curl_global_cleanup();
}





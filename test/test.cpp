//
// Created by 18604 on 10/15/2021.
//
#include "../pdm-network.h"
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <curl/curl.h>

#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{

  string user_name = "user1";
  string test_file = "new_file1.pdm";
  string test_file_path = "C:/Users/18604/AppData/Roaming/pdm/user1/new_file1.pdm";
  if (argc == 2){
    test_file = argv[1];
  }
  pdm_network test(user_name);
//  test.upload_sync_multi(test_file);
  test.download_sync(test_file,test_file_path);
  return 0;
}
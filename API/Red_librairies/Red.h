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
  SET_DEVICE_ID, 
  SET_DATA_TYPE,
  SET_BUFFER,
  GET_HOST,
  GET_DEVICE_ID,
  GET_DATA_TYPE,
  GET_BUFFER

  };

static const string Red_adress ="http://localhost:3000";

class Red{	

  protected:
    
	string host;
  int device_id;     
  string data_type;
  string buffer;


  public:
   
    Red(string ahost,int adevice_id,string adata_type);
    Red();
    ~Red();

    virtual void display();
   // virtual Red* red_config();

    virtual string post(Red* red,string value);
    virtual void list_permission();
    virtual void watch();
    virtual void update();
    virtual string get(Red* red);
    virtual string get_from(Red* red);
    


	  virtual void set_red_option(Red* red,Red_Option option,string value);
    virtual void set_red_option(Red* red,Red_Option option,int value);
    virtual void set_red_option(Red* red,Red_Option option,float value);
    virtual void set_red_option(Red* red,Red_Option option,char value);
    virtual string set_red_option(Red* red,Red_Option option); 
    

    virtual void set_host(string new_host);
    virtual void set_buffer(string abuffer);
    virtual void set_device_id(int id);
    virtual void set_data_type(string type);
    
    virtual string get_host();
    virtual string get_buffer();
    virtual int get_device_id();
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

Red::Red(string ahost,int adevice_id,string adata_type) :
  host(ahost),device_id(adevice_id),data_type(adata_type)
{}

Red::Red()
{}

Red::~Red()
{
  //cout << endl<<"Red object being destroyed!" << endl;
}


void Red::display(){;
  cout <<endl<< "The host is: " << host <<endl<< "The device Id is: "<<device_id<<endl<<"The data type is: "<<data_type<<endl;
  !(buffer.empty()) ? cout<<"The buffer is: "<<buffer<<endl : cout<<endl;
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}


string Red::post (Red* red,string value)
{

  CURL *curl;
  CURLcode res;
  string response_POST_from_server;
  string response;

  string host =red->get_host();
  host+="/device";

  string post ="deviceid=";
  post+= to_string(red->get_device_id());
  post+="&datatype=";
  post+=red->get_data_type();
  post+="&value=";
  post+=value; 

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, host.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 4);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_POST_from_server);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  
  }
  if(response_POST_from_server.find("\"ok\":1")!=string::npos)
  {
     response+="Well sent\n";
  }
  if(response_POST_from_server.find("\"nModified\":1"))
  {
      response+="Your data as been added to your device\n"; 
  }
    

  return response;


}

void Red::list_permission()
{

}
void Red::watch()
{

}
void Red::update()
{

}
string Red::get_from(Red* red)
{
  return "Soon ready" ;
}


string Red::get (Red* red)
{
  CURL *curl;
  CURLcode res;
  string response_GET_from_server;  
  string get = red->get_host();
  get+="/device/";
  get+=to_string(red->get_device_id());
  get+="/";
  get+=red->get_data_type();
  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, get.c_str());

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

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
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

void Red::set_host(string new_host)
{
  host=new_host;
}

void Red::set_device_id(int id)
{
  device_id=id;
}
void Red::set_data_type(string type)
{
  data_type=type;
}

string Red::get_host()
{
  return host;
}
int Red::get_device_id()
{
  return device_id;
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


void Red::set_red_option(Red* red,Red_Option option,string value)
{
    //cout<<"STRING"<<endl;
    switch (option) 
    {
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
}

void Red::set_red_option(Red *red,Red_Option option,int value)
{
     //cout<<"INT"<<endl;
       red->set_device_id(value);
    
}

void Red::set_red_option(Red* red,Red_Option option, float value)
{
     //cout<<"FLOAT"<<endl;
    red->set_device_id((int)value);
}

void Red::set_red_option(Red* red,Red_Option option, char value)
{
     //cout<<"CHAR"<<endl;
    red->set_device_id((int)value);
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
      case  GET_DEVICE_ID:
      return to_string(red->get_device_id());
      break;
      case  GET_BUFFER:
      return red->get_buffer();
      break;
      case SET_RED_HOST:
             red->set_host(Red_adress);
      return "Red servers are now the new host";
      default:
      return "no recognize option: ";
    }
    return "Error";
}


#endif // RED_H_INCLUDED

#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <fstream>
#include <streambuf>


using namespace std;
using namespace pqxx;


string read_script(string script){
   std::ifstream t (script.c_str(), std::ifstream::in);
   std::string str;

   t.seekg(0, std::ios::end);   
   str.reserve(t.tellg());
   t.seekg(0, std::ios::beg);

   str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());
   
   return str;
}


int main(int argc, char* argv[])
{
   string sql;
   
   try {
      connection C("dbname=trabalho_bd user=usuario_bd password=pass123 \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

      sql  = read_script("test.sql");
   
      work W(C);
         
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}

#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
  int hdata[14], compdata[7];
  int bitstr, i;
  ifstream in;
  ofstream out;

  in.open("hex", ios_base::in);
  in.setf(ios_base::hex, ios_base::basefield);
  for(i=0; i<14; ++i){ in >> hdata[i]; }
  in.close();
  out.open("comp", ios_base::out | ios_base::binary);
  for(i=0; i<7; i++)
  { 
    compdata[i]=hdata[i*2]*1024+hdata[i*2+1];
    out.write(reinterpret_cast<char *>(compdata+i), sizeof(int));
  }
  out.close();
  in.open("comp", ios_base::in | ios_base::binary);
  while(in.read(reinterpret_cast<char *>(&bitstr), sizeof(int)))
  {
    for(i=19; i>=0; --i)
    {
      cout << (((bitstr>>i)%2) ? "  " : "\x1b[47m  \x1b[0m");
      if(i==10 || i==0){ cout << endl; }
    }
  }
  in.close();
  
  return 0;
}

#include <iostream>
#include <fstream>
#include <unistd.h>
#define S 100000

using namespace std;

int bitmap[3][7];

void showbitmap(int i)
{
  int j, k;

  cout << "\x1b[2J";
  for(j=0; j<7; ++j)
  {
    for(k=19; k>=0; --k)
    {
      cout << "\x1b[" << j*2+(19-k)/10+1 << ";" << ((19-k)%10+1)*2-1 << "H";
      if((bitmap[i][j]>>k)%2){ cout << "  "; }
      else{ cout << "\x1b[47m  \x1b[40m"; } 
    }
  }
  cout << "\x1b[15;1H" << flush;
  usleep(S);
}

int main()
{
  int i, j, k;
  int tmp1, tmp2;
  ifstream in;
  ofstream out;

  in.setf(ios_base::hex, ios_base::basefield);
  in.open("hex", ios_base::in);
  out.open("comp", ios_base::out | ios_base::binary);
  while(in >> tmp1)
  {
    in >> tmp2;
    tmp1=(tmp1<<10)+tmp2;
    out.write(reinterpret_cast<char *>(&tmp1), sizeof(tmp1));
  }
  in.close();
  out.close();

  in.open("comp", ios_base::in | ios_base::binary);
  for(i=0; i<3; ++i)
  {
    for(j=0; j<7; ++j){ in.read(reinterpret_cast<char *>(bitmap[i]+j), sizeof(bitmap[i][j])); }
  }
  while(1)
  { 
    i=0;
    for(; i<3; ++i)
    {
      showbitmap(i);
    }
    --i;
    for(; i>=0; --i)
    {
      showbitmap(i);
    }
  }

  return 0;
}

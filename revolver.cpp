#include "blueprint.h"
#include <cstdlib>      // EXIT_FAILURE, etc
#include <string>
#include <iostream>
#include <fstream>
#include <dlfcn.h>      // dynamic library loading, dlopen() etc
#include <memory>       // std::shared_ptr
#include <fstream>
#include <streambuf>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdlib.h>


using namespace std;

// Video resolution
#define W 720
#define H 576
#define fW 720
#define fH 576

unsigned short frame[W*H*3] = {0};

// allocate a buffer to store one frame
//unsigned bit_field frame[h][w][3];
float pi = acos(-1);
const float two_pi = pi*2.0;


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
  char ** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end)
  {
    return *itr;
  }
  return 0;
}

/* MAGIC HAPPENS HERE
// compile code, instantiate class and return pointer to base class
// https://www.linuxjournal.com/article/3687
// http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html
// https://stackoverflow.com/questions/11016078/
// https://stackoverflow.com/questions/10564670/
*/
std::shared_ptr<A> compile(const std::string& code)
{
  // temporary cpp/library output files
  std::string outpath="/tmp";
  std::string headerfile="blueprint.h";
  std::string cppfile=outpath+"/jitcode.cpp";
  std::string libfile=outpath+"/jitlib.so";
  std::string logfile=outpath+"/jitlog.log";
  std::ofstream out(cppfile.c_str(), std::ofstream::out);

  // copy required header file to outpath
  std::string cp_cmd="cp " + headerfile + " " + outpath;
  system(cp_cmd.c_str());

  // add necessary header to the code
  std::string newcode =   "#include \"" + headerfile + "\"\n\n"
    + code + "\n\n"
    "extern \"C\" {\n"
    "A* maker()\n"
    "{\n"
    "    return (A*) new B(); \n"
    "}\n"
    "} // extern C\n";


  // output code to file
  if(out.bad()) {
    std::cout << "cannot open " << cppfile << std::endl;
    exit(EXIT_FAILURE);
  }
  out << newcode;
  out.flush();
  out.close();

  // compile the code
  std::string cmd = "g++ -Wall -Wextra " + cppfile + " -o " + libfile
    + " -O2 -shared -fPIC &> " + logfile;
  int ret = system(cmd.c_str());
  if(WEXITSTATUS(ret) != EXIT_SUCCESS) {
    std::cout << "compilation failed, see " << logfile << std::endl;
    system("cat /tmp/jitlog.log");
    exit(EXIT_FAILURE);
  }

  // load dynamic library
  void* dynlib = dlopen (libfile.c_str(), RTLD_LAZY);
  if(!dynlib) {
    std::cerr << "error loading library:\n" << dlerror() << std::endl;
    exit(EXIT_FAILURE);
  }

  // loading symbol from library and assign to pointer
  // (to be cast to function pointer later)
  void* create = dlsym(dynlib, "maker");
  const char* dlsym_error=dlerror();
  if(dlsym_error != NULL)  {
    std::cerr << "error loading symbol:\n" << dlsym_error << std::endl;
    exit(EXIT_FAILURE);
  }

  // execute "create" function
  // (casting to function pointer first)
  // https://stackoverflow.com/questions/8245880/
  A* a = reinterpret_cast<A*(*)()> (create)();

  // cannot close dynamic lib here, because all functions of the class
  // object will still refer to the library code
  // dlclose(dynlib);

  return std::shared_ptr<A>(a);
}

// MAIN ICI

int main(int argc, char** argv)
{

  int x, y, count;
  char * output = getCmdOption(argv, argv + argc, "-o");  

  char * input = getCmdOption(argv, argv + argc, "-i");

  //inputpipe.append(input);
  //inputpipe.append(" -f image2pipe -vf scale=48x40 -an -vcodec rawvideo -pix_fmt rgb24 -");

  std::string outputpipe("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb48le -s ");
  outputpipe.append(to_string(W));
  outputpipe.append("x");
  outputpipe.append(to_string(H));
  outputpipe.append(" -r 25 -i - -an -vcodec ffv1");
  //outputpipe.append(" -color_primaries bt709 -colorspace bt709 -color_trc bt709");
  outputpipe.append(" -pix_fmt yuv422p10le -vf 'pad=");
  outputpipe.append(to_string(fW));
  outputpipe.append(":");
  outputpipe.append(to_string(fH));
  outputpipe.append(":(ow-iw)/2:0' -r 25 -threads 4 ");
  outputpipe.append(output);

  // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
  //FILE *pipein = popen(inputpipe.c_str(), "r");
  FILE *pipeout = popen(outputpipe.c_str(), "w");


  // JIT kung-fu loader ///////////////////////////////////////////////////////

  std::ifstream t(input);
  std::string inject((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());


  // code to be compiled at run-time
  // class needs to be called B and derived from A
  std::string code =  "class B : public A {\n" 
    "    void f(unsigned short in[], int frameCount,int x,int y) const \n" 
    "    {\n" 
    "    unsigned short R,G,B; R=in[0]; G=in[1]; B=in[1];" +
    inject +
    "    oR=R;oG=G;oB=B;"
    "    }\n" 
    "};";

  unsigned short R,G,B;
  R = G = B = 0;

  std::cout << "compiling.." << std::endl;
  std::shared_ptr<A> a = compile(code);
  std::cout << "JIT code run: \n"<< std::endl;

  int frameCount = 0;
  int time = 1;

  //ffmpeg frame loop
  while(1)
  {

    int noise = 1;
    int count = 0;
    float smooth = 25.0;
    srand(time);
   unsigned short RGB[3];
    
    // jit loops over pixels
    for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
    {
      //idiotic
      RGB[0]=R;
      RGB[1]=G;
      RGB[2]=B;
      //unsigned short RGBmod[3];

      a->f(RGB,frameCount,x,y);
      
      R=a->R();
      G=a->G();
      B=a->B();

      // pixel range limiter
      if(R>65535)R=65535;
      if(G>65535)G=65535;
      if(B>65535)B=65535;

      if(R<0)R=0;
      if(G<0)G=0;
      if(B<0)B=0;


      // updatePixels()
      frame[count] += (R-frame[count])/smooth;
      count++;
      frame[count] += (G-frame[count])/smooth;
      count++;
      frame[count] += (B-frame[count])/smooth;
      count++;

      //proceed steps
      time++;

    }

    //proceed frameCount
    frameCount++;

    // Write this frame to the output pipe
    fwrite(frame, sizeof(unsigned short), H*W*3 , pipeout);
  }

  // mem cleanup
  // dlclose(dynlib);
  fflush(pipeout);
  pclose(pipeout);

  return EXIT_SUCCESS;
}

#include "blueprint.h"
#include <cstdlib>      // EXIT_FAILURE, etc
#include <string>
#include <iostream>
#include <sstream>
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
#include <cstring>

using namespace std;

// Video resolution
int W = 720;
int H = 576;
int fW = 720;
int fH = 576;

int rot = 0;
std::shared_ptr<A> a;
void* dynlib;
void* create;
string frameRate = "25.0";
string pixfmt = "yuv422p10le";
//unsigned short frame[];// = {0};

// allocate a buffer to store one frame
//unsigned bit_field frame[h][w][3];

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
  std::string clean = "rm " + libfile;
  std::string cmd = "g++ -Wall -Wextra " + cppfile + " -o " + libfile
    + " -O2 -shared -fPIC &> " + logfile;
  
  int ret = system(clean.c_str());
  int ret2 = system(cmd.c_str());
  
  if(WEXITSTATUS(ret) != EXIT_SUCCESS) {
    std::cout << "no files to remove" << std::endl;
  }

  if(WEXITSTATUS(ret2) != EXIT_SUCCESS) {
    std::cout << "compilation failed, see " << logfile << std::endl;
    system("cat /tmp/jitlog.log");
    exit(EXIT_FAILURE);
  }

  // load dynamic library
  
  if(dynlib){
  dlclose(dynlib);
  } 
  dynlib = dlopen (libfile.c_str(), RTLD_LAZY);
  if(!dynlib) {
    std::cerr << "error loading library:\n" << dlerror() << std::endl;
    exit(EXIT_FAILURE);
  }

  // loading symbol from library and assign to pointer
  // (to be cast to function pointer later)
  create = dlsym(dynlib, "maker");
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


vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

void rebuild(char * input){

  // JIT kung-fu loader ///////////////////////////////////////////////////////

  std::ifstream t(input);
  std::string inject((std::istreambuf_iterator<char>(t)),
  std::istreambuf_iterator<char>());


  // code to be compiled at run-time
  // class needs to be called B and derived from A
  std::string code =  "class B : public A {\n" 
    "    void initFrame(int _width, int _height) const \n"
    "    {\n" 
    "      width = _width;\n"
    "      height = _height;\n"
    "    }\n"
    "    void f(unsigned short in[],vector<unsigned short>& pixels, int frameCount,int x,int y) const \n" 
    "    {\n" 
    "    unsigned short R=in[0], G=in[1], B=in[2];" +
    inject +
    "    oR=R;oG=G;oB=B;"
    "    }\n" 
    "};";

  std::cout << "compiling.." << std::endl;
  a = compile(code);
  a->initFrame(W,H);
  std::cout << "JIT code run: \n"<< std::endl;
}

// MAIN ICI

int main(int argc, char** argv)
{

  char * output = getCmdOption(argv, argv + argc, "-o");  
  char * input = getCmdOption(argv, argv + argc, "-i");
  char * ssize = getCmdOption(argv, argv + argc, "-s");
  char * fsize = getCmdOption(argv, argv + argc, "-f");
  char * pix_fmt = getCmdOption(argv, argv + argc, "-p");
  char * rate = getCmdOption(argv, argv + argc, "-r");
  char * timer = getCmdOption(argv, argv + argc, "-t");
  char * quiet = getCmdOption(argv, argv + argc, "-q");
  char * rotate = getCmdOption(argv, argv + argc, "-w");

  // it works, duh
  // todo broken parsing.. 
  if(ssize){
    string siz(ssize);
    vector<string> dim = split(siz,'x');
    string s="";
    for (const auto &piece : dim[0]) s += piece;
    W = atoi(s.c_str());
    s="";
    for (const auto &piece : dim[1]) s += piece;
    H = atoi(s.c_str());
  }
  
  if(fsize){
    string siz(fsize);
    vector<string> dim = split(siz,'x');
    string s="";
    for (const auto &piece : dim[0]) s += piece;
    fW = atoi(s.c_str());
    s="";
    for (const auto &piece : dim[1]) s += piece;
    fH = atoi(s.c_str());
  }

  if(pix_fmt){
    pixfmt=string(pix_fmt);
  }

  if(rate){
    frameRate=string(rate);
  }

  if(rotate){
    rot=atoi(rotate);
  }

  //inputpipe.append(input);
  //inputpipe.append(" -f image2pipe -vf scale=48x40 -an -vcodec rawvideo -pix_fmt rgb24 -");
  
  cout << W << "x" << H << " framed in " << fW << "x" << fH << endl;
  
  bool adjust = false;
 
  if(W>fW){fW=W;adjust=true;}
  if(H>fH){fH=H;adjust=true;}

  if(fW<W){W=fW;adjust=true;}
  if(fH<H){H=fH;adjust=true;}

  if(adjust){
  cout << "adjusting pix area to " << W << "x" << H << " framed in " << fW << "x" << fH << endl;
  }

  std::string outputpipe("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb48le -s ");
  outputpipe.append(to_string(W));
  outputpipe.append("x");
  outputpipe.append(to_string(H));
  outputpipe.append(" -r ");
  outputpipe.append(frameRate); // string or float? that is a question
  
  if(!quiet)
  outputpipe.append(" -loglevel fatal "); // string or float? that is a question
  
  outputpipe.append(" -i - -an -vcodec ffv1");
  //outputpipe.append(" -color_primaries bt709 -colorspace bt709 -color_trc bt709");
  outputpipe.append(" -pix_fmt ");
  outputpipe.append(pixfmt);
  outputpipe.append(" -vf 'pad=");
  outputpipe.append(to_string(fW));
  outputpipe.append(":");
  outputpipe.append(to_string(fH));
  outputpipe.append(":(ow-iw)/2:(oh-ih)/2' -r ");
  outputpipe.append(frameRate);
  if(timer){
    outputpipe.append(" -t ");
    outputpipe.append(timer);
  }
  if(!quiet){
  outputpipe.append(" -f matroska - | tee ");
  outputpipe.append(output);
  outputpipe.append(" | mpv -");
  }else{

  outputpipe.append(" -f matroska ");
  outputpipe.append(output);
  }

  // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
  //FILE *pipein = popen(inputpipe.c_str(), "r");
  FILE *pipeout = popen(outputpipe.c_str(), "w");

  // compile code
  rebuild(input);

  int frameCount = 0;
  int time = 1;
  int which = 1;
  int x, y, count = 0;
  unsigned short R,G,B;
  R = G = B = 0;
  unsigned short RGB[3];
  cout << "memory to alocate has " << (W*H*3) << " bytes" << endl;
  
  
  vector<unsigned short> frame;
  for(int i = 0 ; i < W*H*3;i++)
    frame.push_back((unsigned short)1);
  
  //ffmpeg frame loop
  while(1)
  {


    

    //srand(time);
    count = 0; 

    // jit loops over pixels
    for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
    {
      RGB[0]=frame[count];
      RGB[1]=frame[count+1];
      RGB[2]=frame[count+2];

      a->f(RGB,frame,frameCount,x,y);

      R=a->R();
      G=a->G();
      B=a->B();

      frame[count++]=R;
      frame[count++]=G;
      frame[count++]=B;

      time++;

      /*
      // probably useless?
      // pixel range limiter
      if(R>65535)R=65535;
      if(G>65535)G=65535;
      if(B>65535)B=65535;

      if(R<0)R=0;
      if(G<0)G=0;
      if(B<0)B=0;
      */
    }

    if(rot>0)
    if(frameCount%rot==0){
      string fn = "formulas/"+to_string(which+1)+".cpp";
      char * ina = new char[fn.length()+1];
      strcpy(ina,fn.c_str());
      cout << "recompiling " << ina << " " << frameCount << endl << endl;
      rebuild(ina);

      which++;
      if(which>10)
      which = 1;
    }
    
    //proceed frameCount
    frameCount++;

    // Write this frame to the output pipe
    fwrite(frame.data(), sizeof(unsigned short), W*H*3 , pipeout);
    /*
    for(unsigned i=0;i<frame.size();++i){
      unsigned short tmp[1] = {frame[i]};
      fwrite(tmp, sizeof(unsigned short), 1 , pipeout);
    }*/
  }

  // mem cleanup
  dlclose(dynlib);
  // frame=vector<unsigned char>();
  fflush(pipeout);
  pclose(pipeout);

  return EXIT_SUCCESS;
}

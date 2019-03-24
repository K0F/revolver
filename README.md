# REVOLVER

  Revolver is a digital video synthetiser. It inputs valid c++ code snippet and turning it into a pixel value. Something similar as GLSL is doing on GPU but computed by CPU. 

  _Q: That is crazy.. why would you do that? ..it is so much slower_
  
  _A: Yup, but it is sort of tricky to get 16-bit pixel out of your GPU ..and it is much more fun! ;)_

## options:

  - ```-i program.txt``` setting input program textfile
  - ```-o output.mkv``` setting output videofile

### optional:

  - ```-s 24000/1001``` or i.e. ```-s 23.97602397602397602397``` to set framerate (defaults on PAL 25)
  - ```-s 720x576``` output size
  - ```-f 1998x1080``` actual framesize (adding letterboxes / pilarboxes to ```-s```)
  - ```-p yuv444p16le``` setting pixelformat of the output (see ```ffmpeg -pix_fmts``` for full list)
  - ```-t 3600``` how much seconds to render i.e. ```-t 01:30:00``` gives 1 hour and half
  - ```-q 1``` do no show live preview (render mode)

## dependencies:

  - ```ffmpeg``` swiss army knife for video
  - ```mpv``` modern videoplayer
  - ```g++``` c++ compiler

## build:

  - ```git clone https://github.com/K0F/revolver```
  - ```cd revolver```
  - ```make```

## run:

  - ```./revolver -i formulas/1.txt -s 4096x2160 -p yuv444p16le -r 24 -o My4kBlockBuster.mkv```
 
  It outputs FFV1 codec in Matroška container, later you can convert such MASTER into DPX series, DCP or ProRes to use it in whatever professional video editor of your choice.

## compatibility:

  It works on Linux only (MacOs would possibly do as well, untested)

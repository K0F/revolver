# REVOLVER

  Revolver is a digital video synthetiser. It inputs valid c++ code snippet and turning it into a pixel value. Something similar as GLSL is doing on GPU but computed by CPU. 

  _Q: That is crazy.. why would you do that? ..it is so much slower_
  
  _A: Yup, but it is sort of tricky to get 16-bit pixel out of your GPU ..and it much more fun! ;)_

## options:

  - ```-i program.txt``` setting input program textfile
  - ```-o output.mkv``` setting output videofile

### optional:

  - ```-s 720x576``` size
  - ```-f 1998x1080``` actual framesize (adding letterboxes / pilarboxes to ```-s```)
  - ```-p yuv444p16le``` setting pixelformat of the output (see ```ffmpeg -pix_fmts``` for full list)


## dependencies:

  - ```ffmpeg``` swiss army knife for video
  - ```mpv``` modern videoplayer
  - ```g++``` c++ compiler

## compatibility:

  It works on Linux only (MacOs would possibly do as well, untested)

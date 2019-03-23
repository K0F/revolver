# REVOLVER

Revolver is a digital video synthetiser. It inputs valid c++ code snippet and turning it into a pixel value. Something similar as GLSL but computed by CPU. 

_Q: That seems crazy.. why would you do that? ..it is so much slower_
_A: Yup, but it is sort of tricky to get 16-bit pixel out of your GPU_

## options:

```-i program.txt``` setting input program textfile
```-o output.mkv``` setting output videofile

### optional:

```-s 720x576``` size
```-f 1998x1080``` actual framesize (adding letterboxes / pilarboxes to ```-s```)
```-p yuv444p16le``` setting pixelformat of the output (see ```ffmpeg -pix_fmts``` for full list)

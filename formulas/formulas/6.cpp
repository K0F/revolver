

int id = (y*width+x)*3;
R=(oR+R-R-x+y)/100.0+pixels[id+3%(width*height*3)];
B=G=R;

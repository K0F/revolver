R+=10;
B=G=R;

int id = (y*width+x)*3;
pixels[id]=(sin(pixels[id]*TWO_PI)+1.0)/2.0*max;
pixels[id+1]=(sin(pixels[id+1]*TWO_PI)+1.0)/2.0*max;
pixels[id+2]=(sin(pixels[id+2]*TWO_PI)+1.0)/2.0*max;

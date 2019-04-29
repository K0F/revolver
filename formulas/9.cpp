
int X = x-width/2;
int Y = y-height/2;
double TAU = (sin(sqrt(X*X+Y*Y)/100.0*sin(frameCount/250.0*TWO_PI))+1.0001)/10.0;
R = (sin(TAU*0.1*TWO_PI*X/10.0+sqrt(frameCount*TWO_PI))+1.0)*max;
G = (sin(TAU*0.1*TWO_PI*X/10.1+sqrt(frameCount*TWO_PI))+1.0)*max;
B = (sin(TAU*0.1*TWO_PI*X/10.2+sqrt(frameCount*TWO_PI))+1.0)*max;


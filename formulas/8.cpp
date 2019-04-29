double X = x-width/2;
double Y = y-height/2;
double TAU = pow(sqrt(X*X+Y*Y),sin(frameCount/25000.0*TWO_PI)+1.001);
R=(sin((y*10.0)+(frameCount*10.1)*TAU/height*TWO_PI)+1.0)*max/2.0;
G=(((R-G))/5.0)+G;
B=(((R-B))/5.0)+B;

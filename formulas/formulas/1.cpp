// comment
x = width/2-x;
y = height/2-y;
double l = (sin(frameCount/1000.0*TWO_PI)+1.1)*500.0;
double d = sqrt(x*x+y*y);
double d1 = ((sin(d / l - frameCount/10001.0 )*TWO_PI)+1.0) * 50.0;
double d2 = ((sin(d / l - frameCount/10000.0 )*TWO_PI)+1.0) * 50.0;
double d3 = ((sin(d / l - frameCount/9999.0 )*TWO_PI)+1.0) * 50.0;
double smooth = (sin(frameCount*(x^y)/1000.0)+1.01)*500.0;
R+=(frameCount*d1-R)/smooth;
G+=(frameCount*d2-G)/smooth;
B+=(frameCount*d3-B)/smooth;


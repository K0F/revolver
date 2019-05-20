
int X = width/2-x;
int Y = height/2-y;
double theta = (sqrt(X*X+Y*Y)+1.1)*sin(frameCount/25.0*(121.3/120.0)*TWO_PI);
double at1 = atan2(Y,y);
double at2 = atan2(X,x);

int q;
for(q=1;q<10;q++){
  R+=((sin(theta/100.1*(at1*at2+at1)*q)+1.0)*10000.0-R)/(theta/q);
  G+=((sin(theta/100.22*(at1*at2+at1)*q)+1.0)*10000.0-G)/(theta/q);
  B+=((sin(theta/100.33*(at1*at2+at1)*q)+1.0)*10000.0-B)/(theta/q);
}

if(R>1024&&R<max-1024)
R+=sin((oR-R)/1000.0*TWO_PI)*512;

if(G>1024&&G<max-1024)
G-=sin((oG-G)/1000.0*TWO_PI)*512;

if(B>1024&&B<max-1024)
B-=sin((oB-B)/1000.0*TWO_PI)*512;



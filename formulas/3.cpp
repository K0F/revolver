x=(0.25+x)-width/2;
y=(0.25+y)-height/2;
float d = sqrt(x*x+y*y);

B=(sin(pow(d,sin(frameCount/101.0)+1.0)/width*TWO_PI*100.0+sin(frameCount-x/10.24*TWO_PI))+1.0)/2.0*max;

G+=(B-G)/1.1;
R+=(B-R)/1.2;

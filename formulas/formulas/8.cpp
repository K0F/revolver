double X = x-width/2;
double Y = y-height/2;
double TAU = pow(sqrt(X*X+Y*Y),sin(frameCount/2500.0*TWO_PI)+1.001)/100.0;
if(x<width/2+sin((frameCount+y)/33.33334*TWO_PI)*6.28){
G+=((sin((y/1009.0)+(frameCount*0.1)*TAU/height*TWO_PI)+1.0)*max/2.0-G)/10.0;
}else{
G+=((sin((y/1007.01)+(frameCount*0.1013)*TAU/height*TWO_PI)+1.001)*max/2.0-G)/10.0;

}
R=(((G-R))/5.0)+R;
B=(((G-B))/5.0)+B;

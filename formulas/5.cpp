/*
if(frameCount==0)
{
  R=random()%max;
  G=B=R;
}
*/
int X = x-(cos(frameCount/250.0*TWO_PI)*height/2+height/2);
int Y = y-(sin(frameCount/250.0*TWO_PI)*height/2+height/2);
float d = sqrt(X*X+Y*Y);

if(d < 20){
  R=G=B=(sin(frameCount/5.0*TWO_PI)+1.0)*max/2.0;
}else{
  int id = y*width+x;
  int siz = pixels.size();
  int sel = id*3+pow(d*3,1.1)/10;
  R+=(pixels[sel]-R)/1;
  G+=(pixels[sel+1]-G)/1;
  B+=(pixels[sel+2]-B)/1;
}

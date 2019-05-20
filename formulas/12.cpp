int id = (y*width+x)*3;
int mm = (height*width+width)*3;
int matix[20] = {1,1,1,1,1,1,1,1,1,1,4,5,6,1,1,1,1,1,7,13};
int sel = (frameCount+x+y)%20;
float dist = sqrt(((width/2)-x)*(width/2-x)+(height/2-y)*(height/2-y));

if(frameCount==1){
  R=rand()%max;
  G=rand()%max;
  B=rand()%max;
}

R+=(pixels[(id+((x+matix[sel])%width))]-R)/1000.1*dist;
G+=(pixels[(id+((x+matix[sel])%height))]-G)/1000.2*dist;
B+=(pixels[(id+((x+matix[sel])%height))]-B)/1000.2*dist;


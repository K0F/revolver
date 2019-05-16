int id = (y*width+x)*3;
int mm = (height*width+width)*3;
int matix[20] {1,1,1,1,1,1,1,1,1,1,4,5,6,1,1,1,1,1,7,13};
int sel = (frameCount+x+y)%20;
float dist = sqrt(x*x+y*y);
R+=x;
G+=y;
B+=x+y;

R+=(pixels[(id+((x+matix[sel])%width))]-R)/1000.1*dist;
G+=(pixels[(id+((y+matix[sel])%height))]-G)/1000.2*dist;
B+=(pixels[(id+matix[sel])%mm]-B)/1000.3*dist;



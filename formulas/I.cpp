int mm = width*height;

//if(frameCount==0){
  R+=100;
  G+=100;
  B+=100;
//}

R+=(pixels[(((y*width+x)+1)%mm)*1]+10-R)/10.0;
G+=(pixels[(((y*width+x)+1)%(mm*2))*2]+10-G)/10.0;
B+=(pixels[(((y*width+x)+1)%(mm*3))*3]+10-B)/10.0;

R+=(oR*sqrt(oG)-R)/2501.0;
G+=(oG*sqrt(oB)-G)/2502.0;
B+=(oB*sqrt(oR)-B)/2503.0;

if(R+G+B>100){
R*=0.98;
G*=0.98;
B*=0.98;
}

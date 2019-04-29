
for(float ii = 0 ; ii< 10;ii+=1){
  R+=((sin(frameCount/(sin(x/ii/100.0*TWO_PI)+2.0))+1.0)*(max/2.0)-R)/10.0;
  G+=((sin(frameCount/(sin(x/ii/100.01*TWO_PI)+2.0))+1.0)*(max/2.0)-G)/10.0;
  B+=((sin(frameCount/(sin(x/ii/100.02*TWO_PI)+2.0))+1.0)*(max/2.0)-B)/10.0;
}

float dd = sqrt((width/2-x)*(width/2-x)+(height/2-y)*(height/2-y));
float dis = ((x-frameCount)^y<<frameCount&0xFFFF|y);
float speed = 121.3/240.0*TWO_PI/25.0*dis/1000.0;
//*((width/2-x)/100.0;
    //+sin((height/2-y)/100.0*TWO_PI));
R=((sin(frameCount*speed)+1.0)*max/2.0);
G=((sin(frameCount*speed)+1.0)*max/2.0);
B=((sin(frameCount*speed)+1.0)*max/2.0);

/*
if(R>512&&R<max-512)
R+=sin((oR-R)*TWO_PI)*512.0;
if(G>512&&G<max-512)
G+=sin((oG-G)*TWO_PI)*512.0;
if(B>512&&B<max-512)
B+=sin((oB-B)*TWO_PI)*512.0;
*/

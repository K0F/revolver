
float speed = 121.3 / 120.0 * frameCount * TWO_PI / 25.0;


int selX[10] = {1,1,1,1,1,1,1,1,1,70};
int selY[10] = {1,1,1,1,1,1,1,1,1,30};

int X = width/2-x;
int Y = height/2-y;
float dd = pow(sqrt(X*X+Y*Y),0.01)+1.0;
float d = atan2(X,Y)/100.0*sin(dd)+1.0;
float bright = (sin(speed/1.01*d)+1.0)/2.0;
R=(sin(speed*d)+1.0)/2.0*max*bright;
G=(sin(speed/15.01517*d)+1.0)/2.0*max*bright;
B=(sin(speed/30.03324*d)+1.0)/2.0*max*bright;


/*
if(R>512&&R<max-512)
G+=sin(oR-R)*256;

if(G>512&&G<max-512)
G+=sin(oG-G)*256;

if(B>512&&B<max-512)
G+=sin(oB-B)*256;
*/

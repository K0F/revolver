
  int X = width/2-x;
  int Y = height/2-y;
  double theta = sqrt(X*X+Y*Y+frameCount*frameCount+frameCount)+1;
  double at1 = atan2(Y,y);
  double at2 = atan2(X,x);


  int q;
  for(q=1;q<10;q++){
    R+=((sin(theta/2.1*at1*q)+1.0)*10000.0-R)/pow(theta,0.1*q);
    G+=((sin(theta/2.22*at1*q)+1.0)*10000.0-G)/pow(theta,0.11*q);
    B+=((sin(theta/2.33*at1*q)+1.0)*10000.0-B)/pow(theta,0.11*q);
  }

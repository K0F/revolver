
if(frameCount==0)
{
R=random()%max;
G=B=R;
}
int siz = pixels.size();
int sel = (frameCount-7+siz)%siz;
R+=(pixels[sel]-R)/10.0;
G+=(pixels[sel+1]-G)/10.0;
B+=(pixels[sel+2]-B)/10.0;

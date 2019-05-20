#!/bin/bash
#ffmpeg -f lavfi -i color=c=black:size=1998x1080:rate=25 -width 1998 -loop 1 -i kof19.svg -filter_complex "[0:v][1:v]overlay,fade=in:75:5,fade=out:175:5" -t 8 -c:v ffv1 -pix_fmt yuv444p16le -y kof19.mkv
cp no.svg tmp.svg
DATE=`date +%m/%d/%y`
echo $DATE
sed -i 's/replaceme/'"$1"'/g' tmp.svg
sed -i 's#datereplace#'$DATE'#g' tmp.svg
ffmpeg -f lavfi -i color=c=black:size=1920x1080:rate=25 -width 1920 -loop 1 -i tmp.svg -filter_complex "[0:v][1:v]overlay,fade=in:75:5,fade=out:175:5" -t 8 -c:v prores_ks -profile:v 3 -pix_fmt yuv422p10le -movflags +faststart -y "$1".mov
#echo "file kof19.mkv" > concat.txt
#echo "file no.mkv" >> concat.txt
#ffmpeg -f concat -i concat.txt -safe 0 -c:v copy -y "$1".mkv

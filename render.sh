#!/bin/bash
width=$2
height=$3
pushd ~/src/titler
./genTitle.sh "$1" $width $height
popd
mv ~/src/titler/"$1".mkv output/
echo file "$1".mov > output/concat.txt
echo file "$1"ren.mov >> output/concat.txt
./revolver -q 1 -i formulas/"$1".cpp -p yuv422p10le -s "$width"x"$height" -t 292 -o output/"$1"ren.mov
cd output
ffmpeg -f concat -safe 0 -i concat.txt -c:v copy -y "$1"complete.mov
ffmpeg -i "$1"complete.mkv -vf scale=1920:1 -c:v rawvideo -pix_fmt gray16le -f rawvideo - | ffmpeg -ar 48000 -f u16le -ac 1 -i - -c:a pcm_s16le -ar 48000 -ac 2 -y "$1".wav
sox "$1".wav "$1"_22hp.wav norm -3 highpass 22 gain -3 norm -3 dither
ffmpeg -i "$1"complete.mkv -i "$1"_22hp.wav -c:a copy -c:v copy -y "$1".mov
#rm "$1".mkv "$1"ren.mkv concat.txt
#rm "$1"complete.mkv "$1"_22hp.wav "$1".wav
#rm "$1"ren.mkv "$1"complete.mov "$1".wav "$1"_22hp.wav concat.txt
../encodeYT.sh "$1".mov

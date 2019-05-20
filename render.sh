#!/bin/bash
width=$2
height=$3
pushd titler
./genTitle.sh "$1" $width $height
popd
mv titler/"$1".mkv output/
echo file "$1".mkv > output/concat.txt
echo file "$1"ren.mkv >> output/concat.txt
./revolver -q 1 -i formulas/"$1".cpp -p yuv422p10le -s "$width"x"$height" -t 12 -o output/"$1"ren.mkv
cd output
ffmpeg -f concat -safe 0 -i concat.txt -c:v copy -y "$1"complete.mkv
ffmpeg -i "$1"complete.mkv -vf scale=1920:1 -c:v rawvideo -pix_fmt gray16le -f rawvideo - | ffmpeg -ar 48000 -f u16le -ac 1 -i - -c:a pcm_s16le -ar 48000 -ac 2 -y "$1".wav
sox "$1".wav "$1"_22hp.wav norm -3 highpass 22 gain -3 norm -3 dither
ffmpeg -i "$1"complete.mkv -i "$1"_22hp.wav -c:a copy -c:v copy -y "$1".mkv
#rm "$1".mkv "$1"ren.mkv concat.txt
#rm "$1"complete.mkv "$1"_22hp.wav "$1".wav
rm "$1"ren.mkv "$1"complete.mkv "$1".wav "$1"_22hp.wav concat.txt
../encodeYT.sh "$1".mkv

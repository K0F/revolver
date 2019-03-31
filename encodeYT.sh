#!/bin/bash
ffmpeg -i "$1" -c:v libx264 -preset slow -profile:v high10 -crf 18 -coder 1 -pix_fmt yuv420p10le -movflags +faststart -g 12 -bf 2 -c:a aac -b:a 384k -profile:a aac_low -y `basename -s .mkv "$1"`.mp4

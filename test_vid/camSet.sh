#!/bin/sh

v4l2-ctl --set-ctrl=brightness=5

v4l2-ctl --set-ctrl=contrast=100

v4l2-ctl --set-ctrl=saturation=0

v4l2-ctl -d /dev/video0 -p 120


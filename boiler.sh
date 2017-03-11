#!/bin/bash

# run test_vids on all the boiler images

for fid in images/boiler/*.jpg 
do
		echo 
		echo $fid
		test_vid/build/Vision -p -m $fid 
done
					 

# ImageProcessingProject
Open both videos and process the frames:

- Copy the foreground objects to the other video. (combined)
- Smooth the edges of the objects. 
- create a copy of the combined image (dest).        
- smooth the whole combined image (smoothed).
- create a mask of the objects (black and white, white pixeles belongs to the objects)
- dilate the mask (mask_bigger)
- erode the mask (mask_smaller)
- subtract the mask_smaller from the mask_bigger (edges_mask)
- copy the pixels under the edges_mask from the smoothed image to the dest image (e.g.: copyTo)
- Show the result and wait some milliseconds.

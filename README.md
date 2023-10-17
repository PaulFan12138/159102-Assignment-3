# 159102-Assignment-3

1. **pixel_class**: This is a custom class used to represent pixels in images. It contains the color values for the red (R), green (G), and blue (B) channels of the pixel, as well as a boolean `exclude` attribute that marks whether the pixel needs to be checked.

2. **loadButtons function**: This function is used to load image data from the PPM image file named "Buttons.ppm" and fill it into the `picture` array. It reads the header information and pixel data of the file and stores them in the corresponding location in the `picture` array. At the same time, it initializes the `exclude` property to `false`.

3. **main function**: The main function of the program, which includes the following steps:
    - Call the `loadButtons` function to load image data.
    - Loop through each pixel of the image, obtain the red channel value of the pixel through `picture[x][y].getR()` and obtain the value of the `exclude` attribute through `picture[x][y].getexclude()` .
    - Based on specific conditions (gray value greater than 128 and `exclude` is `false`), call the `CheckPixel` function to identify potential patterns or objects, and use `total` to count the number of relevant pixels.
    - Based on the value of `total`, call the `DrawBox` function to draw a rectangular box. If `total` is less than 7800, draw a red box, otherwise draw a green box.
    - Finally, output the processed image data as a new PPM image file "NewButtons.ppm".

4. **CheckPixel Function**: This function is used to recursively check the pixels associated with possible patterns and find the boundaries of the pattern. It continuously expands into adjacent pixels, labeling and determining the shape of the pattern. If the grayscale value of a pixel is less than or equal to 128 or the `exclude` attribute is `true`, the pixel will no longer be processed.

5. **DrawBox function**: This function is used to draw a colored rectangular box. The boundary of the box is determined by the `CheckPixel` function. It modifies the color values and `exclude` properties of pixels in the image to label pixels within a rectangular box.

In summary, the purpose of this program is to process the loaded image, identify possible patterns or objects, visualize them with rectangular boxes, and then save the processed image data as a new PPM file. This program involves image processing, file manipulation, and the use of recursive functions.

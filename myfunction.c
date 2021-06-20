// 311408264 Shlomi Ben-Shushan

#include <stdbool.h>

// Define "short" functions at preprocessor stage to save time.
#define min(a, b) (a < b ? a : b)	// Moved min function to preprocessor.
#define max(a, b) (a > b ? a : b)	// Same for max function.
#define getWeight(p) ((int) p.red + (int) p.green + (int) p.blue)
#define effiMult9(n) ((n << 3) + n)	// Multiply by 9 with shifts.

// This struct defines a pixel (I found pixel_sum struct unnecessary).
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

/******************************************************************************
* Function: setBlur
* Input: image's dimension, pointer pix, pointer src and index i.
* Output: void, but it changes pix's values.
* Description:	This function apply Blur-kernel on a specific pixel. It gets a
*				pointer (pix) to the pixel, and by using src array and index i,
*				it finds the values of the pixels around it to calculate the
*				values to be set as red, green and blue of the specific pixel.
******************************************************************************/
void setBlur(size_t n, pixel *pix, pixel *src, register int i) {

    // Set 9 pixels using given src array.
    // I found it more efficient to assign the values this way.
    pixel p11 = src[i - n - 1];
    pixel p12 = src[i - n];
    pixel p13 = src[i - n + 1];
    pixel p21 = src[i - 1];
    pixel p22 = src[i];
    pixel p23 = src[i + 1];
    pixel p31 = src[i + n - 1];
    pixel p32 = src[i + n];
    pixel p33 = src[i + n + 1];

    // Color assignments to sum is done by using only "+" because it is faster
    // than using "*". Moreover, in Blue-Kernel all weights are 1 so it is enough
    // to compute this way.

    // Assign red.
    int red =   (int) p11.red + (int) p12.red + (int) p13.red +
                (int) p21.red + (int) p22.red + (int) p23.red +
                (int) p31.red + (int) p32.red + (int) p33.red;
                
    // Assign green.
    int green = (int) p11.green + (int) p12.green + (int) p13.green +
                (int) p21.green + (int) p22.green + (int) p23.green +
                (int) p31.green + (int) p32.green + (int) p33.green;

    // Assign blue.
    int blue =  (int) p11.blue + (int) p12.blue + (int) p13.blue +
                (int) p21.blue + (int) p22.blue + (int) p23.blue +
                (int) p31.blue + (int) p32.blue + (int) p33.blue;

    // Divide each color by 9 and assign it to pixel.
    pix->red = (unsigned char) (red / 9);
    pix->green = (unsigned char) (green / 9);
    pix->blue = (unsigned char) (blue / 9);

}

/******************************************************************************
* Function: setFilter
* Input: image's dimension, pointer pix, pointer src and index i.
* Output: void, but it changes pix's values.
* Description:	This function works in a similiar way to setBlur(), but its
*				also finds a lightest and heaviest pixels out of the 9 pixels
*				under the kernel, and subrtact their values from the sum of the
*				red, green and blue of the examine pixel. Also the division in
*				the end is by 7 and not 9.
******************************************************************************/
void setFilter(size_t n, pixel *pix, pixel *src, register int i) {

    // Efficiently assign pixels.
    pixel p11 = src[i - n - 1];
    pixel p12 = src[i - n];
    pixel p13 = src[i - n + 1];
    pixel p21 = src[i - 1];
    pixel p22 = src[i];
    pixel p23 = src[i + 1];
    pixel p31 = src[i + n - 1];
    pixel p32 = src[i + n];
    pixel p33 = src[i + n + 1];

    // Find the heaviest and lightest pixels. Tried to avoid loop.
    pixel light = p11;
    pixel heavy = p11;
    int weight = getWeight(p11);
    int min_intensity = weight;
    int max_intensity = weight;
    weight = getWeight(p12);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p12;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p12;
    }
    weight = getWeight(p13);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p13;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p13;
    }
    weight = getWeight(p21);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p21;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p21;
    }
    weight = getWeight(p22);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p22;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p22;
    }
    weight = getWeight(p23);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p23;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p23;
    }
    weight = getWeight(p31);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p31;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p31;
    }
    weight = getWeight(p32);
    if (weight <= min_intensity) {
        min_intensity = weight;
        light = p32;
    }
    if (weight > max_intensity) {
        max_intensity = weight;
        heavy = p32;
    }
    weight = getWeight(p33);
    if (weight <= min_intensity) {
        light = p33;
    }
    if (weight > max_intensity) {
        heavy = p33;
    }

    // Note that in this function, filter is applied by subtract the values of
    // the light and heavy pixels from the sum.

    // Assign red.
    int red =   (int) p11.red + (int) p12.red + (int) p13.red +
                (int) p21.red + (int) p22.red + (int) p23.red +
                (int) p31.red + (int) p32.red + (int) p33.red -
                (int) heavy.red - (int) light.red;

    // Assign green.
    int green = (int) p11.green + (int) p12.green + (int) p13.green +
                (int) p21.green + (int) p22.green + (int) p23.green +
                (int) p31.green + (int) p32.green + (int) p33.green -
                (int) heavy.green - (int) light.green;

    // Assign blue.
    int blue =  (int) p11.blue + (int) p12.blue + (int) p13.blue +
                (int) p21.blue + (int) p22.blue + (int) p23.blue +
                (int) p31.blue + (int) p32.blue + (int) p33.blue -
                (int) heavy.blue - (int) light.blue;

    // Divide each color by 7 and ssign it to pixel.
    pix->red = (unsigned char) (red / 7);
    pix->green = (unsigned char) (green / 7);
    pix->blue = (unsigned char) (blue / 7);

}

/******************************************************************************
* Function: setSharp
* Input: image's dimension, pointer pix, pointer src and index i.
* Output: void, but it changes pix's values.
* Description:	this function works in a similiar way to setBlur() and
*				setFilter(), but it apply Sharp-Kernel.
******************************************************************************/
void setSharp(size_t n, pixel *pix, pixel *src, register int i) {

    // Efficiently assign pixels.
    pixel p11 = src[i - n - 1];
    pixel p12 = src[i - n];
    pixel p13 = src[i - n + 1];
    pixel p21 = src[i - 1];
    pixel p22 = src[i];
    pixel p23 = src[i + 1];
    pixel p31 = src[i + n - 1];
    pixel p32 = src[i + n];
    pixel p33 = src[i + n + 1];

    // According to Sharp-Kernel, the middle pixel have to be multiplied by 9.
    // This multiplication is efficiently done for each color, by using the
    // function effiMult9() which uses shits instead of "*".

    // Assign red.
    int red =   (int) p11.red + (int) p12.red + (int) p13.red +
                (int) p21.red - effiMult9((int) p22.red) + (int) p23.red +
                (int) p31.red + (int) p32.red + (int) p33.red;

    // Assign green.
    int green = (int) p11.green + (int) p12.green + (int) p13.green +
                (int) p21.green - effiMult9((int) p22.green) + (int) p23.green +
                (int) p31.green + (int) p32.green + (int) p33.green;

    // Assign blue.
    int blue =  (int) p11.blue + (int) p12.blue + (int) p13.blue +
                (int) p21.blue - effiMult9((int) p22.blue) + (int) p23.blue +
                (int) p31.blue + (int) p32.blue + (int) p33.blue;

    // Negate all numbers (not bitwisely) and limit them to match the Sharp-Kernel.
    pix->red = (unsigned char) min(max(0 - red, 0), 255);
    pix->green = (unsigned char) min(max(0 - green, 0), 255);
    pix->blue = (unsigned char) min(max(0 - blue, 0), 255);

}

/******************************************************************************
* Function: doConvolution
* Input: pointer to the pixelsImg and backupOrg arrays, and editor function.
* Output: void, but it changes the image.
* Description: I have merged doConvulation(), smooth() and applyKernel()
*              functions to one function that do the job efficiently by
*              iterating the image (pixelImg array) and call the relevant edit
*              function for each pixel. The function gets a pointer to an
*              editor function - setBlur(), setFilter() or setSharp() - and use
*              it to change pixel's values. I found some arguments unnecessary
*              so I removed them and now this function only gets a pointers to
*              the arrays and to the editor function.
*              Generally, I can say I tried to maintain Seperation-of-Concerns
*              idea, I used code-motion, loop-unrolling, pointers instead of
*              values, avoid expensive operations like "*" and removed
*              unnecessary or unefficient functions. In addition, I'll note
*              that I have violated the open-close principle in favor of
*              optimizations. For example, I assumed that only blur and sharp
*              kernel exists, so the functions I wrote are relevant only to
*              these kernels.
******************************************************************************/
void doConvolution(pixel* pixelsImg, pixel* backupOrg, void (*edit)()) {
    register int i, j, k;	// register indexes might be faster than regular ones.
    int temp = 1, limit = n - 1; 
    for (i = 1; i < limit; ++i) {
        temp += n;
        k = temp;
        for (j = 1; j < limit; ++j, ++k) {
            edit(n, &pixelsImg[k], backupOrg, k);	// different function for different operation.
        }
    }
}

/******************************************************************************
* Function: myfunction
* Input: necessary pointers, strings and filter flag.
* Output: void, but it changes the image.
* Description: entry point of the algorithm.
******************************************************************************/
void myfunction(Image* image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {

    // I didn't use the kernels as arrays, instead I made specific function
    // for each kernel. It might violate the open-closed principle, but I
    // found it more efficient and that is the focus of the exercise.
    // int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    // int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};
    
    // Took the size calculation outside doConvulation to save time.
    size_t size = m * n;		// Couldn't avoid this mult.
    size = size + size + size;	// size = 3*m*n.
    
    // Moved pixelsImg and backupOrg to myfunction to avoid reassignments.
    pixel* pixelsImg = (pixel*) image->data;	// Avoid another malloc.
    pixel* backupOrg = malloc(size);			// Use size to avoid recalculations.
    
    // memcpy is an efficient function that can replace opriginal copyPixels().
    // I moved it here from doConvulation to avoid passing size variable.

    if (flag == '1') {
        // blur image
        memcpy(backupOrg, pixelsImg, size);
        doConvolution(pixelsImg, backupOrg, &setBlur);

        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);

        // sharpen the resulting image
        memcpy(backupOrg, pixelsImg, size);
        doConvolution(pixelsImg, backupOrg, &setSharp);

        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);
    } else {
        // apply extermum filtered kernel to blur image
        memcpy(backupOrg, pixelsImg, size);
        doConvolution(pixelsImg, backupOrg, &setFilter);

        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);

        // sharpen the resulting image
        memcpy(backupOrg, pixelsImg, size);
        doConvolution(pixelsImg, backupOrg, &setSharp);

        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
        
    // Free allocated memory.
    free(backupOrg);

}


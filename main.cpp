
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <iostream>
#include <vector>
#include <cstring>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

void savePNG(XImage *image, int w, int h, const std::string & filename)
{
    std::vector<uint8_t> raw_image;
    std::cout << "create screenshot " << filename << " (" << w << "," << h << ")" << std::endl;
   
    for (auto y = 0; y <h  ; y++)
        for (auto x = 0; x < w ; x++)
        {    
            auto pixel = XGetPixel(image,x,y);
            raw_image.push_back(pixel );
            raw_image.push_back(pixel >> 8);
            raw_image.push_back(pixel >> 16);
        }    
    stbi_write_png("test.png",w,h, 3, &raw_image[0], w * 3);
}

int main(int argc, char **argv)
{
 
    if(argc < 2)
    { 
        std::cout << "usage: " << argv[0] << " shot_name" << std::endl;
        exit(-1);
    }    
    
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attr;

    XGetWindowAttributes(display, root, &attr);
   
    XImage *image = XGetImage(display,root, 0,0 , attr.width,attr.height, AllPlanes, ZPixmap);
    savePNG(image, attr.width, attr.height, std::string(argv[1]) +".png");
  
   return 0;
}
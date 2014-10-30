
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

typedef struct
{
    uint8_t  identsize;            // size of ID field that follows 18 uint8_theader (0 usually)
    uint8_t  colourmaptype;        // type of colour map 0=none, 1=has palette
    uint8_t  imagetype;            // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
    uint8_t  colormap[5];
    uint16_t xstart;               // x origin
    uint16_t ystart;               // y origin
    uint16_t width;                // width in pixels
    uint16_t height;               // height in pixels
    uint8_t  bits;                 // bits per pixel 8,16,24,32
    uint8_t  descriptor;           // descriptor bits (vh flip bits)
} TGAheader;


void saveTGA(XImage *image, int w, int h, const std::string & filename)
{
    TGAheader hdr;
    std::memset(&hdr,0, sizeof(hdr));
    std::vector<uint8_t> raw_image;
   
    std::cout << "create screenshot " << filename << " (" << w << "," << h << ")" << std::endl;
   
    for (auto y = h-1; y >= 0; y--)
        for (auto x = 0; x < w ; x++)
        {    
            auto pixel = XGetPixel(image,x,y);
            raw_image.push_back(pixel );
            raw_image.push_back(pixel >> 8);
            raw_image.push_back(pixel >> 16);
           // raw_image.push_back(255);
        }    

    hdr.imagetype = 2;
    hdr.width  = w;
    hdr.height = h;
    hdr.bits = 24;
    
    std::ofstream stream;
    stream.open(filename, std::ios::out | std::ios::binary);
    stream.write(reinterpret_cast<char *>(&hdr), sizeof(hdr));
    stream.write(reinterpret_cast<char *>(&raw_image[0]),raw_image.size());
    stream.close();
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
    saveTGA(image, attr.width, attr.height, std::string(argv[1]) +".tga");
  
   return 0;
}
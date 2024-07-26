#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <fstream>
#include "xwindow.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height} {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[7][20]={"white", "black", "red", "green", "blue", "rgb:ef/ef/d2", "rgb:77/97/56"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 7; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[BLACK]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[BLACK]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawImage(int x, int y, std::string file) {
	// Read the image details from the requested file
	ifstream input(file.c_str(), ios::binary);
	int width, height, screen = DefaultScreen(d), sz = sizeof(int);
	input.read(reinterpret_cast<char*>(&width), sz);
	input.read(reinterpret_cast<char*>(&height), sz);
	char *png = new char[width * height * sz];
	input.read(png, width * height * sz);

	// Draw the image to the requested position
	XImage* xim = XCreateImage(
		d, DefaultVisual(d,screen), DefaultDepth(d,screen),
		ZPixmap, 0, reinterpret_cast<char*>(png), width, height, 32, 0
	);
	XPutImage(d, w, gc, xim, 0, 0, x, y, xim->width, xim->height);
	XDestroyImage(xim);
}

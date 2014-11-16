/********************
Sept. 2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
creative commons license 3.0: Attribution-ShareAlike CC BY-SA
This software is furnished "as is", without technical support, and with no 
warranty, express or implied, as to its usefulness for any purpose.

Thread Safe: No
Extensible: Yes

Use graphics screens (adafruit library based) as menu output
www.r-site.net
***/
#ifndef RSITE_ARDUINOP_MENU_GFX
	#define RSITE_ARDUINOP_MENU_GFX
	#include <Adafruit_GFX.h>
	#include "menu.h"

	#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

	// Color definitions RGB565
	#define BLACK 0x0000
	#define BLUE 0x001F
	#define RED 0xF800
	#define GREEN 0x07E0
	#define GRAY RGB565(128,128,128)
	#define SILVER RGB565(200,200,200)
	#define CYAN 0x07FF
	#define MAGENTA 0xF81F
	#define YELLOW 0xFFE0 
	#define WHITE 0xFFFF

  class menuGFX:public menuOut {
    public:
  	uint16_t hiliteColor=BLUE;
  	uint16_t bgColor=SILVER;
  	uint16_t enabledColor=WHITE;
  	uint16_t disabledColor=RED;
    Adafruit_GFX& gfx;
    menuGFX(
    	Adafruit_GFX& gfx,
    	uint16_t hiliteColor=BLUE,
    	uint16_t bgColor=BLACK,
    	uint16_t enabledColor=WHITE,
    	uint16_t disabledColor=SILVER,
    	int resX=5,
    	int resY=8
    )
	  	:gfx(gfx),
	  	bgColor(bgColor),
	  	enabledColor(enabledColor),
	  	disabledColor(disabledColor),
	  	hiliteColor(hiliteColor),
	  	menuOut(gfx.width()/resX,gfx.height()/resY,resX,resY) {}
	  	
    virtual void clear() {
    	//gfx.fillScreen(bgColor);
    	Serial<<"max:"<<maxX<<","<<maxY<<endl
    		<<"res:"<<resX<<","<<resY<<endl;
    	gfx.fillRect(0,0,resX*maxX,resY*maxY,bgColor);
    	gfx.setCursor(0,0);
    }
    virtual void setCursor(int x,int y) {gfx.setCursor(x*resX,y*resY);}
    virtual void print(char ch) {gfx.print(ch);}
    virtual void print(const char *text) {gfx.print(text);}
    virtual void println(const char *text="") {gfx.println(text);};
    virtual void print(int i) {gfx.print(i);};
    virtual void println(int i) {gfx.println(i);};
    virtual void print(double i) {gfx.print(i);};
    virtual void println(double i) {gfx.println(i);};
    virtual void print(prompt &o,bool selected,int idx,int posY,int width) {
    	Serial<<"menuGFX printing prompt "<<o.text<<endl;
    	gfx.fillRect(0,posY*resY,width*resX,resY,selected?hiliteColor:bgColor);
    	gfx.setTextColor(o.enabled?enabledColor:disabledColor);
    	gfx.setCursor(0,posY*resY);
    	o.printTo(gfx);
    	//println();
    }
    /*virtual void print(menuField &o,bool selected,int idx,int posY,int width) {
			p.print(text);
			p.print(activeNode==this?(tunning?'>':':'):' ');
			p.print(value);
			p.print(" ");
			p.print(units);
			p.print("  ");
    }*/
    /*drawStyle getStyle(prompt& p,bool selected,bool editing=false) {
    	if (p.enabled)
    		return selected?SELECTED:NORMAL;
    	else return DISABLED;
    }*/
		virtual void printMenu(menu& m,bool drawExit) {
			if (drawn!=&m) clear();//clear all screen when changing menu
			if (m.sel-top>=maxY) top=m.sel-maxY+1;//selected option outside device (bottom)
			else if (m.sel<top) top=m.sel;//selected option outside device (top)
			int i=top;for(;i<m.sz;i++) {
				//if ((i>=top)&&((i-top)<maxY)) {
				  if(i-top>=maxY) break;
				  if (needRedraw(m,i)) {
				  	print(*m.data[i],i==m.sel,i+1,i-top,m.width);
				  }
				//}
			}
			if (drawExit&&i-top<maxY&&needRedraw(m,i))
				print(menu::exitOption,m.sel==m.sz,0,i-top,m.width);
			lastTop=top;
			lastSel=m.sel;
			drawn=&m;
		}
  };
#endif RSITE_ARDUINOP_MENU_LCD

/**
 * Resources.h
 * emptyExample
 *
 * Created by Marek Bereza on 29/06/2011.
 *
 */
#pragma once
#include "ofMain.h"


#include <map>
#define DEFAULT_FONT "res/mono0755.ttf"
#define DEFAULT_FONT_SIZE 6


namespace xmlgui {
	class Control;
	class Resources {
	public:
		
		static void setCustomFont(string path, int size);
		
		
		// when you draw a string, it doesn't draw it immediately
		// unless you call "drawStringImmediate", or you're using bitmap font.
		// it draws them at the end of the draw loop all together.
		// you need to pass in the object calling this, so we can calculate
		// the absolute position on the screen.
		static void drawString(xmlgui::Control *caller, string str, int x, int y, ofFloatColor color = ofFloatColor(1.f,1.f,1.f,1.f));
		
		
		// draws the text immediately, slow!
		static void drawString(string str, int x, int y);


		static ofImage *getImage(string path);
		static void bindFont();
		static void unbindFont();
		
		static void drawVerticalStripes(const ofRectangle &r);
		static void drawDiagonalStripes(const ofRectangle &r);
		
		static void drawAllDeferredStrings();
		static ofTrueTypeFont *getFont();
		static int getFontCharWidth();
		static int stringWidth(const string &s);
	private:
		static ofTrueTypeFont *font;
		static bool customFontNotAvailable;
		static map<string,ofImage*> images;
		static void checkFontLoaded();
		static string fontPath;
		static int fontSize;
		
	};
};

/**
 * RootContainer.h
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#pragma once


#include "xmlgui/framework/Container.h"

namespace xmlgui {
	class ofGuiEventDispatcher {
	public:
		ofGuiEventDispatcher();
		void setup(xmlgui::Container *root, int prio = OF_EVENT_ORDER_AFTER_APP);
		
		void enableEvents();
		void disableEvents();
		
		void enableInteraction();
		void disableInteraction();
		
		bool isEnabled();
		void setEnabled(bool enabled);
		
		void setManualDraw(bool manualDraw);

		void draw(ofEventArgs &e);	
		
		bool mousePressed(ofMouseEventArgs &e);
		void mouseMoved(ofMouseEventArgs &e);
		bool mouseDragged(ofMouseEventArgs &e);
		bool mouseReleased(ofMouseEventArgs &e);
		
		bool keyPressed(ofKeyEventArgs &e);
		bool keyReleased(ofKeyEventArgs &e);
		
		bool touchDown(ofTouchEventArgs &e);
		bool touchMoved(ofTouchEventArgs &e);
		bool touchUp(ofTouchEventArgs &e);
	private:
		xmlgui::Container *root;
		bool enabled;
		bool manualDraw;
		int priority;

	};
};

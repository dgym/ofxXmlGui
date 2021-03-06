
/*
 *  Graph.h
 *  Gui
 *
 *  Created by Marek Bereza on 12/06/2013.
 *
 */

#pragma once

#include "xmlgui/framework/Control.h"
namespace xmlgui {
	class Graph: public LabeledControl {
	public:


		float minValue;
		float maxValue;
		int updateCounter;
		int updatePeriod;
		bool autoAdjustBounds;
		Graph(): LabeledControl() {
			value = new float[1];
			minValue = 0;
			maxValue = 1;
			height = 40;
			width = 200;
			updateCounter = 0;
			updatePeriod =1;
			autoAdjustBounds = true;
		}
		deque<float> history;



		void draw() {
			updateCounter++;
			if(updateCounter%updatePeriod==0) history.push_front(fval(value));

			if(autoAdjustBounds) {
				if(fval(value)>maxValue) {
					maxValue = fval(value);
				} else if(fval(value)<minValue) {
					minValue = fval(value);
				}
			}

			while(history.size()>width) history.pop_back();
			ofSetColor(50, 50, 50);
			ofDrawRectangle(x, y, width, height);
			ofSetColor(255, 255, 255);
			//glBegin(GL_LINE_STRIP);
			ofNoFill();
			ofBeginShape();
			int i = 0;
			glColor4f(1,1,1,1);
			deque<float>::iterator it = history.begin();
			for(; it != history.end(); it++) {
				ofVertex(x+i,
				  ofMap((*it), minValue, maxValue, y+height, y));

				i++;
			}
			//glEnd();
			ofEndShape();
			ofFill();
			string lab = name + "  " + ofToString(fval(value), 3);
			drawCustomLabel(lab, x, y-3);

		}
	};
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bool succ = true;
	succ = image.load("stars.png");
	if (!succ) {
		cerr << "loading image failed ...\n";
	}
	image.resize(200, 200);
	mesh.setMode(OF_PRIMITIVE_LINES);
	
	float intensityThreshold = 150.0;
	int w = image.getWidth();
	int h = image.getHeight();
	for (int x=0; x<w; ++x) {
		for (int y=0; y<h; ++y) {
			ofColor c = image.getColor(x, y);
			float intensity = c.getLightness();
			if (intensity >= intensityThreshold) {
				// We shrunk our image by a factor of 4, so we need to multiply our pixel
				// locations by 4 in order to have our mesh cover the openFrameworks window
				ofVec3f pos(x*4, y*4, 0.0);
				mesh.addVertex(pos);
				mesh.addColor(c);
			}
		}
	}
	
	float connectionDistance = 30;
	int numVerts = mesh.getNumVertices();
	for (int a=0; a<numVerts; ++a) {
		ofVec3f verta = mesh.getVertex(a);
		for (int b=a+1; b<numVerts; ++b) {
			ofVec3f vertb = mesh.getVertex(b);
			float distance = verta.distance(vertb);
			if (distance <= connectionDistance) {
				mesh.addIndex(a);
				mesh.addIndex(b);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor centerColor = ofColor(85, 78, 68);
	ofColor edgeColor(0, 0, 0);
	ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
	mesh.draw();
}

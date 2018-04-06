#pragma once
#include "ofMain.h"
#include "opencv2/opencv.hpp"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	// Make Method
	void draw_clock(ofPoint point, int frame_number);

	// Make Member
	ofFbo fbo;

	cv::VideoCapture cap;
	cv::Size cap_size;
	vector<cv::Mat> frames;

	cv::Mat blend_frame;
	ofImage blend_image;
};
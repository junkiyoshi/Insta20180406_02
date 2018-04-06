#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	this->cap.open("D:\\video\\image13.mp4");
	this->cap_size = cv::Size(256, 144);

	while (true) {

		cv::Mat src, mini_src;
		this->cap >> src;
		if (src.empty()) {

			break;
		}
		cv::resize(src, mini_src, this->cap_size);
		cv::cvtColor(mini_src, mini_src, CV_RGB2BGR);

		this->frames.push_back(mini_src);
	}

	this->blend_image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	this->blend_frame = cv::Mat(this->blend_image.getHeight(), this->blend_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->blend_image.getPixels().getNumChannels()), this->blend_image.getPixels().getData(), 0);
}

//--------------------------------------------------------------
void ofApp::update() {

	cv::Rect rect;
	rect.width = this->cap_size.width;
	rect.height = this->cap_size.height;
	for (int x = 0; x < this->blend_image.getWidth(); x += rect.width) {
		
		for (int y = 0; y < this->blend_image.getHeight(); y += rect.height) {

			rect.x = x;
			rect.y = y;

			float noise_value = ofNoise(x * 0.005, y * 0.005, ofGetFrameNum() * 0.001);
			int frame_number = noise_value * this->frames.size();

			cv::Mat roi(this->blend_frame, rect);
			this->frames[frame_number].copyTo(roi);
		}
	}

	this->blend_image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	this->blend_image.draw(0, 0);

	ofSetColor(239, 239);
	for (int x = 0; x < this->blend_image.getWidth(); x += this->cap_size.width) {

		for (int y = 0; y < this->blend_image.getHeight(); y += this->cap_size.height) {

			float noise_value = ofNoise(x * 0.005, y * 0.005, ofGetFrameNum() * 0.001);
			int frame_number = noise_value * this->frames.size();

			this->draw_clock(ofPoint(x + this->cap_size.width / 2, y + this->cap_size.height / 2), frame_number);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_clock(ofPoint point, int frame_number) {

	int radius = 60;

	int minute = ofMap(frame_number, 0, this->frames.size() - 1, 0, 720);
	int time = minute / 60;
	minute = minute - time * 60;
	int time_deg = time * 30 + ofMap(minute, 0, 59, 0, 30);
	int minute_deg = minute * 6;

	ofPushMatrix();
	ofTranslate(point);
	ofRotate(-45);

	ofSetLineWidth(3);
	ofNoFill();

	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 1) {

		ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
	}
	ofEndShape(true);

	ofSetLineWidth(5);
	ofDrawLine(ofPoint(), ofPoint(radius * 0.6 * cos(time_deg * DEG_TO_RAD), radius * 0.6 * sin(time_deg * DEG_TO_RAD)));

	ofSetLineWidth(3);
	ofDrawLine(ofPoint(), ofPoint(radius * 0.8 * cos(minute_deg * DEG_TO_RAD), radius * 0.8 * sin(minute_deg * DEG_TO_RAD)));

	ofFill();
	ofDrawCircle(ofPoint(), 5);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
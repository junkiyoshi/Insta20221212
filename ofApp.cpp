#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto span = 40;
	auto radius = span * 0.5;
	for (int x = span * -8; x <= span * 8; x += span) {

		for (int y = span * -8; y <= span * 8; y += span) {

			if (x == 0 && y == 0) { continue; }

			auto noise_param = abs(x) > abs(y) ? abs(x) : abs(y);
			auto noise_value = ofNoise(noise_param * 0.0035, ofGetFrameNum() * 0.005);
			auto deg_start = 0;

			if (noise_value < 0.2) { deg_start = 0; }
			else if (noise_value < 0.25) { deg_start = ofMap(noise_value, 0.2, 0.25, 0, 90); }
			else if (noise_value < 0.45) { deg_start = 90; }
			else if (noise_value < 0.50) { deg_start = ofMap(noise_value, 0.45, 0.50, 90, 180); }
			else if (noise_value < 0.70) { deg_start = 180; }
			else if (noise_value < 0.75) { deg_start = ofMap(noise_value, 0.7, 0.75, 180, 270); }
			else if (noise_value < 0.95) { deg_start = 270; }
			else if (noise_value < 1.0) { ofMap(noise_value, 0.95, 1.0, 270, 360); }

			deg_start += 180 + atan2(-y, -x) * RAD_TO_DEG;

			ofNoFill();
			ofBeginShape();
			for (int deg = deg_start - 135; deg <= deg_start + 135; deg++) {

				ofVertex(x + radius * 0.8 * cos(deg * DEG_TO_RAD), y + radius * 0.8 * sin(deg * DEG_TO_RAD));
			}
			ofEndShape();

			ofFill();
			ofDrawCircle(glm::vec2(x + radius * 0.7 * cos((deg_start + 180) * DEG_TO_RAD), y + radius * 0.7 * sin((deg_start + 180) * DEG_TO_RAD)), 4);
			
		}
	}

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
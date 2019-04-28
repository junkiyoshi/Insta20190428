#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 180;
	int len = 150;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			ofPushMatrix();
			ofTranslate(x, y);

			vector<glm::vec2> right, left;
			for (auto param = 0; param <= 50; param++) {

				auto noise_value = ofNoise(x, y, param * 0.08, ofGetFrameNum() * 0.02);

				if (noise_value < 0.65) {

					right.push_back(this->make_point(len, param));
					left.push_back(this->make_point(len, 100 - param));
				}
				else {

					this->draw_shape(right, left);
				}
			}

			this->draw_shape(right, left);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
void ofApp::draw_shape(vector<glm::vec2>& param1 , vector<glm::vec2>& param2) {

	if (param1.size() > 0 && param2.size() > 0) {

		std::reverse(param2.begin(), param2.end());

		ofBeginShape();
		ofVertices(param1);
		ofVertices(param2);
		ofEndShape(true);

		param1.clear();
		param2.clear();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
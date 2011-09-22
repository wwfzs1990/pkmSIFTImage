/*
 *  Created by Parag K. Mital - http://pkmital.com 
 *  Contact: parag@pkmital.com
 *
 *  Copyright 2011 Parag K. Mital. All rights reserved.
 * 
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *	
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,	
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *	OTHER DEALINGS IN THE SOFTWARE.
 */

#include "testApp.h"

void testApp::closeApp()
{
    // deallocate	
	OF_EXIT_APP(0);
}

//--------------------------------------------------------------
void testApp::setup()
{
    videoReader = new ofVideoPlayer();
    if(!videoReader->loadMovie(ofToDataPath("target.mp4")))
    {
        printf("[ERROR] Movie file \"data\\target.mp4\" not found!\n");
        OF_EXIT_APP(0);
    }

	totalFrames             = videoReader->getTotalNumFrames();
	currentFrame            = 1;
    
    siftImage.allocate(videoReader->getWidth(), videoReader->getHeight());
    colorImg.allocate(videoReader->getWidth(), videoReader->getHeight());
    grayImg.allocate(videoReader->getWidth(), videoReader->getHeight());
    colorSiftImg.allocate(videoReader->getWidth(), videoReader->getHeight());
    
    //string output = ofToDataPath(string("out.mov"));
    //videoSaver.setup(videoReader->getWidth(), videoReader->getHeight(), output);
    //videoSaver.setCodecPhotoJpeg();
    
	ofSetVerticalSync(false);
	ofSetWindowShape(videoReader->getWidth()*2 + 80, videoReader->getHeight() + 80);
	ofSetFrameRate(30);
}


//--------------------------------------------------------------
void testApp::update(){
    if (currentFrame < totalFrames) {
        
        videoReader->setFrame(currentFrame);
        videoReader->update();
        
        colorImg.setFromPixels(videoReader->getPixels(), videoReader->getWidth(), videoReader->getHeight());
        grayImg = colorImg;
        siftImage.computeSIFTImage(grayImg.getPixels(), videoReader->getWidth(), videoReader->getHeight());
        
        // get reprojection for drawing
        colorSiftImg.setFromPixels(siftImage.getSIFTImageForDrawing(), videoReader->getWidth(), videoReader->getHeight());
        colorSiftImg.convertHsvToRgb();
        //colorSiftImg.scale(siftImage.stepSize, 1.0);
        colorSiftImgLab.flagImageChanged();
        
        currentFrame += 5;
    }
    else {
        OF_EXIT_APP(0);
    }

}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(0);
    colorImg.draw(20, 20);
    colorSiftImg.draw(60 + videoReader->getWidth(), 20);
    
	sprintf(buf, "fps: %02.2f", ofGetFrameRate());
	ofDrawBitmapString(buf, ofPoint(20,videoReader->getHeight() + 40));
	
	sprintf(buf, "frame: %d/%d", currentFrame, totalFrames);
	ofDrawBitmapString(buf, ofPoint(20,videoReader->getHeight() + 55));
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == 'n')
        currentFrame = totalFrames;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
    
}

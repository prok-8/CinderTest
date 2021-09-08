#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LearningProjApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void LearningProjApp::setup()
{
}

void LearningProjApp::mouseDown( MouseEvent event )
{
}

void LearningProjApp::update()
{
}

void LearningProjApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( LearningProjApp, RendererGl )

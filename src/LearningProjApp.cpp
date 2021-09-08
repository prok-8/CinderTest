#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Shape.h"

using namespace ci;
using namespace ci::app;

class LearningProjApp : public App {
public:
	LearningProjApp();
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void draw() override;

private:
	std::list<MovingCircle> mCircles;
	MovingCircle mDummyCircle;
	MovingCircle* mLastCircle;
};

void prepareSettings(LearningProjApp::Settings* settings)
{
	settings->setMultiTouchEnabled(false);
}

void LearningProjApp::mouseDown(MouseEvent event)
{
	if (event.isLeft()) {
		MovingCircle c;
		c.location = event.getPos();
		c.radius = randFloat(4.0f, 32.0f);
		c.color = Color(randFloat(), randFloat(), randFloat());
		c.direction = randVec2();
		c.velocity = randFloat(2.0f, 8.0f);
		mCircles.push_back(c);
		auto endItr = mCircles.end();
		--endItr;
		mLastCircle = &*endItr;
	}
	else if (event.isRight())
	{
		auto itr = mCircles.end();
		while (itr != mCircles.begin()) {
			--itr;
			if (itr->isInside(event.getPos()))
			{
				mCircles.erase(itr);
				if (mCircles.empty())
				{
					mLastCircle = &mDummyCircle;
				}
				else
				{
					itr = mCircles.end();
					--itr;
					mLastCircle = &*itr;
				}
				break;
			}
		}
	}
}

LearningProjApp::LearningProjApp()
	:mLastCircle(&mDummyCircle)
{
}

void LearningProjApp::keyDown(KeyEvent event)
{
	const int eventCode = event.getCode();

	switch (eventCode)
	{
	case KeyEvent::KEY_f:
		setFullScreen(!isFullScreen());
		break;
	case KeyEvent::KEY_SPACE:
		mCircles.clear();
		break;
	case KeyEvent::KEY_ESCAPE:
		if (isFullScreen())
			setFullScreen(false);
		else
			quit();
		break;
	case KeyEvent::KEY_w:
		mLastCircle->location.y -= 4.0f;
		break;
	case KeyEvent::KEY_s:
		mLastCircle->location.y += 4.0f;
		break;
	case KeyEvent::KEY_a:
		mLastCircle->location.x -= 4.0f;
		break;
	case KeyEvent::KEY_d:
		mLastCircle->location.x += 4.0f;
		break;
	}
}

void LearningProjApp::draw()
{
	gl::clear(Color::gray(0.1f));

	for (MovingCircle& c : mCircles) {
		gl::color(c.color);
		gl::drawSolidCircle(c.location, c.radius);


		vec2 moveVec = c.direction * c.velocity;
		float ratio;

		// Adjust movement vector to prevent clipping outside of screen.
		float clip = moveVec.x > 0.0f
			? c.location.x + moveVec.x + c.radius - getWindowSize().x
			: (c.location.x + moveVec.x - c.radius) * -1;
		if (clip >= 0.0f)
		{
			ratio = 1.0f - clip / moveVec.x;
			moveVec *= ratio;
			c.direction.x *= -1;
		}

		clip = moveVec.y > 0.0f
			? clip = c.location.y + moveVec.y + c.radius - getWindowSize().y
			: (c.location.y + moveVec.y - c.radius) * -1;
		if (clip >= 0.0f)
		{
			ratio = 1.0f - clip / moveVec.y;
			moveVec *= ratio;
			c.direction.y *= -1;
		}

		c.location += moveVec;
	}
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(LearningProjApp, RendererGl, prepareSettings)
#include <string>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/CinderImGui.h"
#include "rapidjson.h"
#include "filewritestream.h"

#include "Shape.h"
#include "PropertyGroup.h"
#include "Serialization.h"

using namespace ci;
using namespace app;

class learning_proj_app final : public App {
public:
	learning_proj_app();
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void draw() override;
	void setup() override;
	void update() override;

private:
	std::list<moving_circle> m_circles_;
	moving_circle m_dummy_circle_;
	moving_circle* m_last_circle_;

	circle m_circle_;
	circle_property_group m_circle_prop_;
	square m_square_;
	square_property_group m_square_prop_;
	rectangle m_rectangle_;
	rectangle_property_group m_rectangle_prop_;
	
	std::array<property_group*, 3> m_property_groups_;
	int m_selected_shape_index_;

	void write_shapes_json();
};

void prepare_settings(learning_proj_app::Settings* settings)
{
	settings->setMultiTouchEnabled(false);
}

learning_proj_app::learning_proj_app()
	:m_last_circle_(&m_dummy_circle_),
	m_circle_prop_(&m_circle_),
	m_square_prop_(&m_square_),
	m_rectangle_prop_(&m_rectangle_),
	m_property_groups_{
		&m_circle_prop_,
		&m_square_prop_,
		&m_rectangle_prop_,
},
m_selected_shape_index_(-1)
{
}

void learning_proj_app::mouseDown(const MouseEvent event)
{
	if (event.isLeft()) {
		moving_circle c;
		c.location = event.getPos();
		c.radius = randFloat(4.0f, 32.0f);
		c.color = Color(randFloat(), randFloat(), randFloat());
		c.direction = randVec2();
		c.velocity = randFloat(2.0f, 8.0f);
		m_circles_.push_back(c);
		auto end_itr = m_circles_.end();
		--end_itr;
		m_last_circle_ = &*end_itr;
	}
	else if (event.isRight())
	{
		auto itr = m_circles_.end();
		while (itr != m_circles_.begin()) {
			--itr;
			if (itr->is_inside(event.getPos()))
			{
				m_circles_.erase(itr);
				if (m_circles_.empty())
				{
					m_last_circle_ = &m_dummy_circle_;
				}
				else
				{
					itr = m_circles_.end();
					--itr;
					m_last_circle_ = &*itr;
				}
				break;
			}
		}
	}
}

void learning_proj_app::keyDown(const KeyEvent event)
{
	switch (event.getCode())
	{
	case KeyEvent::KEY_f:
		setFullScreen(!isFullScreen());
		break;
	case KeyEvent::KEY_SPACE:
		m_circles_.clear();
		break;
	case KeyEvent::KEY_ESCAPE:
		if (isFullScreen())
			setFullScreen(false);
		else
			quit();
		break;
	case KeyEvent::KEY_w:
		m_last_circle_->location.y -= 4.0f;
		break;
	case KeyEvent::KEY_s:
		m_last_circle_->location.y += 4.0f;
		break;
	case KeyEvent::KEY_a:
		m_last_circle_->location.x -= 4.0f;
		break;
	case KeyEvent::KEY_d:
		m_last_circle_->location.x += 4.0f;
		break;
	default:
		break;
	}
}

void learning_proj_app::draw()
{
	gl::clear(Color::gray(0.1f));

	for (moving_circle& c : m_circles_) {
		gl::color(c.color);
		gl::drawSolidCircle(c.location, c.radius);


		vec2 move_vec = c.direction * c.velocity;
		float ratio;

		// Adjust movement vector to prevent clipping outside of screen.
		float clip = move_vec.x > 0.0f
			? c.location.x + move_vec.x + c.radius - getWindowSize().x
			: (c.location.x + move_vec.x - c.radius) * -1;
		if (clip >= 0.0f)
		{
			ratio = 1.0f - clip / move_vec.x;
			move_vec *= ratio;
			c.direction.x *= -1;
		}

		clip = move_vec.y > 0.0f
			? clip = c.location.y + move_vec.y + c.radius - getWindowSize().y
			: (c.location.y + move_vec.y - c.radius) * -1;
		if (clip >= 0.0f)
		{
			ratio = 1.0f - clip / move_vec.y;
			move_vec *= ratio;
			c.direction.y *= -1;
		}

		c.location += move_vec;
	}
}

void learning_proj_app::setup()
{
	ImGui::Initialize();
}

void learning_proj_app::update()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("Save", nullptr))
			{
				write_shapes_json();
			}
			
			ImGui::MenuItem("Open");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	
	ImGui::Begin("List");
	ImGui::ListBox(
		"",
		&m_selected_shape_index_,
		[](void* data, const int idx, const char** out_text)
		{			
			*out_text = static_cast<property_group**>(data)[idx]->name;
			return true;
		},
		m_property_groups_.data(),
		m_property_groups_.size());
	ImGui::End();

	ImGui::Begin("Properties");
	if (m_selected_shape_index_ >= 0) {
		m_property_groups_[m_selected_shape_index_]->draw();
	}
	ImGui::End();
}

void learning_proj_app::write_shapes_json()
{
	FILE* file = fopen("output.json", "wb");
	char buffer[1024];
	FileWriteStream stream(file, buffer, sizeof(buffer));
	PrettyWriter<FileWriteStream> writer(stream);
	writer.StartObject();
	writer.String("circle");
	serialize<circle>(m_circle_, writer);
	writer.String("square");
	serialize<square>(m_square_, writer);
	writer.String("rectangle");
	serialize<rectangle>(m_rectangle_, writer);
	writer.EndObject();
	fclose(file);
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(learning_proj_app, RendererGl, prepare_settings)
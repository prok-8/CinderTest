#include "ExtendedCheckbox.h"

#include "cinder/Timeline.h"
#include "cinder/Tween.h"
#include "imgui/imgui.h"
#include "ColorInterp.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "imgui/imgui_internal.h"

ImGui::ExtendedCheckbox::ExtendedCheckbox(const char* label, cinder::Timeline* timeline) :
	label_(label),
	state_(false),
	transitioning_(false),
	timeline_(timeline),
    knob_position_(0.0f),
	knob_color_(cinder::Color8u(255, 0, 0))
{
}

bool ImGui::ExtendedCheckbox::Draw()
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label_);
    const ImVec2 label_size = CalcTextSize(label_, nullptr, true);

    const float square_sz = GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, pos + ImVec2(square_sz * 2 + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
    {
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return false;
    }

    bool hovered, held;
    const bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
    	if(state_)
    	{
            state_ = false;
            timeline_->apply(&knob_position_, 0.0f, transition_time_, cinder::EaseOutBack(3.0f));
            timeline_->apply(&knob_color_, cinder::Color8u(255, 0, 0), transition_time_, cinder::EaseOutQuad(), Color8uInterp());
    	}
    	else
        {
            state_ = true;
            timeline_->apply(&knob_position_, square_sz, transition_time_, cinder::EaseOutBack(3.0f));
            timeline_->apply(&knob_color_, cinder::Color8u(0, 255, 0), transition_time_, cinder::EaseOutQuad(), Color8uInterp());
        }
    	
        transitioning_ = true;
        MarkItemEdited(id);
    }

    const ImU32 knob_color_value = 0xff000000 | knob_color_.value().b << 16 | knob_color_.value().g << 8 | knob_color_.value().r;
    const ImRect check_bb(pos, pos + ImVec2(square_sz * 2, square_sz));
    const unsigned int frame_col = GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
    RenderFrame(check_bb.Min, check_bb.Max, frame_col, true, square_sz / 2);

    const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
    window->DrawList->AddCircleFilled(check_bb.GetCenter() + ImVec2(knob_position_ - square_sz / 2, 0.0f), square_sz / 2 - pad, knob_color_value);
	
    const ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
    if (label_size.x > 0.0f)
        RenderText(label_pos, label_);
	

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
    return pressed;
}

#include "ca/gui/widgets/checkbox.hpp"
#include "ca/gui/guimanager.hpp"
#include "ca/gui/rendering/theme.hpp"
#include "ca/gui/backend/renderbackend.hpp"

namespace ca { namespace gui {

	CheckBox::CheckBox() :
		Clickable(this),
		m_textWidth(0.0f),
		m_checked(false),
		m_backgroundTexture(0)
	{
		Widget::setKeyboardFocusable(true);
		m_checkmarkTexture[0] = m_checkmarkTexture[1] = 0;
		addOnButtonChangeFunc(
			[](Widget* _thisBtn, const Coord2&, int, MouseState::ButtonState){
				static_cast<CheckBox*>(_thisBtn)->m_checked = !static_cast<CheckBox*>(_thisBtn)->m_checked;
			},
			MouseState::ButtonState(MouseState::CLICKED | MouseState::DBL_CLICKED));
	}

	void CheckBox::draw() const
	{
		// Background
		if(m_backgroundTexture)
			GUIManager::theme().drawImage(m_refFrame, m_backgroundTexture);
		else
			GUIManager::theme().drawButton(m_refFrame, false, false);

		// Determine vertical center for text and box
		float padding = GUIManager::theme().getTextSize() * 0.25f;
		float downScale = ei::min(1.0f, ei::min(m_refFrame.height() / (GUIManager::theme().getTextSize() + 2.0f),
			m_refFrame.width() / (m_textWidth + 6.0f + GUIManager::theme().getTextSize())));
		float size = (GUIManager::theme().getTextSize() - 2.0f) * downScale;
		float vcenter = (m_refFrame.bottom() + m_refFrame.top() - size) * 0.5f;

		// "Icon"
		bool mouseOver = GUIManager::hasMouseFocus(this);
		// Create a rectangle with the same size as the global font size
		RefFrame checkRect;
		checkRect.sides[SIDE::LEFT] = floorf(padding + m_refFrame.left());
		checkRect.sides[SIDE::RIGHT] = floorf(checkRect.sides[SIDE::LEFT] + size);
		checkRect.sides[SIDE::BOTTOM] = floorf(vcenter);
		checkRect.sides[SIDE::TOP] = floorf(checkRect.sides[SIDE::BOTTOM] + size);
		GUIManager::theme().drawCheckbox(checkRect, m_checked, mouseOver);

		// Text
		GUIManager::theme().drawText(Coord2(checkRect.sides[SIDE::RIGHT] + padding, vcenter - 1.0f), m_text.c_str(), downScale, mouseOver);
	}

	void CheckBox::setText(const char* _text)
	{
		m_text = _text;
		m_textWidth = GUIManager::theme().getTextBB(Coord2(0.0f), _text, 1.0f).max.x;
	}

	void CheckBox::setBackgroundTexture(const char * _textureFile, bool _smooth)
	{
		m_backgroundTexture = GUIManager::renderBackend().getTexture(_textureFile, _smooth);
	}

}} // namespace ca::gui

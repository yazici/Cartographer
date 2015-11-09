#pragma once

#include "properties/coordinate.hpp"

namespace cag {

	/// Interface for different rendering implementations (look).
	/// \details Dependent on the generality a new theme does not ever need a new implementation.
	///		Changing colors should be possible over theme settings. A theme is more a general
	///		style like flat buttos versus bloby buttons...
	class ITheme
	{
	public:
		/// Draw a background for text
		virtual void drawTextArea() = 0;
		/// Draw the background for buttons
		virtual void drawButton(const class RefFrame& _rect, bool _mouseOver) = 0;
		/// Draw the box with the check mark
		virtual void drawCheckbox(bool _checked) = 0;
		/// Draw a string
		virtual void drawText(const Coord& _position, const char* _text, bool _mouseOver, float _alignX = 0.0f, float _alignY = 0.0f) = 0;
		/// Draw an image
		virtual void drawImage(const class RefFrame& _rect, uint64 _texHandle) = 0;
		/// Draw an arrow for sliders, scrollbars or drop down menus
		virtual void drawArrowButton() = 0;
		
		// more are following...
	};

} // namespace cag
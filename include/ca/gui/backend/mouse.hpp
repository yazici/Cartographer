#pragma once

#include "ca/gui/properties/coordinate.hpp"

namespace ca { namespace gui {

	/// Descriptor for the current mouse state.
	struct MouseState
	{
		/// Cursor position in internal coordinates.
		/// \details Coordinates outside [0,width/heigh] are possible if the mouse leaves the window
		///		while being pressed or if the window was resized and the mouse is not yet repositioned.
		Coord2 position;

		/// Change of the position since last frame.
		Coord2 deltaPos() const { return position - lastPosition; }

		/// Flags of a mouse button state.
		/// \details It is possible that multiple flags are set in a single frame. This happens
		///		if DOWN and UP event occured in the same frame. The PRESSED flag is never set
		///		when DOWN is set.
		///
		///		Metastates are generated by some components like clickables. The manager will not
		///		produce them.
		enum ButtonState
		{
			RELEASED = 0,		///< Button is not pressed
			DOWN = 1,			///< Button was clicked in the current frame
			PRESSED = 4,		///< Button is still pressed (was clicked in the past)
			UP = 2,				///< Button was released in the current frame
			// The following meta events are handled by the gui itself.
			// There is no need for a backend to set these values.
			CLICKED = 8,		///< Metastate (UP and DOWN where done on the same component)
			DBL_CLICKED = 16,	///< Metastate Two CLICK events occured in a short period
		};

		enum class Button
		{
			LEFT = 0,
			RIGHT = 1,
			MIDDLE = 2,
			MB3 = 3,
			MB4 = 4,
			MB5 = 5,
			MB6 = 6,
			MB7 = 7
		};

		/// State for up to 8 buttons
		ButtonState buttons[8];
		/// Is there any DOWN or UP event for any of the 8 buttons?
		bool anyButtonUp, anyButtonDown, anyButtonPressed;

		ei::Vec2 deltaScroll;

		/// Reset/change states
		void clear();
	private:
		Coord2 lastPosition;
	};

	/// Desired shape of the cursor.
	/// \detais The GUI will set thes in the manager and expects that the application will render
	///		according shapes.
	enum class CursorType
	{
		ARROW,					///< Standard arrow/pointer
		IBEAM,					///< Text input cursor
		CROSSHAIR,				///< The cross for precise picking
		HAND,					///< The Hand
		RESIZE_H,				///< Arrow for horizontal resizing
		RESIZE_V,				///< Arrow for vertical resizing
		RESIZE_DUP,				///< Arrow for resizing with Lower-Left to Upper-Right orientation
		RESIZE_DDOWN,			///< Arrow for resizing with Upper-Right to Lower-Left orientation
		MOVE,					///< The cross for movements
		WAIT,					///< Hour-glass or similar
	};

}} // namespace ca::gui
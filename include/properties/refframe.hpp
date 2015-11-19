#pragma once

#include "coordinate.hpp"

namespace cag {

	class IRegion
	{
	public:
		/// Check if the mouse position is over this element.
		/// \param [in] _mousePos Position of the cursor in screenspace [0,1]^2.
		virtual bool isMouseOver(const Coord2& _mousePos) = 0;
	};

	/// A general purpose enum to define positioning schemes
	/// \details To access general dimensions (i.e. x and y) in vectors you can use SIDE/2 as
	///		index.
	struct SIDE
	{
		enum Val
		{
			LEFT = 0,
			RIGHT = 1,
			BOTTOM = 2,
			TOP = 3
		};
	};

	/// Basic rectangular area which is used as reference from all widgets.
	class RefFrame: public IRegion
	{
	public:
		float sides[4];	/// An array of the four side coordinates sorted after SIDE

		float left() const { return sides[SIDE::LEFT]; }
		float right() const { return sides[SIDE::RIGHT]; }
		float bottom() const { return sides[SIDE::BOTTOM]; }
		float top() const { return sides[SIDE::TOP]; }
		float width() const { return sides[SIDE::RIGHT] - sides[SIDE::LEFT]; }
		float height() const { return sides[SIDE::TOP] - sides[SIDE::BOTTOM]; }

		/// Check if the mouse cursor is on this reference frame.
		/// \param [in] _mousePos Position of the cursor in screenspace [0,1]^2.
		virtual bool isMouseOver(const Coord2& _mousePos) override;
	};

} // namespace cag
#include "Input.h"

namespace Skel
{
	double SKInput::scroll = 0.0f;

	void SKInput::SetMouseScrollOffset(double y)
	{
		scroll = y;
	}

	bool SKInput::isMouseScrollUp()
	{
		return scroll > 0.0f;
	}

	bool SKInput::isMouseScrollDown()
	{
		return scroll < 0.0f;
	}
}
#include "Input.h"

namespace Skel
{
	double Input::scroll = 0.0f;

	void Input::SetMouseScrollOffset(double y)
	{
		scroll = y;
	}

	bool Input::isMouseScrollUp()
	{
		return scroll > 0.0f;
	}

	bool Input::isMouseScrollDown()
	{
		return scroll < 0.0f;
	}
}
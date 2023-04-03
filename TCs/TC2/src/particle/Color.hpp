#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color {
	public:
		Color(float r, float g, float b);
		Color(int hexColor);
		float getRed();
		float getGreen();
		float getBlue();

	private:
		float r;
		float g;
		float b;
};

#endif

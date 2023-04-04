#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color {
	public:
		Color();
		Color(float r, float g, float b);
		Color(unsigned char r, unsigned char g, unsigned char b);
		Color(int hexColor);
		float getRed();
		float getGreen();
		float getBlue();
		void setRed(float r);
		void setGreen(float g);
		void setBlue(float b);

	private:
		float r;
		float g;
		float b;
};

#endif

#ifndef _COORDINATE_2D_HPP_
#define _COORDINATE_2D_HPP_

class Coordinate2D {
	public:
		Coordinate2D();
		Coordinate2D(float x, float y);
		Coordinate2D(float same);
		~Coordinate2D();
		float getX();
		float getY();
		void setX(float x);
		void setY(float y);

		bool operator==(Coordinate2D coordinate);
		bool operator!=(Coordinate2D coordinate);

		Coordinate2D operator+(Coordinate2D coordinate);
		Coordinate2D operator-(Coordinate2D coordinate);
		Coordinate2D operator*(float num);
		Coordinate2D operator/(float num);

		void operator +=(Coordinate2D coordinate);
		void operator -=(Coordinate2D coordinate);
		void operator *=(float num);
		void operator /=(float num);

		float squaredDistance(Coordinate2D coordinate);
		float magnitude();

	private:
		float x;
		float y;
};

#endif

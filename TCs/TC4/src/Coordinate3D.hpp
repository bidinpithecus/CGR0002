#ifndef _COORDINATE3D_HPP_
#define _COORDINATE3D_HPP_

class Coordinate3D {
	public:
		Coordinate3D();
		Coordinate3D(float x, float y, float z);
		Coordinate3D(float same);
		~Coordinate3D();
		float getX();
		float getY();
		float getZ();
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		bool operator==(Coordinate3D coordinate);
		bool operator!=(Coordinate3D coordinate);

		Coordinate3D operator+(Coordinate3D coordinate);
		Coordinate3D operator-(Coordinate3D coordinate);
		Coordinate3D operator*(float num);
		Coordinate3D operator/(float num);

		void operator +=(Coordinate3D coordinate);
		void operator -=(Coordinate3D coordinate);
		void operator *=(float num);
		void operator /=(float num);

		float squaredDistance(Coordinate3D coordinate);
		float magnitude();

	private:
		float x;
		float y;
		float z;
};

#endif

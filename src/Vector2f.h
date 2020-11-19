#pragma once

#include<iostream>

class Vector2f {
	private:
		float _x;
		float _y;

	public:
		Vector2f() = default;
		Vector2f(float x, float y);
		//Vector2f(int x, int y);
		void set(float x, float y);
		float x() const;
		float y() const;
		Vector2f add(const Vector2f& v) const;
		Vector2f sub(const Vector2f& v) const;
		Vector2f mul(const Vector2f& v) const;
		Vector2f div(const Vector2f& v) const;
		Vector2f scale(float v) const;
		float dot(const Vector2f& v) const;
		float len2() const;
		float len() const;
		
		Vector2f operator+(Vector2f r) const {
			return add(r);
		}

		Vector2f operator+=(Vector2f r){
			auto temp = add(r);
			_x = temp._x;
			_y = temp._y;
			return temp;
		}

		Vector2f operator-(Vector2f r) const {
			return sub(r);
		}

		Vector2f operator-=(Vector2f r){
			auto temp = sub(r);
			_x = temp._x;
			_y = temp._y;
			return temp;
		}

		Vector2f operator*(float r) const {
			return scale(r);
		}

		Vector2f operator*=(float r){
			auto temp = scale(r);
			_x = temp._x;
			_y = temp._y;
			return temp;
		}

		Vector2f operator/(float r) const {
			return scale(1/r);
		}

		Vector2f operator/=(float r){
			auto temp = scale(1/r);
			_x = temp._x;
			_y = temp._y;
			return temp;
		}

		Vector2f unit() const {
			auto temp = len();
			if(temp > .000001)
				return (*this)/temp;
			return *this;
		}

};

Vector2f operator*(float l, Vector2f r){
	return r*l;
}

std::ostream& operator<<(std::ostream& os, Vector2f v){
	os << "v2f(" << v.x() << ", " << v.y() << ")";
	return os;
}
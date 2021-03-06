#pragma once

#include <math.h>

Vector2f::Vector2f(float x, float y) {
	_x = x;
	_y = y;
}

void Vector2f::set(float x, float y) {
	_x = x;
	_y = y;
}

void Vector2f::set(Vector2f v) {
	_x = v.x();
	_y = v.y();
}

void Vector2f::setx(float x) {
	_x = x;
}

void Vector2f::sety(float y) {
	_y = y;
}

float Vector2f::x() const {
	return _x;
}

float Vector2f::y() const {
	return _y;
}

Vector2f Vector2f::add(const Vector2f& v) const {
	return Vector2f(_x + v.x(), _y + v.y());
}

Vector2f Vector2f::sub(const Vector2f& v) const {
	return Vector2f(_x - v.x(), _y - v.y());
}

Vector2f Vector2f::mul(const Vector2f& v) const {
	return Vector2f(_x * v.x(), _y * v.y());
}

Vector2f Vector2f::div(const Vector2f& v) const {
	return Vector2f(_x / v.x(), _y / v.y());
}

Vector2f Vector2f::add(const float x, const float y) const {
	return Vector2f(_x + x, _y + y);
}

Vector2f Vector2f::sub(const float x, const float y) const {
	return Vector2f(_x - x, _y - y);
}

Vector2f Vector2f::mul(const float x, const float y) const {
	return Vector2f(_x * x, _y * y);
}

Vector2f Vector2f::div(const float x, const float y) const {
	return Vector2f(_x / x, _y / y);
}

Vector2f Vector2f::scale(float v) const {
	return Vector2f(_x * v, _y * v);
}

float Vector2f::dot(const Vector2f& v) const {
	return _x * v.x() + _y * v.y();
}

float Vector2f::len2() const {
	return dot(*this);
}

float Vector2f::len() const {
	return sqrt(len2());
}

#include "vector2.h"

std::ostream &operator<<(std::ostream &os, Vector2 const &m) {
	return os << m.x << "," << m.y;
}
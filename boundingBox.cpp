#include "boundingBox.hpp"

bool BoundingBox::isInBounds(BoundingBox& box) {
	Tmpl8::vec2 firstPos = getPos();
	Tmpl8::vec2 firstSize = getSize();
	Tmpl8::vec2 secondPos = box.getPos();
	Tmpl8::vec2 secondSize = box.getSize();


	return (
		firstPos.x < secondPos.x + secondSize.x &&
		firstPos.x + firstSize.x > secondPos.x &&
		firstPos.y < secondPos.y + secondSize.y &&
		firstPos.y + firstSize.y > secondPos.y
		);
}
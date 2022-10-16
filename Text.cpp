#include "Text.h"
#include <Novice.h>

Text::Text()
{

}

Text::Text(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float afterY, float speed)
{
}

void SlideLeft(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed) {

	if (x > afterX) {
		x -= speed;
	}

	if (x < afterX) {
		x = afterX;
	}

	Novice::DrawQuad(x, y, x + width, y, x, y + height, x + width, y + height, srcX, srcY, srcW, srcH, textureHandle, color);

}

void SlideRight(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed) {

	if (x < afterX) {
		x += speed;
	}

	if (x > afterX) {
		x = afterX;
	}

	Novice::DrawQuad(x, y, x + width, y, x, y + height, x + width, y + height, srcX, srcY, srcW, srcH, textureHandle, color);

}

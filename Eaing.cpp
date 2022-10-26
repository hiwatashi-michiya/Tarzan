#include "Easing.h"
#define _USE_MATH_DEFINES
# include <math.h>

bool Easing::Use(float& PosX, float& PosY, const float& startPosX, const float& startPosY, const float& endPosX, const float& endPosY, Type type, float spd, float& num) {
	if (num >= 1.0f || num < 0) {
		num = 0;
	}

	float T = 0.0f;

	EaseType(num, T, type);

	num += spd;
	PosX = (1 - T) * startPosX + T * endPosX;
	PosY = (1 - T) * startPosY + T * endPosX;

	if (num >= 1.0f || PosX == endPosX && PosY == endPosY) {
		return true;
	}
	else {
		return false;
	}
}

bool Easing::Use(float& Pos, const float& startPos, const float& endPos, Type type, float spd, float& num) {
	if (num >= 1.0f || num < 0) {
		num = 0;
	}

	float T = 0.0f;

	EaseType(num, T, type);

	num += spd;
	Pos = (1 - T) * startPos + T * endPos;

	if (num >= 1.0f || Pos == endPos) {
		return true;
	}
	else {
		return false;
	}
}

float Easing::InSine(float x) {
	return 1.0f - cosf((x * M_PI) / 2.0f);
}

float Easing::OutSine(float x) {
	return sinf((x * M_PI) / 2.0f);
}
float Easing::InOutSine(float x) {
	return -1.0f * (cosf(M_PI * x) - 1.0f) / 2.0f;
}
float Easing::InQuad(float x) {
	return powf(x, 2.0f);
}
float Easing::OutQuad(float x) {
	return 1.0f - (1.0f - x) * (1.0f - x);
}
float Easing::InOutQuad(float x) {

	if (x < 0.5f)
	{
		return 2.0f * powf(x, 2.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 2.0f) / 2.0f;
	}
}
float Easing::InCubic(float x) {
	return powf(x, 3.0f);
}
float Easing::OutCubic(float x) {
	return 1.0f - powf(1.0f - x, 3.0f);
}
float Easing::InOutCubic(float x) {
	if (x < 0.5f)
	{
		return 4.0f * powf(x, 4.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f;
	}
}
float Easing::InQuart(float x) {
	return powf(x, 4.0f);
}
float Easing::OutQuart(float x) {
	return 1.0f - powf(1.0f - x, 4.0f);
}
float Easing::InOutQuart(float x) {
	if (x < 0.5f)
	{
		return 8.0f * powf(x, 4.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f;
	}
}
float Easing::InQuint(float x) {
	return powf(x, 5.0f);
}
float Easing::OutQuint(float x) {
	return 1.0f - powf(1.0f - x, 5.0f);
}
float Easing::InOutQuint(float x) {
	if (x < 0.5f)
	{
		return 16.0f * powf(x, 5.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f;
	}
}
float Easing::InExpo(float x) {
	if (x == 0.0f)
	{
		return 0.0f;
	}
	else
	{
		return powf(2.0f, 10.0f * x - 10.0f);
	}
}
float Easing::OutExpo(float x) {
	if (x == 1.0f)
	{
		return 1.0f;
	}
	else
	{
		return (1.0f - powf(2.0f, -10.0f * x));
	}
}
float Easing::InOutExpo(float x) {
	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else if (x < 0.5f)
	{
		return powf(2.0f, 20.0f * x - 10.0f) / 2.0f;
	}
	else
	{
		return (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f;
	}
}
float Easing::InCirc(float x) {
	return 1.0f - sqrtf(1.0f - powf(x, 2.0f));
}
float Easing::OutCirc(float x) {
	return sqrtf(1.0f - powf(x - 1.0f, 2.0f));
}
float Easing::InOutCirc(float x) {
	if (x < 0.5f)
	{
		return (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f;
	}
	else
	{
		return (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}
}
float Easing::InBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return (c3 * powf(x, 3.0f)) - (c1 * powf(x, 2.0f));
}
float Easing::OutBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return 1 + c3 * powf(x - 1.0f, 3.0f) + c1 * powf(x - 1.0f, 2.0f);
}
float Easing::InOutBack(float x) {
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	if (x < 0.5f)
	{
		return (powf(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f;
	}
	else
	{
		return (powf(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
	}
}
float Easing::InElastic(float x) {
	const float c4 = (2.0f * M_PI) / 3.0f;

	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else
	{
		return -powf(2.0f, 10.0f * x - 10.0f) * sinf((x * 10.0f - 10.75f) * c4);
	}
}
float Easing::OutElastic(float x) {
	const float c4 = (2.0f * M_PI) / 3.0f;

	if (x == 0.0f) {
		return 0.0f;
	}
	else if (x >= 1.0f) {
		return 1.0f;
	}
	else {
		return powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
	}
}
float Easing::InOutElastic(float x) {
	const float c5 = (2.0f * M_PI) / 4.5f;

	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else if (x < 0.5f)
	{
		return -1.0f * (powf(2.0f, 20.0f * x - 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f;
	}
	else
	{
		return (powf(2.0f, -20.0f * x + 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
	}
}
float Easing::InBounce(float x) {
	return 1.0f - OutBounce(1.0f - x);
}
float Easing::OutBounce(float x) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1.0f / d1) {
		return n1 * powf(x, 2.0f);
	}
	else if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}
float Easing::InOutBounce(float x) {
	if (x < 0.5f)
	{
		return (1.0f - OutBounce(1.0f - 2.0f * x)) / 2.0f;
	}
	else
	{
		return (1.0f + OutBounce(2.0f * x - 1.0f)) / 2.0f;
	}
}

void Easing::EaseType(const float &num, float& T, Type type) {
	switch (type) {
	case Type::kInSine:
		T = Easing::InSine(num);
		break;
	case Type::kOutSine:
		T = Easing::OutSine(num);
		break;
	case Type::kInOutSine:
		T = Easing::InOutSine(num);
		break;
	case Type::kInQuad:
		T = Easing::InQuad(num);
		break;
	case Type::kOutQuad:
		T = Easing::OutQuad(num);
		break;
	case Type::kInOutQuad:
		T = Easing::InOutQuad(num);
		break;
	case Type::kInCubic:
		T = Easing::InCubic(num);
		break;
	case Type::kOutCubic:
		T = Easing::OutCubic(num);
		break;
	case Type::kInOutCubic:
		T = Easing::InOutCubic(num);
		break;
	case Type::kInQuart:
		T = Easing::InQuart(num);
		break;
	case Type::kOutQuart:
		T = Easing::OutQuart(num);
		break;
	case Type::kInOutQuart:
		T = Easing::InOutQuart(num);
		break;
	case Type::kInQuint:
		T = Easing::InQuint(num);
		break;
	case Type::kOutQuint:
		T = Easing::OutQuart(num);
		break;
	case Type::kInOutQuint:
		T = Easing::InOutQuart(num);
		break;
	case Type::kInExpo:
		T = Easing::InExpo(num);
		break;
	case Type::kOutExpo:
		T = Easing::OutExpo(num);
		break;
	case Type::kInOutExpo:
		T = Easing::InOutExpo(num);
		break;
	case Type::kInCirc:
		T = Easing::InCirc(num);
		break;
	case Type::kOutCirc:
		T = Easing::OutCirc(num);
		break;
	case Type::kInOutCirc:
		T = Easing::InOutCirc(num);
		break;
	case Type::kInBack:
		T = Easing::InBack(num);
		break;
	case Type::kOutBack:
		T = Easing::OutBack(num);
		break;
	case Type::kInOutBack:
		T = Easing::InOutBack(num);
		break;
	case Type::kInElastic:
		T = Easing::InElastic(num);
		break;
	case Type::kOutElastic:
		T = Easing::OutElastic(num);
		break;
	case Type::kInOutElastic:
		T = Easing::InOutElastic(num);
		break;
	case Type::kInBounce:
		T = Easing::InBounce(num);
		break;
	case Type::kOutBounce:
		T = Easing::OutBounce(num);
		break;
	case Type::kInOutBounce:
		T = Easing::InOutBounce(num);
		break;
	}
}
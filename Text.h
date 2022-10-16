#pragma once


class Text
{
public:
	Text();
	Text(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
		int textureHandle, int color, float afterX, float afterY, float speed);


private:

	float x;
	float y;

	float width;
	float height;

	float srcX;
	float srcY;
	float srcW;
	float srcH;

	int textureHandle;
	int color;

	float afterX;
	float afterY;
	float speed;

};

/// <summary>
/// 左側に画像をスライドさせる
/// </summary>
/// <param name="x">移動前左上のX座標</param>
/// <param name="y">左上のY座標</param>
/// <param name="width">横幅</param>
/// <param name="height">縦幅</param>
/// <param name="srcX">画像上の描画したい範囲左上X座標</param>
/// <param name="srcY">画像上の描画したい範囲左上Y座標</param>
/// <param name="srcW">画像上の描画したい範囲横幅</param>
/// <param name="srcH">画像上の描画したい範囲縦幅</param>
/// <param name="textureHandle">テクスチャのハンドル</param>
/// <param name="color">色</param>
/// <param name="afterX">移動後の左上X座標</param>
/// <param name="speed">移動させる速度</param>
void SlideLeft(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed);

/// <summary>
/// 右側に画像をスライドさせる
/// </summary>
/// <param name="x">移動前左上のX座標</param>
/// <param name="y">左上のY座標</param>
/// <param name="width">横幅</param>
/// <param name="height">縦幅</param>
/// <param name="srcX">画像上の描画したい範囲左上X座標</param>
/// <param name="srcY">画像上の描画したい範囲左上Y座標</param>
/// <param name="srcW">画像上の描画したい範囲横幅</param>
/// <param name="srcH">画像上の描画したい範囲縦幅</param>
/// <param name="textureHandle">テクスチャのハンドル</param>
/// <param name="color">色</param>
/// <param name="afterX">移動後の左上X座標</param>
/// <param name="speed">移動させる速度</param>
void SlideRight(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed);

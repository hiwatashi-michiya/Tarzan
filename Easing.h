#pragma once

// インスタンス化の必要なし
// Easing オブジェクト名;　のように書かなくて良い

/*　イージングチートシート参照（左上[1]から右下[30]にかけて）　*/

///		使い方：例文(Use関数使わないほう)
///		if(フラグ == true){
///			T = Easing::EaseInSine(num);		//Easing(クラス名)::EaseInSine(クラス内変数名)
///			num += spd;
///			pos_x = (1 - T) * 始点 + T * 終点;
///			pos_y = (1 - T) * 始点 + T * 終点;
///			if(num >= 1.0f){
///				フラグ = false;
///			}
///		}

///		使い方：例文
///		if(フラグ == true) {
///			// Easing(クラス名)::EaseInSine(クラス内変数名)
///			if(Use(動かしたいポジション, スタート位値,終わり位置,Easing::イージングタイプ,、イージングのスピード, 線形保管用の値)){
///				フラグ = false;
///			}
///		}

class Easing {
public:
	static enum Type {
		kInSine = 0,
		kOutSine,
		kInOutSine,
		kInQuad,
		kOutQuad,
		kInOutQuad,
		kInCubic,
		kOutCubic,
		kInOutCubic,
		kInQuart,
		kOutQuart,
		kInOutQuart,
		kInQuint,
		kOutQuint,
		kInOutQuint,
		kInExpo,
		kOutExpo,
		kInOutExpo,
		kInCirc,
		kOutCirc,
		kInOutCirc,
		kInBack,
		kOutBack,
		kInOutBack,
		kInElastic,
		kOutElastic,
		kInOutElastic,
		kInBounce,
		kOutBounce,
		kInOutBounce
	} type;

	/*
	イージング

	第一引数：イージングしたいポジション　X　第二引数：イージングしたいポジション　Y　
	第三引数：スタートポジション　　　　X  　第四引数：スタートポジション　　　　Y　
	第五引数：エンドポジション　　　　　X　第五引数：エンドポジション　　　　　Y
	第七引数：イージングのタイプ(詳しくはイージングチートシートを参照) URLはhttps://easings.net/ja#
	第八引数：イージングのスピード
	第八引数：線形保管用の数字(0～１の範囲外の数字が入ると0に初期化される)

	戻り値：１：イージング終わり
	　　　　0 : イージング中
	*/
	static bool Use(float& PosX, float& PosY, const float& startPosX, const float& startPosY, const float& endPosX, const float& endPosY, Type type, float spd, float& num);
	/*
	イージング

	第一引数：イージングしたいポジション
	第二引数：スタートポジション
	第三引数：エンドポジション
	第四引数：イージングのタイプ(詳しくはイージングチートシートを参照) URLはhttps://easings.net/ja#
	第五引数：イージングのスピード
	第六引数：線形保管用の数字(0～１の範囲外の数字が入ると0に初期化される)

	戻り値：１：イージング終わり
	　　　　0 : イージング中
	*/
	static bool Use(float& Pos, const float& startPos, const float& endPos, Type type, float spd, float& num);



	///
	///以下イージングチートシート丸パクリ
	/// 数字はイージングチートシートの順番に準拠
	/// Use関数が分からないときは以下の関数を使ってください
	/// 使用例は上
	/// 

	//	1番
	static float InSine(float x);
	//	2
	static float OutSine(float x);
	//	3
	static float InOutSine(float x);
	//	4
	static float InQuad(float x);
	//	5
	static float OutQuad(float x);
	//	6
	static  float InOutQuad(float x);
	//	7
	static  float InCubic(float x);
	//	8
	static  float OutCubic(float x);
	//	9
	static float InOutCubic(float x);
	//	10
	static float InQuart(float x);
	//	11
	static float OutQuart(float x);
	//	12
	static float InOutQuart(float x);
	//	13
	static float InQuint(float x);
	//	14
	static float OutQuint(float x);
	//	15
	static float InOutQuint(float x);
	//	16
	static float InExpo(float x);
	//	17
	static float OutExpo(float x);
	//	18
	static float InOutExpo(float x);
	//	19
	static float InCirc(float x);
	//	20
	static float OutCirc(float x);
	//	21
	static float InOutCirc(float x);
	//	22
	static float InBack(float x);
	//	23
	static float OutBack(float x);
	//	24
	static float InOutBack(float x);
	//	25
	static float InElastic(float x);
	//	26
	static float OutElastic(float x);
	//	27
	static float InOutElastic(float x);
	//	28
	static float InBounce(float x);
	//	29
	static float OutBounce(float x);
	//	30
	static float InOutBounce(float x);

private:
	static void EaseType(const float& num, float& T, Type type);
};
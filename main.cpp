#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1C_23_ヤリタ_コウヤ_タイトル";

struct Vector2
{
	float x;
	float y;
};
struct Bullet
{
	Vector2 pos;
	Vector2 prePoint;
	Vector2 fixedPos;
	Vector2 move;
	bool isAlive;
	float radius;
	float speed;
	float velocity;
	float length;
	float theta;
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
//Bullet
	const int maxBullet = 6;
	Bullet bullet[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bullet[i].pos = { 1200.0f,360.0f };
		bullet[i].prePoint;
		bullet[i]. fixedPos = { 1200.0f,360.0f };
		bullet[i].move;
		bullet[i].radius = 30.0f;
		bullet[i].speed = 10.0f;
		bullet[i].velocity = 10.0f;
		bullet[i].isAlive = true;
		bullet[i].length = 0.0f;
		bullet[i].theta = 0.0f;
	}
	

	/*Vector2  fixedPos = { 1200.0f,40.0f };*/
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//for (int i = 0; i < maxBullet; i++) {
		//	
		//	//回転
		//	bullet[i].theta += 1.0f / 128.0f * float(M_PI);
		//	bullet[i].prePoint.x = cosf(bullet[i].theta) - sinf(bullet[i].theta);
		//	bullet[i].prePoint.y = sinf(bullet[i].theta) + cosf(bullet[i].theta);
		//	if (bullet[i].isAlive == true) {
		//		bullet[i].move.x = bullet[i].prePoint.x;
		//		bullet[i].move.y = bullet[i].prePoint.y;
		//		bullet[i].pos.x -= bullet[i].speed;
		//		bullet[i].pos.y -= bullet[i].velocity;
		//		//正規化
		//		bullet[i].length = sqrtf(bullet[i].move.x * bullet[i].move.x + bullet[i].move.y * bullet[i].move.y);

		//		/*if (bullet[i].length <= 0.0f) {
		//			bullet[i].move.x /= bullet[i].length;
		//			bullet[i].move.y /= bullet[i].length;
		//			bullet[i].pos.x += bullet[i].move.x;
		//			bullet[i].pos.y += bullet[i].move.y;
		//		}*/
		//	}
		//	if (bullet[i].pos.x == 0.0f) {
		//		bullet[i].isAlive = false;
		//		bullet[i].pos = bullet[i].fixedPos;
		//		if (bullet[i].pos.x == bullet[i].fixedPos.x) {
		//			bullet[i].isAlive = true;
		//		}
		//	}
		//}
		for (int i = 0; i < maxBullet; i++) {
			bullet[i].velocity = bullet[i].velocity - (i * 1);
			//回転
			bullet[i].theta = (7.0f - i) / maxBullet * float(M_PI);///1/6～8/6の角度
			bullet[i].move.x = cosf(bullet[i].theta) - sinf(bullet[i].theta);
			bullet[i].move.y = sinf(bullet[i].theta) + cosf(bullet[i].theta);
			if (bullet[i].isAlive == true) {
				/*bullet[i].pos.x -= bullet[i].speed;
				bullet[i].pos.y -= bullet[i].velocity;*/
				////正規化
				bullet[i].length = sqrtf(bullet[i].move.x * bullet[i].move.x + bullet[i].move.y * bullet[i].move.y);

				if (bullet[i].length >= 1.0f) {
					bullet[i].move.x /= bullet[i].length;
					bullet[i].move.y /= bullet[i].length;
					bullet[i].pos.x += bullet[i].move.x;
					bullet[i].pos.y += bullet[i].move.y;
				}
			}
			if (bullet[i].pos.x == 0.0f || bullet[i].pos.y == 0.0f|| bullet[i].pos.y == 720.0f) {
				bullet[i].isAlive = false;
				bullet[i].pos = bullet[i].fixedPos;
				if (bullet[i].pos.x == bullet[i].fixedPos.x) {
					bullet[i].isAlive = true;
				}
				/*bullet[i].speed = 10.0f;
				bullet[i].velocity = 10.0f;*/
			}
		
				
				
			
			
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (int i = 0; i < maxBullet; i++) {
			if (bullet[i].isAlive == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/
				


				Novice::DrawEllipse(
					static_cast<int>(bullet[i].pos.x), static_cast<int>(bullet[i].pos.y),
					static_cast<int>(bullet[i].radius), static_cast<int>(bullet[i].radius),
					1.0f, RED, kFillModeSolid);
			}
			
		}
		for (int i = 0; i < maxBullet; i++) {
			Novice::ScreenPrintf(0, i*17, "posx%d", static_cast<int>(bullet[i].pos.x));

			Novice::ScreenPrintf(0, 102+i * 17, "posy%d", static_cast<int>(bullet[i].pos.y));
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

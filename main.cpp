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
	float coolTime;
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	//Bullet
	const int maxBullet = 6;
	//横
	Bullet bulletBeside[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bulletBeside[i].pos = { 1200.0f,360.0f };
		bulletBeside[i].prePoint;
		bulletBeside[i].fixedPos = { 1200.0f,360.0f };
		bulletBeside[i].move;
		bulletBeside[i].radius = 30.0f;
		bulletBeside[i].speed = 20.0f;
		bulletBeside[i].velocity = 20.0f;
		bulletBeside[i].isAlive = true;
		bulletBeside[i].length = 0.0f;
		bulletBeside[i].theta = 0.0f;
		bulletBeside[i].coolTime = 30.0f;

	}
	//縦
	Bullet bulletVertical[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bulletVertical[i].pos = { 640.0f,30.0f };
		bulletVertical[i].prePoint;
		bulletVertical[i].fixedPos = { 640.0f,30.0f };
		bulletVertical[i].move;
		bulletVertical[i].radius = 30.0f;
		bulletVertical[i].speed = 10.0f;
		bulletVertical[i].velocity = 10.0f;
		bulletVertical[i].isAlive = true;
		bulletVertical[i].length = 0.0f;
		bulletVertical[i].theta = 0.0f;
		bulletVertical[i].coolTime = 30.0f;
	}
	//斜め
	Bullet bulletDiagonal[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bulletDiagonal[i].pos = { 1250.0f,30.0f };
		bulletDiagonal[i].prePoint;
		bulletDiagonal[i].fixedPos = { 1250.0f,30.0f };
		bulletDiagonal[i].move;
		bulletDiagonal[i].radius = 30.0f;
		bulletDiagonal[i].speed = 10.0f;
		bulletDiagonal[i].velocity = 10.0f;
		bulletDiagonal[i].isAlive = true;
		bulletDiagonal[i].length = 0.0f;
		bulletDiagonal[i].theta = 0.0f;
		bulletDiagonal[i].coolTime = 30.0f;
	}
	/*int coolTimeVertical = 30;*/
	int coolTimeBeside = 0;
	float bullretBesideCount = 0.0f;
	float bullretVerticalCount = 0.0f;
	float bullretDiagonalCount = 0.0f;

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

		//縦散弾
		if (bullretVerticalCount < 6) {
			for (int i = 0; i < maxBullet; i++) {

				//回転
				bulletVertical[i].theta = (6.0f - i) / 12.0f * float(M_PI);//1/6～8/6の角度
				bulletVertical[i].move.x = cosf(bulletVertical[i].theta) - sinf(bulletVertical[i].theta);
				bulletVertical[i].move.y = sinf(bulletVertical[i].theta) + cosf(bulletVertical[i].theta);
				if (bulletVertical[i].isAlive == true) {
					//正規化
					bulletVertical[i].length = sqrtf(bulletVertical[i].move.x * bulletVertical[i].move.x + bulletVertical[i].move.y * bulletVertical[i].move.y);

					if (bulletVertical[i].length >= 1.0f) {
						bulletVertical[i].move.x /= bulletVertical[i].length;
						bulletVertical[i].move.y /= bulletVertical[i].length;
						bulletVertical[i].pos.x += bulletVertical[i].move.x ;
						bulletVertical[i].pos.y += bulletVertical[i].move.y ;
					}
				}
				if (bulletVertical[i].pos.x <= 0.0f || bulletVertical[i].pos.y <= 0.0f || bulletVertical[i].pos.y >= 720.0f || bulletVertical[i].pos.x >= 1280.0f) {
					bulletVertical[i].isAlive = false;
					bulletVertical[i].pos = bulletVertical[i].fixedPos;
					bullretVerticalCount++;
					if (bullretVerticalCount == maxBullet) {
						bulletVertical[i].isAlive = true;
						bullretVerticalCount = 0.0f;
						for (int j = 0; j < maxBullet; j++) {
							bulletVertical[j].pos = { 640.0f,30.0f };
							bulletVertical[j].prePoint;
							bulletVertical[j].fixedPos = { 640.0f,30.0f };
							bulletVertical[j].move;
							bulletVertical[j].radius = 30.0f;
							bulletVertical[j].speed = 10.0f;
							bulletVertical[j].velocity = 10.0f;
							bulletVertical[j].isAlive = true;
							bulletVertical[j].length = 0.0f;
							bulletVertical[j].theta = 0.0f;
							bulletVertical[j].coolTime = 30.0f;
						}

					}
				}
			}
		}
		
		//横散弾
		if (bullretBesideCount < 6) {
			for (int i = 0; i < maxBullet; i++) {
				if (coolTimeBeside % 1 == 0) {
					//回転
					bulletBeside[i].theta = (10.0f - i) / 12.0f * float(M_PI);//1/6～8/6の角度
					bulletBeside[i].move.x = cosf(bulletBeside[i].theta) - sinf(bulletBeside[i].theta);
					bulletBeside[i].move.y = sinf(bulletBeside[i].theta) + cosf(bulletBeside[i].theta);
					if (bulletBeside[i].isAlive == true) {

						////正規化
						bulletBeside[i].length = sqrtf(bulletBeside[i].move.x * bulletBeside[i].move.x + bulletBeside[i].move.y * bulletBeside[i].move.y);

						if (bulletBeside[i].length >= 1.0f) {
							bulletBeside[i].move.x /= bulletBeside[i].length;
							bulletBeside[i].move.y /= bulletBeside[i].length;
							bulletBeside[i].pos.x += bulletBeside[i].move.x;
							bulletBeside[i].pos.y += bulletBeside[i].move.y;
						}
					}
					if (bulletBeside[i].pos.x < 0.0f || bulletBeside[i].pos.x > 1280.0f || bulletBeside[i].pos.y < 0.0f || bulletBeside[i].pos.y > 720.0f) {
						bulletBeside[i].isAlive = false;
						bulletBeside[i].pos = bulletBeside[i].fixedPos;
						bullretBesideCount++;

						if (bullretBesideCount == maxBullet) {
							bulletBeside[i].isAlive = true;
							bullretBesideCount = 0;
							for (int j = 0; j < maxBullet; j++) {
								bulletBeside[j].pos = { 1200.0f,360.0f };
								bulletBeside[j].prePoint;
								bulletBeside[j].fixedPos = { 1200.0f,360.0f };
								bulletBeside[j].move;
								bulletBeside[j].radius = 30.0f;
								bulletBeside[j].speed = 10.0f;
								bulletBeside[j].velocity = 10.0f;
								bulletBeside[j].isAlive = true;
								bulletBeside[j].length = 0.0f;
								bulletBeside[j].theta = 0.0f;
								bulletBeside[j].coolTime = 30.0f;

							}
						}
					}

				}

				coolTimeBeside++;


			}
		}
		//斜め散弾
		if (bullretDiagonalCount < 6) {
			for (int i = 0; i < maxBullet; i++) {

				//回転
				bulletDiagonal[i].theta = (9.0f - i) / 12.0f * float(M_PI);//1/6～8/6の角度
				bulletDiagonal[i].move.x = cosf(bulletDiagonal[i].theta) - sinf(bulletDiagonal[i].theta);
				bulletDiagonal[i].move.y = sinf(bulletDiagonal[i].theta) + cosf(bulletDiagonal[i].theta);
				if (bulletDiagonal[i].isAlive == true) {
					//正規化
					bulletDiagonal[i].length = sqrtf(bulletDiagonal[i].move.x * bulletDiagonal[i].move.x + bulletDiagonal[i].move.y * bulletDiagonal[i].move.y);

					if (bulletDiagonal[i].length >= 1.0f) {
						bulletDiagonal[i].move.x /= bulletDiagonal[i].length;
						bulletDiagonal[i].move.y /= bulletDiagonal[i].length;
						bulletDiagonal[i].pos.x += bulletDiagonal[i].move.x;
						bulletDiagonal[i].pos.y += bulletDiagonal[i].move.y;
					}
				}
				if (bulletDiagonal[i].pos.x <= 0.0f || bulletDiagonal[i].pos.y <= 0.0f || bulletDiagonal[i].pos.y >= 720.0f || bulletDiagonal[i].pos.x >= 1280.0f) {
					bulletDiagonal[i].isAlive = false;
					bulletDiagonal[i].pos = bulletDiagonal[i].fixedPos;
					bullretDiagonalCount++;
				if (bullretDiagonalCount == maxBullet) {
						bulletDiagonal[i].isAlive = true;
						bullretDiagonalCount = 0.0f;
						for (int j = 0; j < maxBullet; j++) {
							bulletDiagonal[j].pos = { 1250.0f,30.0f };
							bulletDiagonal[j].prePoint;
							bulletDiagonal[j].fixedPos = { 1250.0f,30.0f };
							bulletDiagonal[j].move;
							bulletDiagonal[j].radius = 30.0f;
							bulletDiagonal[j].speed = 10.0f;
							bulletDiagonal[j].velocity = 10.0f;
							bulletDiagonal[j].isAlive = true;
							bulletDiagonal[j].length = 0.0f;
							bulletDiagonal[j].theta = 0.0f;
							bulletDiagonal[j].coolTime = 30.0f;
						}

					}
				}
			}
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (int i = 0; i < maxBullet; i++) {
			if (bulletVertical[i].isAlive == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/



				Novice::DrawEllipse(
					static_cast<int>(bulletVertical[i].pos.x), static_cast<int>(bulletVertical[i].pos.y),
					static_cast<int>(bulletVertical[i].radius), static_cast<int>(bulletVertical[i].radius),
					1.0f, RED, kFillModeSolid);
			}
			if (bulletBeside[i].isAlive == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/



				Novice::DrawEllipse(
					static_cast<int>(bulletBeside[i].pos.x), static_cast<int>(bulletBeside[i].pos.y),
					static_cast<int>(bulletBeside[i].radius), static_cast<int>(bulletBeside[i].radius),
					1.0f, RED, kFillModeSolid);
			}
			if (bulletDiagonal[i].isAlive == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/



				Novice::DrawEllipse(
					static_cast<int>(bulletDiagonal[i].pos.x), static_cast<int>(bulletDiagonal[i].pos.y),
					static_cast<int>(bulletDiagonal[i].radius), static_cast<int>(bulletDiagonal[i].radius),
					1.0f, RED, kFillModeSolid);
			}
		}
		for (int i = 0; i < maxBullet; i++) {
			Novice::ScreenPrintf(0, i * 17, "posxVertical%disAlive%d\n\n", static_cast<int>(bulletVertical[i].pos.x), bulletVertical[i].isAlive);
			Novice::ScreenPrintf(0, 102 + i * 17, "posyVertical%d isAlive%d\n\n", static_cast<int>(bulletVertical[i].pos.y), bulletVertical[i].isAlive);
			Novice::ScreenPrintf(0, 204 + i * 17, "posxBeside%d isAlive%d\n\n", static_cast<int>(bulletBeside[i].pos.x), bulletBeside[i].isAlive);
			Novice::ScreenPrintf(0, 306 + i * 17, "posyBeside%d isAlive%d", static_cast<int>(bulletBeside[i].pos.y), bulletBeside[i].isAlive);
			Novice::ScreenPrintf(0, 425 + i * 17, "posxDiagonal%d isAlive%d\n\n", static_cast<int>(bulletDiagonal[i].pos.x), bulletDiagonal[i].isAlive);
			Novice::ScreenPrintf(0, 527 + i * 17, "posyDiagonal%d isAlive%d", static_cast<int>(bulletDiagonal[i].pos.y), bulletDiagonal[i].isAlive);
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

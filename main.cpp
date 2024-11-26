#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


const char kWindowTitle[] = "LC1C_23_ヤリタ_コウヤ_タイトル";

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Player {
	Vector2 pos;
	Vector2 subPos;
	Vector2 prePos;
	Vector2 mapPos;
	Vector2 map;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 move;
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	float lenght;
	float height;
	float width;
	float radius;
	bool isHit;
	int life;
	int jumpCount;
	int rect;
	int moveSpeed;
	int lifeCount;
}Ball;



struct Bullet
{
	Vector2 pos;
	Vector2 prePoint;
	Vector2 fixedPos;
	Vector2 move;
	bool isHit;
	float radius;
	float speed;
	float velocity;
	float length;
	float theta;
	float coolTime;
	float distance;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 736);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	unsigned int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);
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
		bulletBeside[i].speed = 0.0f;
		bulletBeside[i].velocity = 20.0f;
		bulletBeside[i].isHit = true;
		bulletBeside[i].length = 0.0f;
		bulletBeside[i].theta = 0.0f;
		bulletBeside[i].coolTime = 30.0f;
		bulletBeside[i].distance;
	}

	//縦
	Bullet bulletVertical[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bulletVertical[i].pos = { 640.0f,30.0f };
		bulletVertical[i].prePoint;
		bulletVertical[i].fixedPos = { 640.0f,30.0f };
		bulletVertical[i].move;
		bulletVertical[i].radius = 30.0f;
		bulletVertical[i].speed = 0.0f;
		bulletVertical[i].velocity = 10.0f;
		bulletVertical[i].isHit = true;
		bulletVertical[i].length = 0.0f;
		bulletVertical[i].theta = 0.0f;
		bulletVertical[i].coolTime = 30.0f;
		bulletVertical[i].distance;
	}

	//斜め
	Bullet bulletDiagonal[maxBullet] = {};
	for (int i = 0; i < maxBullet; i++) {
		bulletDiagonal[i].pos = { 1250.0f,30.0f };
		bulletDiagonal[i].prePoint;
		bulletDiagonal[i].fixedPos = { 1250.0f,30.0f };
		bulletDiagonal[i].move;
		bulletDiagonal[i].radius = 30.0f;
		bulletDiagonal[i].speed = 0.0f;
		bulletDiagonal[i].velocity = 10.0f;
		bulletDiagonal[i].isHit = true;
		bulletDiagonal[i].length = 0.0f;
		bulletDiagonal[i].theta = 0.0f;
		bulletDiagonal[i].coolTime = 30.0f;
		bulletDiagonal[i].distance;
	}

	/*int coolTimeVertical = 30;*/
	int coolTimeBeside = 0;
	float bullretBesideCount = 0.0f;
	float bullretVerticalCount = 0.0f;
	float bullretDiagonalCount = 0.0f;

	int block1 = Novice::LoadTexture("./Resources/block_1.png");//地面ブロック
	int block2 = Novice::LoadTexture("./Resources/block_2.png");//浮いてるブロック
	int Bullet = Novice::LoadTexture("./Resources/Bullet.png");//
	//kint Bullet = Novice::LoadTexture("./Resources/Bullet.png");//



	int blockSize = 32;
	int blockNum = 0;

	int map[23][40] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	};

	Player player{};
	player.pos = { 64.0f,636.0f };
	player.prePos = { 0.0f,0.0f };
	player.mapPos = { 0.0f,0.0f };
	player.map = { 0.0f,0.0f };
	player.velocity = { 0.0f,0.0f };
	player.acceleration = { 0.0f,0.8f };
	player.move = { 0.0f,0.0f };
	player.leftTop = { 0.0f,0.0f };
	player.rightTop = { 0.0f,0.0f };
	player.leftBottom = { 0.0f,0.0f };
	player.rightBottom = { 0.0f,0.0f };
	player.lenght = 0.0f;
	player.height = 32.0f;
	player.width = 32.0f;
	player.jumpCount = 0;
	player.rect = 100;
	player.moveSpeed = 5;
	player.radius = 25.0f;
	player.isHit = true;
	player.lifeCount = 200;

	player.subPos = { player.pos.x + player.width / 2,player.pos.y + player.height / 2 };
	Vector2 mapNumber = { player.pos.x / 32,player.pos.y / 32 };





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

#pragma region bullet

		//縦散弾

		
			
		

		if (bullretVerticalCount < 6) {

			for (int i = 0; i < maxBullet; i++) {
				
				//回転
				bulletVertical[i].theta = (6.0f - i) / 12.0f * float(M_PI);//1/6～8/6の角度
				bulletVertical[i].move.x = cosf(bulletVertical[i].theta) - sinf(bulletVertical[i].theta);
				bulletVertical[i].move.y = sinf(bulletVertical[i].theta) + cosf(bulletVertical[i].theta);
				if (bulletVertical[i].isHit == true) {
					//正規化
					bulletVertical[i].length = sqrtf(bulletVertical[i].move.x * bulletVertical[i].move.x + bulletVertical[i].move.y * bulletVertical[i].move.y);

					if (bulletVertical[i].length >= 1.0f) {
						bulletVertical[i].move.x /= bulletVertical[i].length;
						bulletVertical[i].move.y /= bulletVertical[i].length;
						bulletVertical[i].pos.x += bulletVertical[i].move.x * (bulletVertical[i].speed + rand() % 9 + 1);
						bulletVertical[i].pos.y += bulletVertical[i].move.y * (bulletVertical[i].speed + rand() % 13 + 1);
					}
				}
				if (bulletVertical[i].pos.x <= 0.0f || bulletVertical[i].pos.y <= 0.0f || bulletVertical[i].pos.y >= 720.0f || bulletVertical[i].pos.x >= 1280.0f) {
					bulletVertical[i].isHit = false;
					bulletVertical[i].pos = bulletVertical[i].fixedPos;
					bullretVerticalCount++;
					if (bullretVerticalCount == maxBullet) {
						bulletVertical[i].isHit = true;
						bullretVerticalCount = 0.0f;
						for (int j = 0; j < maxBullet; j++) {
							bulletVertical[j].pos = { 640.0f,30.0f };
							bulletVertical[j].prePoint;
							bulletVertical[j].fixedPos = { 640.0f,30.0f };
							bulletVertical[j].move;
							bulletVertical[j].radius = 30.0f;
							bulletVertical[j].speed = 0.0f;
							bulletVertical[j].velocity = 10.0f;
							bulletVertical[j].isHit = true;
							bulletVertical[j].length = 0.0f;
							bulletVertical[j].theta = 0.0f;
							bulletVertical[j].coolTime = 30.0f;
							bulletVertical[i].pos.x = static_cast<float>(rand() % 1280 + 1);
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
					if (bulletBeside[i].isHit == true) {

						////正規化
						bulletBeside[i].length = sqrtf(bulletBeside[i].move.x * bulletBeside[i].move.x + bulletBeside[i].move.y * bulletBeside[i].move.y);

						if (bulletBeside[i].length >= 1.0f) {
							bulletBeside[i].move.x /= bulletBeside[i].length;
							bulletBeside[i].move.y /= bulletBeside[i].length;
							bulletBeside[i].pos.x += bulletBeside[i].move.x * (bulletBeside[i].speed + rand() % 9 + 1);
							bulletBeside[i].pos.y += bulletBeside[i].move.y * (bulletBeside[i].speed + rand() % 13 + 1);
						}
					}
					if (bulletBeside[i].pos.x < 0.0f || bulletBeside[i].pos.x > 1280.0f || bulletBeside[i].pos.y < 0.0f || bulletBeside[i].pos.y > 720.0f) {
						bulletBeside[i].isHit = false;
						bulletBeside[i].pos = bulletBeside[i].fixedPos;
						bullretBesideCount++;

						if (bullretBesideCount == maxBullet) {
							bulletBeside[i].isHit = true;
							bullretBesideCount = 0;
							for (int j = 0; j < maxBullet; j++) {
								bulletBeside[j].pos = { 1200.0f,360.0f };
								bulletBeside[j].prePoint;
								bulletBeside[j].fixedPos = { 1200.0f,360.0f };
								bulletBeside[j].move;
								bulletBeside[j].radius = 30.0f;
								bulletBeside[j].speed = 0.0f;
								bulletBeside[j].velocity = 10.0f;
								bulletBeside[j].isHit = true;
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
				if (bulletDiagonal[i].isHit == true) {
					//正規化
					bulletDiagonal[i].length = sqrtf(bulletDiagonal[i].move.x * bulletDiagonal[i].move.x + bulletDiagonal[i].move.y * bulletDiagonal[i].move.y);

					if (bulletDiagonal[i].length >= 1.0f) {
						bulletDiagonal[i].move.x /= bulletDiagonal[i].length;
						bulletDiagonal[i].move.y /= bulletDiagonal[i].length;
						bulletDiagonal[i].pos.x += bulletDiagonal[i].move.x * (bulletDiagonal[i].speed + rand() % 9 + 1);
						bulletDiagonal[i].pos.y += bulletDiagonal[i].move.y * (bulletDiagonal[i].speed + rand() % 13 + 1);
					}
				}
				if (bulletDiagonal[i].pos.x <= 0.0f || bulletDiagonal[i].pos.y <= 0.0f || bulletDiagonal[i].pos.y >= 720.0f || bulletDiagonal[i].pos.x >= 1280.0f) {
					bulletDiagonal[i].isHit = false;
					bulletDiagonal[i].pos = bulletDiagonal[i].fixedPos;
					bullretDiagonalCount++;
					if (bullretDiagonalCount == maxBullet) {
						bulletDiagonal[i].isHit = true;
						bullretDiagonalCount = 0.0f;
						for (int j = 0; j < maxBullet; j++) {
							bulletDiagonal[j].pos = { 1250.0f,30.0f };
							bulletDiagonal[j].prePoint;
							bulletDiagonal[j].fixedPos = { 1250.0f,30.0f };
							bulletDiagonal[j].move;
							bulletDiagonal[j].radius = 30.0f;
							bulletDiagonal[j].speed = 0.0f;
							bulletDiagonal[j].velocity = 10.0f;
							bulletDiagonal[j].isHit = true;
							bulletDiagonal[j].length = 0.0f;
							bulletDiagonal[j].theta = 0.0f;
							bulletDiagonal[j].coolTime = 30.0f;
						}

					}
				}
			}
		}

#pragma endregion
#pragma region 弾の当たり判定
		if (player.isHit == true) {
			for (int i = 0; i < maxBullet; i++) {

				player.subPos = { player.pos.x + (player.width / 2),player.pos.y + (player.height / 2) };
				//距離計算
				bulletBeside[i].distance =
					sqrtf((bulletBeside[i].pos.x - player.subPos.x) * (bulletBeside[i].pos.x - player.subPos.x) +
						(bulletBeside[i].pos.y - player.subPos.y) * (bulletBeside[i].pos.y - player.subPos.y));
				bulletDiagonal[i].distance =
					sqrtf((bulletDiagonal[i].pos.x - player.subPos.x) * (bulletDiagonal[i].pos.x - player.subPos.x) +
						(bulletDiagonal[i].pos.y - player.subPos.y) * (bulletDiagonal[i].pos.y - player.subPos.y));
				bulletVertical[i].distance =
					sqrtf((bulletVertical[i].pos.x - player.subPos.x) * (bulletVertical[i].pos.x - player.subPos.x) +
						(bulletVertical[i].pos.y - player.subPos.y) * (bulletVertical[i].pos.y - player.subPos.y));


				if (bulletBeside[i].isHit == true) {
					if (bulletBeside[i].distance < player.radius + bulletBeside[i].radius) {
						bulletBeside[i].isHit = false;
						player.isHit = false;
						bullretBesideCount++;
						if (bullretBesideCount == maxBullet) {
							bulletBeside[i].isHit = true;
							bullretBesideCount = 0;
							for (int j = 0; j < maxBullet; j++) {
								bulletBeside[j].pos = { 1200.0f,360.0f };
								bulletBeside[j].prePoint;
								bulletBeside[j].fixedPos = { 1200.0f,360.0f };
								bulletBeside[j].move;
								bulletBeside[j].radius = 30.0f;
								bulletBeside[j].speed = 10.0f;
								bulletBeside[j].velocity = 10.0f;
								bulletBeside[j].isHit = true;
								bulletBeside[j].length = 0.0f;
								bulletBeside[j].theta = 0.0f;
								bulletBeside[j].coolTime = 30.0f;

							}
						}
					}

				}
				if (bulletDiagonal[i].isHit == true) {
					if (bulletDiagonal[i].distance < player.radius + bulletDiagonal[i].radius) {
						bulletDiagonal[i].isHit = false;
						player.isHit = false;
						bullretDiagonalCount++;
						if (bullretDiagonalCount == maxBullet) {
							bulletDiagonal[i].isHit = true;
							bullretDiagonalCount = 0.0f;
							for (int j = 0; j < maxBullet; j++) {
								bulletDiagonal[j].pos = { 1250.0f,30.0f };
								bulletDiagonal[j].prePoint;
								bulletDiagonal[j].fixedPos = { 1250.0f,30.0f };
								bulletDiagonal[j].move;
								bulletDiagonal[j].radius = 30.0f;
								bulletDiagonal[j].speed = 10.0f;
								bulletDiagonal[j].velocity = 10.0f;
								bulletDiagonal[j].isHit = true;
								bulletDiagonal[j].length = 0.0f;
								bulletDiagonal[j].theta = 0.0f;
								bulletDiagonal[j].coolTime = 30.0f;
							}
						}
					}
				}
				if (bulletVertical[i].isHit == true) {
					if (bulletVertical[i].distance < player.radius + bulletVertical[i].radius) {
						bulletVertical[i].isHit = false;
						player.isHit = false;
						bullretVerticalCount++;

						if (bullretVerticalCount == maxBullet) {
							bulletVertical[i].isHit = true;
							bullretVerticalCount = 0.0f;
							for (int j = 0; j < maxBullet; j++) {
								bulletVertical[j].pos = { 640.0f,30.0f };
								bulletVertical[j].prePoint;
								bulletVertical[j].fixedPos = { 640.0f,30.0f };
								bulletVertical[j].move;
								bulletVertical[j].radius = 30.0f;
								bulletVertical[j].speed = 10.0f;
								bulletVertical[j].velocity = 10.0f;
								bulletVertical[j].isHit = true;
								bulletVertical[j].length = 0.0f;
								bulletVertical[j].theta = 0.0f;
								bulletVertical[j].coolTime = 30.0f;
							}

						}


					}
				}

			}
		}
		if (player.isHit == false) {
			player.lifeCount--;
			if (player.lifeCount <= 0) {
				player.isHit = true;
				player.lifeCount = 200;
			}
		}
#pragma endregion

#pragma region 地面との当たり判定

		//段差と床の当たり判定
		if (player.pos.x >= 0 && player.pos.x < 6 * blockSize ||
			player.pos.x + player.width >= 34 * blockSize && player.pos.x + player.width < 36 * blockSize) {
			blockNum = 16;
		}

		if (player.pos.x >= 6 * blockSize && player.pos.x < 8 * blockSize ||
			player.pos.x + player.width >= 32 * blockSize && player.pos.x + player.width < 34 * blockSize) {
			blockNum = 17;


		}

		if (player.pos.x >= 8 * blockSize && player.pos.x < 10 * blockSize ||
			player.pos.x + player.width >= 30 * blockSize && player.pos.x + player.width < 32 * blockSize) {
			blockNum = 18;


		}

		if (player.pos.x >= 10 * blockSize && player.pos.x < 29 * blockSize) {
			blockNum = 19;

		}

		//空中の床の当たり判定
		//左下
		if ((player.pos.x >= 7 * blockSize && player.pos.x < 15 * blockSize) &&
			(player.pos.y >= 14 * blockSize && player.pos.y < 15 * blockSize)) {
			blockNum = 13;
			player.velocity.y = 0.0f;

		}
		//左上
		if ((player.pos.x >= 7 * blockSize && player.pos.x < 15 * blockSize) &&
			(player.pos.y >= 6 * blockSize && player.pos.y < 7 * blockSize)) {
			blockNum = 5;
			player.velocity.y = 0.0f;

		}

		//右下
		if ((player.pos.x >= 24 * blockSize && player.pos.x < 32 * blockSize) &&
			(player.pos.y >= 14 * blockSize && player.pos.y < 15 * blockSize)) {
			blockNum = 13;
			player.velocity.y = 0.0f;

		}
		//右上
		if ((player.pos.x >= 24 * blockSize && player.pos.x < 32 * blockSize) &&
			(player.pos.y >= 6 * blockSize && player.pos.y < 7 * blockSize)) {
			blockNum = 5;
			player.velocity.y = 0.0f;

		}

		//真ん中
		if ((player.pos.x >= 13 * blockSize && player.pos.x < 26 * blockSize) &&
			(player.pos.y >= 10 * blockSize && player.pos.y < 11 * blockSize)) {
			blockNum = 9;
			player.velocity.y = 0.0f;

		}
#pragma endregion

#pragma region 自機の移動

		player.move.x = 0.0f;
		player.move.y = 0.0f;

		if (keys[DIK_A] || keys[DIK_LEFT]) {
			player.move.x -= 1.0f;
			if (player.pos.y == 18 * blockSize && player.pos.x <= 6.1f * blockSize ||
				player.pos.y == 17 * blockSize && player.pos.x <= 8.1f * blockSize ||
				player.pos.y == 16 * blockSize && player.pos.x <= 10.13f * blockSize) {
				player.move.x += 1.0f;
			}
		}

		if (keys[DIK_D] || keys[DIK_RIGHT]) {
			player.move.x += 1.0f;
			if (player.pos.y == 18 * blockSize && player.pos.x + player.width >= 33.9f * blockSize ||
				player.pos.y == 17 * blockSize && player.pos.x + player.width >= 31.9f * blockSize ||
				player.pos.y == 16 * blockSize && player.pos.x + player.width >= 29.8f * blockSize) {
				player.move.x -= 1.0f;
			}
		}

		player.lenght = sqrtf(player.move.x * player.move.x + player.move.y * player.move.y);
		if (player.lenght != 0.0f) {
			player.move.x /= player.lenght;
			player.move.y /= player.lenght;
		}

		player.pos.x += player.move.x * player.moveSpeed;
		player.pos.y += player.move.y * player.moveSpeed;

#pragma endregion


#pragma region ジャンプ

		//地上でのジャンプ
		if (keys[DIK_SPACE] != 0 && !preKeys[DIK_SPACE] && player.pos.y == player.height) {
			if (player.jumpCount <= 2) {
				player.velocity.y = 13.0f;
			}
		}

		//空中ジャンプ
		if (keys[DIK_SPACE] != 0 && !preKeys[DIK_SPACE] && player.pos.y >= player.height) {
			if (player.jumpCount <= 2) {
				player.velocity.y = 13.0f;
			}
		}

		//ジャンプの回数制限
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			player.jumpCount++;
		}

		//ジャンプの速度に加速度を足す
		player.velocity.x -= player.acceleration.x;
		player.velocity.y -= player.acceleration.y;

		//ジャンプの位置に速度を足す
		player.pos.x -= player.velocity.x;
		player.pos.y -= player.velocity.y;

		if (player.pos.y >= player.height + blockNum * blockSize) {
			player.pos.y = player.height + blockNum * blockSize;
			player.jumpCount = 0;
		}

#pragma endregion





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		for (int y = 0; y < 23; y++) {
			for (int x = 0; x < 40; x++) {
				if (map[y][x] == 1) {
					Novice::DrawSprite(x * 32, y * 32, block1, 1.0f, 1.0f, 0.0f, WHITE);
				}
				if (map[y][x] == 2) {
					Novice::DrawSprite(x * 32, y * 32, block2, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
		}


		for (int i = 0; i < maxBullet; i++) {
			if (bulletVertical[i].isHit == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/
				Novice::DrawSprite(
					static_cast<int>(bulletVertical[i].pos.x - 25), static_cast<int>(bulletVertical[i].pos.y - 25),
					Bullet, 1.0f, 1.0f, 0.0f, WHITE);


				/*Novice::DrawEllipse(
					static_cast<int>(bulletVertical[i].pos.x), static_cast<int>(bulletVertical[i].pos.y),
					static_cast<int>(bulletVertical[i].radius), static_cast<int>(bulletVertical[i].radius),
					1.0f, RED, kFillModeSolid);*/
			}
			if (bulletBeside[i].isHit == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/
				Novice::DrawSprite(
					static_cast<int>(bulletBeside[i].pos.x - 25), static_cast<int>(bulletBeside[i].pos.y - 25),
					Bullet, 1.0f, 1.0f, 0.0f, WHITE);



				/*Novice::DrawEllipse(
					static_cast<int>(bulletBeside[i].pos.x), static_cast<int>(bulletBeside[i].pos.y),
					static_cast<int>(bulletBeside[i].radius), static_cast<int>(bulletBeside[i].radius),
					1.0f, RED, kFillModeSolid);*/
			}
			if (bulletDiagonal[i].isHit == true) {
				/*bullet[i].pos.y = 100.0f + i * 80.0f;*/
				Novice::DrawSprite(
					static_cast<int>(bulletDiagonal[i].pos.x - 25), static_cast<int>(bulletDiagonal[i].pos.y - 25),
					Bullet, 1.0f, 1.0f, 0.0f, WHITE);


				/*Novice::DrawEllipse(
					static_cast<int>(bulletDiagonal[i].pos.x), static_cast<int>(bulletDiagonal[i].pos.y),
					static_cast<int>(bulletDiagonal[i].radius), static_cast<int>(bulletDiagonal[i].radius),
					1.0f, RED, kFillModeSolid);*/
			}
		}


		for (int y = 0; y < 23; y++) {
			for (int x = 0; x < 40; x++) {
				if (map[y][x] == 1) {
					Novice::DrawSprite(x * blockSize, y * blockSize, block1, 1.0f, 1.0f, 0.0f, WHITE);
				}
				if (map[y][x] == 2) {
					Novice::DrawSprite(x * blockSize, y * blockSize, block2, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
		}

		if (player.isHit == true) {
			Novice::DrawBox(
				static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
				static_cast<int>(player.width), static_cast<int>(player.height),
				0.0f, WHITE, kFillModeSolid);
		}
		else if (player.lifeCount >= 0) {

			if (player.lifeCount % 10 == 0) {
				Novice::DrawBox(
					static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
					static_cast<int>(player.width), static_cast<int>(player.height),
					0.0f, RED, kFillModeSolid);
			}

		}
		//デバッグ用の描画
		Novice::ScreenPrintf(0, 0, "player.pos.x %.1f", player.pos.x);
		Novice::ScreenPrintf(0, 20, "player.pos.y %.1f", player.pos.y);
		Novice::ScreenPrintf(0, 40, "ball.height %.1f", player.height);
		Novice::ScreenPrintf(0, 60, "player.leftTop.x %.1f", player.leftTop.x);
		Novice::ScreenPrintf(0, 80, "player.leftTop.y %.1f", player.leftTop.y);
		Novice::ScreenPrintf(0, 100, "player.rightTop.x %.1f", player.rightTop.x);
		Novice::ScreenPrintf(0, 120, "player.rightTop.y %.1f", player.rightTop.y);
		Novice::ScreenPrintf(0, 140, "player.leftBottom.x %.1f", player.leftBottom.x);
		Novice::ScreenPrintf(0, 160, "player.leftBottom.y %.1f", player.leftBottom.y);
		Novice::ScreenPrintf(0, 180, "player.rightBottom.x %.1f", player.rightBottom.x);
		Novice::ScreenPrintf(0, 200, "player.rightBottom.y %.1f", player.rightBottom.y);
		Novice::ScreenPrintf(0, 220, "bulletB = %d", static_cast<int>(bullretBesideCount));
		Novice::ScreenPrintf(0, 240, "bulletD = %d", static_cast<int>(bullretDiagonalCount));
		Novice::ScreenPrintf(0, 260, "bulletV = %d", static_cast<int>(bullretVerticalCount));
		Novice::ScreenPrintf(0, 280, "player.isHit %d", player.isHit);
		Novice::ScreenPrintf(0, 300, "player.count %d", player.lifeCount);




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

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>



const char kWindowTitle[] = "LC1C_23_ヤリタ_コウヤ_タイトル";

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Player {
	Vector2 pos;
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
	int jumpCount;
	int rect;
	int moveSpeed;
	//レーザーに使う
	float radius;
	unsigned int color;
}Ball;



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

typedef struct Laser {
	Vector2 pos;//画面の位置
	Vector2 width;
	float size;//画像のサイズ
	float move;//レーザーの描画範囲を動かす
	int isShot;//レーザーの
	int coolTime;
}Laser;

typedef struct LaserCapsule {
	Vector2 start;
	Vector2 end;
	float radius;
	unsigned int color;
}LaserCapsule;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 736);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	enum Scene {
		TITLE,
		EXPLAIN,
		GAMESCENE,
		GAMEOVER,
		CLEAR
	};
	int scene = GAMESCENE;

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


#pragma region レーザー初期
#pragma region 横向きレーザー初期
	Laser horizontalLaser = {};
	horizontalLaser.size = 64.0f;//元の画像サイズ
	horizontalLaser.pos = { 0.0f,0.0f };//画面の上の位置
	horizontalLaser.move = 0;//レーザーの描画範囲を動かす
	horizontalLaser.width = { 64.0f,64.0f };
	horizontalLaser.isShot = true;
	horizontalLaser.coolTime = 5;

	LaserCapsule horizontalLaserCapsule = {};
	horizontalLaserCapsule.start = { -100 , float(rand() % 720 + 40) };
	horizontalLaserCapsule.end = { -100,horizontalLaserCapsule.start.y + 32 };
	horizontalLaserCapsule.radius = { 32.0f };
	horizontalLaserCapsule.color = WHITE;

	Vector2 horizontalLaserLineVector{};
	Vector2 horizontalLaserUnitVector{};
	Vector2 horizontalLaserToCenter{};
	Vector2 horizontalLaserClosestPoint{};
	Vector2 horizontalLaserClosestPointToCenter{};

	float horizontalLaserLength = 0.0f;
	float horizontalLaserDot = 0.0f;
	float horizontalLaserSumRadius = 0.0f;
#pragma endregion

#pragma region 縦向きレーザー初期
	Laser verticalLaser = {};
	verticalLaser.size = 64.0f;//元の画像サイズ
	verticalLaser.pos = { 0.0f,0.0f };//画面の位置
	verticalLaser.move = 0;//レーザーの描画範囲を動かす
	verticalLaser.width = { 64.0f,64.0f };
	verticalLaser.isShot = true;
	verticalLaser.coolTime = 5;

	LaserCapsule verticalLaserCapsule = {};
	verticalLaserCapsule.start = { float(rand() % 1200 + 40) ,-100 };
	verticalLaserCapsule.end = { verticalLaserCapsule.start.x + 32,-100 };
	verticalLaserCapsule.radius = { 32.0f };
	verticalLaserCapsule.color = WHITE;

	Vector2 verticalLaserLineVector{};
	Vector2 verticalLaserUnitVector{};
	Vector2 verticalLaserToCenter{};
	Vector2 verticalLaserClosestPoint{};
	Vector2 verticalLaserClosestPointToCenter{};

	float verticalLaserLength = 0.0f;
	float verticalLaserDot = 0.0f;
	float verticalLaserSumRadius = 0.0f;
#pragma endregion

#pragma region 斜めレーザー
	Laser obliqueLaser = {};
	obliqueLaser.size = 128.0f;
	obliqueLaser.pos = { 0.0f,0.0f };
	obliqueLaser.move = 0;
	obliqueLaser.isShot = false;
	obliqueLaser.coolTime = 5;

	//カプセル(斜め)
	LaserCapsule obliqueLaserCapsule = {};
	obliqueLaserCapsule.start = { float(rand() % 1200),0 };
	obliqueLaserCapsule.end = { obliqueLaserCapsule.start.x+1024, obliqueLaserCapsule.start.y + 1024 };
	obliqueLaserCapsule.radius = { 32.0f };
	obliqueLaserCapsule.color = WHITE;

	Vector2 obliqueLaserLineVector{};
	Vector2 obliqueLaserUnitVector{};
	Vector2 obliqueLaserToCenter{};
	Vector2 obliqueLaserClosestPoint{};
	Vector2 obliqueLaserClosestPointToCenter{};

	float obliqueLaserLength = 0.0f;
	float obliqueLaserDot = 0.0f;
	float obliqueLaserSumRadius = 0.0f;
#pragma endregion

#pragma endregion
#pragma region レーザー画像
	int horizontalLaserGr = Novice::LoadTexture("./Resources/laser.png");
	int verticalLaserGr = Novice::LoadTexture("./Resources/verticalLaser.png");
	int obliqueLaserGr = Novice::LoadTexture("./Resources/obliqueLaser.png");
#pragma endregion


	int block1 = Novice::LoadTexture("./Resources/block_1.png");//地面ブロック
	int block2 = Novice::LoadTexture("./Resources/block_2.png");//浮いてるブロック

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

	Player player;
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
	player.radius = 16.0f;
	player.color = WHITE;

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

		if (scene == GAMESCENE)
		{

#pragma region bullet

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
							bulletVertical[i].pos.x += bulletVertical[i].move.x;
							bulletVertical[i].pos.y += bulletVertical[i].move.y;
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

#pragma endregion

#pragma region レーザー当たり判定
#pragma region レーザー当たり判定(横)		
			//横向きのレーザー縦向きのレーザー
			if (horizontalLaserCapsule.end.x < 1300)
			{
				horizontalLaser.isShot = true;

				horizontalLaserLineVector.x = horizontalLaserCapsule.end.x - horizontalLaserCapsule.start.x;
				horizontalLaserLineVector.y = horizontalLaserCapsule.end.y - horizontalLaserCapsule.start.y;
				horizontalLaserLength = sqrtf(horizontalLaserLineVector.x * horizontalLaserLineVector.x + horizontalLaserLineVector.y * horizontalLaserLineVector.y);

				horizontalLaserUnitVector = horizontalLaserLineVector;
				if (horizontalLaserLength != 0.0f)
				{
					horizontalLaserUnitVector.x = horizontalLaserLineVector.x / horizontalLaserLength;
					horizontalLaserUnitVector.y = horizontalLaserLineVector.y / horizontalLaserLength;
				}

				horizontalLaserToCenter.x = player.pos.x - horizontalLaserCapsule.start.x;
				horizontalLaserToCenter.y = player.pos.y - horizontalLaserCapsule.start.y;

				horizontalLaserDot = horizontalLaserToCenter.x * horizontalLaserUnitVector.x + horizontalLaserToCenter.y * horizontalLaserUnitVector.y;

				horizontalLaserDot = fmaxf(0.0f, fminf(horizontalLaserDot, horizontalLaserLength));
				horizontalLaserClosestPoint.x = horizontalLaserCapsule.start.x + horizontalLaserUnitVector.x * horizontalLaserDot;
				horizontalLaserClosestPoint.y = horizontalLaserCapsule.start.y + horizontalLaserUnitVector.y * horizontalLaserDot;

				horizontalLaserClosestPointToCenter.x = player.pos.x - horizontalLaserClosestPoint.x;
				horizontalLaserClosestPointToCenter.y = player.pos.y - horizontalLaserClosestPoint.y;

				horizontalLaserDot = sqrtf(horizontalLaserClosestPointToCenter.x * horizontalLaserClosestPointToCenter.x + horizontalLaserClosestPointToCenter.y * horizontalLaserClosestPointToCenter.y);

				horizontalLaserSumRadius = player.radius + horizontalLaserCapsule.radius;

				if (horizontalLaserDot < horizontalLaserSumRadius)
				{
					horizontalLaser.isShot = true;
					player.color = RED;
				} else
				{
					player.color = WHITE;
				}
			} else
			{
				horizontalLaser.isShot = false;
				horizontalLaserCapsule.start = { -64,float(rand() % 700 + 40) };
				horizontalLaserCapsule.end = { -64,horizontalLaserCapsule.start.y + 32 };

			}
#pragma endregion
#pragma region レーザー当たり判定(縦)
			if (verticalLaserCapsule.end.y < 800)
			{
				verticalLaser.isShot = true;
				//縦
				verticalLaserLineVector.x = verticalLaserCapsule.end.x - verticalLaserCapsule.start.x;
				verticalLaserLineVector.y = verticalLaserCapsule.end.y - verticalLaserCapsule.start.y;
				verticalLaserLength = sqrtf(verticalLaserLineVector.x * verticalLaserLineVector.x + verticalLaserLineVector.y * verticalLaserLineVector.y);

				verticalLaserUnitVector = verticalLaserLineVector;
				if (verticalLaserLength != 0.0f)
				{
					verticalLaserUnitVector.x = verticalLaserLineVector.x / verticalLaserLength;
					verticalLaserUnitVector.y = verticalLaserLineVector.y / verticalLaserLength;
				}

				verticalLaserToCenter.x = player.pos.x - verticalLaserCapsule.start.x;
				verticalLaserToCenter.y = player.pos.y - verticalLaserCapsule.start.y;

				verticalLaserDot = verticalLaserToCenter.x * verticalLaserUnitVector.x + verticalLaserToCenter.y * verticalLaserUnitVector.y;

				verticalLaserDot = fmaxf(0.0f, fminf(verticalLaserDot, verticalLaserLength));
				verticalLaserClosestPoint.x = verticalLaserCapsule.start.x + verticalLaserUnitVector.x * verticalLaserDot;
				verticalLaserClosestPoint.y = verticalLaserCapsule.start.y + verticalLaserUnitVector.y * verticalLaserDot;

				verticalLaserClosestPointToCenter.x = player.pos.x - verticalLaserClosestPoint.x;
				verticalLaserClosestPointToCenter.y = player.pos.y - verticalLaserClosestPoint.y;

				verticalLaserDot = sqrtf(verticalLaserClosestPointToCenter.x * verticalLaserClosestPointToCenter.x + verticalLaserClosestPointToCenter.y * verticalLaserClosestPointToCenter.y);

				verticalLaserSumRadius = player.radius + verticalLaserCapsule.radius;

				if (verticalLaserDot < verticalLaserSumRadius)
				{
					player.color = BLUE;
					verticalLaser.isShot = true;
				}
			} else
			{
				verticalLaser.isShot = false;
				player.color = WHITE;
				verticalLaserCapsule.start = { float(rand() % 1200+0) ,-64 };
				verticalLaserCapsule.end = { verticalLaserCapsule.start.x + 32,-60 };
				verticalLaserCapsule.radius = { 32.0f };
			}

#pragma endregion
#pragma region レーザー当たり判定(斜め)
			if ( obliqueLaserCapsule.end.y<1000)//obliqueLaserCapsule.end.x<1024||
			{
				obliqueLaser.isShot = true;

				obliqueLaserLineVector.x = obliqueLaserCapsule.end.x - obliqueLaserCapsule.start.x;
				obliqueLaserLineVector.y = obliqueLaserCapsule.end.y - obliqueLaserCapsule.start.y;
				obliqueLaserLength = sqrtf(obliqueLaserLineVector.x * obliqueLaserLineVector.x + obliqueLaserLineVector.y * obliqueLaserLineVector.y);

				obliqueLaserUnitVector = obliqueLaserLineVector;
				if (obliqueLaserLength != 0.0f)
				{
					obliqueLaserUnitVector.x = obliqueLaserLineVector.x / obliqueLaserLength;
					obliqueLaserUnitVector.y = obliqueLaserLineVector.y / obliqueLaserLength;
				}

				obliqueLaserToCenter.x = player.pos.x - obliqueLaserCapsule.start.x;
				obliqueLaserToCenter.y = player.pos.y - obliqueLaserCapsule.start.y;

				obliqueLaserDot = obliqueLaserToCenter.x * obliqueLaserUnitVector.x + obliqueLaserToCenter.y * obliqueLaserUnitVector.y;

				obliqueLaserDot = fmaxf(0.0f, fminf(obliqueLaserDot, obliqueLaserLength));
				obliqueLaserClosestPoint.x = obliqueLaserCapsule.start.x + obliqueLaserUnitVector.x * obliqueLaserDot;
				obliqueLaserClosestPoint.y = obliqueLaserCapsule.start.y + obliqueLaserUnitVector.y * obliqueLaserDot;

				obliqueLaserClosestPointToCenter.x = player.pos.x - obliqueLaserClosestPoint.x;
				obliqueLaserClosestPointToCenter.y = player.pos.y - obliqueLaserClosestPoint.y;

				obliqueLaserDot = sqrtf(obliqueLaserClosestPointToCenter.x * obliqueLaserClosestPointToCenter.x + obliqueLaserClosestPointToCenter.y * obliqueLaserClosestPointToCenter.y);

				obliqueLaserSumRadius = player.radius + obliqueLaserCapsule.radius;

				if (obliqueLaserDot < obliqueLaserSumRadius)
				{
					
					player.color = GREEN;
					obliqueLaser.isShot = true;
					
				}
			} else
			{
				obliqueLaser.isShot = false;
				player.color = WHITE;
				obliqueLaserCapsule.start = { float(rand() % 1200 + 40)-1024 ,-1024};
				obliqueLaserCapsule.end = { (obliqueLaserCapsule.start.x) + 720, (obliqueLaserCapsule.start.y) + 720 };
				obliqueLaserCapsule.radius = { 32.0f };
			}
#pragma endregion
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
			//下
			if ((map[int(player.pos.y / 32 + 1)][int(player.pos.x / 32)] == 2 && player.pos.y >= 13 * blockSize) ||
				(map[int(player.pos.y / 32 + 1)][int((player.pos.x + player.width) / 32)] == 2 && player.pos.y >= 13 * blockSize)) {
				blockNum = 13;
				player.velocity.y = 0.0f;
				if (keys[DIK_S] && keys[DIK_SPACE]) {
					blockNum = 15;
					player.pos.y = float(blockNum * 32);
				}
			}

			//上
			if ((map[int(player.pos.y / 32 + 1)][int(player.pos.x / 32)] == 2 && player.pos.y <= 7 * blockSize) ||
				(map[int(player.pos.y / 32 + 1)][int((player.pos.x + player.width) / 32)] == 2 && player.pos.y <= 7 * blockSize)) {
				blockNum = 5;
				player.velocity.y = 0.0f;
				if (keys[DIK_S] && keys[DIK_SPACE]) {
					blockNum = 7;
					player.pos.y = float(blockNum * 32);
				}
			}

			//真ん中
			if ((map[int(player.pos.y / 32 + 1)][int(player.pos.x / 32)] == 2 && player.pos.y >= 10 * blockSize) &&
				(map[int(player.pos.y / 32 + 1)][int((player.pos.x + player.width) / 32)] == 2 && player.pos.y <= 11 * blockSize)) {
				blockNum = 9;
				player.velocity.y = 0.0f;
				if (keys[DIK_S] && keys[DIK_SPACE]) {
					blockNum = 11;
					player.pos.y = float(blockNum * 32);
				}
			}
#pragma endregion


#pragma region 自機の移動

			player.move.x = 0.0f;
			player.move.y = 0.0f;

			if (keys[DIK_A] || keys[DIK_LEFT]) {
				player.move.x -= 1.0f;
				if (map[int(player.pos.y / 32)][int(player.pos.x / 32 - 0.13f)] == 1) {
					player.move.x += 1.0f;
				}
			}

			if (keys[DIK_D] || keys[DIK_RIGHT]) {
				player.move.x += 1.0f;
				if (map[int(player.pos.y / 32)][int(player.pos.x / 32 + 1.13f)] == 1) {
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

			//ボールの速度に加速度を足す
			player.velocity.x -= player.acceleration.x;
			player.velocity.y -= player.acceleration.y;

			//ボールの位置に速度を足す
			player.pos.x -= player.velocity.x;
			player.pos.y -= player.velocity.y;


			if (player.pos.y >= player.height + blockNum * blockSize) {
				player.pos.y = player.height + blockNum * blockSize;
				player.jumpCount = 0;
			}

#pragma endregion
		}

#pragma region シーンの切り替え
		switch (scene)
		{
		case TITLE:
			Novice::ScreenPrintf(0, 0, "title");
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = GAMESCENE;
			}

			break;
		case EXPLAIN:
			Novice::ScreenPrintf(0, 0, "title");
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = GAMESCENE;
			}
			break;
		case GAMESCENE:
			Novice::ScreenPrintf(0, 0, "gamescene");
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = CLEAR;
			}

			break;
		case GAMEOVER:
			Novice::ScreenPrintf(0, 0, "gameover");
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = TITLE;
			}

			break;
		case CLEAR:
			Novice::ScreenPrintf(0, 0, "clear");
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = TITLE;
			}

			break;
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
		if (scene == GAMESCENE)
		{
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

			/*for (int i = 0; i < maxBullet; i++) {
				Novice::ScreenPrintf(0, i * 17, "posxVertical%disAlive%d\n\n", static_cast<int>(bulletVertical[i].pos.x), bulletVertical[i].isAlive);
				Novice::ScreenPrintf(0, 102 + i * 17, "posyVertical%d isAlive%d\n\n", static_cast<int>(bulletVertical[i].pos.y), bulletVertical[i].isAlive);
				Novice::ScreenPrintf(0, 204 + i * 17, "posxBeside%d isAlive%d\n\n", static_cast<int>(bulletBeside[i].pos.x), bulletBeside[i].isAlive);
				Novice::ScreenPrintf(0, 306 + i * 17, "posyBeside%d isAlive%d", static_cast<int>(bulletBeside[i].pos.y), bulletBeside[i].isAlive);
				Novice::ScreenPrintf(0, 425 + i * 17, "posxDiagonal%d isAlive%d\n\n", static_cast<int>(bulletDiagonal[i].pos.x), bulletDiagonal[i].isAlive);
				Novice::ScreenPrintf(0, 527 + i * 17, "posyDiagonal%d isAlive%d", static_cast<int>(bulletDiagonal[i].pos.y), bulletDiagonal[i].isAlive);
			}*/

#pragma region レーザー描画
			//レーザー
			if (horizontalLaserCapsule.end.x < 1300 || verticalLaserCapsule.end.y < 800)
			{

				horizontalLaser.move = 0;
				horizontalLaser.move += horizontalLaser.move + 4;
				Novice::DrawQuad(
					static_cast<int>(horizontalLaserCapsule.start.x), static_cast<int>(horizontalLaserCapsule.start.y - 16),
					static_cast<int>(horizontalLaserCapsule.end.x += horizontalLaser.move), static_cast<int>(horizontalLaserCapsule.start.y - 16),
					static_cast<int>(horizontalLaserCapsule.start.x), static_cast<int>(horizontalLaserCapsule.end.y + horizontalLaser.size) - 16,
					static_cast<int>(horizontalLaserCapsule.end.x += horizontalLaser.move), static_cast<int>(horizontalLaserCapsule.end.y + horizontalLaser.size) - 16,
					0, 0, static_cast<int>(horizontalLaser.move), static_cast<int>(horizontalLaser.size),
					horizontalLaserGr, WHITE
				);

				//Novice::DrawEllipse(static_cast<int>(horizontalLaserCapsule.start.x), static_cast<int>(horizontalLaserCapsule.start.y + 32), static_cast<int>(horizontalLaserCapsule.radius), static_cast<int>(horizontalLaserCapsule.radius), 0.0f, horizontalLaserCapsule.color, kFillModeWireFrame);
				//Novice::DrawEllipse(static_cast<int>(horizontalLaserCapsule.end.x-32), static_cast<int>(horizontalLaserCapsule.end.y + 16), static_cast<int>(horizontalLaserCapsule.radius), static_cast<int>(horizontalLaserCapsule.radius), 0.0f, horizontalLaserCapsule.color, kFillModeWireFrame);


				verticalLaser.move = 0;
				verticalLaser.move += verticalLaser.move + 4;
				Novice::DrawQuad(
					static_cast<int>(verticalLaserCapsule.start.x) - 16, static_cast<int>(verticalLaserCapsule.start.y),
					static_cast<int>(verticalLaserCapsule.end.x+ verticalLaser.size) - 16, static_cast<int>(verticalLaserCapsule.start.y ),
					static_cast<int>(verticalLaserCapsule.start.x) - 16, static_cast<int>(verticalLaserCapsule.end.y += verticalLaser.move),
					static_cast<int>(verticalLaserCapsule.end.x+ verticalLaser.size ) - 16, static_cast<int>(verticalLaserCapsule.end.y += verticalLaser.move),
					0, 0,static_cast<int>(verticalLaser.size) , static_cast<int>(verticalLaser.move),
					verticalLaserGr, WHITE
				);
				//Novice::DrawEllipse(static_cast<int>(verticalLaserCapsule.start.x), static_cast<int>(verticalLaserCapsule.start.y), static_cast<int>(verticalLaserCapsule.radius), static_cast<int>(verticalLaserCapsule.radius), 0.0f, verticalLaserCapsule.color, kFillModeWireFrame);
				//Novice::DrawEllipse(static_cast<int>(verticalLaserCapsule.end.x), static_cast<int>(verticalLaserCapsule.end.y - 16), static_cast<int>(verticalLaserCapsule.radius), static_cast<int>(verticalLaserCapsule.radius), 0.0f, verticalLaserCapsule.color, kFillModeWireFrame);
				Novice::ScreenPrintf(300, 300, "%f", verticalLaserCapsule.end.y);

			}
			//斜め向きのレーザー
			if ( obliqueLaserCapsule.end.y < 1000) {//obliqueLaserCapsule.end.x < 1024 ||
				
				obliqueLaser.move = 0;
				obliqueLaser.move += obliqueLaser.move + 3;
				//Novice::DrawEllipse(static_cast<int>(obliqueLaserCapsule.start.x), static_cast<int>(obliqueLaserCapsule.start.y), static_cast<int>(obliqueLaserCapsule.radius), static_cast<int>(obliqueLaserCapsule.radius), 0.0f, obliqueLaserCapsule.color, kFillModeWireFrame);
				//Novice::DrawEllipse(static_cast<int>(obliqueLaserCapsule.end.x += obliqueLaser.move), static_cast<int>(obliqueLaserCapsule.end.y += obliqueLaser.move), static_cast<int>(obliqueLaserCapsule.radius), static_cast<int>(obliqueLaserCapsule.radius), 0.0f, obliqueLaserCapsule.color, kFillModeWireFrame);
				Novice::DrawSprite(static_cast<int>(obliqueLaserCapsule.end.x += obliqueLaser.move)-1024, static_cast<int>(obliqueLaserCapsule.end.y += obliqueLaser.move) - 1024, obliqueLaserGr, 1.0f, 1.0f, 0.0f, WHITE);
			}
#pragma endregion

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



		


			Novice::DrawBox(
				static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
				static_cast<int>(player.width), static_cast<int>(player.height),
				0.0f, WHITE, kFillModeSolid);
			Novice::DrawBox(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), static_cast<int>(player.width), static_cast<int>(player.height), 0.0f, player.color, kFillModeSolid);
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
			Novice::ScreenPrintf(0, 220, "blockNum %d", blockNum);
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

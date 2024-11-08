#include <Novice.h>
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
}Ball;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 736);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
	player.pos = { 64.0f,160.0f };
	player.prePos = { 0.0f,0.0f };
	player.mapPos = { 0.0f,0.0f };
	player.map = { 0.0f,0.0f };
	player.velocity = { 0.0f,0.0f };
	player.acceleration = { 0.0f,-0.8f };
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

	Vector2 mapNumber = { player.pos.x / 32,player.pos.y / 32 };


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

#pragma region 地面との当たり判定

		if (player.pos.x >= 0 && player.pos.x < 6 * blockSize ||
			player.pos.x + player.width >= 34 * blockSize && player.pos.x + player.width < 36 * blockSize) {
			blockNum = 5;
		}

		if (player.pos.x >= 6 * blockSize && player.pos.x < 8 * blockSize ||
			player.pos.x + player.width >= 32 * blockSize && player.pos.x + player.width < 34 * blockSize) {
			blockNum = 4;
		}

		if (player.pos.x >= 8 * blockSize && player.pos.x < 10 * blockSize ||
			player.pos.x + player.width >= 30 * blockSize && player.pos.x + player.width < 32 * blockSize) {
			blockNum = 3;
		}

		if (player.pos.x >= 10 * blockSize && player.pos.x < 29 * blockSize) {
			blockNum = 2;
		}

#pragma endregion

#pragma region 自機の移動

		player.move.x = 0.0f;
		player.move.y = 0.0f;

		if (keys[DIK_A] || keys[DIK_LEFT]) {
			player.move.x -= 1.0f;
			if (player.pos.y == 5 * blockSize && player.pos.x <= 6.1f * blockSize ||
				player.pos.y == 4 * blockSize && player.pos.x <= 8.1f * blockSize ||
				player.pos.y == 3 * blockSize && player.pos.x <= 10.13f * blockSize) {
				player.move.x += 1.0f;
			}
		}

		if (keys[DIK_D] || keys[DIK_RIGHT]) {
			player.move.x += 1.0f;
			if (player.pos.y == 5 * blockSize && player.pos.x + player.width >= 33.9f * blockSize ||
				player.pos.y == 4 * blockSize && player.pos.x + player.width >= 31.9f * blockSize ||
				player.pos.y == 3 * blockSize && player.pos.x + player.width >= 29.8f * blockSize) {
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
				player.velocity.y = 12.0f;
			}
		}

		//空中ジャンプ
		if (keys[DIK_SPACE] != 0 && !preKeys[DIK_SPACE] && player.pos.y >= player.height) {
			if (player.jumpCount <= 2) {
				player.velocity.y = 12.0f;
			}
		}

		//ジャンプの回数制限
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			player.jumpCount++;
		}

		//ボールの速度に加速度を足す
		player.velocity.x += player.acceleration.x;
		player.velocity.y += player.acceleration.y;

		//ボールの位置に速度を足す
		player.pos.x += player.velocity.x;
		player.pos.y += player.velocity.y;

		if (player.pos.y <= player.height + blockNum * blockSize) {
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
					Novice::DrawSprite(x * blockSize, y * blockSize, block1, 1.0f, 1.0f, 0.0f, WHITE);
				}
				if (map[y][x] == 2) {
					Novice::DrawSprite(x * blockSize, y * blockSize, block2, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
		}


		Novice::DrawBox(
			static_cast<int>(player.pos.x), static_cast<int>(-player.pos.y + 736.0f),
			static_cast<int>(player.width), static_cast<int>(player.height),
			0.0f, WHITE, kFillModeSolid);

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

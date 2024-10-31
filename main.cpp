#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "LC1C_23_ヤリタ_コウヤ_タイトル";

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Ball {
	Vector2 pos;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 move;
	float lenght;
	float radius;
	int jumpCount;
	int rect;
	int moveSpeed;
}Ball;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Ball ball;
	ball.pos = { 100.0f,100.0f };
	ball.velocity = { 0.0f,0.0f };
	ball.acceleration = { 0.0f,-0.8f };
	ball.move = { 0.0f,0.0f };
	ball.lenght = 0.0f;
	ball.radius = 20.0f;
	ball.jumpCount = 0;
	ball.rect = 100;
	ball.moveSpeed = 5;


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

#pragma region 自機の移動
		
		ball.move.x = 0.0f;
		ball.move.y = 0.0f;

		if (keys[DIK_A] || keys[DIK_LEFT]) {
			ball.move.x -= 1.0f;
		}

		if (keys[DIK_D] || keys[DIK_RIGHT]) {
			ball.move.x += 1.0f;
		}

		ball.lenght = sqrtf(ball.move.x * ball.move.x + ball.move.y * ball.move.y);
		if (ball.lenght != 0.0f) {
			ball.move.x /= ball.lenght;
			ball.move.y /= ball.lenght;
		}

		ball.pos.x += ball.move.x * ball.moveSpeed;
		ball.pos.y += ball.move.y * ball.moveSpeed;

#pragma endregion


#pragma region ジャンプ

		//地上でのジャンプ
		if (keys[DIK_SPACE] != 0 && !preKeys[DIK_SPACE]&& ball.pos.y == ball.radius) {
			if (ball.jumpCount <= 2) {
				ball.velocity.y = 12.0f;
			}
		}

		//空中ジャンプ
		if (keys[DIK_SPACE] != 0 && !preKeys[DIK_SPACE] && ball.pos.y >= ball.radius) {
			if (ball.jumpCount <= 2) {
				ball.velocity.y = 12.0f;
			}
		}

		//ジャンプの回数制限
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			ball.jumpCount++;
		}

		//ボールの速度に加速度を足す
		ball.velocity.x += ball.acceleration.x;
		ball.velocity.y += ball.acceleration.y;

		//ボールの位置に速度を足す
		ball.pos.x += ball.velocity.x;
		ball.pos.y += ball.velocity.y;

		if (ball.pos.y <= ball.radius) {
			ball.pos.y = ball.radius;
			ball.jumpCount = 0;
		}

#pragma endregion

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(
			static_cast<int>(ball.pos.x), static_cast<int>(ball.pos.y * -1 + 620.0f),
			static_cast<int>(ball.radius), static_cast<int>(ball.radius),
			0.0f, WHITE, kFillModeSolid);

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

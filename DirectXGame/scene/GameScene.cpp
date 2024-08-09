#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

    GameScene::GameScene() {}

GameScene::~GameScene() { delete model, delete player; }

void GameScene::Initialize() {

	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureHandle = TextureManager::Load("");
	// モデルの生成
	model = Model::Create();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	worldTransform_.Initialize();

	// 自キャラ作成
	player = new Player();
	// 初期化
	player->Initialize(model, textureHandle, &viewProjection_);
}

void GameScene::Update() { player->Update(); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
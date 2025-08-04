#include "GameManager.h"
#include "../../Component/Renderer2D.h"
#include "../../Object/Sprite.h"
#include "../../Util/Assets/AssetLoader.h"

void GameManager::Start() {
	GameObject* gameObject = new GameObject();
	gameObject->SetName("TestGameObject");

	Renderer2D* renderer2D = gameObject->AddComponent<Renderer2D>();

	Shader* shader = Shader::Load(R"(C:\Users\airhood\source\repos\CubicEngine\CubicEngine\Sources\Shader\Default.csl)");
	Material* mat = new Material();
	mat->shader = shader;
	Sprite sprite = Sprite();

	// ����, �ʷ�, �Ķ�, ��� 4�ȼ�¥�� (RGBA ���� 4����Ʈ)
	unsigned char data[] = {
		255, 0,   0,   255,  // ����
		0,   255, 0,   255,  // �ʷ�
		0,   0,   255, 255,  // �Ķ�
		255, 255, 255, 255   // ���
	};
	
	//Texture2D* tex2D = new Texture2D(2, 2);
	//tex2D->Load(data);
	const Texture2D* tex2D = AssetLoader::LoadTexture(R"(C:\Users\airhood\Desktop\Dimo\DIMO.png)");
	Texture2D* tex2D_clone = tex2D->Clone();
	tex2D_clone->Apply();
	sprite.texture = tex2D_clone;
	sprite.pixelsPerUnit = 500;
	sprite.pivot = glm::vec2(0, 0);
	
	renderer2D->SetSprite(sprite);
	renderer2D->SetMaterial(mat);
}
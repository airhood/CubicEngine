#include "GameManager.h"
#include "../../Component/Renderer2D.h"
#include "../../Object/Sprite.h"

void GameManager::Start() {
	GameObject* gameObject = new GameObject();
	gameObject->SetName("TestGameObject");

	Renderer2D* renderer2D = gameObject->AddComponent<Renderer2D>();

	Shader* shader = Shader::Load(R"(C:\Users\airhood\source\repos\CubicEngine\CubicEngine\Sources\Shader\TestShader.csl)");
	Material* mat = new Material();
	mat->shader = shader;
	Sprite* sprite = new Sprite();

	// ����, �ʷ�, �Ķ�, ��� 4�ȼ�¥�� (RGBA ���� 4����Ʈ)
	unsigned char data[] = {
		255, 0,   0,   255,  // ����
		0,   255, 0,   255,  // �ʷ�
		0,   0,   255, 255,  // �Ķ�
		255, 255, 255, 255   // ���
	};
	
	Texture2D* tex2D = new Texture2D(2, 2);
	tex2D->Load(data);
	sprite->texture = tex2D;
	
	renderer2D->sprite = sprite;
	renderer2D->SetMaterial(mat);
}
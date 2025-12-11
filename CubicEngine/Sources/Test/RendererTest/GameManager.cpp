#include "GameManager.h"
#include "../../Component/Rendering/Renderer2D.h"
#include "../../Object/Sprite.h"
#include "../../Util/Assets/AssetLoader.h"
#include "../../Component/Rendering/MeshRenderer.h"

void GameManager::Start() {
	GameObject* gameObject = new GameObject();
	gameObject->SetName("TestGameObject");

	Renderer2D* renderer2D = gameObject->AddComponent<Renderer2D>();

	Shader* shader = Shader::Load(R"(C:\Users\airhood\source\repos\CubicEngine\CubicEngine\Sources\Shader\Default.csl)");
	Material* mat = new Material();
	mat->shader = shader;

	Sprite sprite = Sprite();

	Texture2D* tex2D = AssetLoader::LoadTexture(R"(C:\Users\airhood\Desktop\Dimo\DIMO.png)");
	Texture2D* tex2D_clone = tex2D->Clone();
	tex2D_clone->Apply();


	sprite.texture = tex2D_clone;
	sprite.pixelsPerUnit = 500;
	sprite.pivot = glm::vec2(0, 0);
	
	renderer2D->SetSprite(sprite);
	renderer2D->SetMaterial(mat);

	GameObject* gameObject2 = new GameObject();

	MeshRenderer* meshRenderer = gameObject2->AddComponent<MeshRenderer>();

	Shader* mesh_shader = Shader::Load(R"(C:\Users\airhood\source\repos\CubicEngine\CubicEngine\Sources\Shader\MeshRender.csl)");
	Material* mesh_mat = new Material();
	mesh_mat->mainTexture = tex2D_clone;
	mesh_mat->shader = mesh_shader;

	//Mesh* mesh = new Mesh();
	//mesh->vertices = {
	//	{ {-1, -1, 0}, {0,0,1}, {0,0}, {1,0,0}, {0,1,0}, {0}, {0} },
	//	{ { 1, -1, 0}, {0,0,1}, {1,0}, {1,0,0}, {0,1,0}, {0}, {0} },
	//	{ { 1,  1, 0}, {0,0,1}, {1,1}, {1,0,0}, {0,1,0}, {0}, {0} },
	//	{ {-1,  1, 0}, {0,0,1}, {0,1}, {1,0,0}, {0,1,0}, {0}, {0} }
	//};

	//mesh->indices = { 0, 1, 2, 2, 3, 0 };


	Mesh* mesh = new Mesh();

	mesh->vertices = {
		// 4-sided pyramid (base + 4 faces)
		// position           normal           uv         tangent    bitangent
		{{-1, 0, -1}, {0, -1, 0}, {0,0}, {1,0,0}, {0,1,0}},
		{{ 1, 0, -1}, {0, -1, 0}, {1,0}, {1,0,0}, {0,1,0}},
		{{ 1, 0,  1}, {0, -1, 0}, {1,1}, {1,0,0}, {0,1,0}},
		{{-1, 0,  1}, {0, -1, 0}, {0,1}, {1,0,0}, {0,1,0}},

		// Top vertex
		{{0, 1.5f, 0}, {0,1,0}, {0.5,0.5}, {1,0,0}, {0,1,0}},
	};

	mesh->indices = {
		// Base
		0, 1, 2,
		2, 3, 0,

		// 4 side triangles
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};


	meshRenderer->SetMesh(mesh);
	meshRenderer->SetMaterial(mesh_mat);
}
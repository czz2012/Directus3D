/*
Copyright(c) 2016-2017 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ======================
#include "../../Graphics/Texture.h"
#include "../../Graphics/Model.h"
//=================================

struct aiNode;
struct aiScene;
struct aiMaterial;
struct aiMesh;

namespace Directus
{
	class Material;
	class GameObject;
	class Model;
	class Transform;

	class DLL_API ModelImporter
	{
	public:
		ModelImporter();
		~ModelImporter();

		bool Initialize(Context* context);
		void LoadAsync(Model* model, const std::string& filePath);
		void ReadAnimations(Model* model, const aiScene* scene);
		bool Load(Model* model, const std::string& filePath);

		std::string GetStatMeshProcessed() { return m_statMeshProcessed; }
		std::string GetStatNodeProcessed() { return m_statNodeProcessed; }
		int GetStatNodeCount() { return m_stateNodeCount; }
		int GetStatNodeCurrent() { return m_stateNodeCurrent; }

	private:
		// PROCESSING
		void ReadNodeHierarchy(Model* model, const aiScene* assimpScene, aiNode* assimpNode, const std::weak_ptr<GameObject>& parentNode, std::weak_ptr<GameObject>& newNode);
		void LoadMesh(Model* model, aiMesh* assimpMesh, const aiScene* assimpScene, const std::weak_ptr<GameObject>& parentGameObject);
		void LoadAiMeshVertices(aiMesh* assimpMesh, std::shared_ptr<Mesh> mesh);
		void LoadAiMeshIndices(aiMesh* assimpMesh, std::shared_ptr<Mesh> mesh);
		std::shared_ptr<Material> AiMaterialToMaterial(Model* model, aiMaterial* assimpMaterial);

		// HELPER FUNCTIONS
		void AddTextureToMaterial(Model* model, const std::weak_ptr<Material>& material, TextureType textureType, const std::string& texturePath);
		std::string FindTexture(const std::string& texturePath);
		std::string TryPathWithMultipleExtensions(const std::string& fullpath);
		void CalculateNodeCount(aiNode* node, int& count);
		void ResetStats();

		bool m_isLoading;
		Model* m_model;
		std::string m_modelPath;

		// Statistics	
		std::string m_statMeshProcessed;
		std::string m_statNodeProcessed;
		int m_stateNodeCount;
		int m_stateNodeCurrent;
		
		Context* m_context;
	};
}
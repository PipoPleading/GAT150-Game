#pragma once
#include "RenderComponents.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace kiko
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		virtual const char* GetClassName() {
			return "ModelRenderComponent";
		} virtual void Read(const json_t& value); virtual std::unique_ptr<Object> Clone() {
			return std::make_unique<ModelRenderComponent>(*this);
		} class Register {
		public: Register() {
			Factory::Instance().Register<ModelRenderComponent>("ModelRenderComponent");
		}
		}; //trouble with std::make_unique

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }
		//void Read(const json_t& value);
	public:
		std::string modelName;
		res_t<Model> m_model;
	};


}
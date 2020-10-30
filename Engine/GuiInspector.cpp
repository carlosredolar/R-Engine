#include "Application.h"
#include "GuiInspector.h"
#include "ModuleGui.h"

using namespace ImGui;

GuiInspector::GuiInspector() : GuiWindow()
{
	is_on = true;
	strncpy(buf, "Insert a text", 128);
	gameObjectSelected = nullptr;
}

GuiInspector::~GuiInspector()
{}

bool GuiInspector::Start()
{
	bool ret = true;
	return ret;
}

bool GuiInspector::CleanUp()
{
	bool ret = true;

	return ret;
}

void GuiInspector::Select(GameObject* selected) {
	gameObjectSelected = selected;
	strncpy(buf, gameObjectSelected->GetName(), 128);
	transformGO = gameObjectSelected->GetComponent<Component_Transform>();
	meshGO = gameObjectSelected->GetComponent<Component_Mesh>();
	textureGO = gameObjectSelected->GetComponent<Component_Texture>();
}

void GuiInspector::Draw()
{
	Begin("Inspector", &is_on);

	if (gameObjectSelected != nullptr) {
		static bool gameobjectCheck = gameObjectSelected->IsEnabled();
		Checkbox("Active", &gameobjectCheck);
		(gameobjectCheck) ? gameObjectSelected->Enable() : gameObjectSelected->Disable();
		SameLine();
		InputText("Name", buf, ARRAYSIZE(buf));
		gameObjectSelected->ChangeName(buf);

		if (CollapsingHeader("Transform")) 
		{
			float3 tempValues = transformGO->GetPosition();
			static float pos[3] = { tempValues.x, tempValues.y, tempValues.z };
			tempValues = transformGO->GetRotationEuler();
			static float rot[3] = { tempValues.x, tempValues.y, tempValues.z };
			tempValues = transformGO->GetScale();
			static float scl[3] = { tempValues.x, tempValues.y, tempValues.z };
			DragFloat3("Position", pos, 0.05f);
			DragFloat3("Rotation", rot, 0.05f);
			DragFloat3("Scale", scl, 0.05f);
			float3 pos_ = { pos[0], pos[1], pos[2] };
			float3 rot_ = { rot[0], rot[1], rot[2] };
			float3 scl_ = { scl[0], scl[1], scl[2] };
			transformGO->SetTransform(pos_, rot_, scl_);
		}
		if (meshGO)
		{
			if (CollapsingHeader("Mesh"))
			{
				static bool meshCheck = meshGO->IsEnabled();
				Checkbox("Mesh Active", &meshCheck);
				(meshCheck) ? meshGO->Enable() : meshGO->Disable();
				strncpy(buf, meshGO->GetName(), 128);
				InputText("Mesh Name", buf, ARRAYSIZE(buf));
			}
		}
		if (textureGO)
		{
			if (CollapsingHeader("Texture"))
			{
				static bool textureCheck = textureGO->IsEnabled();
				Checkbox("Texture Active", &textureCheck);
				(textureCheck) ? textureGO->Enable() : textureGO->Disable();
			}
		}


		Text("Here goes the inspector with all the components");
	}

	End();
}
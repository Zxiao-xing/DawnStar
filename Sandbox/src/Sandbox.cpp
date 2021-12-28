#pragma once

#include <DawnStar.h>
#include <Core/EntryPoint.h>

class Sandbox : public DawnStar::Application {
public:
	Sandbox() {

	}
};

DawnStar::UniquePtr<DawnStar::Application> DawnStar::CreateApplication() {
	Sandbox sandbox;
	return CreateUnique<Sandbox>(sandbox);
}
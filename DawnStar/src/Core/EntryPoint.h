#pragma once

#if DS_PLATFORM_WINDOWS
extern DawnStar::UniquePtr<DawnStar::Application> DawnStar::CreateApplication();

int main(int argc, char** argv) {
	auto app = DawnStar::CreateApplication();

	app->Run();

	app->Close();

	return 0;
}

#endif // DS_PLATFORM_WINDOWS
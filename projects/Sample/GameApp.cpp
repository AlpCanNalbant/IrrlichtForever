#include "GameApp.hpp"

GameApp::GameApp() noexcept
	: App(L"My Game")
{
	Device->setResizable(true);

	// If you want to use file system directly, you can set its path like below.
	// Optional when you only you th
	auto resPath = GetResourcePath();
	Irr::PathNavigator{}.ToNextFolder(resPath, {"Content"});
	SetResourcePath(resPath);
}

bool GameApp::OnInit() noexcept
{
	ResourceMgr.SetBasePath(L"Content");
	return true;
}

bool GameApp::OnLoad() noexcept
{
	const auto ninjaFile = ResourceMgr.Load(L"Model/Ninja.b3d");
	const auto ninjaSkinFile = ResourceMgr.Load(L"Texture/NinjaDiff.jpg");
	const auto mapFile = ResourceMgr.Load(L"Map/Map20kdm2.pk3");

	// Load animated 3D ninja model.
	{
		auto mesh = Irr::GrabPtr(SceneMgr->getMesh(ninjaFile.Get()));
		auto ninjaNode = Irr::GrabPtr(SceneMgr->addAnimatedMeshSceneNode(mesh.Get()));
		if (ninjaNode)
		{
			ninjaNode->setMaterialFlag(irr::EMF_LIGHTING, false);
			ninjaNode->setFrameLoop(0, 13); // ninjaNode->setMD2Animation(scene::EMAT_RUN);
			ninjaNode->setAnimationSpeed(15.f);
			ninjaNode->setScale({10.f, 10.f, 10.f});
			ninjaNode->setRotation({0.f, -90.f, 0.f});
			ninjaNode->setMaterialTexture(0, Driver->getTexture(ninjaSkinFile.Get()));
			auto anim = Irr::GrabCreatedPtr(SceneMgr->createFlyStraightAnimator({100.f, -10.f, 60.f}, {-100.f, -10.f, 60.f}, 3500, true));
			if (anim)
			{
				ninjaNode->addAnimator(anim.Get());
				// anim->drop(); // You do not need this anymore.
			}
		}
	}

	// Add Quake III Arena map format archive.
	if (Device->getFileSystem()->addFileArchive(mapFile.Get()))
	{
		// Load the map file of Quake III Arena.
		auto mesh = Irr::GrabPtr(SceneMgr->getMesh("20kdm2.bsp"));
		Irr::Pointer<irr::IMeshSceneNode> node;
		if (mesh)
		{
			if (node = Irr::GrabPtr(SceneMgr->addOctreeSceneNode(mesh->getMesh(0))))
				node->setPosition({-1300, -144, -1249}); // Set position of the map node.
		}
	}

	// Key maps for the fps camera.
	std::array<irr::SKeyMap, 6> keyMap;
	keyMap[0] = {irr::EKA_MOVE_FORWARD, irr::KEY_KEY_W};
	keyMap[1] = {irr::EKA_MOVE_BACKWARD, irr::KEY_KEY_S};
	keyMap[2] = {irr::EKA_STRAFE_LEFT, irr::KEY_KEY_A};
	keyMap[3] = {irr::EKA_STRAFE_RIGHT, irr::KEY_KEY_D};
	keyMap[4] = {irr::EKA_JUMP_UP, irr::KEY_SPACE};
	keyMap[5] = {irr::EKA_CROUCH, irr::KEY_LCONTROL};
	// Add to the scene a fps camera.
	SceneMgr->addCameraSceneNodeFPS(nullptr, 100.f, 0.2f, -1, keyMap.data(), keyMap.size(), true, 0.1f);

	// Now hide the cursor.
	Device->getCursorControl()->setVisible(false);
	return true; // If we have not any fatal error, successfully return true.
}

void GameApp::OnUpdate() noexcept
{
	if (Keyboard->IsKeyUp(Irr::Key::Escape))
		ShutDown();
}

void GameApp::OnDraw() noexcept
{
}

void GameApp::OnUnload() noexcept
{
}

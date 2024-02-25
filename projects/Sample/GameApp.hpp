#pragma once
#include "IrrlichtForever/App.hpp"

class GameApp final : public Irr::App
{
public:
	GameApp() noexcept;

protected:
	bool OnInit() noexcept final;
	bool OnLoad() noexcept final;
	void OnUpdate() noexcept final;
	void OnDraw() noexcept final;
	void OnUnload() noexcept final;
};

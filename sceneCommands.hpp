#pragma once
#include "command.hpp"
#include "sceneSignals.hpp"

class ChangeSceneCommand : public Command {
public:
	ChangeSceneCommand(Scenes scene) : scene_(scene) {}
	void execute() override { changeScene.emit(scene_); }
private:
	Scenes scene_;
};

class StackSceneCommand : public Command {
public:
	StackSceneCommand(Scenes scene) : scene_(scene) {}
	void execute() override { stackScene.emit(scene_); }
private:
	Scenes scene_;
};

class CloseSceneCommand : public Command {
public:
	CloseSceneCommand() {}
	void execute() override { closeScene.emit(); }
};
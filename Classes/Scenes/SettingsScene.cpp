#include "SettingsScene.h"
Scene* SettingsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingsScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingsScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	createUserInterface();
	setDefaultUIState();

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

//========================================UI

void SettingsScene::createUserInterface()
{
	createBackground();
	createBGSoundCheckBox();
	createMusicVolumeSlider();
	createBackButton();
	createApplyButton();
}

void SettingsScene::createBackground()
{
	auto backgroundImage = UImanager::createBackground(SETTINGS_BACKROUND_IMAGE, 0.9f);
	this->addChild(backgroundImage, -1);
}

void SettingsScene::createBGSoundCheckBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sliderLabel = UImanager::createTextLabel("Background sound enabled",
		SETTINGS_LABEL_FONT, SETTINGS_LABEL_SIZE / 2,
		Vec2(origin.x + visibleSize.width * 1.5 / 10, origin.y + visibleSize.height * 8 / 10));

	bgSoundCB = UImanager::createCheckBox(sliderLabel->getPosition() + Vec2(220, 6), 0.03f);
	bgSoundCB->addEventListener([&](Ref* sender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED) {
			AudioManager::getInstance().playBackgroundAudio();
			AudioManager::getInstance().setBackgroundAudioVolume(volumeSlider->getPercent() / 100.f);
		}
		else if (type == CheckBox::EventType::UNSELECTED)	
			AudioManager::getInstance().stopBackgroundAudio();
	});

	this->addChild(sliderLabel, 1);
	this->addChild(bgSoundCB, 1);
}

void SettingsScene::createMusicVolumeSlider()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sliderLabel = UImanager::createTextLabel("Background sound volume",
		SETTINGS_LABEL_FONT, SETTINGS_LABEL_SIZE / 2, 
		Vec2(origin.x + visibleSize.width * 1.5 / 10, origin.y + visibleSize.height * 8 / 10 - 70));

	volumeSlider = UImanager::createSlider(sliderLabel->getPosition() + Vec2(sliderLabel->getContentSize().width + 20, 0));	
	volumeSlider->addEventListener([&](Ref* sender, Slider::EventType type) 
	{
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			AudioManager::getInstance().setBackgroundAudioVolume((float)volumeSlider->getPercent() / 100);
	});
	this->addChild(sliderLabel, 1);
	this->addChild(volumeSlider);
}

void SettingsScene::createBackButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto backButton = UImanager::createButton("Back", ccc4(215, 255, 0, 255), CC_CALLBACK_1(SettingsScene::backButtonPressed, this),
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5)); 
	MenuItems.pushBack(backButton);
}

void SettingsScene::createApplyButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto applyButton = UImanager::createButton("Apply", ccc4(215, 255, 0, 255), CC_CALLBACK_1(SettingsScene::applyButtonPressed, this),
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4)); 
	MenuItems.pushBack(applyButton);
}

// Set UI state from config
void SettingsScene::setDefaultUIState()
{
	bgSoundCB->setSelectedState(SettingsConfRW::readBGMusicPlaying());
	volumeSlider->setPercent(SettingsConfRW::readBGMusicVolume() * 100);
}

//======================================Callbacks

void SettingsScene::backButtonPressed(Ref* pSender)
{
	if (SettingsConfRW::readBGMusicPlaying() == true) {					//if BGM should be played
		if (!AudioManager::getInstance().isBackgroundMusicPlaying()) {  //but not playing 
			AudioManager::getInstance().playBackgroundAudio();		    //play it and set volume to config level
			AudioManager::getInstance().setBackgroundAudioVolume(SettingsConfRW::readBGMusicVolume());
		}
		else {														    //and playing -> set volume to config level		
			AudioManager::getInstance().setBackgroundAudioVolume(SettingsConfRW::readBGMusicVolume());
		}
	}
	else {																//if should not be played
		AudioManager::getInstance().stopBackgroundAudio();				//stop it
	}

	auto scene = MainMenuScene::createScene();							
	Director::getInstance()->replaceScene(scene);
}

//set values from UI to config
void SettingsScene::applyButtonPressed(Ref* pSender)
{
	SettingsConfRW::writeBGMusicPlaying(bgSoundCB->isSelected());
	SettingsConfRW::writeBGMusicVolume(volumeSlider->getPercent() / 100.f);
}
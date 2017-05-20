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
	drawUserInterface();
	setDefaultUIState();
	return true;	
}

//========================================UI
void SettingsScene::drawUserInterface()
{
	drawBackground();
	drawBGSoundCheckBox();
	drawMusicVolumeSlider();
	drawAIStateCheckBox();
	drawMenu();
}

void SettingsScene::drawBackground()
{
	auto backgroundImage = UImanager::createBackground(SETTINGS_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -1);
}

void SettingsScene::drawBGSoundCheckBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto textLabel = UImanager::createTextLabel("Background sound enabled",
		SETTINGS_LABEL_FONT, visibleSize.height / 20, Vec2::ZERO);
	textLabel->setPosition(Vec2(origin.x + textLabel->getBoundingBox().size.width / 1.3,
		origin.y + visibleSize.height - textLabel->getBoundingBox().size.height * 2.5));

	bgSoundCB = UImanager::createCheckBox(textLabel->getPosition() + Vec2(textLabel->getBoundingBox().size.height * 8, 6) , 
		Director::getInstance()->getWinSize().height / 18000);
	bgSoundCB->addEventListener([&](Ref* sender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED) {
			AudioManager::getInstance().playBackgroundAudio();
			AudioManager::getInstance().setBackgroundAudioVolume(volumeSlider->getPercent() / 100.f);
		}
		else if (type == CheckBox::EventType::UNSELECTED)	
			AudioManager::getInstance().stopBackgroundAudio();
	});

	this->addChild(textLabel, 1);
	this->addChild(bgSoundCB, 1);
}

void SettingsScene::drawMusicVolumeSlider()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sliderLabel = UImanager::createTextLabel("Background sound volume",
		SETTINGS_LABEL_FONT, visibleSize.height / 20, Vec2::ZERO);
	sliderLabel->setPosition(Vec2(origin.x + sliderLabel->getBoundingBox().size.width / 1.3,
		origin.y + visibleSize.height - sliderLabel->getBoundingBox().size.height * 5));

	volumeSlider = UImanager::createSlider(Vec2(bgSoundCB->getPosition().x, sliderLabel->getPosition().y),
		Director::getInstance()->getWinSize().height / 600);
	volumeSlider->addEventListener([&](Ref* sender, Slider::EventType type) 
	{
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			AudioManager::getInstance().setBackgroundAudioVolume((float)volumeSlider->getPercent() / 100);
	});
	this->addChild(sliderLabel, 1);
	this->addChild(volumeSlider);
}

void SettingsScene::drawAIStateCheckBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto textLabel = UImanager::createTextLabel("AI opponent enabled",
		SETTINGS_LABEL_FONT, visibleSize.height / 20, Vec2::ZERO);
	textLabel->setPosition(Vec2(origin.x + textLabel->getBoundingBox().size.width / 1.3,
		origin.y + visibleSize.height - textLabel->getBoundingBox().size.height * 7.5));

	aiEnabledCB = UImanager::createCheckBox(Vec2(bgSoundCB->getPosition().x, textLabel->getPosition().y),
		Director::getInstance()->getWinSize().height / 18000);

	this->addChild(textLabel, 1);
	this->addChild(aiEnabledCB, 1);
}

void SettingsScene::drawMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Vec2 menuPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5);

	std::vector<ButtonData*> *data = new std::vector<ButtonData*>;
	data->reserve(2);
	data->push_back(new ButtonData("Back", CC_CALLBACK_1(SettingsScene::backButtonPressed, this)));
	data->push_back(new ButtonData("Apply", CC_CALLBACK_1(SettingsScene::applyButtonPressed, this)));
	auto menu = UImanager::createMenu(data, false, menuPosition);
	this->addChild(menu, 1);
}

// Set UI state from config
void SettingsScene::setDefaultUIState()
{
	bgSoundCB->setSelectedState(Settings::getInstance().getBackgroundAudioEnabled());
	volumeSlider->setPercent(Settings::getInstance().getBackgroundAudioVolume() * 100);
	aiEnabledCB->setSelectedState(Settings::getInstance().getAIOpponentEnabled());
}

//======================================Callbacks

void SettingsScene::backButtonPressed(Ref* pSender)
{
	if (Settings::getInstance().getBackgroundAudioEnabled() == true) {	//if BGM should be played
		if (!AudioManager::getInstance().isBackgroundMusicPlaying()) {  //but not playing 
			AudioManager::getInstance().playBackgroundAudio();		    //play it and set volume to config level
			AudioManager::getInstance().setBackgroundAudioVolume(Settings::getInstance().getBackgroundAudioVolume());
		}
		else {														    //and playing -> set volume to config level		
			AudioManager::getInstance().setBackgroundAudioVolume(Settings::getInstance().getBackgroundAudioVolume());
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
	SettingsConfRW::writeBGMusicPlaying(bgSoundCB->isSelected());   //write to config
	SettingsConfRW::writeBGMusicVolume(volumeSlider->getPercent() / 100.f);
	SettingsConfRW::writeAIEnabled(aiEnabledCB->isSelected());

	Settings::getInstance().setBackgroundAudioEnabledState(bgSoundCB->isSelected()); //writeToSingleton
	Settings::getInstance().setBackgroundAudioVolumeValue(volumeSlider->getPercent() / 100.f);
	Settings::getInstance().setAIOpponentEnabled(aiEnabledCB->isSelected());
}
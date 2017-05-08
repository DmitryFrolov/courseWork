#ifndef UI_MANAGER
#define UI_MANAGER

#include "cocos2d.h"
#include <ui/CocosGUI.h>
USING_NS_CC;
#define BUTTON_LABEL_FONT "fonts/Enchanted Land cyr-lat.ttf"
#define BUTTON_LABEL_SIZE 60

static class UImanager 
{
public:
	static ui::LoadingBar* createLoadingBar(const Vec2 &loadingBarPosition)
	{
		auto loadingBar = ui::LoadingBar::create("slider/slider-track-fill.png", 20);
		loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
		loadingBar->setPosition(loadingBarPosition);
		return loadingBar;
	}
	
	static cocos2d::Sprite* createBackground(	const std::string &pathToImage,
												const float scale)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		auto backgroundImage = Sprite::create(pathToImage);
		backgroundImage->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)); 
		//background position at the center of the screen
		backgroundImage->setScale(scale);
		return backgroundImage;
	}

	static cocos2d::MenuItemLabel* createButton(const std::string &text, 
												const cocos2d::Color4B &textColor,
												const cocos2d::ccMenuCallback &callback, 
												const Vec2 &position)
	{
		auto label = Label::createWithTTF(text, BUTTON_LABEL_FONT, BUTTON_LABEL_SIZE);
		label->setTextColor(textColor);
		auto button = MenuItemLabel::create(label, callback);
		button->setPosition(position);
		return button;
	}

	static cocos2d::Label* createTextLabel(	const char *text, 
											const char *fontFilePath, 
											const int fontSize, 
											const Vec2 &position)
	{
		Label *label = Label::createWithTTF(text, fontFilePath, fontSize);
		label->setAnchorPoint(Vec2(0.5, 0.5));
		label->setPosition(position);
		return label;
	}

	static cocos2d::ui::Slider* createSlider(	const Vec2 &position, 
												const float scale = 1)
	{
		auto slider = cocos2d::ui::Slider::create();
		slider->setAnchorPoint(Vec2(0, 0.5));
		slider->loadBarTexture("slider/slider-track.png");
		slider->loadSlidBallTextures("slider/slider-cap.png", "slider/slider-cap.png", "");
		slider->loadProgressBarTexture("slider/slider-track-fill.png");
		slider->setPosition(position);
		slider->setScale(scale);

		return slider;
	}

	static cocos2d::ui::CheckBox* createCheckBox(	const Vec2 &position, 
													const float scale = 1)
	{
		auto checkBox = cocos2d::ui::CheckBox::create("CBdisabledYellow.png", "vote.png", cocos2d::ui::Widget::TextureResType::LOCAL);
		checkBox->setAnchorPoint(Vec2(0, 0.5));
		checkBox->setPosition(position);
		checkBox->setScale(scale);

		return checkBox;
	}
};

#endif // !UI_MANAGER

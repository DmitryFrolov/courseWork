#ifndef UI_MANAGER
#define UI_MANAGER

#include "cocos2d.h"
#include <ui/CocosGUI.h>
USING_NS_CC;
#define BUTTON_LABEL_FONT "fonts/Enchanted Land cyr-lat.ttf"
#define BUTTON_LABEL_SIZE 60

struct ButtonData
{
	std::string text;
	cocos2d::ccMenuCallback callback;

	ButtonData(std::string text, cocos2d::ccMenuCallback callback)
	{
		this->text = text;
		this->callback = callback;
	}
};

class UImanager 
{
public:
	static ui::LoadingBar* createLoadingBar(const Vec2 &loadingBarPosition)
	{
		auto loadingBar = ui::LoadingBar::create("slider/slider-track-fill.png", 0);
		loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
		loadingBar->setPosition(loadingBarPosition);
		return loadingBar;
	}
	
	static cocos2d::Sprite* createBackground(	const std::string &pathToImage)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto winSize = Director::getInstance()->getWinSize();

		auto backgroundImage = Sprite::create(pathToImage);
		backgroundImage->setPosition(Vec2(origin.x + visibleSize.width / 2, 
			origin.y + visibleSize.height / 2)); 
		//background position at the center of the screen
		backgroundImage->setScaleX(winSize.width / backgroundImage->getBoundingBox().size.width);
		backgroundImage->setScaleY(winSize.height / backgroundImage->getBoundingBox().size.height);
		return backgroundImage;
	}

	static cocos2d::MenuItemLabel* createButton(const std::string &text, 
												const cocos2d::Color4B &textColor,
												const cocos2d::ccMenuCallback &callback, 
												const Vec2 &position)
	{
		auto label = Label::createWithTTF(text, BUTTON_LABEL_FONT, 
			Director::getInstance()->getVisibleSize().height / 15);
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
		auto checkBox = cocos2d::ui::CheckBox::create("CBdisabledYellow.png", "vote.png", 
			cocos2d::ui::Widget::TextureResType::LOCAL);
		checkBox->setAnchorPoint(Vec2(0, 0.5));
		checkBox->setPosition(position);
		checkBox->setScale(scale);

		return checkBox;
	}

	static cocos2d::Menu* createMenu(	const std::vector<ButtonData*>* data,
										const bool isMenuVertical = true,
										Vec2 menuCenterPosition = Vec2::ZERO,
										const float spaceSize = 1.2,
										const cocos2d::Color4B color = ccc4(215, 255, 0, 255))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		Vector <MenuItem*> buttons;
		buttons.reserve(data->size());
		for (auto currentData : *data)
			buttons.pushBack(createButton(currentData->text, color, currentData->callback, Vec2::ZERO));
		
		if (menuCenterPosition == Vec2::ZERO)
			menuCenterPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

		Vec2 btnSpace, firstBtnPosition;
		if (isMenuVertical) {
			btnSpace = Vec2(0, buttons.at(0)->getContentSize().height * (1 + spaceSize));
			/*default space between btns*/
			Vec2 menuSize = btnSpace * buttons.size() - btnSpace * 0.6;
			firstBtnPosition = menuCenterPosition + menuSize / 2;
			for (size_t it = 0; it < buttons.size(); it++)
				buttons.at(it)->setPosition(firstBtnPosition - btnSpace * it);
		} else {
			btnSpace = Vec2(buttons.at(0)->getContentSize().width * (1 + spaceSize), 0);
			Vec2 menuSize = btnSpace * buttons.size() - btnSpace * 0.6;
			firstBtnPosition = menuCenterPosition - menuSize / 2;		
			for (size_t it = 0; it < buttons.size(); it++)
				buttons.at(it)->setPosition(firstBtnPosition + btnSpace * it);
		}		
		auto menu = Menu::createWithArray(buttons);
		menu->setPosition(Vec2::ZERO);
		return menu;
	}
};

#endif // !UI_MANAGER

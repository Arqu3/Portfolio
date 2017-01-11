#include "ResourceHandler.h"

using namespace std;

ResourceHandler::ResourceHandler() :
	mTextures(),
	mTextureNames(),
	mSounds(),
	mSoundNames(),
	mMusicNames(),
	textureCounter(0),
	soundCounter(0),
	musicCounter(0),
	mLevel1Loaded(false),
	mLevel3Loaded(false),
	mLastLevelLoaded(false)
{
	addTexture("loadscreen.png");
	addTexture("MainMenuBackground.png");
	addTexture("Test1.png");

	loadScreen.setSize(sf::Vector2f(1024, 576));
	loadScreen.setTexture(getTexture("loadscreen.png"));

	mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
	mLoadMessage.setFont(mFont);
	mLoadMessage.setCharacterSize(18);
	mLoadMessage.setStyle(sf::Text::Bold);
	mLoadMessage.setColor(sf::Color::White);
	mLoadMessage.setPosition(430, 490);
	mLoadMessage.setString("Laddar...");

	mView.setCenter(512, 288);
	mView.setSize(1024, 576);
}

ResourceHandler::~ResourceHandler()
{
	internalClear();
}

void ResourceHandler::internalClear()
{
	textureCounter = 0;
	soundCounter = 0;
	musicCounter = 0;
	mTextures.clear();
	mTextureNames.clear();

	mSounds.clear();
	mSoundNames.clear();

	mMusicNames.clear();
}

void ResourceHandler::loadGeneral(sf::RenderWindow &window)
{
	drawLoadScreen(window, "Teklar Karaktärer");
	//Thomas
	//addTexture("ThomasWalk.png");
	////Hilma
	//addTexture("HilmaWalk.png");
	//addTexture("HilmaPush.png");
	//addTexture("HilmaFishing.png");
	//Mr. RiddleSpider
	addTexture("RiddleSpider.png");

	addTexture("sepia.png");
	drawLoadScreen(window, "Lailar Ansiktsuttryck");
	//Character Expressions
	addTexture("expressionArnoldApologetic.png");
	addTexture("expressionArnoldHappy.png");
	addTexture("expressionArnoldLaughing.png");
	addTexture("expressionArnoldNeutral.png");
	addTexture("expressionArnoldSurprised.png");
	addTexture("expressionHilmaAbject.png");
	addTexture("expressionHilmaAngry.png");
	addTexture("expressionHilmaConfident.png");
	addTexture("expressionHilmaDetermined.png");
	addTexture("expressionHilmaGrumpy.png");
	addTexture("expressionHilmaHappy.png");
	addTexture("expressionHilmaNervous.png");
	addTexture("expressionHilmaNeutral.png");
	addTexture("expressionHilmaSad.png");
	addTexture("expressionHilmaSigh.png");
	addTexture("expressionHilmaSurprised.png");
	addTexture("expressionHilmaThoughtful.png");
	addTexture("expressionLadyAngry.png");
	addTexture("expressionLadyFriendly.png");
	addTexture("expressionLadyGiggling.png");
	addTexture("expressionLadyImpatient.png");
	addTexture("expressionLadyNeutral.png");
	addTexture("expressionLadyRemembers.png");
	addTexture("expressionLadyRemorseful.png");
	addTexture("expressionLadySurprised.png");
	addTexture("expressionLillemorHappy.png");
	addTexture("expressionLillemorLaughing.png");
	addTexture("expressionLillemorNeutral.png");
	addTexture("expressionLillemorSympathic.png");
	addTexture("expressionLillemorThinking.png");
	addTexture("expressionLisaEnthusiastic.png");
	addTexture("expressionLisaHappy.png");
	addTexture("expressionLisaIrritable.png");
	addTexture("expressionLisaNeutral.png");
	addTexture("expressionPutteAbject.png");
	addTexture("expressionPutteBrightens.png");
	addTexture("expressionPutteChocked.png");
	addTexture("expressionPutteHappy.png");
	addTexture("expressionPutteHelpless.png");
	addTexture("expressionPutteNervous.png");
	addTexture("expressionPutteNeutral.png");
	addTexture("expressionPutteRelieved.png");
	addTexture("expressionPutteSad.png");
	addTexture("expressionPutteSigh.png");
	addTexture("expressionPutteWorried.png");
	addTexture("expressionSkatmaranConfident.png");
	addTexture("expressionSkatmaranHappy.png");
	addTexture("expressionSkatmaranLaughing.png");
	addTexture("expressionSkatmaranNeutral.png");
	addTexture("expressionSkatmaranSigh.png");
	addTexture("expressionSkatmaranSnide.png");
	addTexture("expressionSkatmaranSurprised.png");
	addTexture("expressionSkatmaranThoughtful.png");
	addTexture("expressionThomasAngry.png");
	addTexture("expressionThomasBlush.png");
	addTexture("expressionThomasChocked.png");
	addTexture("expressionThomasCry.png");
	addTexture("expressionThomasDetermined.png");
	addTexture("expressionThomasHappy.png");
	addTexture("expressionThomasNeutral.png");
	addTexture("expressionThomasSad.png");
	addTexture("expressionThomasSceptic.png");
	addTexture("expressionThomasSigh.png");
	addTexture("expressionThomasSmile.png");
	addTexture("expressionThomasSurprised.png");
	addTexture("expressionThomasThoughtful.png");
	addTexture("expressionThomasWorried.png");
	addTexture("expressionTotteHappy.png");
	addTexture("expressionTotteNeutral.png");
	addTexture("expressionTotteSigh.png");
	addTexture("expressionTotteUncertain.png");
	addTexture("expressionTotteTest.png");
	drawLoadScreen(window, "Davidar UI");
	//In-game UI
	addTexture("InventoryIconGlow.png");
	addTexture("ExitIconGlow.png");
	addTexture("CluesIconGlow.png");
	addTexture("inventory.png");
	addTexture("ClueBackground1.png");
	addTexture("InfoIcon.png");
	addTexture("InfoBox.png");
	addTexture("textbox.png");
	addTexture("textboxSmall.png");
	//Main menu buttons
	addTexture("NewGame.png");
	addTexture("NewGameGLOW.png");
	addTexture("Continue.png");
	addTexture("ContinueGLOW.png");
	addTexture("Options.png");
	addTexture("OptionsGLOW.png");
	addTexture("Exit.png");
	addTexture("ExitGLOW.png");
	//Level Select Buttons
	addTexture("Level1.png");
	addTexture("Level1Glow.png");
	addTexture("Level2.png");
	addTexture("Level2Glow.png");
	addTexture("Level3.png");
	addTexture("Level3Glow.png");
	addTexture("Level4.png");
	addTexture("Level4Glow.png");

	drawLoadScreen(window, "Davidar Muspekare");
	//Cursors
	addTexture("mousecursor.png");
	addTexture("openhand.png");
	addTexture("closedhand.png");
	addTexture("speechbubble.png");
	addTexture("eyecursor.png");
	addTexture("scenechangecursor.png");

	drawLoadScreen(window, "Lailar Ansiktsuttryck");
	//Character Expressions
	addTexture("expressionHilmaAbject.png");
	addTexture("expressionHilmaAngry.png");
	addTexture("expressionHilmaConfident.png");
	addTexture("expressionHilmaDetermined.png");
	addTexture("expressionHilmaGrumpy.png");
	addTexture("expressionHilmaHappy.png");
	addTexture("expressionHilmaNervous.png");
	addTexture("expressionHilmaNeutral.png");
	addTexture("expressionHilmaSad.png");
	addTexture("expressionHilmaSigh.png");
	addTexture("expressionHilmaSurprised.png");
	addTexture("expressionHilmaThoughtful.png");
	addTexture("expressionThomasAngry.png");
	addTexture("expressionThomasBlush.png");
	addTexture("expressionThomasChocked.png");
	addTexture("expressionThomasCry.png");
	addTexture("expressionThomasDetermined.png");
	addTexture("expressionThomasHappy.png");
	addTexture("expressionThomasNeutral.png");
	addTexture("expressionThomasSad.png");
	addTexture("expressionThomasSceptic.png");
	addTexture("expressionThomasSigh.png");
	addTexture("expressionThomasSmile.png");
	addTexture("expressionThomasSurprised.png");
	addTexture("expressionThomasThoughtful.png");
	addTexture("expressionThomasWorried.png");

	drawLoadScreen(window, "Laddar Sepia");
	//Sepia
	addTexture("sepia.png");
	//Textboxes
	addTexture("textboxSmall.png");
	addTexture("textbox.png");

	drawLoadScreen(window, "PerHeimerar Musik");
	//Music
	addMusic("Level1Music.ogg");

	drawLoadScreen(window, "Matatasar Ljud");
	//Sound
	addSound("Footsteps_Thomas.ogg");
	addSound("Level1_Ambience.ogg");
	addSound("Aquarium.ogg");
	addSound("Magnet_Catch.ogg");
	addSound("Magnet_Drop.ogg");
	addSound("Pushing_Object.ogg");
	addSound("Radio_Noise.ogg");
	addSound("Regular_Item_Pickup.ogg");
	addSound("Crafting.ogg");
	addSound("Menu_Hat.ogg");
	addSound("Menu_Inventory.ogg");
	addSound("Menu_MainUI.ogg");
	addSound("Critical_Item.ogg");
	addSound("Inventory_Move.ogg");
}

void ResourceHandler::loadLevel1(sf::RenderWindow &window)
{
	//internalClear();

	mView.setCenter(512, 288);
	window.setView(mView);

	if (!mLevel1Loaded)
	{
		drawLoadScreen(window, "Davidar Inventoryikoner");
		//Inventory icons
		addTexture("AstronautINV.png");
		addTexture("FishingRodINV.png");
		addTexture("MagnetINV.png");
		addTexture("ScrewDeviceINV.png");
		//Custom clue icons
		addTexture("Clue1Aqua.png");
		addTexture("Clue1First.png");

		// Level1
		drawLoadScreen(window, "Maxar Objekt");
		//Thomas rum items
		addTexture("thomasstar.png");
		addTexture("thomasblock.png");
		addTexture("thomasmagnet.png");
		addTexture("thomasastronaut.png");
		addTexture("thomasbowl.png");
		addTexture("thomascube.png");
		addTexture("FishingRod.png");
		addTexture("FishingRodMagnet.png");
		addTexture("thomaswallstar.png");
		addTexture("RogerSwim.png");
		addTexture("AstronautGlow.png");

		drawLoadScreen(window, "Maxar Bakgrunder");
		//Thomas room background, playground, foreground
		addTexture("thomasbg.png");
		addTexture("thomaspg.png");
		addTexture("thomasfg.png");
		//Thomas zoom background, playground, foreground
		addTexture("thomaszoombg.png");
		addTexture("thomaszoompg.png");
		addTexture("thomaszoomfg.png");

		drawLoadScreen(window, "PerHeimerar Musik");
		//Music
		addMusic("Level1Music.ogg");
		//Narrator
		addMusic("Dialogue Narrator lvl1 part 1.ogg");
		addMusic("Dialogue Narrator lvl1 part 2.ogg");
		addMusic("Dialogue Narrator lvl1 part 3.ogg");
		addMusic("Dialogue Narrator lvl1 part 4.ogg");
		addMusic("Dialogue Narrator lvl1 part 5.ogg");
		addMusic("Dialogue Narrator lvl1 part 6.ogg");
		addMusic("Dialogue Narrator lvl1 part 7.ogg");
		addMusic("Dialogue Narrator lvl1 part 8.ogg");
		addMusic("Dialogue Narrator lvl1 part 9.ogg");
		//Thomas
		addMusic("Thomas lvl 1 Beginning part 1.ogg");
		addMusic("Thomas lvl 1 Beginning part 2.ogg");
		addMusic("Thomas lvl 1 Beginning part 3.ogg");
		addMusic("Thomas lvl 1 Beginning part 4.ogg");
		addMusic("Thomas lvl 1 Beginning part 5.ogg");
		addMusic("Thomas lvl 1 Beginning part 6.ogg");
		addMusic("Thomas lvl 1 Beginning part 7.ogg");
		addMusic("Thomas lvl 1 End part 1.ogg");
		addMusic("Thomas lvl 1 End part 2.ogg");
		addMusic("Thomas lvl 1 End part 3.ogg");
		addMusic("Thomas lvl 1 End part 4.ogg");
		addMusic("Thomas lvl 1 End part 5.ogg");
		addMusic("Thomas lvl 1 End part 6.ogg");
		addMusic("Thomas lvl 1 End part 7.ogg");
		addMusic("Thomas lvl 1 End part 8.ogg");
		addMusic("Thomas lvl 1 End part 9.ogg");
		addMusic("Thomas lvl 1 End part 10.ogg");
		addMusic("Thomas lvl 1 End part 11.ogg");
		addMusic("Thomas lvl 1 End part 12.ogg");
		//Hilma
		addMusic("Hilma lvl 1 Beginning part 1.ogg");
		addMusic("Hilma lvl 1 Beginning part 2.ogg");
		addMusic("Hilma lvl 1 Beginning part 3.ogg");
		addMusic("Hilma lvl 1 Beginning part 4.ogg");
		addMusic("Hilma lvl 1 Beginning part 5.ogg");
		addMusic("Hilma lvl 1 Beginning part 6.ogg");
		addMusic("Hilma lvl 1 Beginning part 7.ogg");
		addMusic("Hilma lvl 1 Beginning part 8.ogg");
		addMusic("Hilma lvl 1 Beginning part 9.ogg");
		addMusic("Hilma lvl 1 Beginning part 10.ogg");
		addMusic("Hilma lvl 1 Beginning part 11.ogg");
		addMusic("Hilma lvl 1 Beginning part 12.ogg");
		addMusic("Hilma lvl 1 Beginning part 13.ogg");
		addMusic("Hilma lvl 1 Beginning part 14.ogg");
		addMusic("Hilma lvl 1 End part 1.ogg");
		addMusic("Hilma lvl 1 End part 2.ogg");
		addMusic("Hilma lvl 1 End part 3.ogg");
		addMusic("Hilma lvl 1 End part 4.ogg");
		addMusic("Hilma lvl 1 End part 5.ogg");
		addMusic("Hilma lvl 1 End part 6.ogg");
		addMusic("Hilma lvl 1 End part 7.ogg");
		addMusic("Hilma lvl 1 End part 8.ogg");
		addMusic("Hilma lvl 1 End part 9.ogg");
		addMusic("Hilma lvl 1 End part 10.ogg");
		addMusic("Hilma lvl 1 End part 11.ogg");
		addMusic("Hilma lvl 1 End part 12.ogg");

		drawLoadScreen(window, "Matatasar Ljud");
		//Sound
		addSound("Footsteps_Thomas.ogg");
		addSound("Level1_Ambience.ogg");
		addSound("Aquarium.ogg");
		addSound("Magnet_Catch.ogg");
		addSound("Magnet_Drop.ogg");
		addSound("Pushing_Object.ogg");
		addSound("Radio_Noise.ogg");

		mLevel1Loaded = true;
	}
	else
	{
		drawLoadScreen(window, "Redan Laddad");
	}
}

void ResourceHandler::loadLevel2(sf::RenderWindow & window)
{
	mView.setCenter(512, 288);
	window.setView(mView);

	if (!mLevel2Loaded)
	{
		drawLoadScreen(window, "Verkstad to the limits");
		//Level 3
		addTexture("Workshop.png");
		addTexture("PutteSad.png");
		addTexture("LastLevel_ItemTest1.png");
		addTexture("LastLevel_ItemTest2.png");

		mLevel2Loaded = true;
	}
	else
	{
		drawLoadScreen(window, "Redan Laddad");
	}
}

void ResourceHandler::loadLevel3(sf::RenderWindow &window)
{
	mView.setCenter(512, 288);
	window.setView(mView);

	if (!mLevel3Loaded)
	{
		drawLoadScreen(window, "Gör Saker Med Blommor");
		//Level 3
		addTexture("Garden.png");
		addTexture("GardenForeground.png");
		addTexture("CabinBackground.png");
		addTexture("CabinForeground.png");
		addTexture("CabinPlayground.png");
		addTexture("magicworld_background.png");
		addTexture("magicworld_foreground.png");

		//Karaktärer
		addTexture("KNEKT.png");

		//Props
		addTexture("LastLevel_ItemTest1.png");
		addTexture("LastLevel_ItemTest2.png");
		addTexture("transparent.png");
		addTexture("Stick.png");
		addTexture("StickINV.png");
		addTexture("StickIcon.png");
		addTexture("Trimmer.png");
		addTexture("TrimmerINV.png");
		addTexture("Leash.png");
		addTexture("Flowers.png");
		addTexture("FlowersINV.png");
		addTexture("Sawdust.png");
		addTexture("SawdustINV.png");
		addTexture("Featherball.png");
		addTexture("FeatherballINV.png");
		addTexture("Skjuletfjun.png");
		addTexture("SkjuletfjunINV.png");
		addTexture("Clover.png");
		addTexture("CloverINV.png");
		addTexture("NailINV.png");
		addTexture("RippedClothINV.png");
		addTexture("Statue.png");

		mLevel3Loaded = true;
	}
	else
	{
		drawLoadScreen(window, "Redan Laddad");
	}
}

void ResourceHandler::loadLastLevel(sf::RenderWindow &window)
{
	//internalClear();

	mView.setCenter(512, 288);
	window.setView(mView);

	if (!mLastLevelLoaded)
	{
		drawLoadScreen(window, "Matatasar Ljud");
		//Sound
		addSound("Fish_Hit_Floor.ogg");
		addSound("Cat_Hissing.ogg");
		addSound("Cat.ogg");
		addSound("Planet_Puzzle.ogg");
		addSound("Gramophone.ogg");
		addSound("Running_Water.ogg");
		addSound("Screw_Globe.ogg");
		addSound("Jewelry_Box.ogg");

		drawLoadScreen(window, "Lailar Karaktärer");
		//Static Characters
		addTexture("LisaTotte.png");
		addTexture("PutteSad.png");
		addTexture("PutteLillemor.png");

		drawLoadScreen(window, "Davidar Inventoryikoner");
		//Inventory icons
		addTexture("beigeballINV.png");
		addTexture("needleINV.png");
		addTexture("marsINV.png");
		addTexture("pocketwatchINV.png");
		addTexture("saturnusringINV.png");
		addTexture("earthINV.png");
		addTexture("fishINV.png");
		addTexture("saturnusINV.png");
		addTexture("ScrewDeviceINV.png");
		addTexture("plutoINV.png");
		addTexture("clamINV.png");
		addTexture("MagnetINV.png"); //TODO - Replace with Pump INV Texture

		drawLoadScreen(window, "PerHeimerar Musik");
		//Music
		addMusic("LastLevelMusic.ogg");

		drawLoadScreen(window, "Maxar Bakgrunder");
		//Backgrounds
		addTexture("ARBETSRUMbakgrund.png");
		addTexture("ARBETSRUMmellangrund.png");
		addTexture("ARBETSRUMförgrund.png");
		addTexture("VARDAGSRUMbakgrund.png");
		addTexture("VARDAGSRUMmellangrund.png");
		addTexture("VARDAGSRUMförgrund.png");
		addTexture("KÖKbakgrund.png");
		addTexture("KÖKmellangrund.png");
		addTexture("KÖKförgrund.png");
		addTexture("Tavlan.png");

		drawLoadScreen(window, "Maxar Objekt");
		//Items
		addTexture("Fisk2.png");
		addTexture("Jordglob.png");
		addTexture("Apelsin.png");
		addTexture("thomasbowl.png");
		addTexture("Saturnus.png");
		addTexture("Venus.png");
		addTexture("Pluto.png");
		addTexture("Fisk1.png");
		addTexture("transparent.png");
		addTexture("GramophoneGlow.png");
		addTexture("TapGlow.png");
		addTexture("FoodbowlGlow.png");

		drawLoadScreen(window, "Beccar Testsaker");
		//Test Textures
		addTexture("LastLevel_ItemTest1.png");
		addTexture("LastLevel_ItemTest2.png");

		drawLoadScreen(window, "Teklar Katten");
		//Animations
		/*addTexture("CatWalking.png");
		addTexture("CatEating.png");*/

		mLastLevelLoaded = true;
	}
	else
	{
		drawLoadScreen(window, "Redan Laddad");
	}
}

//Adds a texture to the texture vector
void ResourceHandler::addTexture(string fileName)
{
	mTextures.push_back(new sf::Texture());
	mTextureNames.push_back(fileName);
	textureCounter++;

	if (!mTextures[textureCounter - 1]->loadFromFile("Resources/Textures/" + fileName))
	{
		cout << "Could not load texture at index: " << textureCounter - 1 << endl;
	}
}

//Adds sound to the sound vector
void ResourceHandler::addSound(string fileName)
{
	mSounds.push_back(new sf::SoundBuffer());
	mSoundNames.push_back(fileName);
	soundCounter++;

	if (!mSounds[soundCounter - 1]->loadFromFile("Resources/Sounds/" + fileName))
	{
		cout << "Could not load sound at index: " << soundCounter - 1 << endl;
	}
}

//Adds music name to the name vector
void ResourceHandler::addMusic(string fileName)
{
	mMusicNames.push_back("Resources/Music/" + fileName);
}

//Get texture at specific index
sf::Texture* ResourceHandler::getTexture(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mTextures.size() - 1);

	return mTextures[index];
}

//Get texture via name
sf::Texture* ResourceHandler::getTexture(string name)
{
	for (StringVector::size_type i = 0; i < mTextureNames.size(); i++)
	{
		if (name == mTextureNames[i])
		{
			return mTextures[i];
			break;
		}
	}
	return NULL;
}

//Get sound at specific index
sf::SoundBuffer* ResourceHandler::getSound(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mSounds.size() - 1);

	return mSounds[index];
}

//Get sound via name
sf::SoundBuffer* ResourceHandler::getSound(string name)
{
	for (StringVector::size_type i = 0; i < mSoundNames.size(); i++)
	{
		if (name == mSoundNames[i])
		{
			return mSounds[i];
			break;
		}
	}
	return NULL;
}

//Get music at specific index
string ResourceHandler::getMusic(int index)
{
	assert(index >= 0);
	assert((unsigned int)index <= mMusicNames.size() - 1);

	return mMusicNames[index];
}

//Get music via name
string ResourceHandler::getMusic(string name)
{
	for (StringVector::size_type i = 0; i < mMusicNames.size(); i++)
	{
		if ("Resources/Music/" + name == mMusicNames[i])
		{
			return mMusicNames[i];
			break;
		}
	}
	return NULL;
}

void ResourceHandler::drawLoadScreen(sf::RenderWindow &window, string loadMessage)
{
	mLoadMessage.setString(loadMessage);
	window.clear(sf::Color::Black);
	window.draw(loadScreen);
	window.draw(mLoadMessage);
	window.display();
}
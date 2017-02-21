#include "Assignment3.h"
 
TutorialApplication::TutorialApplication()
  : mTerrainGroup(0),
    mTerrainGlobals(0),
    mInfoLabel(0),
	mDistance(0),
	mWalkSpd(70.0),
	mDirection(Ogre::Vector3::ZERO),
	mDestination(Ogre::Vector3::ZERO),
	mAnimationState(0),
	mEntity(0),
	mNode(0)
{
}
 
TutorialApplication::~TutorialApplication()
{
}

void TutorialApplication::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setNearClipDistance(.1);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
	mCameraMan->setStyle(OgreBites::CS_MANUAL);
}

void TutorialApplication::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}
 
void TutorialApplication::createScene()
{
  bool infiniteClip =
    mRoot->getRenderSystem()->getCapabilities()->hasCapability(
      Ogre::RSC_INFINITE_FAR_PLANE);
 
  if (infiniteClip)
    mCamera->setFarClipDistance(0);
  else
    mCamera->setFarClipDistance(50000);
 
  mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .2));
 
  Ogre::Vector3 lightDir(.55, -.3, .75);
  lightDir.normalise();
 
  Ogre::Light* light = mSceneMgr->createLight("TestLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(lightDir);
  light->setDiffuseColour(Ogre::ColourValue::White);
  light->setSpecularColour(Ogre::ColourValue(.4, .4, .4));

  //ninja stuff
  Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("ninja.mesh");
  Ogre::SceneNode* ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ninjaNode", Ogre::Vector3(2000, 10, 1925));
  ninjaEntity->setCastShadows(true);
  ninjaNode->attachObject(ninjaEntity);
  ninjaNode->createChildSceneNode("ninjaCameraParent");
  Ogre::SceneNode* ninjaCameraParent = mSceneMgr->getSceneNode("ninjaCameraParent");
  ninjaCameraParent->createChildSceneNode("ninjaCamera", Ogre::Vector3(0, 100, 500));
  Ogre::SceneNode* ninjaCamera = mSceneMgr->getSceneNode("ninjaCamera");
  ninjaCamera->attachObject(mCamera);

  //ninja idle animation
  mAnimationState = ninjaEntity->getAnimationState("Idle1");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);

  //ogre stuff
  Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
  Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ogreNode", Ogre::Vector3(1990, 20, 1925));
  ogreEntity->setCastShadows(true);
  ogreNode->attachObject(ogreEntity);
 
  // Fog
 Ogre::ColourValue fadeColour(.9, .9, .9);
  mWindow->getViewport(0)->setBackgroundColour(fadeColour);
 
mSceneMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.002);
 
  // Terrain
  mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
 
  mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
    mSceneMgr,
    Ogre::Terrain::ALIGN_X_Z,
    513, 12000.0);
  mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
  mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
 
  configureTerrainDefaults(light);
 
  for (long x = 0; x <= 0; ++x)
    for (long y = 0; y <= 0; ++y)
      defineTerrain(x, y);
 
  mTerrainGroup->loadAllTerrains(true);
 
  if (mTerrainsImported)
  {
    Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
 
    while (ti.hasMoreElements())
    {
      Ogre::Terrain* t = ti.getNext()->instance;
      initBlendMaps(t);
    }
  }
 
  mTerrainGroup->freeTemporaryResources();

  mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
   Ogre::Plane plane;
   plane.d = 1000;
   plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
}
 
void TutorialApplication::createFrameListener()
{
  BaseApplication::createFrameListener();
 
  mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TerrainInfo", "", 350);
}
 
void TutorialApplication::destroyScene()
{
  OGRE_DELETE mTerrainGroup;
  OGRE_DELETE mTerrainGlobals;
}
 
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  if (!processUnbufferedInput(fe)) return false;

  rotateHead();
  mAnimationState->addTime(fe.timeSinceLastFrame);

  bool ret = BaseApplication::frameRenderingQueued(fe);
 
  if (mTerrainGroup->isDerivedDataUpdateInProgress())
  {
    mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
    mInfoLabel->show();
 
    if (mTerrainsImported)
      mInfoLabel->setCaption("Building terrain...");
    else
      mInfoLabel->setCaption("Updating textures...");
  }
  else
  {
    mTrayMgr->removeWidgetFromTray(mInfoLabel);
    mInfoLabel->hide();
 
    if (mTerrainsImported)
    {
      mTerrainGroup->saveAllTerrains(true);
      mTerrainsImported = false;
    }
  }
 
  return ret;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent & fe)
{
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 250;

	mKeyboard->capture();
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (mKeyboard->isKeyDown(OIS::KC_UP))
	{
		dirVec.z -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_DOWN))
	{
		dirVec.z += move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_LEFT))
	{
		mSceneMgr->getSceneNode("ninjaNode")->yaw(Ogre::Degree(5 * rotate));
	}
	if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
	{
		mSceneMgr->getSceneNode("ninjaNode")->yaw(Ogre::Degree(-5 * rotate));
	}

	mSceneMgr->getSceneNode("ninjaNode")->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	
	return true;
}

void TutorialApplication::rotateHead() 
{
	static Ogre::Real spin = .5;

	static Ogre::Real rotationDistance = 250;
	Ogre::Quaternion currentRotation = Ogre::Quaternion::ZERO;

	Ogre::Real current = Ogre::ControllerManager::getSingleton().getElapsedTime();
	currentRotation.x = current;

	Ogre::Real x = rotationDistance * Ogre::Math::Cos(currentRotation.x);
	Ogre::Real z = rotationDistance * Ogre::Math::Sin(currentRotation.x);

	mSceneMgr->getSceneNode("ogreNode")->lookAt(mSceneMgr->getSceneNode("ninjaNode")->getPosition(), Ogre::Node::TS_PARENT);
	mSceneMgr->getSceneNode("ogreNode")->setPosition(mSceneMgr->getSceneNode("ninjaNode")->getPosition() + Ogre::Vector3(x, 150, z));
	
	Ogre::Quaternion q(Ogre::Degree(160), Ogre::Vector3::UNIT_X);
	Ogre::Quaternion i(Ogre::Degree(-1.8721), Ogre::Vector3::UNIT_Z);

	mSceneMgr->getSceneNode("ogreNode")->rotate(q);
}
 
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
  img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
 
  if (flipX)
    img.flipAroundY();
  if (flipY)
    img.flipAroundX();
 
}
 
void TutorialApplication::defineTerrain(long x, long y)
{
  Ogre::String filename = mTerrainGroup->generateFilename(x, y);
 
  bool exists =
    Ogre::ResourceGroupManager::getSingleton().resourceExists(
      mTerrainGroup->getResourceGroup(),
      filename);
 
  if (exists)
    mTerrainGroup->defineTerrain(x, y);
  else
  {
    Ogre::Image img;
    getTerrainImage(x % 2 != 0, y % 2 != 0, img);
    mTerrainGroup->defineTerrain(x, y, &img);
 
    mTerrainsImported = true;
  }
}
 
void TutorialApplication::initBlendMaps(Ogre::Terrain* terrain)
{
  Ogre::Real minHeight0 = 70;
  Ogre::Real fadeDist0 = 40;
  Ogre::Real minHeight1 = 70;
  Ogre::Real fadeDist1 = 15;
 
  Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
  Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
 
  float* pBlend0 = blendMap0->getBlendPointer();
  float* pBlend1 = blendMap1->getBlendPointer();
 
  for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
  {
    for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
    {
      Ogre::Real tx, ty;
 
      blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
      Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
      Ogre::Real val = (height - minHeight0) / fadeDist0;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend0++ = val;
 
      val = (height - minHeight1) / fadeDist1;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend1++ = val;
    }
  }
 
  blendMap0->dirty();
  blendMap1->dirty();
  blendMap0->update();
  blendMap1->update();
 
}
 
void TutorialApplication::configureTerrainDefaults(Ogre::Light* light)
{
  mTerrainGlobals->setMaxPixelError(8);
  mTerrainGlobals->setCompositeMapDistance(3000);
 
  mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
  mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
  mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
 
  Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
  importData.terrainSize = 513;
  importData.worldSize = 12000.0;
  importData.inputScale = 600;
  importData.minBatchSize = 33;
  importData.maxBatchSize = 65;
 
  importData.layerList.resize(3);
  importData.layerList[0].worldSize = 100;
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_diffusespecular.dds");
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_normalheight.dds");
  importData.layerList[1].worldSize = 30;
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_diffusespecular.dds");
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_normalheight.dds");
  importData.layerList[2].worldSize = 200;
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_diffusespecular.dds");
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_normalheight.dds");
 
}
 
 
#if Ogre_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    // Create application object
    TutorialApplication app;
 
    try {
      app.go();
    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
	e.getFullDescription().c_str() << std::endl;
#endif
    }
 
    return 0;
  }
 
#ifdef __cplusplus
}
#endif
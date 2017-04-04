#include "Final.h"

int jumpFlag = 0;
int forwardFlag = 0;
int stealthFlag = 0;
int kickFlag = 0;
int crouchFlag = 0;
int backflipFlag = 0;
int attackFlag = 0;
int blockFlag = 0;
int rotateCameraFlag = 0;
 
TutorialApplication::TutorialApplication()
  : mTerrainGroup(0),
    mTerrainGlobals(0),
    mInfoLabel(0),
	mAnimationState(0),
	mEntity(0)
{
}
 
TutorialApplication::~TutorialApplication()
{
}

void TutorialApplication::createCamera()
{
	mSceneMgr->createCamera("PlayerCam");
	mSceneMgr->createCamera("MinimapCam");
}

void TutorialApplication::createViewports()
{
	mWindow->removeAllViewports();

	Ogre::Camera *cam = mSceneMgr->getCamera("PlayerCam");
	Ogre::Viewport *vp = mWindow->addViewport(cam, 0, 0, 0, 1, 1);
	vp->setOverlaysEnabled(false);
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::Camera *minimapCam = mSceneMgr->getCamera("MinimapCam");
	vp = mWindow->addViewport(minimapCam, 1, 0.75, 0, 0.25, 0.25);
	vp->setOverlaysEnabled(false);
	minimapCam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void TutorialApplication::createBulletSim(void) {
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new   btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -100, 0));
	{
		///create a few basic rigid bodies
		// start with ground plane, 1500, 1500
		Ogre::Terrain * pTerrain = mTerrainGroup->getTerrain(0, 0);
		float* terrainHeightData = pTerrain->getHeightData();
		Ogre::Vector3 terrainPosition = pTerrain->getPosition();
		float * pDataConvert = new float[pTerrain->getSize() *pTerrain->getSize()];
		for (int i = 0; i<pTerrain->getSize(); i++)
			memcpy(
				pDataConvert + pTerrain->getSize() * i, // source
				terrainHeightData + pTerrain->getSize() * (pTerrain->getSize() - i - 1), // target
				sizeof(float)*(pTerrain->getSize()) // size
			);

		float metersBetweenVertices = pTerrain->getWorldSize() / (pTerrain->getSize() - 1); //edit: fixed 0 -> 1 on 2010-08-13
		btVector3 localScaling(metersBetweenVertices, 1, metersBetweenVertices);

		btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(
			pTerrain->getSize(),
			pTerrain->getSize(),
			pDataConvert,
			1/*ignore*/,
			pTerrain->getMinHeight(),
			pTerrain->getMaxHeight(),
			1,
			PHY_FLOAT,
			true);

		groundShape->setUseDiamondSubdivision(true);
		groundShape->setLocalScaling(localScaling);

		btRigidBody * mGroundBody = new btRigidBody(0, new btDefaultMotionState(), groundShape);

		mGroundBody->getWorldTransform().setOrigin(
			btVector3(
				terrainPosition.x,
				terrainPosition.y + (pTerrain->getMaxHeight() - pTerrain->getMinHeight()) / 2,
				terrainPosition.z));

		mGroundBody->getWorldTransform().setRotation(
			btQuaternion(
				Ogre::Quaternion::IDENTITY.x,
				Ogre::Quaternion::IDENTITY.y,
				Ogre::Quaternion::IDENTITY.z,
				Ogre::Quaternion::IDENTITY.w));

		dynamicsWorld->addRigidBody(mGroundBody);
		collisionShapes.push_back(groundShape);
	}
}
 
void TutorialApplication::createScene()
{
  bool infiniteClip =
    mRoot->getRenderSystem()->getCapabilities()->hasCapability(
      Ogre::RSC_INFINITE_FAR_PLANE);
 
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

  //back camera
  ninjaNode->createChildSceneNode("ninjaCameraParent");
  Ogre::SceneNode* ninjaCameraParent = mSceneMgr->getSceneNode("ninjaCameraParent");
  ninjaCameraParent->createChildSceneNode("ninjaCamera", Ogre::Vector3(0, 100, 500));
  Ogre::SceneNode* ninjaCamera = mSceneMgr->getSceneNode("ninjaCamera");
  Ogre::Camera* backCamera = mSceneMgr->getCamera("PlayerCam");
  ninjaCamera->attachObject(backCamera);

  //minimap camera
  ninjaNode->createChildSceneNode("minimapCamParent");
  Ogre::SceneNode* minimapCamParent = mSceneMgr->getSceneNode("minimapCamParent");
  minimapCamParent->createChildSceneNode("minimapCameraNode", Ogre::Vector3(0, 800, 0));
  Ogre::SceneNode* minimapCameraNode = mSceneMgr->getSceneNode("minimapCameraNode");
  Ogre::Camera* minimapCamera = mSceneMgr->getCamera("MinimapCam");
  minimapCameraNode->pitch(Ogre::Degree(270));
  minimapCameraNode->attachObject(minimapCamera);

  //ninja idle animation
  mEntity = ninjaEntity;
  mAnimationState = mEntity->getAnimationState("Idle1");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);
  
  //draw ogre heads
  int numEnemies = 20;
  std::vector<Ogre::SceneNode *> ogreEnemies;

  for (int i = 0; i < numEnemies; i++) {
	  Ogre::String enemyName = "ogreEnemyNode" + std::to_string(i);
	  Ogre::Real enemyX = 1600 + (i * 70);

	  Ogre::Entity* ogreEnemy = mSceneMgr->createEntity("ogrehead.mesh");
	  Ogre::SceneNode* ogreEnemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(enemyName, Ogre::Vector3(enemyX, 70, 1625));
	  ogreEnemy->setCastShadows(true);
	  ogreEnemyNode->attachObject(ogreEnemy);

	  ogreEnemies.push_back(ogreEnemyNode);
  }

  // Fog
 Ogre::ColourValue fadeColour(.9, .9, .9);
  mWindow->getViewport(0)->setBackgroundColour(fadeColour);
 
mSceneMgr->setFog(Ogre::FOG_NONE, fadeColour, 0.002);
 
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

bool TutorialApplication::frameStarted(const Ogre::FrameEvent &evt)
{
	for (int i = 0; i < ptrToOgreObjects.size(); i++) {
		/*if (isProjectile(ptrToOgreObjects[i]->objectType)) {
			ptrToOgreObjects[i]->timeAlive += evt.timeSinceLastFrame;
			if (ptrToOgreObjects[i]->timeAlive >= 5) {
				RemoveObject(ptrToOgreObjects[i], i);
			}
		}*/
	}
	dynamicsWorld->stepSimulation(evt.timeSinceLastFrame);
	CheckCollisions();
	return true;
}

bool TutorialApplication::frameEnded(const Ogre::FrameEvent &evt) {
	for (int i = 0; i < ptrToOgreObjects.size(); i++) {
		ogreObject* currentObject = ptrToOgreObjects[i];
		/*if (isProjectile(currentObject->objectType)) {
			std::vector<ogreObject*> collidedObjects = currentObject->objectCollisions;

			//collision logic
			if (collidedObjects.size() == 1) {
				collidedObjects[0]->objectDelete = true;
				currentObject->objectDelete = true;
			}
			else {
				for (int j = 0; j < collidedObjects.size(); j++) {
					ogreObject* currentCollisionObject = collidedObjects[j];
					if (currentCollisionObject->isRed) {
						currentCollisionObject->objectDelete = true;
					}
					else {
						currentCollisionObject->entityObject->setMaterialName("Custom/Red");
						currentCollisionObject->isRed = true;
					}
					currentObject->objectDelete = true;
				}
			}
		}

		if (currentObject->objectDelete) {
			RemoveObject(currentObject, i);
		}*/
	}
	return true;
}

void TutorialApplication::RemoveObject(ogreObject* object, int index) {
	object->entityObject->detachFromParent();
	mSceneMgr->destroyEntity(object->entityObject);
	object->entityObject = NULL;
	mSceneMgr->destroySceneNode(object->sceneNodeObject);
	object->sceneNodeObject = NULL;

	dynamicsWorld->removeRigidBody(object->btRigidBodyObject);
	if (object->btRigidBodyObject && object->btRigidBodyObject->getMotionState())
		delete object->btRigidBodyObject->getMotionState();
	object->myMotionStateObject = NULL;
	dynamicsWorld->removeCollisionObject(object->btCollisionObjectObject);
	delete object->btCollisionObjectObject;
	object->btCollisionObjectObject = NULL;
	object->btRigidBodyObject = NULL;
	delete object->btCollisionShapeObject;
	object->btCollisionShapeObject = NULL;

	ptrToOgreObjects.erase(ptrToOgreObjects.begin() + index);
}

ogreObject* TutorialApplication::getOgreObject(const btCollisionObject * obj) {
	for (int i = 0; i < ptrToOgreObjects.size(); ++i) {
		if (ptrToOgreObjects[i]->btCollisionObjectObject == obj)
			return ptrToOgreObjects[i];

	}
	ogreObject* ret = new ogreObject;
	return ret;

}

void TutorialApplication::CheckCollisions() {

	//dynamicsworld->stepsimulation called in frameStarted function
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {

		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);

		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		ogreObject* ogreA = (ogreObject*)obA->getUserPointer();
		ogreObject* ogreB = (ogreObject*)obB->getUserPointer();

		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++) {
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f) {
				if (ogreA == NULL || ogreB == NULL) {
					continue;
				}

				/*if (isProjectile(ogreA->objectType) && isCube(ogreB->objectType)) {
					if (!ogreB->objectDelete) {
						ogreA->objectCollisions.push_back(ogreB);
					}
				}

				if (isProjectile(ogreB->objectType) && isCube(ogreA->objectType)) {
					if (!ogreA->objectDelete) {
						ogreB->objectCollisions.push_back(ogreA);
					}
				}*/
			}
		}
	}
}
 
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  if (!processUnbufferedInput(fe)) return false;

  handleAnimations(fe);
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

void TutorialApplication::handleAnimations(const Ogre::FrameEvent& evt)
{
	if (jumpFlag == 1)
	{
		jumpFlag = 0;
		mAnimationState = mEntity->getAnimationState("Jump");
		mAnimationState->setLoop(false);
		mAnimationState->setEnabled(true);
	}
	else if(forwardFlag != 0)
	{
		forwardFlag = 0;
		mAnimationState = mEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	else if (crouchFlag == 1)
	{
		crouchFlag = 0;
		mAnimationState = mEntity->getAnimationState("Crouch");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	else if (stealthFlag == 1)
	{
		stealthFlag = 0;
		mAnimationState = mEntity->getAnimationState("Stealth");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	else if (backflipFlag == 1)
	{
		backflipFlag = 0;
		mAnimationState = mEntity->getAnimationState("Backflip");
		mAnimationState->setLoop(false);
		mAnimationState->setEnabled(true);
	}
	else if (attackFlag == 1)
	{
		attackFlag = 0;
		mAnimationState = mEntity->getAnimationState("Attack1");
		mAnimationState->setLoop(false);
		mAnimationState->setEnabled(true);
	}
	else if (kickFlag == 1)
	{
		kickFlag = 0;
		mAnimationState = mEntity->getAnimationState("Kick");
		mAnimationState->setLoop(false);
		mAnimationState->setEnabled(true);
	}
	else if (blockFlag == 1)
	{
		blockFlag = 0;
		mAnimationState = mEntity->getAnimationState("Block");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	else
	{
		mAnimationState = mEntity->getAnimationState("Idle1");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent & fe)
{
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 250;

	mKeyboard->capture();
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	Ogre::SceneNode* ninjaNode = mSceneMgr->getSceneNode("ninjaNode");

	if (mKeyboard->isKeyDown(OIS::KC_UP))
	{
		dirVec.z -= move;
		forwardFlag = 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_DOWN))
	{
		dirVec.z += move;
		forwardFlag = -1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_LEFT))
	{
		ninjaNode->yaw(Ogre::Degree(5 * rotate));
	}
	if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
	{
		ninjaNode->yaw(Ogre::Degree(-5 * rotate));
	}
	if (mKeyboard->isKeyDown(OIS::KC_SPACE)) {
		jumpFlag = 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_LCONTROL))
	{
		if (jumpFlag == 0) {
			crouchFlag = 1;
		}
	}
	if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	{
		if (jumpFlag == 0) {
			stealthFlag = 1;
		}
	}
	if (mKeyboard->isKeyDown(OIS::KC_B))
	{
		if (jumpFlag == 0) {
			backflipFlag = 1;
		}
	}
	if (mKeyboard->isKeyDown(OIS::KC_E))
	{
		attackFlag = 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_K))
	{
		kickFlag = 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_X))
	{
		blockFlag = 1;
	}

	Ogre::Vector3 ninjaPos = ninjaNode->getPosition();
	float height = mTerrainGroup->getTerrain(0, 0)->getHeightAtWorldPosition(ninjaPos);
	dirVec.y = height - ninjaPos.y;
	mSceneMgr->getSceneNode("ninjaNode")->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	
	return true;
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
#include "Final.h"


 
TutorialApplication::TutorialApplication()
  : mTerrainGroup(0),
    mTerrainGlobals(0),
    mInfoLabel(0),
	mAnimationState(0),
	mEntity(0)
{
	forwardFlag = 0;
	points = 0;
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
	dynamicsWorld->setGravity(btVector3(0, -980, 0));
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
	createNinja();
	createOgres(20);
}
 
void TutorialApplication::createScene()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .2));

	Ogre::Vector3 lightDir(.55, -.3, .75);
	lightDir.normalise();

	Ogre::Light* light = mSceneMgr->createLight("TestLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightDir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(.4, .4, .4));

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

	createBulletSim();

	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	//ui inputs
	pointsLabel = wmgr.createWindow("TaharezLook/StaticText");
	std::string pointsText = "Points: " + std::to_string(points);
	pointsLabel->setText(pointsText);
	pointsLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	pointsLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.05, 0)));

	sheet->addChild(pointsLabel);
}

void TutorialApplication::createNinja() {
	std::string name = "ninjaNode";
	btVector3 Position = btVector3(2000, 10, 1925);
	btScalar mass = 1.0f;
	Ogre::Entity *ninja = mSceneMgr->createEntity("ninja.mesh");
	Ogre::SceneNode *ninjaNode;

	Ogre::Vector3 size = Ogre::Vector3::ZERO;
	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
	// Convert the bullet physics vector to the ogre vector
	ptrToOgreObject = new ogreObject;
	pos.x = Position.getX();
	pos.y = Position.getY();
	pos.z = Position.getZ();
	ptrToOgreObject->entityObject = ninja;
	ptrToOgreObject->entityObject->setCastShadows(true);
	try {
		ninjaNode = mSceneMgr->getSceneNode(name);
		ptrToOgreObject->sceneNodeObject = ninjaNode;
	}
	catch (Ogre::Exception& e) {
		ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
		ptrToOgreObject->sceneNodeObject = ninjaNode;
	}
	ptrToOgreObject->sceneNodeObject->attachObject(ptrToOgreObject->entityObject);
	assignItems(ninjaNode, ninja);

	Ogre::AxisAlignedBox boundingB = ptrToOgreObject->entityObject->getBoundingBox();
	size = boundingB.getSize()*0.95f;
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);
	ptrToOgreObject->myMotionStateObject = new MyMotionState(Transform, ptrToOgreObject->sceneNodeObject);
	//Give the rigid body half the size
	btVector3 HalfExtents(size.x, size.y, size.z);
	ptrToOgreObject->btCollisionShapeObject = new btBoxShape(HalfExtents);
	btVector3 LocalInertia = btVector3(0, 0, 0);
	ptrToOgreObject->btCollisionShapeObject->calculateLocalInertia(mass, LocalInertia);
	ptrToOgreObject->btRigidBodyObject = new btRigidBody(mass, ptrToOgreObject->myMotionStateObject, ptrToOgreObject->btCollisionShapeObject, LocalInertia);
	ptrToOgreObject->btRigidBodyObject->setAngularFactor(btVector3(0, 0, 0));
	ptrToOgreObject->btRigidBodyObject->setLinearFactor(btVector3(0, 0, 0));
	// Store a pointer to the Ogre Node so we can update it later
	ptrToOgreObject->btRigidBodyObject->setUserPointer((void *)(ptrToOgreObject));

	ptrToOgreObject->btCollisionObjectObject = ptrToOgreObject->btRigidBodyObject;
	ptrToOgreObject->objectDelete = false;
	ptrToOgreObject->objectType = name;
	ptrToOgreObjects.push_back(ptrToOgreObject);

	// Add it to the physics world
	dynamicsWorld->addRigidBody(ptrToOgreObject->btRigidBodyObject);
	collisionShapes.push_back(ptrToOgreObject->btCollisionShapeObject);

	ptrToNinja = ptrToOgreObject;
}

void TutorialApplication::assignItems(Ogre::SceneNode *node, Ogre::Entity *entity) {
	//back camera
	node->createChildSceneNode("ninjaCameraParent");
	Ogre::SceneNode* ninjaCameraParent = mSceneMgr->getSceneNode("ninjaCameraParent");
	ninjaCameraParent->createChildSceneNode("ninjaCamera", Ogre::Vector3(0, 100, 500));
	Ogre::SceneNode* ninjaCamera = mSceneMgr->getSceneNode("ninjaCamera");
	Ogre::Camera* backCamera = mSceneMgr->getCamera("PlayerCam");
	ninjaCamera->attachObject(backCamera);

	//minimap camera
	node->createChildSceneNode("minimapCamParent");
	Ogre::SceneNode* minimapCamParent = mSceneMgr->getSceneNode("minimapCamParent");
	minimapCamParent->createChildSceneNode("minimapCameraNode", Ogre::Vector3(0, 800, 0));
	Ogre::SceneNode* minimapCameraNode = mSceneMgr->getSceneNode("minimapCameraNode");
	Ogre::Camera* minimapCamera = mSceneMgr->getCamera("MinimapCam");
	minimapCameraNode->pitch(Ogre::Degree(270));
	minimapCameraNode->attachObject(minimapCamera);

	//ninja idle animation
	mEntity = entity;
	mAnimationState = mEntity->getAnimationState("Idle1");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
}

void TutorialApplication::createOgre(std::string name, btScalar mass, btVector3 &Position) {
	Ogre::Vector3 size = Ogre::Vector3::ZERO;
	// Convert the bullet physics vector to the ogre vector
	ptrToOgreObject = new ogreObject;
	ptrToOgreObject->entityObject = mSceneMgr->createEntity("ogrehead.mesh");;
	ptrToOgreObject->entityObject->setCastShadows(true);
	try {
		ptrToOgreObject->sceneNodeObject = mSceneMgr->getSceneNode(name);;
	}
	catch (Ogre::Exception& e) {
		ptrToOgreObject->sceneNodeObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	}
	ptrToOgreObject->sceneNodeObject->attachObject(ptrToOgreObject->entityObject);

	Ogre::AxisAlignedBox boundingB = ptrToOgreObject->entityObject->getBoundingBox();
	size = boundingB.getSize()*0.95f;
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);
	ptrToOgreObject->myMotionStateObject = new MyMotionState(Transform, ptrToOgreObject->sceneNodeObject);
	//Give the rigid body half the size
	btVector3 HalfExtents(size.x, size.y, size.z);
	ptrToOgreObject->btCollisionShapeObject = new btBoxShape(HalfExtents);
	btVector3 LocalInertia = btVector3(0, 0, 0);
	ptrToOgreObject->btCollisionShapeObject->calculateLocalInertia(mass, LocalInertia);
	ptrToOgreObject->btRigidBodyObject = new btRigidBody(mass, ptrToOgreObject->myMotionStateObject, ptrToOgreObject->btCollisionShapeObject, LocalInertia);
	ptrToOgreObject->btRigidBodyObject->setAngularFactor(btVector3(0, 0, 0));
	ptrToOgreObject->btRigidBodyObject->setLinearFactor(btVector3(0, 0, 0));
	// Store a pointer to the Ogre Node so we can update it later
	ptrToOgreObject->btRigidBodyObject->setUserPointer((void *)(ptrToOgreObject));

	ptrToOgreObject->btCollisionObjectObject = ptrToOgreObject->btRigidBodyObject;
	ptrToOgreObject->objectDelete = false;
	ptrToOgreObject->objectType = name;
	ptrToOgreObjects.push_back(ptrToOgreObject);

	// Add it to the physics world
	dynamicsWorld->addRigidBody(ptrToOgreObject->btRigidBodyObject);
	collisionShapes.push_back(ptrToOgreObject->btCollisionShapeObject);
}

void TutorialApplication::createOgres(int numOgres) {
	//draw ogre heads

	for (int i = 0; i < numOgres; i++) {
		Ogre::String enemyName = "ogreEnemyNode" + std::to_string(i);
		createOgre(enemyName, 1.0f, btVector3(1600 + (i * 70), 70, 1625));
	}
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

bool TutorialApplication::isNinja(std::string name) {
	return name.substr(0, 5) == "ninja";
}

bool TutorialApplication::isOgre(std::string name) {
	return name.substr(0, 4) == "ogre";
}

bool TutorialApplication::frameStarted(const Ogre::FrameEvent &evt)
{
	dynamicsWorld->stepSimulation(evt.timeSinceLastFrame);
	CheckCollisions();
	return true;
}

bool TutorialApplication::frameEnded(const Ogre::FrameEvent &evt) {
	for (int i = 0; i < ptrToOgreObjects.size(); i++) {
		ogreObject* currentObject = ptrToOgreObjects[i];
		if (isNinja(currentObject->objectType)) {
			std::vector<ogreObject*> collidedObjects = currentObject->objectCollisions;

			for (int j = 0; j < collidedObjects.size(); j++) {
				collidedObjects[j]->objectDelete = true;
			}
		}

		if (currentObject->objectDelete) {
			RemoveObject(currentObject, i);
			points += 100;
			std::string pointsText = "Points: " + std::to_string(points);
			pointsLabel->setText(pointsText);
		}
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
				
				if (isNinja(ogreA->objectType) && isOgre(ogreB->objectType)) {
					if (!ogreB->objectDelete) {
						ogreA->objectCollisions.push_back(ogreB);
					}
				}
				
				if (isNinja(ogreB->objectType) && isOgre(ogreA->objectType)) {
					if (!ogreA->objectDelete) {
						ogreB->objectCollisions.push_back(ogreA);
					}
				}
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
	if(forwardFlag != 0)
	{
		forwardFlag = 0;
		mAnimationState = mEntity->getAnimationState("Walk");
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
	btRigidBody* ninjaBody = ptrToNinja->btRigidBodyObject;

	if (mKeyboard->isKeyDown(OIS::KC_UP))
	{
		forwardFlag = 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_DOWN))
	{
		forwardFlag = -1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_LEFT))
	{
		btTransform src = ninjaBody->getCenterOfMassTransform();
		btVector3 up = btVector3(Ogre::Vector3::UNIT_Y.x, Ogre::Vector3::UNIT_Y.y, Ogre::Vector3::UNIT_Y.z);
		btVector3 normDirection = btVector3(0, 5 * rotate, 0).normalized();
		btScalar angle = acos(up.dot(normDirection));
		btVector3 axis = up.cross(normDirection);
		src.setRotation(btQuaternion(axis, angle));
		ninjaBody->setCenterOfMassTransform(src);
	}
	if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
	{
		//ninjaBody->setAngularVelocity(btVector3(0, -5 * rotate, 0));
	}

	ninjaBody->setLinearVelocity(btVector3(0, 0, -1000 * forwardFlag));
	
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
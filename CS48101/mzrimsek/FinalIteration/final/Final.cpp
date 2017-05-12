#include "Final.h"

TutorialApplication::TutorialApplication()
  : mInfoLabel(0),
	mAnimationState(0),
	mEntity(0)
{
	forwardFlag = 0;
	sidewayFlag = 0;
	upFlag = 0;

	points = 0;
	ogresKilled = 0;
	numOgres = 100;

	gameOver = false;
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
	
	createNinja();
	createOgres(numOgres);
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

	mSceneMgr->setSkyDome(true, "Examples/SpaceSkyBox");

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

	ogreLabel = wmgr.createWindow("TaharezLook/StaticText");
	std::string ogreText = "Ogres: " + std::to_string(ogresKilled) + "/" + std::to_string(numOgres);
	ogreLabel->setText(ogreText);
	ogreLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	ogreLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.10, 0)));

	timerBox = wmgr.createWindow("TaharezLook/StaticText", "CEGUIDemo/Time");
	timerBox->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	timerBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.15, 0)));
	timerBox->setText("Time Left: ");

	sheet->addChild(pointsLabel);
	sheet->addChild(ogreLabel);
	sheet->addChild(timerBox);
}

void TutorialApplication::resetTargets()
{
	ptrToNinja->sceneNodeObject->removeAndDestroyAllChildren();
	for (int i = 0; i < ptrToOgreObjects.size(); i++) {
			RemoveObject(ptrToOgreObjects[i], i);
	}

	collisionShapes.clear();
	delete dynamicsWorld;
	createBulletSim();
}

void TutorialApplication::createNinja() {
	std::string name = "ninjaNode";
	btVector3 Position = btVector3(0, 0, 2500);
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
	}
	catch (Ogre::Exception& e) {
		ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	}
	ptrToOgreObject->sceneNodeObject = ninjaNode;
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

void TutorialApplication::createOgre(std::string name, btScalar mass, btVector3 &Position, bool isSpecial) {
	Ogre::Vector3 size = Ogre::Vector3::ZERO;
	// Convert the bullet physics vector to the ogre vector
	ptrToOgreObject = new ogreObject;
	ptrToOgreObject->entityObject = mSceneMgr->createEntity("ogrehead.mesh");
	ptrToOgreObject->entityObject->setCastShadows(true);
	try {
		ptrToOgreObject->sceneNodeObject = mSceneMgr->getSceneNode(name);
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
	ptrToOgreObject->btRigidBodyObject->setLinearFactor(btVector3(0, 0, 0));
	// Store a pointer to the Ogre Node so we can update it later
	ptrToOgreObject->btRigidBodyObject->setUserPointer((void *)(ptrToOgreObject));

	if (isSpecial) 
	{
		ptrToOgreObject->btRigidBodyObject->setAngularVelocity(btVector3(0, 50, 0));
	}

	ptrToOgreObject->btCollisionObjectObject = ptrToOgreObject->btRigidBodyObject;
	ptrToOgreObject->objectDelete = false;
	ptrToOgreObject->objectType = name;
	ptrToOgreObject->isSpecial = isSpecial;
	ptrToOgreObjects.push_back(ptrToOgreObject);

	// Add it to the physics world
	dynamicsWorld->addRigidBody(ptrToOgreObject->btRigidBodyObject);
	collisionShapes.push_back(ptrToOgreObject->btCollisionShapeObject);
}

void TutorialApplication::createOgres(int numOgres) {
	srand(time(NULL));

	for (int i = 0; i < numOgres; i++) {
		Ogre::String enemyName = "ogreEnemyNode" + std::to_string(i);

		int xPos = rand() % 2500 - 1250;
		int yPos = rand() % 2500 - 1250;
		int zPos = rand() % 2500 - 1250;

		bool isSpecial = (xPos * yPos * zPos) % 35 == 0;
		createOgre(enemyName, 1.0f, btVector3(xPos, yPos, zPos), isSpecial);
	}
}
 
void TutorialApplication::createFrameListener()
{
  BaseApplication::createFrameListener();
}
 
void TutorialApplication::destroyScene()
{
  
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
			bool isSpecial = currentObject->isSpecial;
			RemoveObject(currentObject, i);

			ogresKilled++;
			std::string ogreText = "Ogres: " + std::to_string(ogresKilled) + "/" + std::to_string(numOgres);
			ogreLabel->setText(ogreText);

			if (isSpecial)
			{
				points += 500;
			}
			else {
				points += 100;
			}
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
	curTime = timer.getMilliseconds() / 1000;
	if (!gameOver) 
	{
		timerBox->setText("Time: " + Ogre::StringConverter::toString(60 - curTime));
	}

	//Timer up, game over
	if (curTime >= 60 || ogresKilled == numOgres)
	{
		gameOver = true;
		timerBox->setText("Game Over");
	}

  if (!processUnbufferedInput(fe)) return false;

  handleAnimations(fe);
  mAnimationState->addTime(fe.timeSinceLastFrame);

  bool ret = BaseApplication::frameRenderingQueued(fe);
 
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
	if (sidewayFlag != 0)
	{
		sidewayFlag = 0;
		mAnimationState = mEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	if (upFlag != 0)
	{
		upFlag = 0;
		mAnimationState = mEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
	if (sidewayFlag == 0 && forwardFlag == 0 && upFlag == 0)
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

	if (!gameOver)
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		{
			if (mKeyboard->isKeyDown(OIS::KC_UP))
			{
				upFlag = -1;
			}
			else if (mKeyboard->isKeyDown(OIS::KC_DOWN))
			{
				upFlag = 1;
			}
		}
		else
		{
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
				sidewayFlag = 1;
			}
			if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
			{
				sidewayFlag = -1;
			}
		}
	}
	else
	{
		if (mKeyboard->isKeyDown(OIS::KC_Y)) {
			//resetTargets();
		}
	}

	

	ninjaBody->setLinearVelocity(btVector3(-1000 * sidewayFlag, -1000 * upFlag, -1000 * forwardFlag));
	
	return true;
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
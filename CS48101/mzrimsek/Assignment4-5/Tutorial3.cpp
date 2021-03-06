#include "Tutorial3.h"

#define ROWS 5
#define COLS 3
#define CUBE_WIDTH 40
#define STARTING_X 2000
#define VELOCITY 10
 
TutorialApplication::TutorialApplication()
  : mTerrainGroup(0),
    mTerrainGlobals(0),
    mInfoLabel(0)
{
	//init globals from defines
	numRows = ROWS;
	numCols = COLS;
	cube_size = CUBE_WIDTH;
	velocity_magnitude = VELOCITY;
}
 
TutorialApplication::~TutorialApplication()
{
}
 
void TutorialApplication::CreateSphere(const btVector3 &Position, btScalar Mass, const btVector3 &scale, std::string name, float velocity){
	// empty ogre vectors for the sphere size and position
	Ogre::Vector3 size = Ogre::Vector3::ZERO;
	Ogre::Vector3 pos = Ogre::Vector3::ZERO;

	ptrToOgreObject = new ogreObject;
	// Convert the bullet physics vector to the ogre vector
	pos.x = Position.getX();
	pos.y = Position.getY();
	pos.z = Position.getZ();
	ptrToOgreObject->entityObject = mSceneMgr->createEntity(name, "sphere.mesh");
	ptrToOgreObject->entityObject->setCastShadows(true);
	ptrToOgreObject->entityObject->setMaterialName("Examples/SphereMappedRustySteel");

	ptrToOgreObject->sceneNodeObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	ptrToOgreObject->sceneNodeObject->attachObject(ptrToOgreObject->entityObject);
	ptrToOgreObject->sceneNodeObject->scale(Ogre::Vector3(scale.getX(), scale.getY(), scale.getZ()));

	Ogre::AxisAlignedBox boundingB = ptrToOgreObject->entityObject->getBoundingBox();

	boundingB.scale(Ogre::Vector3(scale.getX(), scale.getY(), scale.getZ()));
	size = boundingB.getSize()*0.95f;
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);
	ptrToOgreObject->myMotionStateObject = new MyMotionState(Transform, ptrToOgreObject->sceneNodeObject);

	btScalar HalfExtents(size.x);
	ptrToOgreObject->btCollisionShapeObject = new btSphereShape(HalfExtents);
	btVector3 LocalInertia;
	ptrToOgreObject->btCollisionShapeObject->calculateLocalInertia(Mass, LocalInertia);
	ptrToOgreObject->btRigidBodyObject = new btRigidBody(Mass, ptrToOgreObject->myMotionStateObject, ptrToOgreObject->btCollisionShapeObject, LocalInertia);

	ptrToOgreObject->btRigidBodyObject->setUserPointer((void *)(ptrToOgreObject));

	ptrToOgreObject->btCollisionObjectObject = ptrToOgreObject->btRigidBodyObject;
	ptrToOgreObject->objectDelete = false;
	ptrToOgreObject->objectType = name;
	ptrToOgreObject->timeAlive = 0;
	ptrToOgreObjects.push_back(ptrToOgreObject);

	dynamicsWorld->addRigidBody(ptrToOgreObject->btRigidBodyObject);
	collisionShapes.push_back(ptrToOgreObject->btCollisionShapeObject);

	//gets cameras direction
	Ogre::Vector3 CamDirection = mCamera->getDerivedDirection();

	//Vector conversion
	btVector3 FireVelocity = btVector3(CamDirection.x, CamDirection.y, CamDirection.z);

	//Now as we discussed above, we want our vector to have a certain speed. We first normalize it, and then multiply it by Speed
	FireVelocity.normalize();
	FireVelocity *= (velocity * 100);

	//Now we finally propel our box
	ptrToOgreObject->btRigidBodyObject->setLinearVelocity(FireVelocity * 1);
}

void TutorialApplication::CreateCube(const btVector3 &Position, btScalar Mass, const btVector3 &scale, std::string name) {
	// empty ogre vectors for the cubes size and position
	Ogre::Vector3 size = Ogre::Vector3::ZERO;
	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
	// Convert the bullet physics vector to the ogre vector
	ptrToOgreObject = new ogreObject;
	pos.x = Position.getX();
	pos.y = Position.getY();
	pos.z = Position.getZ();
	ptrToOgreObject->entityObject = mSceneMgr->createEntity(name, "cube.mesh");
	ptrToOgreObject->entityObject->setCastShadows(true);
	try {
		ptrToOgreObject->sceneNodeObject = mSceneMgr->getSceneNode(name);
	}
	catch (Ogre::Exception& e) {
		ptrToOgreObject->sceneNodeObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
	}
	ptrToOgreObject->sceneNodeObject->attachObject(ptrToOgreObject->entityObject);
	ptrToOgreObject->sceneNodeObject->scale(Ogre::Vector3(scale.getX(), scale.getY(), scale.getZ()));

	Ogre::AxisAlignedBox boundingB = ptrToOgreObject->entityObject->getBoundingBox();
	boundingB.scale(Ogre::Vector3(scale.getX(), scale.getY(), scale.getZ()));
	size = boundingB.getSize()*0.95f;
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);
	ptrToOgreObject->myMotionStateObject = new MyMotionState(Transform, ptrToOgreObject->sceneNodeObject);
	//Give the rigid body half the size
	// of our cube and tell it to create a BoxShape (cube)
	btVector3 HalfExtents(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);
	ptrToOgreObject->btCollisionShapeObject = new btBoxShape(HalfExtents);
	btVector3 LocalInertia;
	ptrToOgreObject->btCollisionShapeObject->calculateLocalInertia(Mass, LocalInertia);
	ptrToOgreObject->btRigidBodyObject = new btRigidBody(Mass, ptrToOgreObject->myMotionStateObject, ptrToOgreObject->btCollisionShapeObject, LocalInertia);

	// Store a pointer to the Ogre Node so we can update it later
	ptrToOgreObject->btRigidBodyObject->setUserPointer((void *)(ptrToOgreObject));

	ptrToOgreObject->btCollisionObjectObject = ptrToOgreObject->btRigidBodyObject;
	ptrToOgreObject->objectDelete = false;
	ptrToOgreObject->objectType = name;
	ptrToOgreObject->isRed = false;
	ptrToOgreObjects.push_back(ptrToOgreObject);

	// Add it to the physics world
	dynamicsWorld->addRigidBody(ptrToOgreObject->btRigidBodyObject);
	collisionShapes.push_back(ptrToOgreObject->btCollisionShapeObject);
}

void TutorialApplication::CreateCubes(int startingX, int rows, int columns, int cubeWidth) {
	for (int i = 0; i < columns; i++) {
		int x = startingX + (cubeWidth / 2 * (columns*i));
		for (int j = 0; j < rows; j++) {
			std::string name = "Cube" + std::to_string(cubeCount);
			int y = cubeWidth * (j + 1);
			double cubeDimension = 12.0 / cubeWidth;
			CreateCube(btVector3(x, y, 1400), 1.0f, btVector3(cubeDimension, cubeDimension, cubeDimension), name);
			cubeCount++;
		}
	}
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

	CreateCubes(STARTING_X, numRows, numCols, cube_size);
  }

void TutorialApplication::resetTargets() {
	//clean up old cubes
	for (int i = 0; i < ptrToOgreObjects.size(); i++){
		ptrToOgreObjects[i]->objectDelete = true;
	}

	//set global variables from ui inputs
	numRows = std::stoi(rows->getText().c_str());
	numCols = std::stoi(columns->getText().c_str());
	cube_size = std::stoi(size->getText().c_str());
	velocity_magnitude = std::stoi(velocity->getText().c_str());

	collisionShapes.clear();
	delete dynamicsWorld;
	createBulletSim();
}

Ogre::ManualObject* TutorialApplication::createCubeMesh(Ogre::String name, Ogre::String matName) {

	Ogre::ManualObject* cube = new Ogre::ManualObject(name);

	cube->begin(matName);

	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 1);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 1);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 0);
	cube->position(0.5, 0.5, 1.0); cube->normal(0.666667, 0.333333, 0.666667); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 1);
	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 1);
	cube->position(-0.5, 0.5, 1.0); cube->normal(-0.408248, 0.816497, 0.408248); cube->textureCoord(0, 0);
	cube->position(-0.5, 0.5, 0.0); cube->normal(-0.666667, 0.333333, -0.666667); cube->textureCoord(0, 1);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(1, 1);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(1, 0);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(0, 1);
	cube->position(0.5, 0.5, 0.0); cube->normal(0.408248, 0.816497, -0.408248); cube->textureCoord(1, 1);
	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(0, 0);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 0);
	cube->position(-0.5, 0.5, 1.0); cube->normal(-0.408248, 0.816497, 0.408248); cube->textureCoord(1, 0);
	cube->position(0.5, 0.5, 0.0); cube->normal(0.408248, 0.816497, -0.408248); cube->textureCoord(0, 1);
	cube->position(-0.5, 0.5, 0.0); cube->normal(-0.666667, 0.333333, -0.666667); cube->textureCoord(1, 1);
	cube->position(0.5, 0.5, 1.0); cube->normal(0.666667, 0.333333, 0.666667); cube->textureCoord(0, 0);

	cube->triangle(0, 1, 2);      cube->triangle(3, 1, 0);
	cube->triangle(4, 5, 6);      cube->triangle(4, 7, 5);
	cube->triangle(8, 9, 10);      cube->triangle(10, 7, 8);
	cube->triangle(4, 11, 12);   cube->triangle(4, 13, 11);
	cube->triangle(14, 8, 12);   cube->triangle(14, 15, 8);
	cube->triangle(16, 17, 18);   cube->triangle(16, 19, 17);
	cube->end();

	return cube;
}

void TutorialApplication::createScene()
{
  mCamera->setPosition(Ogre::Vector3(2100, 60, 1650));
  mCamera->lookAt(Ogre::Vector3(2050, 50, 1200));
  mCamera->setNearClipDistance(.1);
 
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
  CEGUI::Window *rowLabel = wmgr.createWindow("TaharezLook/StaticText");
  rowLabel->setText("Rows");
  rowLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  rowLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.05, 0)));

  rows = (CEGUI::DefaultWindow*)wmgr.createWindow("TaharezLook/Editbox");
  rows->setText(std::to_string(numRows));
  rows->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  rows->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.10, 0)));

  CEGUI::Window *colLabel = wmgr.createWindow("TaharezLook/StaticText");
  colLabel->setText("Columns");
  colLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  colLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.15, 0)));

  columns = (CEGUI::DefaultWindow*)wmgr.createWindow("TaharezLook/Editbox");
  columns->setText(std::to_string(numCols));
  columns->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  columns->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.20, 0)));

  CEGUI::Window *sizeLabel = wmgr.createWindow("TaharezLook/StaticText");
  sizeLabel->setText("Width (BigNum=Small)");
  sizeLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  sizeLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.25, 0)));

  size = (CEGUI::DefaultWindow*)wmgr.createWindow("TaharezLook/Editbox");
  size->setText(std::to_string(cube_size));
  size->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  size->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.30, 0)));

  CEGUI::Window *velocityLabel = wmgr.createWindow("TaharezLook/StaticText");
  velocityLabel->setText("Sphere velocity");
  velocityLabel->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  velocityLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.35, 0)));

  velocity = (CEGUI::DefaultWindow*)wmgr.createWindow("TaharezLook/Editbox");
  velocity->setText(std::to_string(velocity_magnitude));
  velocity->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  velocity->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.40, 0)));

  CEGUI::Window *Rebuild = wmgr.createWindow("TaharezLook/Button", "Button");
  Rebuild->setText("Y To Restart");
  Rebuild->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  Rebuild->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.45, 0)));
  Rebuild->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::resetButton, this));

  sheet->addChild(rowLabel);
  sheet->addChild(rows);
  sheet->addChild(colLabel);
  sheet->addChild(columns);
  sheet->addChild(sizeLabel);
  sheet->addChild(size);
  sheet->addChild(velocityLabel);
  sheet->addChild(velocity);
  sheet->addChild(Rebuild);
}

bool TutorialApplication::resetButton(const CEGUI::EventArgs& args) {
	resetTargets();
	return true;
}
 
void TutorialApplication::createFrameListener()
{
  BaseApplication::createFrameListener();
}
 
void TutorialApplication::destroyScene()
{
  OGRE_DELETE mTerrainGroup;
  OGRE_DELETE mTerrainGlobals;
}

bool TutorialApplication::frameStarted(const Ogre::FrameEvent &evt)
{
	for (int i = 0; i < ptrToOgreObjects.size(); i++){
		if (isProjectile(ptrToOgreObjects[i]->objectType)){
			ptrToOgreObjects[i]->timeAlive += evt.timeSinceLastFrame;
			if (ptrToOgreObjects[i]->timeAlive >= 5){
				RemoveObject(ptrToOgreObjects[i], i);
			}
		}
	}
	dynamicsWorld->stepSimulation(evt.timeSinceLastFrame);
	CheckCollisions();
	return true;
}

bool TutorialApplication::frameEnded(const Ogre::FrameEvent &evt) {
	for (int i = 0; i < ptrToOgreObjects.size(); i++) {
		ogreObject* currentObject = ptrToOgreObjects[i];
		if (isProjectile(currentObject->objectType)) {
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

bool TutorialApplication::isProjectile(std::string name) {
	return name.substr(0, 10) == "Projectile";
}

bool TutorialApplication::isCube(std::string name) {
	return name.substr(0, 4) == "Cube";
}

// Called in getCollisionPairs function
// sets the ptr to ogreObject to the ogreObject based on btCollisionObject
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
				
				if (isProjectile(ogreA->objectType) && isCube(ogreB->objectType)) {
					if (!ogreB->objectDelete) {
						ogreA->objectCollisions.push_back(ogreB);
					}
				}

				if (isProjectile(ogreB->objectType) && isCube(ogreA->objectType)) {
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
  bool ret = BaseApplication::frameRenderingQueued(fe);

  processUnbufferedInput(fe);

  return ret;
}

void TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe){
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 10;

	Ogre::Vector3 currentPos = mCamera->getPosition();
	
	if (!mKeyboard->isKeyDown(OIS::KC_Y) && isDown) {
		isDown = false;
	}
	if (mKeyboard->isKeyDown(OIS::KC_Y) && !isDown) {
		resetTargets();
		isDown = true;
	}

	if (mKeyboard->isKeyDown(OIS::KC_SPACE)){
		fire = true;
	}
	else if (!mKeyboard->isKeyDown(OIS::KC_SPACE) && fire) {
		fire = false;

		std::string projectileName = "Projectile" + std::to_string(sphereCount);
		CreateSphere(btVector3(mCamera->getPosition().x, mCamera->getPosition().y, mCamera->getPosition().z), 1.0f, btVector3(0.05, 0.05, 0.05), projectileName, velocity_magnitude);
		sphereCount++;
	}

	if (mKeyboard->isKeyDown(OIS::KC_LSHIFT) || mKeyboard->isKeyDown(OIS::KC_RSHIFT)) {
		if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
			currentPos.x -= move;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
			currentPos.x += move;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
			if (currentPos.y > 20) {
				currentPos.y -= move;
			}
		}
		else if (mKeyboard->isKeyDown(OIS::KC_UP)) {
			currentPos.y += move;
		}
	}
	else if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
		mCamera->yaw(Ogre::Degree(5 * rotate));
	}
	else if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
		mCamera->yaw(Ogre::Degree(-5 * rotate));
	}
	else if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
		mCamera->pitch(Ogre::Degree(-5 * rotate));
	}
	else if (mKeyboard->isKeyDown(OIS::KC_UP)) {
		mCamera->pitch(Ogre::Degree(5 * rotate));
	}

	mCamera->setPosition(currentPos);
}
 
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
  img.load("terrain.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
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

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	default:
		return CEGUI::LeftButton;
	}
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel)) return true;
	CEGUI::System &sys = CEGUI::System::getSingleton();
	if (arg.state.Z.rel)
		sys.getDefaultGUIContext().injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	mCameraMan->injectMouseMove(arg);
	return true;
}

bool TutorialApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id))) return true;
	mCameraMan->injectMouseDown(arg, id);
	return true;
}

bool TutorialApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id))) return true;
	mCameraMan->injectMouseUp(arg, id);
	return true;
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg)
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);
	return true;

	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	mCameraMan->injectKeyDown(arg);
	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
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
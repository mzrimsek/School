#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "OgreManualObject.h"
#include "btBulletDynamicsCommon.h"
#include "btHeightfieldTerrainShape.h"
#include "BaseApplication.h"
#include <cstdlib>
#include <random>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <vector>
#include <string>
#include "collisionStructs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
 
class TutorialApplication : public BaseApplication
{
public:
  TutorialApplication();
  virtual ~TutorialApplication();
 
protected:
  virtual void createScene();
  bool resetButton(const CEGUI::EventArgs& args);
  virtual void createFrameListener();
  virtual void destroyScene();
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
  bool frameStarted(const Ogre::FrameEvent &evt);
  bool frameEnded(const Ogre::FrameEvent & evt);
  void CreateCube(const btVector3 &Position, btScalar Mass, const btVector3 &scale, std::string name);
  void CreateCubes(int startingX, int rows, int columns, int cubeWidth);
  void CreateSphere(const btVector3 &Position, btScalar Mass, const btVector3 &scale, std::string name, float velocity);
  Ogre::ManualObject *createCubeMesh(Ogre::String name, Ogre::String matName);
 
private:
  CEGUI::OgreRenderer* mRenderer;
  void resetTargets();
  bool isProjectile(std::string name);
  bool isCube(std::string name);
  void defineTerrain(long x, long y);
  void processUnbufferedInput(const Ogre::FrameEvent& fe);
  bool fire = false;
  void initBlendMaps(Ogre::Terrain* terrain);
  void configureTerrainDefaults(Ogre::Light* light);
  bool mouseMoved(const OIS::MouseEvent & arg);
  bool mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
  bool keyPressed(const OIS::KeyEvent & arg);
  bool keyReleased(const OIS::KeyEvent & arg);
  ogreObject* getOgreObject(const btCollisionObject * obj);
  void CheckCollisions();
  void createBulletSim(void);
  bool mTerrainsImported;
  Ogre::TerrainGroup* mTerrainGroup;
  Ogre::TerrainGlobalOptions* mTerrainGlobals;
 
  bool isDown = false;
  int numOfSpheres = 0;
  OgreBites::Label* mInfoLabel;
  btDefaultCollisionConfiguration* collisionConfiguration;
  btCollisionDispatcher* dispatcher;
  btBroadphaseInterface* overlappingPairCache;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld* dynamicsWorld;
  btCollisionShape* groundShape;
  btAlignedObjectArray<btCollisionShape*> collisionShapes; 
  CEGUI::DefaultWindow *rows;
  CEGUI::DefaultWindow *columns;
  CEGUI::DefaultWindow *size;
  CEGUI::DefaultWindow *velocity;
  int numRows;
  int numCols;
  int cube_size;
  int velocity_magnitude;

  ogreObject* ptrToOgreObject;
  std::vector<ogreObject *> ptrToOgreObjects;
};
 


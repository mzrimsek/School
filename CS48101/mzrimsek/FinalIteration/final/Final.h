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
  void createNinja();
  void assignItems(Ogre::SceneNode * node, Ogre::Entity * entity);
  void createOgre(std::string name, btScalar mass, btVector3 & Position);
  void createOgres(int numOgres);
  virtual void createFrameListener();
  virtual void destroyScene();
  bool isNinja(std::string name);
  bool isOgre(std::string name);
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
  virtual void createCamera();
  virtual void createViewports();
  virtual void handleAnimations(const Ogre::FrameEvent& evt);
  bool frameStarted(const Ogre::FrameEvent &evt);
  bool frameEnded(const Ogre::FrameEvent & evt);
  void RemoveObject(ogreObject * object, int index);
 
private:
  CEGUI::OgreRenderer* mRenderer;
  bool processUnbufferedInput(const Ogre::FrameEvent& fe);
  void createBulletSim(void);  
  void CheckCollisions();
  ogreObject* getOgreObject(const btCollisionObject * obj);
 
  OgreBites::Label* mInfoLabel;
 
  Ogre::AnimationState*		mAnimationState;
  Ogre::Entity*				mEntity;

  btDefaultCollisionConfiguration* collisionConfiguration;
  btCollisionDispatcher* dispatcher;
  btBroadphaseInterface* overlappingPairCache;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld* dynamicsWorld;
  btCollisionShape* groundShape;
  btAlignedObjectArray<btCollisionShape*> collisionShapes;

  ogreObject* ptrToOgreObject;
  ogreObject* ptrToNinja;
  std::vector<ogreObject *> ptrToOgreObjects;

  CEGUI::Window *pointsLabel;
  int forwardFlag;
  int points;
  int sidewayFlag;
};
 


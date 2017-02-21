#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
 
#include "BaseApplication.h"
 
class TutorialApplication : public BaseApplication
{
public:
  TutorialApplication();
  virtual ~TutorialApplication();
 
protected:
  virtual void createScene();
  virtual void createFrameListener();
  virtual void destroyScene();
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
  virtual void createCamera();
  virtual void createViewports();
  virtual void rotateHead();
 
private:
  void defineTerrain(long x, long y);
  void initBlendMaps(Ogre::Terrain* terrain);
  void configureTerrainDefaults(Ogre::Light* light);
  bool processUnbufferedInput(const Ogre::FrameEvent& fe);
 
  bool mTerrainsImported;
  Ogre::TerrainGroup* mTerrainGroup;
  Ogre::TerrainGlobalOptions* mTerrainGlobals;
 
  OgreBites::Label* mInfoLabel;
 
  //animation stuff?
  std::deque<Ogre::Vector3> mWalkList;
  Ogre::Real					mDistance;
  Ogre::Real					mWalkSpd;
  Ogre::Vector3				mDirection;
  Ogre::Vector3				mDestination;
  Ogre::AnimationState*		mAnimationState;
  Ogre::Entity*				mEntity;
  Ogre::SceneNode*			mNode;
};
 


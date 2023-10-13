#pragma once

#include "Game.h"
#include "Door.h"

class CMyGame : public CGame
{
public:
	CMyGame();
	~CMyGame();

    // ----  Declare your game variables and objects here -------------

	// Variables
	int score;
	int level;
	int lives;

	bool gamewon;


    // Models and Model Lists
    CModelMd2 player;   // animated md2 model
    CModel box;			// a single box
    CModelMd2 ghost;		// animated ghost md2 model 
	CModelMd2 ghost2; // animated second ghost md2 model
	CModelMd2 ghost3; // animated third ghost md2 model
	CModelMd2 bossghost; // animated betrayus ghost (leader) md2 model
	CModel dot;
	CModel wallSegment;
	
	CModelList walls;   // list containing models
	CModelList ghosts;   // list of ghosts enemies
	CModelList dots;	// list of pac-dots to collect
	
	CDoor door1;       // door (our new door model class)
	CModel button1;    // button (simple cuboid model)
	
	CSprite startScreen;
	CSprite gameoverScreen;
	CSprite wonScreen;

	// Music Lists
	CSoundPlayer titleMusic;
	CSoundPlayer gameMusic;
	CSoundPlayer bossMusic;

	// Sound Effects Lists
	CSoundPlayer wakaSound;
	CSoundPlayer gameoverSound;
	CSoundPlayer levelupSound;
	CSoundPlayer victorySound;
	
	// game world floor
	CFloor floor;
	
	// Font
	CFont font;

   // -----   Add you member functions here ------
   
   void PlayerControl(); 
   
   void OgroControl();
   
   void CameraControl(CGraphics* g);
   
   void SetupLevel1();
   void SetupLevel2();
   void SetupLevel3();
   void SetupLevel4();
   void SetupLevel5();
	
	
   // ---------------------Event Handling --------------------------

	// Game Loop Funtions
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);
	virtual void OnRender3D(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartLevel(int level);
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};

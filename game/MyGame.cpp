#include "MyGame.h"
#include <fstream>

using namespace std;

CMyGame::CMyGame(void) {}

CMyGame::~CMyGame(void) {}

// --------  game initialisation --------
void CMyGame::OnInitialize()
{

	// Loading graphics and sound assets
	cout << "Loading assets" << endl;
	
	font.LoadDefault(); 
	
	// enable lighting
	Light.Enable();

	// abarlith model
	player.LoadModel("pacman/pacman.md2"); 
	player.SetScale( 15.0f);
	// ghost 1 model
	ghost.LoadModel("blinky/blinky.md2");
	ghost.SetScale( 5.0f);
	// ghost 2 model
	ghost2.LoadModel("inky/inky.md2");
	ghost2.SetScale(3.0f);
	// ghost 3 model
	ghost3.LoadModel("clyde/clyde.md2");
	ghost3.SetScale(7.0f);
	// leader ghost model
	bossghost.LoadModel("betrayus/betrayus.md2");
	bossghost.SetScale(10.0f);
	// coin model
	dot.LoadModel("coin/coin.obj"); 
	dot.SetScale(5.0f);

	wallSegment.LoadModel("wall/wall2.obj");
	wallSegment.SetScale(4.0f);
	wallSegment.SetToFloor(0);

	
	// floor texture
	floor.LoadTexture("metalfloor.bmp");
	floor.SetTiling(true);
	
	// start screen
	startScreen.LoadImage("startScreen.bmp");
	startScreen.SetPosition(Width/2.0f,Height/2.0f);

	// game over screen
	gameoverScreen.LoadImage("gameoverScreen.bmp");
	gameoverScreen.SetPosition(Width / 2.0f, Height / 2.0f);

	// win screen
	wonScreen.LoadImage("wonScreen.bmp");
	wonScreen.SetPosition(Width / 2.0f, Height / 2.0f);

}
	

void CMyGame::SetupLevel1()
{
    level=1;

	gamewon = false;
    
    // --- clear model lists ----
    walls.clear();
    ghosts.clear();
    dots.clear();	
	
	// set size of the game world (2000x2000)
	floor.SetSize(2000,2000);
	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	floor.SetPosition(1000,1000);
  
  // set box position, size and motion
    box.SetSize(100,100,100);  box.SetPosition( 220,50,220); box.SetToFloor(0);
    box.SetColor( CColor::Yellow());
  
    // player position
    player.SetPosition(849,100,947); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0); 
  
    // reset score
    score=0;

	// player has 3 lives
	lives = 3; 

  
    // --- clear model lists ----
    walls.clear();
    ghosts.clear();
    dots.clear();
  
    // --- create the four outer walls -----
    // The height of walls is 200
    float wallheight=200;
    float wallwidth=50;
  
	// declaring new file
	fstream myfile;
	// opening file for reading
	myfile.open("level1.txt", ios_base::in);

	int type, x, y, z, rot;
	// reading while the end of file has not been reached
	bool neof; // not end of file
	do
	{
		myfile >> type >> x >> y >> z >> rot;

		neof = myfile.good();
		//cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
		if (neof) // if not end of file
		{
			if (type == 1)   // wall segments
			{
				CModel* pWall = wallSegment.Clone(); // clone wall segment
				pWall->SetPosition((float)x, (float)y, (float)z);
				pWall->SetRotation(float(rot));
				pWall->SetToFloor(0);
				walls.push_back(pWall);
			}

			if (type == 2)  // coins
			{
				CModel* pCoin = dot.Clone();
				pCoin->SetPosition((float)x, (float)y, (float)z); pCoin->SetRotation((float)rot);
				dots.push_back(pCoin);
			}

			if (type == 3) // ghost
			{
				CModel* pEnemy = ghost.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(100);
				ghosts.push_back(pEnemy);
			}
			if (type == 4) // ghost 2
			{
				CModel* pEnemy = ghost2.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(200);
				ghosts.push_back(pEnemy);
			}
			if (type == 5) // ghost 3
			{
				CModel* pEnemy = ghost3.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(50);
				ghosts.push_back(pEnemy);
			}
		}
	} while (neof);
	myfile.close();
  
  
    // ----  set up door ----
    door1.SetSize(40,wallheight,330);
    // door location, door is currently closed
    door1.SetPosition(730,wallheight/2-10,931);
    // set door open position and closed position
    door1.SetPositions(CVector(730,wallheight/2-10,1201),CVector(730,wallheight/2-10,931));
    door1.SetColor(CColor(0,0,255));
  

    // ---- set up button -----
    button1.SetPosition(970,wallheight/2,758);
    button1.SetSize(40,40,40); 
    button1.SetColor(CColor::Red());
 

	titleMusic.Stop();
	gameMusic.Play("pacgame.wav", -1);
	
}



void CMyGame::SetupLevel2()
{
	level =2;
	
	// --- clear model lists ----
    walls.clear();
    ghosts.clear();
    dots.clear();
    
     // player position
    player.SetPosition(202,100,1809); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0); 
	
	// set size of the game world (2000x2000)
	floor.SetSize(2000,2000);
	
	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	floor.SetPosition(1000,1000);

	
    // declaring new file
    fstream myfile;
    // opening file for reading
    myfile.open("level2.txt", ios_base::in);

	int type, x, y, z, rot;
    // reading while the end of file has not been reached
    bool neof; // not end of file
    do
    {
      myfile >> type >> x >> y >> z >> rot;

	  neof = myfile.good();
      //cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
      if (neof) // if not end of file
      {
		   if (type==1)   // wall segments
		  {
			   CModel* pWall = wallSegment.Clone(); // clone wall segment
			   pWall->SetPosition((float)x, (float)y, (float)z);
			   pWall->SetRotation(float(rot));
			   pWall->SetToFloor(0);
			   walls.push_back( pWall);
		  }
		  
		  if (type==2)  // coins
		  {
			  CModel* pCoin=dot.Clone();
              pCoin->SetPosition((float)x,(float)y,(float)z); pCoin->SetRotation((float)rot);
              dots.push_back( pCoin);  
		  }
		  
		  if (type==3) // ghost
		  {
			 CModel* pEnemy=ghost.Clone();
             pEnemy->SetPosition((float)x,(float)y,(float)z); pEnemy->SetToFloor(0); 
             pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
             pEnemy->SetSpeed(100);
             ghosts.push_back( pEnemy);   
		  }
		  if (type==4) // ghost 2
		  {
			  CModel* pEnemy = ghost2.Clone();
			  pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
			  pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
			  pEnemy->SetSpeed(200);
			  ghosts.push_back(pEnemy);
		  }
		  if (type == 5) // ghost 3
		  {
			  CModel* pEnemy = ghost3.Clone();
			  pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
			  pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
			  pEnemy->SetSpeed(50);
			  ghosts.push_back(pEnemy);
		  }
	  } 
    }
    while(neof);
    myfile.close();
}
   

void CMyGame::SetupLevel3()
{
	level = 3;

	// --- clear model lists ----
	walls.clear();
	ghosts.clear();
	dots.clear();

	// player position
	player.SetPosition(1836, 100, 375); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);

	// set size of the game world (2000x2000)
	floor.SetSize(2000, 2000);

	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	floor.SetPosition(1000, 1000);

	// declaring new file
	fstream myfile;
	// opening file for reading
	myfile.open("level3.txt", ios_base::in);

	int type, x, y, z, rot;
	// reading while the end of file has not been reached
	bool neof; // not end of file
	do
	{
		myfile >> type >> x >> y >> z >> rot;

		neof = myfile.good();
		//cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
		if (neof) // if not end of file
		{
			if (type == 1)   // wall segments
			{
				CModel* pWall = wallSegment.Clone(); // clone wall segment
				pWall->SetPosition((float)x, (float)y, (float)z);
				pWall->SetRotation(float(rot));
				pWall->SetToFloor(0);
				walls.push_back(pWall);
			}

			if (type == 2)  // coins
			{
				CModel* pCoin = dot.Clone();
				pCoin->SetPosition((float)x, (float)y, (float)z); pCoin->SetRotation((float)rot);
				dots.push_back(pCoin);
			}

			if (type == 3) // ghost
			{
				CModel* pEnemy = ghost.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(100);
				ghosts.push_back(pEnemy);
			}
			if (type == 4) // ghost 2
			{
				CModel* pEnemy = ghost2.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(200);
				ghosts.push_back(pEnemy);
			}
			if (type == 5) // ghost 3
			{
				CModel* pEnemy = ghost3.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(50);
				ghosts.push_back(pEnemy);
			}
		}
	}     while (neof);
	myfile.close();
}

void CMyGame::SetupLevel4()
{
	level = 4;

	// --- clear model lists ----
	walls.clear();
	ghosts.clear();
	dots.clear();

	// player position
	player.SetPosition(1660, 100, 852); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);

	// set size of the game world (2000x2000)
	floor.SetSize(2000, 2000);

	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	floor.SetPosition(1000, 1000);

	// declaring new file
	fstream myfile;
	// opening file for reading
	myfile.open("level4.txt", ios_base::in);

	int type, x, y, z, rot;
	// reading while the end of file has not been reached
	bool neof; // not end of file
	do
	{
		myfile >> type >> x >> y >> z >> rot;

		neof = myfile.good();
		//cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
		if (neof) // if not end of file
		{
			if (type == 1)   // wall segments
			{
				CModel* pWall = wallSegment.Clone(); // clone wall segment
				pWall->SetPosition((float)x, (float)y, (float)z);
				pWall->SetRotation(float(rot));
				pWall->SetToFloor(0);
				walls.push_back(pWall);
			}

			if (type == 2)  // coins
			{
				CModel* pCoin = dot.Clone();
				pCoin->SetPosition((float)x, (float)y, (float)z); pCoin->SetRotation((float)rot);
				dots.push_back(pCoin);
			}

			if (type == 3) // ghost
			{
				CModel* pEnemy = ghost.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(100);
				ghosts.push_back(pEnemy);
			}
			if (type == 4) // ghost 2
			{
				CModel* pEnemy = ghost2.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(200);
				ghosts.push_back(pEnemy);
			}
			if (type == 5) // ghost 3
			{
				CModel* pEnemy = ghost3.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(50);
				ghosts.push_back(pEnemy);
			}
		}
	} while (neof);
	myfile.close();
}

void CMyGame::SetupLevel5()
{
	level = 5;

	// --- clear model lists ----
	walls.clear();
	ghosts.clear();
	dots.clear();

	// player position
	player.SetPosition(1231, 100, 141); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);

	// set size of the game world (2000x2000)
	floor.SetSize(2000, 2000);

	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	floor.SetPosition(1000, 1000);

	// declaring new file
	fstream myfile;
	// opening file for reading
	myfile.open("level5.txt", ios_base::in);

	int type, x, y, z, rot;
	// reading while the end of file has not been reached
	bool neof; // not end of file
	do
	{
		myfile >> type >> x >> y >> z >> rot;

		neof = myfile.good();
		//cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
		if (neof) // if not end of file
		{
			if (type == 1)   // wall segments
			{
				CModel* pWall = wallSegment.Clone(); // clone wall segment
				pWall->SetPosition((float)x, (float)y, (float)z);
				pWall->SetRotation(float(rot));
				pWall->SetToFloor(0);
				walls.push_back(pWall);
			}

			if (type == 2)  // coins
			{
				CModel* pCoin = dot.Clone();
				pCoin->SetPosition((float)x, (float)y, (float)z); pCoin->SetRotation((float)rot);
				dots.push_back(pCoin);
			}

			if (type == 3) // ghost
			{
				CModel* pEnemy = ghost.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(100);
				ghosts.push_back(pEnemy);
			}
			if (type == 4) // ghost 2
			{
				CModel* pEnemy = ghost2.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(200);
				ghosts.push_back(pEnemy);
			}
			if (type == 5) // ghost 3
			{
				CModel* pEnemy = ghost3.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(50);
				ghosts.push_back(pEnemy);
			}
			if (type == 6) // leader ghost
			{
				CModel* pEnemy = bossghost.Clone();
				pEnemy->SetPosition((float)x, (float)y, (float)z); pEnemy->SetToFloor(0);
				pEnemy->SetRotation(float(rot)); pEnemy->SetDirection((float)rot);
				pEnemy->SetSpeed(150);
				ghosts.push_back(pEnemy);
			}
		}
	} while (neof);
	myfile.close();

	gameMusic.Stop();
	bossMusic.Play("boss.wav", -1);
}
   
void CMyGame::OnStartLevel(int level)
{
}

// Game Logic in the OnUpdate function called every frame

void CMyGame::OnUpdate() 
{

	if (IsMenuMode())
	{
		titleMusic.Play("title.wav", -1);
	}

	if (IsMenuMode() || IsGameOver()) return;


	long t =  GetTime();
	
	// --- updating models ----
	
	box.Update( t);
	walls.Update( t);
	dots.Update(t);
	door1.Update(t);
	
	OgroControl();
    ghosts.Update( t);
	PlayerControl();
    player.Update( t);


	
}

void CMyGame::PlayerControl()
{
	// player control 
	if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a))
	{
		player.Rotate(5);
		if (player.GetHealth() == 100) player.SetDirection(player.GetRotation());
	}

	if (IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d))
	{
		player.Rotate(-5);
		if (player.GetHealth() == 100) player.SetDirection(player.GetRotation());
	}
	
	// Only move the player forward if it does not collide with a wall
	if (IsKeyDown(SDLK_UP) || IsKeyDown(SDLK_w))
	{ 
		bool move=true; // we assume that we can move

		// checking whether the player collides with any of the walls 
		for (CModel* pWall : walls)
		{
            // don't allow to move if there is a collision
			if (player.HitTestFront( pWall)) move=false;	
		}
		
		// check if player collides with the door
		if (level==1 && player.HitTestFront(&door1)) move=false;
		
		// if no collision, move forward
		if (move)
		{
			player.SetSpeed(500);
		}
		else player.SetSpeed(0);
	}
	else player.SetSpeed(0);
	
	// play running sequence when UP key is pressed
	// otherwise play standing sequence
	if (IsKeyDown(SDLK_UP) || IsKeyDown(SDLK_w))  player.PlayAnimation("Run",7,true);
	else player.PlayAnimation("Stand",5,true);
	
	// add score and remove coins if collected by the player
	for (CModel* pCoin : dots)
	{
		if(player.HitTest( pCoin->GetPositionV()))
		{
			score = score + 10;
			pCoin->Delete();
			wakaSound.Play("waka.wav");
		}
	}
	dots.remove_if(deleted);

}


void CMyGame::OgroControl()
{
	
	// ----- A.I. enemies (ghosts) control -------
	// ogros turn around once they hit a wall
	for (CModel* pGhost : ghosts)
	{
		// has ghost caught the player?
		if (pGhost->HitTest(&player))
		{
			lives = lives - 1;
			gameoverSound.Play("gameover.wav");

			if (level == 1)
			{
				player.SetPosition(849, 100, 947); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);
			}
			if (level == 2)
			{
				player.SetPosition(202, 100, 1809); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);
			}
			if (level == 3)
			{
				player.SetPosition(1836, 100, 375); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);
			}
			if (level == 4)
			{
				player.SetPosition(1660, 100, 852); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);
			}
			if (level == 5)
			{
				player.SetPosition(1231, 100, 141); player.SetToFloor(0); player.SetDirection(0); player.SetRotation(0);
			}

			if (lives <= 0)
			{
				gameMusic.Stop();
				bossMusic.Stop();
				GameOver();
			}
		}
		
		for (CModel* pWall : walls)
		{
		
		  // is ghost hitting a wall or door1?
		  if (pGhost->HitTestFront( pWall) || pGhost->HitTestFront(&door1))
		  {
			  // change direction and rotation of hitting a wall
			  pGhost->SetRotation( pGhost->GetRotation()+180);
			  pGhost->SetDirection( pGhost->GetRotation());
			  break;
			  
		  }
	    }
		
	}	
	
	// play ghost animations according to motion behaviour
	for (CModel* pGhost : ghosts)
	{
		// draw moving animation if moving
		if (pGhost->GetSpeed() > 0) pGhost->PlayAnimation("POSS", 5, true);
		else pGhost->PlayAnimation("POSS", 5, true);

		// make ghost move in a circle
		if (level == 5)
		{
			if (!(player.HitTest(pGhost)))
			{
				pGhost->SetDirection(player.GetX(), player.GetZ());
				pGhost->SetDirectionToPoint(player.GetX(), player.GetZ());
				pGhost->SetRotationToPoint(player.GetX(), player.GetZ());
			}
		}
	}	
}



//-----------------  Draw 2D overlay ----------------------
void CMyGame::OnDraw(CGraphics* g)
{
	if (IsMenuMode())
	{
	  startScreen.Draw(g);
	  return;
	}
	
	// draw level text
	font.SetColor( CColor::White()); font.SetSize( 32); font.DrawText( 10,Height-50, "LEVEL: " );
	font.DrawNumber(120,Height-50, level);
	// draw score
	font.SetColor( CColor::White()); font.DrawText(700, Height - 50, "SCORE: ");
	font.DrawNumber(Width-80,Height-50, score);

	// lives
	font.SetColor(CColor::White()); font.DrawText(700, 600, "LIVES: ");
	font.DrawNumber(820, 600, lives);
	
	// inform player to press the button
	if (level == 1 && player.HitTest(&button1)) 
	{
		font.SetColor( CColor::White());
		font.DrawText( Width/3,2*Height/3, "PRESS E TO ESCAPE" );
	}
	
	// draw GAME OVER if game over
   	if (gamewon == false && IsGameOver())
   	{
		gameoverScreen.Draw(g);
		return;
	}
	if (gamewon == true && IsGameOver())
	{
		wonScreen.Draw(g);
		return;
	}
	
	// draw well done if blue box has been reached
	if (player.HitTest(&box))
   	{
		font.SetSize(48); font.SetColor( CColor::White()); font.DrawText(250,350, "WELL DONE");
		font.SetSize(32); font.DrawText( 150,300, "CLICK MOUSE FOR NEXT LEVEL");	
	}
	
	
}

// ----------------   Draw 3D world -------------------------
void CMyGame::OnRender3D(CGraphics* g)
{

	CameraControl(g);


	// ------- Draw your 3D Models here ----------

	floor.Draw(g);
	//floor.Draw(true); // show floor with grid

	box.Draw(g);
	walls.Draw(g);
	player.Draw(g);
	ghosts.Draw(g);
    dots.Draw(g);

	//wallSegment.Draw(g);

	if (level == 1)
	{
	  door1.Draw(g);
	  button1.Draw(g);
    }
	
	
	//ShowBoundingBoxes();
	ShowCoordinateSystem();
	
}

void CMyGame::CameraControl(CGraphics* g)
{
	// game world tilt 
    float tilt=35;
    float zoom=3.0f;
	

	// ------ Global Transformation Functions -----

	glRotatef(tilt, 1, 0, 0);			// tilt game world around x axis
	glScalef(zoom, zoom, zoom);		    // scale the game world

	// rotate game world with player and face forward
	glRotatef(-player.GetRotation() + 90, 0, 1, 0);

	// Move camera up from player position. Camera will rise with the player
	glTranslatef(0, -player.GetY() - 100, 0);

	// position game world at the player position 
	glTranslatef(-player.GetX(), 0, -player.GetZ());

	UpdateView();
	Light.Apply();
}


// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	level = 1;
	//StartGame();	// this allows to start the game immediately	
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
    
}


// called when Game is Over
void CMyGame::OnGameOver()
{
	
}

// one time termination code
void CMyGame::OnTerminate()
{
	
}

// -------    Keyboard Event Handling ------------

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	
	if (sym == SDLK_SPACE)
	{
		if (IsPaused()) ResumeGame();
		else PauseGame();
	}
	if (sym == SDLK_F2)
	{
		NewGame();
		gameMusic.Stop();
	}
	
	
	// ------- Door Button Interaction -------------------
	// activate door when E is pressed and player colliding with button.
	// Status determines whether the door is opening or closing.
	if (level==1 && sym == SDLK_e && player.HitTest(&button1) && door1.GetStatus()==0 ) 
	{
		door1.Open();
		button1.SetColor( CColor::Green());
		
	}
	else if (level ==1 && sym == SDLK_e && player.HitTest(&button1) && door1.GetStatus()==1 ) 
	{
		door1.Close();
		button1.SetColor( CColor::Red());
	}
  
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	
}

// -----  Mouse Events Handlers -------------

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{

}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{    
	
	if (IsMenuMode() && level == 1) { SetupLevel1(); StartGame(); }	
	if (IsMenuMode() && level == 2) { SetupLevel2(); StartGame(); }
	if (IsMenuMode() && level == 3) { SetupLevel2(); StartGame(); }
	if (IsMenuMode() && level == 4) { SetupLevel2(); StartGame(); }
	if (IsMenuMode() && level == 5) { SetupLevel2(); StartGame(); }

	// change to level 2
	if (level == 1 && player.HitTest(&box))
	{
		lives = lives + 1;
		score = score + 200;
		SetupLevel2();
		levelupSound.Play("levelup.wav");
	}
	// change to level 3
	if (level == 2 && player.HitTest(&box))
	{
		lives = lives + 1;
		score = score + 200;
		SetupLevel3();
		levelupSound.Play("levelup.wav");
	}
	// change to level 4
	if (level == 3 && player.HitTest(&box))
	{
		lives = lives + 1;
		score = score + 200;
		SetupLevel4();
		levelupSound.Play("levelup.wav");
	}
	// change to level 5
	if (level == 4 && player.HitTest(&box))
	{
		lives = lives + 1;
		score = score + 200;
		SetupLevel5();
		levelupSound.Play("levelup.wav");
	}
	if (level == 5 && player.HitTest(&box))
	{
		bossMusic.Stop();
		victorySound.Play("victory.wav");
		gamewon = true;
		GameOver();
	}

}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}

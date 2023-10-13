#include "Sprite.h"

#include "GameApp.h"
#include "MyGame.h"

// export game to be accessed from other classes
extern CMyGame game;  

// make these global
CMyGame game;
CGameApp app;
  
int main(int argc, char* argv[])
{
	app.OpenWindow(900, 700, "PAC-MAN: ESPCAPES - 3D Assignment - K2015106");
    //app.OpenFullScreen();

	app.Run(&game);
	return(0);
}

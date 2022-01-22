#include <3ds.h>
#include <stdio.h>
#include <string.h>

static bool allowed = false;

// If you define this function, you can monitor/debug APT events
void _aptDebug(int a, int b)
{
	
		printf("_aptDebug(%d,%x)\n", a, b);
}

int main()
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	allowed = true;

	u32 aptbuf[0x25/4];

	printf("3DMenu APT chainload - Applets load test app\n");
	printf("Currently working applets:\n");
	printf("Press A to launch error applet\n");
	printf("Press B to launch appleted (Mii Editor)\n");
	printf("Press X to launch C stick tester applet\n");
	printf("Press Y to launch extrapad (draw applet)\n");
	printf("Press L to launch Photo Selector\n");
	printf("Press R to launch Sound Selector\n");
	printf("WIP applets:\n");
	printf("Press ^ to launch web browser (CRASH)\n");
	printf("Press < to launch home menu applet (WIP)\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Press START to exit\n");
	printf("3DMenu beta by mm1911 - Example app by libctru\n");

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 

		gfxFlushBuffers();

		if (kDown)
		{
			NS_APPID appId;


			if (kDown & KEY_Y) appId = APPID_MEMOLIB;
			else if (kDown & KEY_A) appId = APPID_ERROR;
			else if (kDown & KEY_B) appId = APPID_APPLETED;
			else if (kDown & KEY_X) appId = APPID_EXTRAPAD;
			else if (kDown & KEY_L) appId = APPID_PNOTE_AP;
			else if (kDown & KEY_R) appId = APPID_SNOTE_AP;
			else if (kDown & KEY_UP) appId = APPID_WEB;
			else if (kDown & KEY_LEFT) appId = APPID_HOMEMENU;
			else continue;

			memset(aptbuf, 0, sizeof(aptbuf));
			aptLaunchLibraryApplet(appId, aptbuf, sizeof(aptbuf), 0);
			printf("Library applet exited\n");
		}
	}

	// Exit services
	allowed = false;
	gfxExit();
	return 0;
}

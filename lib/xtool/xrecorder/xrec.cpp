/* ---------------------------- INCLUDE SECTION ----------------------------- */

#include "xglobal.h"
// tractortractor's added begin
#include "../../../src/global.h"
#include "../../../src/3d/3d_math.h"
#include "../../../src/iscreen/controls.h"
// tractortractor's added end

/* ----------------------------- STRUCT SECTION ----------------------------- */
/* ----------------------------- EXTERN SECTION ----------------------------- */

// tractortractor's added begin
extern int RecorderMode;
extern unsigned int RNDVAL;
extern RandomGenerator xm_random_generator;
extern unsigned int effectRNDVAL;
extern unsigned int BogusRNDVAL;
// tractortractor's added end

/* --------------------------- PROTOTYPE SECTION ---------------------------- */

int xtDispatchMessage(SDL_Event* msg);
void xtProcessMessageBuffer(void);
void xtSysQuant(void);

/* --------------------------- DEFINITION SECTION --------------------------- */

//#define _XRECORDER_LOG_

#define XREC_MAX_CMESSAGE	3
#define XREC_MAX_IMESSAGE	3

// Captured events...
static int XREC_CMESSAGES[XREC_MAX_CMESSAGE] =
{
	SDL_KEYDOWN,
	SDL_MOUSEBUTTONDOWN,
	SDL_JOYBUTTONDOWN
};

// Ignored events...
static int XREC_IMESSAGES[XREC_MAX_IMESSAGE] =
{
	SDL_MOUSEMOTION,
	SDL_MOUSEBUTTONUP,
	SDL_KEYUP
};

XRecorder XRec;

#ifdef	_XRECORDER_LOG_
XStream XRecLog;
#endif

XRecorder::XRecorder(void)
{
	flags = 0;
	frameCount = controlCount = 0;

	hFile = NULL;
	nextMsg = NULL;
	hWnd = NULL;
}

void XRecorder::Open(char* fname,int mode)
{
	int fmode;
	if(flags & (XRC_RECORD_MODE | XRC_PLAY_MODE))
		Close();

	if(!nextMsg){
		nextMsg = new XRecorderMessage;
		nextMsg -> data = new SDL_Event;
		nextMsgDataSize = sizeof(SDL_Event);
	}
	if(!hFile)
		hFile = new XStream;

	fmode = (mode == XRC_RECORD_MODE) ? XS_OUT : XS_IN;
	hFile -> open(fname,fmode);
#ifdef	_XRECORDER_LOG_
	if(mode == XRC_RECORD_MODE)
		XRecLog.open("xrec_wr.log",XS_OUT);
	else
		XRecLog.open("xrec_pl.log",XS_OUT);
#endif

	// tractortractor's added begin
	unsigned int rand_seed;
	unsigned int _rand_seed;
	unsigned int xm_random_generator_seed;
	if(mode == XRC_RECORD_MODE)
	{
//		std::cout << "XRC_RECORD_MODE" << '\n';
		// TODO implement better seeding.
		RNDVAL = time(NULL);
		rand_seed = time(NULL);
		_rand_seed = time(NULL);
		xm_random_generator_seed = time(NULL);
		effectRNDVAL = time(NULL);
		BogusRNDVAL = time(NULL);

		*hFile < RNDVAL < rand_seed < _rand_seed < xm_random_generator_seed < effectRNDVAL < BogusRNDVAL;
//		std::cout << "\nRNDVAL: " << RNDVAL << "\nrand_seed: " << rand_seed << "\n_rand_seed: " << _rand_seed << "\nxm_random_generator_seed: " << xm_random_generator_seed << "\neffectRNDVAL: " << effectRNDVAL << "\nBogusRNDVAL: " << BogusRNDVAL;
	}
	else if(mode == XRC_PLAY_MODE)
	{
//		std::cout << "XRC_PLAY_MODE" << '\n';
		*hFile > RNDVAL > rand_seed > _rand_seed > xm_random_generator_seed > effectRNDVAL > BogusRNDVAL;
//		std::cout << "\nRNDVAL: " << RNDVAL << "\nrand_seed: " << rand_seed << "\n_rand_seed: " << _rand_seed << "\nxm_random_generator_seed: " << xm_random_generator_seed << "\neffectRNDVAL: " << effectRNDVAL << "\nBogusRNDVAL: " << BogusRNDVAL;
	}
	srand(rand_seed);
	_srand(_rand_seed);
	xm_random_generator.set(xm_random_generator_seed);
	// tractortractor's added end

	frameCount = 0;
	flags |= mode;
}

// tractortractor's added begin
bool XRecorder::saveControls(iKeyControls *iControlsObj)
{
	*hFile < (int)iKEY_MAX_ID < (int)iKEY_OBJECT_SIZE;
	hFile -> write(iControlsObj -> keyCodes,iKEY_OBJECT_SIZE * iKEY_MAX_ID * sizeof(int));
	return true;
}

bool XRecorder::loadControls(iKeyControls *iControlsObj)
{
	int sz0,sz1;

	*hFile > sz0 > sz1;
	// If controls sizes do not match, moving file pointer to the end of controls.
	if(sz0 != iKEY_MAX_ID || sz1 != iKEY_OBJECT_SIZE){
		std::cerr << "XRec.loadControls: Controls' sizes do not match. Skipping controls loading.\n";
		hFile -> seek(sz0*sz1*sizeof(int), XS_CUR);
		return false;
	}
	hFile -> read(iControlsObj -> keyCodes,iKEY_OBJECT_SIZE * iKEY_MAX_ID * sizeof(int));
	return true;
}
// tractortractor's added end

void XRecorder::Close(void)
{
	if(flags & (XRC_RECORD_MODE | XRC_PLAY_MODE)){
		hFile -> close();
		flags &= ~(XRC_RECORD_MODE | XRC_PLAY_MODE | XRC_MESSAGE_READ);
#ifdef	_XRECORDER_LOG_
		XRecLog.close();
#endif
		RecorderMode &= ~(XRC_RECORD_MODE | XRC_PLAY_MODE | XRC_MESSAGE_READ); // tractortractor's added
	}
}

void XRecorder::GetMessage(void)
{
	if(flags & XRC_PLAY_MODE){
		if(hFile -> eof()){
			Close();
			return;
		}
		*hFile > nextMsg -> Type > nextMsg -> Frame > nextMsg -> DataSize;
		if(nextMsg -> DataSize){
			if(nextMsg -> DataSize > nextMsgDataSize){
				delete nextMsg -> data;
				nextMsg -> data = new SDL_Event;
				nextMsgDataSize = nextMsg -> DataSize;
			}
			hFile -> read((char*)nextMsg -> data, nextMsg -> DataSize);
		}
		flags |= XRC_MESSAGE_READ;
	}
}

void XRecorder::DispatchMessage(void)
{
	SDL_Event e;
	if((flags & XRC_MESSAGE_READ) && frameCount == nextMsg -> Frame){
		switch(nextMsg -> Type){
			case XRC_USER_MESSAGE:
				break;
			case XRC_XMOUSE_MESSAGE:
			case XRC_SYSTEM_MESSAGE:
				memcpy(&e, nextMsg->data, sizeof(SDL_Event));
				xtDispatchMessage(&e);
				break;
		}
#ifdef	_XRECORDER_LOG_
//		XRecLog < "\r\nEvent -> " <= nextMsg -> Type < "(" <= nextMsg -> data[0] < "), frame = " <= frameCount; // tractortractor's commented
		XRecLog < "\r\nEvent -> " <= nextMsg -> Type < "(" <= nextMsg -> data[0].type < "), frame = " <= frameCount; // tractortractor's added
#endif
	}
}

void XRecorder::Flush(void)
{
#ifdef	_XRECORDER_LOG_
//		XRecLog < "\r\nEvent -> " <= nextMsg -> Type < "(" <= nextMsg -> data[0] < "), frame = " <= frameCount; // tractortractor's commented
		XRecLog < "\r\nEvent -> " <= nextMsg -> Type < "(" <= nextMsg -> data[0].type < "), frame = " <= frameCount; // tractortractor's added
#endif
	*hFile < nextMsg -> Type < nextMsg -> Frame < nextMsg -> DataSize;
	if(nextMsg -> DataSize){
		hFile -> write((char*)nextMsg -> data, nextMsg -> DataSize);
	}
}

void XRecorder::Quant(void)
{
	frameCount ++;

	if(flags & XRC_PLAY_MODE){
		if(!(flags & XRC_MESSAGE_READ))
			GetMessage();

		while(flags & XRC_MESSAGE_READ && frameCount == nextMsg -> Frame){
			DispatchMessage();
			GetMessage();
		}
	}

	xtSysQuant();

	xtClearMessageQueue();
	xtProcessMessageBuffer();
}

void XRecorder::PutSysMessage(int id,SDL_Event *e)
{
	nextMsg -> Type = id;
	nextMsg -> Frame = frameCount;
	nextMsg -> DataSize = sizeof(SDL_Event);

	if(e->type == SDL_MOUSEMOTION)
	{
		std::cout << e->motion.x << '\n';
		std::cout << e->motion.y << '\n';
	}

	memcpy(nextMsg -> data, e, sizeof(SDL_Event));

	Flush();
}

/*void XRecorder::PutMessage(int msg,int sz,void* p)
{
	int i;
	int* ptr = (int*)p;

	nextMsg -> Type = msg;
	nextMsg -> Frame = frameCount;
	nextMsg -> DataSize = sz;

	if(nextMsgDataSize < nextMsg -> DataSize){
		delete nextMsg -> data;
		nextMsg -> data = new SDL_Event;
		nextMsgDataSize = nextMsg -> DataSize;
	}

	for(i = 0; i < sz; i ++)
		nextMsg -> data[i] = ptr[i];

	Flush();
}*/

int XRecorder::CheckMessage(int code)
{
	int i;
	for(i = 0; i < XREC_MAX_CMESSAGE; i ++){
		if(XREC_CMESSAGES[i] == code){
			if(flags & XRC_PLAY_MODE)
				Close();
			return 0;
		}
	}
	for(i = 0; i < XREC_MAX_IMESSAGE; i ++){
		if(XREC_IMESSAGES[i] == code) return 0;
	}
	return 1;
}

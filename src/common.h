#ifndef __COMMON_H__
#define __COMMON_H__


#define MIN(a,b)	(((a) < (b))?(a):(b))
#define MAX(a,b)	(((a) > (b))?(a):(b))

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

// tractortractor's added begin
extern int vangers_argc;
extern char **vangers_argv;
// tractortractor's added end

const uint MAP_POWER_X = 11;
const uint map_size_x = 1 << MAP_POWER_X;
const uint clip_mask_x = map_size_x - 1;
const uint TOR_POWER = 1;
const uint TOR_XSIZE = TOR_POWER*map_size_x;

extern uint MAP_POWER_Y;
extern uint map_size_y;
extern uint clip_mask_y;
extern uint clip_mask;
extern uint TOR_YSIZE;

#define XCYCL(x)	((x) & clip_mask_x)
#define YCYCL(y)	((y) & clip_mask_y)
#define iXCYCL(x)	((x) & clip_mask_x)
int iYCYCL(int y);

#ifdef _SURMAP_
const int MAX_RADIUS = 175;
#else
const int MAX_RADIUS = 48;
#endif

const int UNIT = 0x10000;	//32768;
const int SHIFT = 16;

const int PIx2 = 1 << 12;
const int PI = PIx2/2;
const int locPI = PIx2/2;

#define rPI(a)	(((a)) & (PIx2 - 1))

extern int* SI;
extern int* CO;

inline int COS(int x) { return CO[rPI(x)]; }
inline int SIN(int x) { return SI[rPI(x)]; }

#undef random
#define random(num) (int)RND(num)
//#define random(num) (std::cout << __FILE__ << "; " << __LINE__ << "; RND" << std::endl, (int)RND(num)) // tractortractor's test

#define RNDSIGN  ((!RND(2)) ? -1 : 1)
//#define RNDSIGN  (std::cout << __FILE__ << "; " << __LINE__ << "; RND" << std::endl ,(!RND(2)) ? -1 : 1) // tractortractor's test

extern const char* mapFName;

extern int ColorShow;
extern unsigned char* palbuf,*palbufA,*palbufC;

extern unsigned int RNDVAL; // tractortractor's added "int"
// tractortractor's test recorder begin
/*
#define RND(m) (recorder_match(RNDVAL, __FILE__, __LINE__), RND_func(m)) // tractortractor's test
extern int RecorderMode;
extern XStream recorder_match_file;
inline void recorder_match(unsigned int rndval, const char* file, unsigned int line)
{
	std::cout << "rndval: " << rndval << "; file: " << file << "; line: " << line << std::endl << std::endl;

	std::size_t file_name_size;
	char file_name_retrieved[200];
	int line_retrieved;
	if (RecorderMode == XRC_RECORD_MODE)
	{
		file_name_size = strlen(file);
		recorder_match_file < file_name_size;
		recorder_match_file.write(file, file_name_size);
		recorder_match_file < line;
	}
	else if(RecorderMode == XRC_PLAY_MODE){
		recorder_match_file > file_name_size;
		recorder_match_file.read(file_name_retrieved, file_name_size);
		file_name_retrieved[file_name_size] = '\0';
		recorder_match_file > line_retrieved;
		if(strcmp(file_name_retrieved,file) || line != line_retrieved) std::cout << "BOGUS!!!" << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}
inline unsigned int RND_func(unsigned m)
*/
// tractortractor's test recorder end
inline unsigned int RND(unsigned m) // tractortractor's added "int"
{
//	std::cout << __FILE__ << "; " << __LINE__ << "; custom" << std::endl; // tractortractor's test
	RNDVAL ^= RNDVAL >> 3;
	RNDVAL ^= RNDVAL << 28;
	RNDVAL &= 0x7FFFFFFF;

//	std::cout << "RNDVAL: " << RNDVAL << '\n'; // tractortractor's test
	if(!m) return 0;
	//std::cout<<"m:"<<m<<" r:"<<RNDVAL%m<<std::endl;
	return RNDVAL%m;
}

//extern XBuffer buffer_out;
//#define RND(m)  (buffer_out < __FILE__ < "\t" <= __LINE__ < "\t" <= RNDVAL < "\n",_RND(m))

/*extern unsigned realRNDVAL;
inline unsigned realRND(unsigned m)
{
	realRNDVAL ^= realRNDVAL >> 3;
	realRNDVAL ^= realRNDVAL << 28;
	realRNDVAL &= 0x7FFFFFFF;

	if(!m) return 0;
	std::cout<<"m:"<<m<<" r:"<<realRNDVAL%m<<std::endl;
	return realRNDVAL%m;
}*/
inline unsigned int realRND(unsigned m) { // tractortractor's added "int"
//	return 0; // tractortractor's test, breaks the game
//	std::cout << __FILE__ << "; " << __LINE__ << "; rand" << std::endl; // tractortractor's test
	if (!m) {
		return 0;
	}
	return rand()%m;
}

// tractortractor's moved from "lib\xtool\xmath\xmath.h" begin
#define xm_inline inline
class RandomGenerator
{
	enum { max_value = 0x7fff };
	int value;
public:
	RandomGenerator(int val = 1) { set(val); }
	void set(int val) { value = val; }
	int get() const { return value; }
	int operator()(); // Generates random value [0..max_value], non-inline due to some bugs with optimization
	xm_inline int operator()(int m) { return m ? (*this)() % m : 0; } // May by used in random_shuffle
	xm_inline float frnd(float x = 1.f){ return (float)((*this)()*2 - max_value)*x/(float)max_value; }
	xm_inline float fabsRnd(float x = 1.f){ return (float)((*this)())*x/(float)max_value; }
	xm_inline float frand(){ return (*this)()/(float)max_value; }
};
#undef xm_inline
// tractortractor's moved from "lib\xtool\xmath\xmath.h" end

inline void cycleTor(int& x,int& y)
{
	x &= TOR_XSIZE - 1;
	y &= TOR_YSIZE - 1;
}

#define PCSIDE	   64
#define PC_MAX	   2*PCSIDE + 1

#define mSQRT(a,b)	sqrt((a)*(double)(a) + (b)*(double)(b))
#define mATAN2(a,b)	rPI((int)(atan2((double)-b,(double)a)*PIx2/(2.*_PI)))

extern void* _video;

#define EXTERNAL_USE

char* GetTargetName(const char* name);

#define UP_LAYER	0
#define DOWN_LAYER	1

#define COL1		255
#define COL2		252
#define COL3		250
#define COL4		249
#define COL5		251

#ifdef _ROAD_
#define CLOCK()		(SDL_GetTicks()*18/1000)

const int SQ_SYSCOLOR = 256 - 8;
const int SYSCOLOR = 159;

struct sqFont {
	short num;
	unsigned char first,last;
	short sx,sy;
	void** data;

	void init(void* d);
	void draw(int x,int y,unsigned char* s,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
	void draw(int x,int y,char* s,int fore = SYSCOLOR,int back = -1){ draw(x,y,(unsigned char*)s,fore,back); }
	void drawtext(int x,int y,char* s,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
	void drawchar(int x,int y,int ch,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
	};
#endif

#ifdef VANGERS_DEBUG // tractortractor's added
extern "C"{ // tractortractor's added
size_t getPeakRSS(); // tractortractor's added
size_t getCurrentRSS(); // tractortractor's added
	} // tractortractor's added
//extern int __GlobalSize__; // tractortractor's added
extern XStream fmemory;
#define _MEM_STATISTIC_(a) fmemory < a <= static_cast<std::size_t>(getCurrentRSS()) < "\tclock\t" <= CLOCK() < "\n"; // tractortractor's commented
#else // tractortractor's added
#define _MEM_STATISTIC_(a) ;
#endif // VANGERS_DEBUG

#ifdef _MSC_VER // tractortractor's added
#define strncasecmp _strnicmp // tractortractor's added
#define strcasecmp _stricmp // tractortractor's added
#endif // _MSC_VER // tractortractor's added

#endif // __COMMON_H__


#include "parser.h"

#define _video_page	VS(_video)->_video

#define ALLOC(b,c)	new c[b]
#define FREE(p) 	delete p;

#include "3d_math.h"
#include "3dgraph.h"
#include "3dobject.h"
#include "heap.h"


extern MemoryHeap load_heap;
#define HEAP_BEGIN(sz)	    load_heap.alloc(sz);
#define HEAP_ALLOC(b,c)     ((c*)(load_heap.get((b)*sizeof(c))))
#define HEAP_ALLOC1(c)	    ((c*)(load_heap.get(sizeof(c))))
#define HEAP_END	    load_heap.end_alloc();


#ifdef VANGERS_DEBUG // tractortractor's _DEBUG -> VANGERS_DEBUG
#define _FOUT_
// extern XStream fout; // tractortractor's commented
#endif
// tractortractor's added begin
#ifdef _FOUT_
extern XStream fout;
#endif
// tractortractor's added end
extern XBuffer msg_buf;





SET(vangers_SRCS
	3d/3d_math.cpp
	3d/3dgraph.cpp
	3d/3dobject.cpp
	3d/dynamics.cpp
	3d/optimize.cpp
	actint/aci_scr.cpp
	actint/actint.cpp
	actint/actintml.cpp
	actint/ascr_fnc.cpp
	actint/ascript.cpp
	actint/chtree.cpp
	actint/sscript.cpp
	backg.cpp
	dast/poly3d.cpp
	iscreen/controls.cpp
	iscreen/hfont.cpp
	iscreen/i_chat.cpp
	iscreen/iextern.cpp
	iscreen/ikeys.cpp
	iscreen/imap_fnc.cpp
	iscreen/iml.cpp
	iscreen/iscr_fnc.cpp
	iscreen/iscreen.cpp
	iscreen/iscript.cpp
	iscreen/ivmap.cpp
	iscreen/script.cpp
	iscreen/smooth.cpp
	network.cpp
	palette.cpp
	particle/bmp2scr.cpp
	particle/deform.cpp
	particle/df.cpp
	particle/light.cpp
	particle/particle.cpp
	particle/partmap.cpp
	particle/pmaptype.cpp
	rle.cpp
	road.cpp
	sound/music.cpp
	sound/sound.cpp
	#sqint/sqibody.cpp #FOR surmap
	#sqint/sqicore.cpp #FOR surmap
	terra/compress.cpp
	terra/huff1.cpp
	terra/land.cpp
	terra/perpslop.cpp
	terra/siderend.cpp #ASM
	terra/slopskip.cpp
	terra/splay.cpp
	terra/vmap.cpp #ASM
	units/effect.cpp
	units/hobj.cpp
	units/items.cpp
	units/mechos.cpp
	units/moveland.cpp
	units/sensor.cpp
	units/track.cpp
	uvs/diagen.cpp
	uvs/screen.cpp
	uvs/univang.cpp
	xjoystick.cpp
	xsocket.cpp
	zmod_client.cpp 
	${WINDOWS_RES}
)

ADD_EXECUTABLE(vangers ${vangers_SRCS})

IF(WIN32)
	SET(WIN_LIB 
		wsock32
#		-mwindows # tractortractor's commented
	)
	IF(MSVC) # tractortractor's added
#		SET(WIN_LIB  # tractortractor's added
#			${WIN_LIB}  # tractortractor's added
#			ws2_32 # tractortractor's added
#		) # tractortractor's added
	ELSE(MSVC) # tractortractor's added
		SET(WIN_LIB  # tractortractor's added
			${WIN_LIB}  # tractortractor's added
			-mwindows # tractortractor's added
		) # tractortractor's added
	ENDIF(MSVC) # tractortractor's added
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(vangers
	${SDL2_LIBRARY}
	${OGG_LIBRARY}
	${VORBIS_LIBRARY}
	${VORBISFILE_LIBRARY}
	${CLUNK_LIBRARY}
	${SDL2_NET_LIBRARY}
	${FFMPEG_LIBRARIES}
	${ZLIB_LIBRARIES}
	${OPENGL_LIBRARIES}
	${WIN_LIB}
#	zip_convert # tractortractor's added
	xtool
	xgraph
	xsound
)

IF(ENTRIES_CONTROL OR VANGERS_DEBUG)
	TARGET_LINK_LIBRARIES(vangers 
		${Boost_LIBRARIES}
	)
ENDIF(ENTRIES_CONTROL OR VANGERS_DEBUG)

# tractortractor's added begin
IF(VANGERS_DEBUG)
	ADD_LIBRARY(getRSS STATIC ${GET_RSS_C_FILE})
	TARGET_LINK_LIBRARIES(vangers
		getRSS
	)
ENDIF(VANGERS_DEBUG)

# Added for correct rpath handling
INSTALL(TARGETS vangers RUNTIME DESTINATION ./)
# tractortractor's added end

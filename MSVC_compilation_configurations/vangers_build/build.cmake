SET(CMAKE_BUILD_TYPE Release CACHE STRING "Build type. Determines which compile flags are used. 4 possible values: Debug, Release, RelWithDebInfo and MinSizeRel")

SET(CMAKE_INSTALL_PREFIX "C:/games/vangers_modern_build" CACHE PATH "Where to install.")


# Only if ENTRIES_CONTROL or VANGERS_DEBUG is ON
SET(BOOST_ROOT "C:/boost/boost_1_59_0_msvc_x64_build" CACHE PATH "Root directory of Boost installation.")


SET(SDL2_INCLUDE_DIR "C:/SDL2_release/include/SDL2" CACHE PATH "Where the SDL2 include directory can be found")

SET(SDL2_LIBRARY "C:/SDL2_release/lib/SDL2.lib" CACHE FILEPATH "Where the SDL2 library can be found")

SET(SDL2MAIN_LIBRARY "C:/SDL2_release/lib/SDL2main.lib" CACHE FILEPATH "Where the SDL2main library can be found")

SET(SDL2_BUILDING_LIBRARY OFF CACHE BOOL "If this is defined, then no SDL2_main will be linked in.")



SET(SDL2_NET_INCLUDE_DIR "C:/SDL2_net_release/include" CACHE PATH "Where the SDL2_net include directory can be found")

SET(SDL2_NET_LIBRARY "C:/SDL2_net_release/lib/SDL2_net.lib" CACHE FILEPATH "Where the SDL2_net library can be found")



SET(OGG_INCLUDE_DIR "C:/libogg_release/include" CACHE PATH "Where the ogg include directory can be found")

SET(OGG_LIBRARY "C:/libogg_release/lib/libogg.lib" CACHE FILEPATH "Where the ogg library can be found")



SET(VORBIS_INCLUDE_DIR "C:/libvorbis_release/include" CACHE PATH "Where the vorbis include directory can be found")

SET(VORBIS_LIBRARY "C:/libvorbis_release/lib/libvorbis.lib" CACHE FILEPATH "Where the vorbis library can be found")


SET(VORBISFILE_INCLUDE_DIR "C:/libvorbis_release/include" CACHE PATH "Where the vorbisfile include directory can be found")

SET(VORBISFILE_LIBRARY "C:/libvorbis_release/lib/libvorbisfile.lib" CACHE FILEPATH "Where the vorbisfile library can be found")



SET(CLUNK_INCLUDE_DIR C:/clunk_for_vangers_release/include/clunk;C:/clunk_for_vangers_release/include CACHE PATH "Path to clunk include directory.")

SET(CLUNK_LIBRARY C:/clunk_for_vangers_release/lib/clunk.lib CACHE FILEPATH "Path to clunk library.")

SET(AVUTIL_INCLUDE_DIR "C:/libav_release/include;C:/libav_release/include/libavutil" CACHE PATH "Where the avutil include directory can be found")
SET(AVUTIL_LIBRARY "C:/libav_release/bin/avutil.lib" CACHE FILEPATH "Where the avutil library can be found")

SET(AVCODEC_INCLUDE_DIR "C:/libav_release/include;C:/libav_release/include/libavcodec" CACHE PATH "Where the avcodec include directory can be found")
SET(AVCODEC_LIBRARY "C:/libav_release/bin/avcodec.lib" CACHE FILEPATH "Where the avcodec library can be found")

SET(AVFORMAT_INCLUDE_DIR "C:/libav_release/include;C:/libav_release/include/libavformat" CACHE PATH "Where the avformat include directory can be found")
SET(AVFORMAT_LIBRARY "C:/libav_release/bin/avformat.lib" CACHE FILEPATH "Where the avformat library can be found")


SET(ZLIB_INCLUDE_DIR "C:/zlib_1.2.11_release/include" CACHE PATH "Where the zlib include directory can be found")

SET(ZLIB_LIBRARY "C:/zlib_1.2.11_release/lib/zlib.lib" CACHE FILEPATH "Where zlib library can be found")



SET(GET_RSS_C_FILE "E:/setup/getRSS/getRSS.c" CACHE PATH "Path to getRSS.c file")



SET(RUSSIAN_VERSION OFF CACHE BOOL "Build russian version")
#SET(BINARY_SCRIPT ON CACHE BOOL "Use binary script for interface") #set lower
SET(WITH_OPENGL OFF CACHE BOOL "Use experimental OpenGL renderer")
#SET(DIAGEN_TEST OFF CACHE BOOL "Dialog generator and test subsystem") #set lower



SET(VANGERS_DEBUG OFF CACHE BOOL "Define MSVC VANGERS_DEBUG macro.")
SET(FOUT OFF CACHE BOOL "Define _FOUT_ macro. Defined if _DEBUG is defined.")
SET(ALL_ITEM_IN_SHOP OFF CACHE BOOL "Define ALL_ITEM_IN_SHOP macro. Defined if _DEBUG is defined.")
SET(TABU_REPORT OFF CACHE BOOL "Define TABU_REPORT macro. Defined if _DEBUG is defined.")
SET(STAND_REPORT OFF CACHE BOOL "Define STAND_REPORT macro. Defined if _DEBUG is defined.")
SET(TOTAL_CASH OFF CACHE BOOL "Define TOTAL_CASH macro. Defined if _DEBUG is defined.")
SET(CHANGE_CYCLE_ON_NETWORK OFF CACHE BOOL "Define CHANGE_CYCLE_ON_NETWORK macro. Defined if _DEBUG is defined.")
SET(MSG_OUT OFF CACHE BOOL "Define MSG_OUT macro. Defined if _DEBUG is defined.")
SET(ENTRIES_CONTROL OFF CACHE BOOL "Define ENTRIES_CONTROL macro. Defined if _DEBUG is defined.")

SET(SICHER_DEBUG OFF CACHE BOOL "Define SICHER_DEBUG macro. Extra debugging mode. Controls are default, special fish and skyfarmers modes, no wall on main worlds, different info in debug menu.")
SET(NO_BORDER_FIELD OFF CACHE BOOL "Define NO_BORDER_FIELD macro.")

SET(IMOVE_MOUSE_OBJECTS OFF CACHE BOOL "Define iMOVE_MOUSE_OBJECTS macro. Allows player to edit positions of buttons of menus and freely move menu screen.")

SET(ACI_LOGFILE OFF CACHE BOOL "Define _ACI_LOGFILE_ macro.")
SET(ACI_SKIP_MAINMENU OFF CACHE BOOL "Define _ACI_SKIP_MAINMENU_ macro.")
SET(ACI_STARTUP_LOAD_GAME OFF CACHE BOOL "Define _ACI_STARTUP_LOAD_GAME_ macro.")
SET(ACI_SKIP_SHOP OFF CACHE BOOL "Define _ACI_SKIP_SHOP_ macro.")
SET(ACI_NO_SHOP_ANIMATION OFF CACHE BOOL "Define _ACI_NO_SHOP_ANIMATION_ macro.")
SET(ACI_ESCAVE_DEBUG OFF CACHE BOOL "Define _ACI_ESCAVE_DEBUG_ macro. Ability to add credits while in escave. Ability to change speech mode of next dialog line.")
SET(ACI_MAP_TESTING OFF CACHE BOOL "Define _ACI_MAP_TESTING_ macro.")
# Should be always ON since that's a very nice feature.
SET(ACI_SHOW_BUGS_ON_MAP ON CACHE BOOL "Define _ACI_SHOW_BUGS_ON_MAP_ macro. Shows beebs on minimap")
SET(ACI_CHECK_PHRASES OFF CACHE BOOL "Define _ACI_CHECK_PHRASES_ macro. Does nothing in this build.")
SET(ACI_BOUND_TEST OFF CACHE BOOL "Define _ACI_BOUND_TEST_ macro.")

SET(DIAGEN_TEST OFF CACHE BOOL "Define DIAGEN_TEST macro. Prints info about current dialog in console, dialog debugging tools.")
SET(IN_FILE OFF CACHE BOOL "Define _IN_FILE_ macro.")

SET(QUICK_LOAD OFF CACHE BOOL "Define QUICK_LOAD macro.")

# D is not a mistake here!
SET(DXSTREAM_DEBUG OFF CACHE BOOL "Define XSTREAM_DEBUG macro. Extra debugging mode. Info about each file opening with XStream is sent to std::cerr stream.")

SET(UNIT_DEBUG_VIEW OFF CACHE BOOL "Define UNIT_DEBUG_VIEW macro. Extra debugging mode. AI paths are seen, facing ray is drawn for controlled vanger.")

SET(TEST_TRACK OFF CACHE BOOL "Define TEST_TRACK macro. Extra debugging mode. No AI vangers, obscure 3d objects manipulations.")

SET(ITEM_LOG OFF CACHE BOOL "Define ITEM_LOG macro. Extra debugging mode. Saves data about items in item.log file.")

SET(SAVE_AI_STATUS OFF CACHE BOOL "Define SAVE_AI_STATUS macro. Extra debugging mode. Saves info about 3d AI evaluations in ai_log.log file.")

SET(TESTDIC OFF CACHE BOOL "Define TESTDIC macro. Game is disabled. Executable performs dictionary tests and quits.")

SET(MEMORY_STATISTICS OFF CACHE BOOL "Define MEMORY_STATISTICS macro.")
SET(ACTINT_MEMSTAT OFF CACHE BOOL "Define _ACTINT_MEMSTAT_ macro. Won't work without MEMORY_STATISTICS defined.")

SET(BINARY_SCRIPT OFF CACHE BOOL "Define _BINARY_SCRIPT_ macro. Use binary script for interface.")
SET(SAVE_BINARY_SCRIPT OFF CACHE BOOL "Define _SAVE_BINARY_SCRIPT_ macro. Works properly only if _BINARY_SCRIPT_ is NOT defined.")
SET(SAVE_PACKED_SCRIPT OFF CACHE BOOL "Define _SAVE_PACKED_SCRIPT_ macro. Works properly only if _BINARY_SCRIPT_ is NOT defined.")
SET(iSCRIPT_DEBUG OFF CACHE BOOL "Define _iSCRIPT_DEBUG_ macro.  Works properly only if _BINARY_SCRIPT_ is NOT defined. Saves info about script execution in \"ISCREEN\\setup.dat\" file.")

SET(FIRE_TEST OFF CACHE BOOL "Define FIRE_TEST macro.")

SET(DEMO OFF CACHE BOOL "Define _DEMO_ macro.")
SET(AUTOMATIC_CHANGE_WORLD OFF CACHE BOOL "Define AUTOMATIC_CHANGE_WORLD macro.")

SET(NO_CDAUDIO OFF CACHE BOOL "Define _NO_CDAUDIO_ macro.")

# Should be always ON since that's a very nice feature.
SET(ZRECORDER_ENABLED ON CACHE BOOL "Define zRECORDER_ENABLED macro.")
SET(XRECORDER_LOG OFF CACHE BOOL "Define _XRECORDER_LOG_ macro.")
SET(RTO_LOG OFF CACHE BOOL "Define _RTO_LOG_ macro.")
SET(AML_DEBUG OFF CACHE BOOL "Define AML_DEBUG macro.")

SET(TERRAIN16 OFF CACHE BOOL "Define TERRAIN16 macro.")
SET(XGR_SUPPRESS_HICOLOR OFF CACHE BOOL "Define XGR_SUPPRESS_HICOLOR macro.")

SET(LARGE_MODEL OFF CACHE BOOL "Define _LARGE_MODEL_ macro.")
SET(STATIC_TABLES OFF CACHE BOOL "Define _STATIC_TABLES_ macro.")

SET(XSTRDUP OFF CACHE BOOL "Define XSTRDUP macro.")

SET(MT OFF CACHE BOOL "Define _MT_ macro.")

SET(GENERATE_MATRIX_SHAPES OFF CACHE BOOL "Define _GENERATE_MATRIX_SHAPES_ macro.")
SET(GENERATE_iMATRIX_SHAPES OFF CACHE BOOL "Define _GENERATE_iMATRIX_SHAPES_ macro.")
SET(GENERATE_ITEM_DATA OFF CACHE BOOL "Define _GENERATE_ITEM_DATA_ macro.")
SET(SAVE_TNT_DATA OFF CACHE BOOL "Define SAVE_TNT_DATA macro.")
SET(FACET_FLOOR OFF CACHE BOOL "Define _FACET_FLOOR_ macro.")

SET(ESCAPE_EXIT OFF CACHE BOOL "Define ESCAPE_EXIT macro.")

SET(SAVE_EXPLOSION OFF CACHE BOOL "Define SAVE_EXPLOSION macro.")

SET(GLOBAL_TIMER OFF CACHE BOOL "Define GLOBAL_TIMER macro.")



# Defined by default
SET(ROAD OFF CACHE BOOL "Define _ROAD_ macro. Defined by default.")
SET(COMPACT_3D OFF CACHE BOOL "Define COMPACT_3D macro.")

SET(LOWLEVEL_OUTPUT OFF CACHE BOOL "Define LOWLEVEL_OUTPUT macro. Defined by default.")

SET(ML_COMPRESS_ON OFF CACHE BOOL "Define ML_COMPRESS_ON macro. Defined by default.")

SET(ACI_PACK_SAVES OFF CACHE BOOL "Define _ACI_PACK_SAVES_ macro. Defined by default.")
SET(ACI_CHECK_DIALOGS OFF CACHE BOOL "Define _ACI_CHECK_DIALOGS_ macro. Defined by default. Does nothing in this build.")
SET(ACI_BML_FONTS OFF CACHE BOOL "Define _ACI_BML_FONTS_ macro. Defined by default.")

SET(ISCREEN OFF CACHE BOOL "Define ISCREEN macro. Defined by default.")
SET(SHOW_IMAGES OFF CACHE BOOL "Define SHOW_IMAGES macro. Defined by default.")
SET(SHOW_LOGOS OFF CACHE BOOL "Define SHOW_LOGOS macro. Defined by default.")

SET(EVENTS_LOG OFF CACHE BOOL "Define EVENTS_LOG macro. Defined by default. Used for multiplayer.")

SET(EXTERNAL_USE OFF CACHE BOOL "Define EXTERNAL_USE macro. Defined by default. Does nothing in this build.")

SET(DYN_ALLOC OFF CACHE BOOL "Define DYN_ALLOC macro. Defined by default.")

SET(GENERATE_EXIT OFF CACHE BOOL "Define _GENERATE_EXIT_ macro.")

SET(STARTUP_TESTING OFF CACHE BOOL "Define STARTUP_TESTING macro.")
SET(SAVE_SINGE_LANGUAGE OFF CACHE BOOL "Define SAVE_SINGE_LANGUAGE macro.")
SET(SINGLE_LANGUAGE OFF CACHE BOOL "Define SINGLE_LANGUAGE macro.")

SET(NEW_TNT OFF CACHE BOOL "Define NEW_TNT macro.")
SET(LOCATION_ENGINE_MESSAGE OFF CACHE BOOL "Define LOCATION_ENGINE_MESSAGE macro.")

SET(ACTINT ON CACHE BOOL "Define ACTINT macro.")

SET(SIMPLE_PARTICLE_ON ON CACHE BOOL "Define SIMPLE_PARTICLE_ON macro.")
SET(PARTICLE_ON ON CACHE BOOL "Define PARTICLE_ON macro.")
SET(STACK_EMPTY_IGNORE ON CACHE BOOL "Define STACK_EMPTY_IGNORE macro.")
SET(MOVELAND_ON ON CACHE BOOL "Define MOVELAND_ON macro.")
SET(DEVICE_ON ON CACHE BOOL "Define DEVICE_ON macro.")

SET(DAST OFF CACHE BOOL "Define _DAST_ macro.")

SET(TINY_MODE OFF CACHE BOOL "Define TINY_MODE macro.")





# Unsupported in this build.
SET(SURMAP OFF CACHE BOOL "Define _SURMAP_ macro.")
SET(SESSION OFF CACHE BOOL "Define SESSION macro.")
SET(FILEMAPPING OFF CACHE BOOL "Define FILEMAPPING macro.")
SET(HIGHC OFF CACHE BOOL "Define __HIGHC__ macro.")
SET(LOW_LEVEL_LINE OFF CACHE BOOL "Define LOW_LEVEL_LINE macro.")
SET(TEST OFF CACHE BOOL "Define _TEST_ macro.")
SET(VTEST OFF CACHE BOOL "Define _VTEST_ macro.")
SET(TURN_TEST OFF CACHE BOOL "Define TURN_TEST macro.")
SET(ZORTECHC OFF CACHE BOOL "Define __ZORTECHC__ macro.")
SET(XT_TEST_LIST OFF CACHE BOOL "Define _XT_TEST_LIST_ macro.")
SET(FULLSCREEN_MODE OFF CACHE BOOL "Define _FULLSCREEN_MODE_ macro.")
SET(SAVE_ABILITY OFF CACHE BOOL "Define SAVE_ABILITY macro.")
SET(NetRally OFF CACHE BOOL "Define _NetRally_ macro.")
SET(ZMOD_BETA OFF CACHE BOOL "Define ZMOD_BETA macro.")
SET(ZMOD_DEBUG OFF CACHE BOOL "Define _ZMOD_DEBUG_ macro.")
SET(BMP2SCR_TURN_ENABLE OFF CACHE BOOL "Define BMP2SCR_TURN_ENABLE macro.")
SET(OVERLAP_CHECK OFF CACHE BOOL "Define OVERLAP_CHECK macro.")
SET(ASM_OPTIMIZE OFF CACHE BOOL "Define ASM_OPTIMIZE macro.")
SET(BETA_TESTING OFF CACHE BOOL "Define BETA_TESTING macro.")
SET(CDCHECK OFF CACHE BOOL "Define CDCHECK macro.")
SET(STEAM_API OFF CACHE BOOL "Define _STEAM_API_ macro.")
SET(XMATH_NO_IOSTREAM OFF CACHE BOOL "Define _XMATH_NO_IOSTREAM macro.")
SET(GENERATE_IND_SHAPE OFF CACHE BOOL "Define _GENERATE_IND_SHAPE_ macro.")
SET(NT OFF CACHE BOOL "Define _NT macro.")

cmake_minimum_required(VERSION 3.20)
project(RestoolTool LANGUAGES CXX RC)

# 1. Collect all restool C++ sources and resources
set(RESTOOL_SOURCES
    COMMUNIC.CPP
    DBTBLST.CPP
    DIALED.CPP
    DLGTEMPL.CPP
    DRDROP.CPP
    EDTEMPL.CPP
    FKLST.CPP
    FLDLST.CPP
    FONTCOL.CPP
    FRMED.CPP
    FRMSHOW.CPP
    GENFULL.CPP
    GENGTBL.CPP
    GENITBL.CPP
    GENREP.CPP
    GENRES.CPP
    GENRTBL.CPP
    GENSCR.CPP
    GET_PUT.CPP
    GLOBLST.CPP
    HLINES.CPP
    INTLST.CPP
    JLST.CPP
    KEYLST.CPP
    LDRIWND.CPP
    METAHLP.CPP
    MISC_RES.CPP
    MKDEP.CPP
    PRADMIN.CPP
    RESFONTS.CPP
    RESINI.CPP
    RESTOOL.CPP
    RIWND.CPP
    RLIST.CPP
    RSDEB.CPP
    SHOWRES.CPP
    SRVED.CPP
    TBLST.CPP
    TOOLHWND.CPP
    TXEDIT.CPP
    WNDINMDI.CPP
    WONSCRIP.CPP
    ../ctool/MYLINE.CPP
    RESTOOL.RC
)

# 2. Build restool as a GUI executable (legacy /SUBSYSTEM:WINDOWS)
add_executable(restool WIN32 ${RESTOOL_SOURCES})

# 3. Expose local headers
target_include_directories(restool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# COMMUNIC.CPP uses MapView code paths guarded by SHAREMEM.
target_compile_definitions(restool PRIVATE SHAREMEM)

# 4. Match historical restool dependency set against the modern targets
target_link_libraries(restool PRIVATE
    user32
    gdi32
    comdlg32
    comctl32
    ddsmem
    dmwapi
    compile
    dbhelp
    ctool
    frmobj
    toolbar
    statbar
    dbclean
)

# Legacy build used non-incremental link for this tool.
if(MSVC)
  target_link_options(restool PRIVATE /INCREMENTAL:NO)
endif()

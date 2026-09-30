#define MAXTESTTYPES  16

#define ANZREFORMAT       0
#define ANZGESREFORMAT    1
#define ANZMAPCHANGE      2
#define ANZGESMAPCHANGE   3
#define ANZGETDATA        4
#define ANZUPDATE         5
#define ANZFINDOBHJ       6
#define ANZFINDID         7
#define ANZGETDOCCONTEXT  8
#define ANZCHANGEOBJ      9
#define ANZREMOVEOBJ      10

extern void IncTestCount (mdiChild *c,int type);

/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono Nerd Font:medium:size=12",
                                        "monospace:size=12"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#502A4F";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
enum { SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6 }; /* color schemes */
/* dwmblocks end */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "﯂"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "REAPER",   NULL,       NULL,       0,            1,           -1 },
	{ "Gpick",    NULL,       NULL,       0,            1,           -1 },
	{ "RuneLite", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "[@]",      spiral },
	
    { "TTT",      bstack },
	{ "|M|",      centeredmaster },
	
    { "HHH",      grid },
	{ "[\\]",     dwindle },

    { "[M]",      monocle },
	{ "H[]",      deck },
	
    { "===",      bstackhoriz },
	{ "###",      nrowgrid },
	
    { "---",      horizgrid },
	{ ":::",      gaplessgrid },
	
    { ">M>",      centeredfloatingmaster },
    { "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,     quit,           {0} },
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("slock")},
	{ MODKEY,                       XK_F12,    spawn,          SHCMD("sysact")},
	
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY,                       XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY,                       XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY,                       XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY,                       XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_0,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_0,      defaultgaps,    {0} },

    { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
    { MODKEY,                       XK_w,      spawn,          SHCMD("firefox")},
    { MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e lf")},
    { MODKEY,                       XK_r,      spawn,          {0} },
    { MODKEY|ShiftMask,             XK_r,      spawn,          {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[3]} }, 
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_p,      setlayout,      {.v = &layouts[5]} },

    { MODKEY,                       XK_a,      defaultgaps,    {0} },
    { MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,      movestack,      {.i = -1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = 0.05} },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|Mod1Mask,              XK_Return, zoom,           {0} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    { 0,                            XK_Print,  spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png")},
	{ MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("maim /home/michael/Pictures/screenshots/Screenshot-$(date '+%y%m%d-%H%M-%S').png")},
    
    { 0, XF86XK_AudioPlay,          spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause")  },      
    { 0, XF86XK_AudioMute,          spawn,     SHCMD("pamixer -t")  },      
    { 0, XF86XK_AudioNext,          spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next")  },      
    { 0, XF86XK_AudioPrev,          spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous")  },      
    
    /* vanitygaps
    { MODKEY,                       XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrgaps,       {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, 
	{ MODKEY,                       XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
    */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


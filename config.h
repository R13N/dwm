/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Mono:size=13", "Symbola:size=13" };
static const char dmenufont[]       = "Fira Mono:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_accent1[]     = "#004433";
static const char col_accent2[]     = "#009900";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_accent1,  col_accent2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
    /* class            instance    title       tags mask     isfloating   monitor */
    { "idea",           NULL,       "LG3D",     0,            0,           -1 },
    { "clion",          NULL,       "LG3D",     0,            0,           -1 },
    { "idea-ultimate",  NULL,       "LG3D",     0,            0,           -1 },
    { "ghidra",         NULL,       "LG3D",     0,            0,           -1 },
    { "bluej",          NULL,       "LG3D",     0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // super
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent1, "-sf", col_gray4, NULL };
static const char *passcmd[] = { "passmenu", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *browsercmd[]        = { "firefox", NULL };

static const char *sound_toggle[]       = { "sound_control.sh", "toggle", NULL };
static const char *sound_up[]           = { "sound_control.sh", "up",     NULL };
static const char *sound_down[]         = { "sound_control.sh", "down",   NULL };

static const char *lockcmd[]            = { "lockscreen",   NULL };
static const char *suspendcmd[]         = { "siesta",       NULL };
static const char *hibernatecmd[]       = { "siesta",       "-Z",   NULL };

static const char *shot_upload[]          = { "shot", "-s", NULL };
static const char *shot_show[]        = { "shotshow", "-s", NULL };

static const char *brightness_up[]      = { "xbacklight", "-inc", "10", NULL };
static const char *brightness_down[]    = { "xbacklight", "-dec", "10", NULL };

static Key keys[] = {
    // XF86XK 'special' keys
    { 0, 0x1008ff11, sspawn,     { .v = sound_down      } }, /* XF86XK_AudioLowerVolume */
    { 0, 0x1008ff12, sspawn,     { .v = sound_toggle    } }, /* XF86XK_AudioMute */
    { 0, 0x1008ff13, sspawn,     { .v = sound_up        } }, /* XF86XK_AudioRaiseVolume */
    //{ 0, 0x1008ff17, mpdchange,  { .i = +1              } }, /* XF86XK_AudioNext */
    //{ 0, 0x1008ff16, mpdchange,  { .i = -1              } }, /* XF86XK_AudioPrev */
    //{ 0, 0x1008ff14, mpdcontrol, { 0                    } }, /* XF86XK_AudioPlay */
    { 0, 0x1008ff02, sspawn,     { .v = brightness_up   } }, /* XF86XK_MonBrightnessUp */
    { 0, 0x1008ff03, sspawn,     { .v = brightness_down } }, /* XF86XK_MonBrightnessDown */

    { MODKEY,           XK_Right,  view_rotate, { .r = RotateRight } },
    { MODKEY,           XK_Left,   view_rotate, { .r = RotateLeft  } },
    { MODKEY|ShiftMask, XK_Right,  tag_rotate,  { .r = RotateRight } },
    { MODKEY|ShiftMask, XK_Left,   tag_rotate,  { .r = RotateLeft  } },


    /* modifier         key        function        argument */
    { MODKEY,           XK_p,      sspawn,         { .v  = dmenucmd     } },
    { MODKEY|ShiftMask, XK_p,      sspawn,         { .v  = passcmd     } },
    { MODKEY,           XK_Return, spawn,          { .v  = termcmd      } },
    { MODKEY,           XK_g,      sspawn,         { .v  = browsercmd  } },
    { MODKEY,           XK_s,      sspawn,         { .v  = shot_show  } },
    { MODKEY|ShiftMask, XK_s,      sspawn,         { .v  = shot_upload    } },
    { MODKEY,           XK_z,      sspawn,         { .v  = hibernatecmd } },
    { MODKEY|ShiftMask, XK_z,      sspawn,         { .v  = suspendcmd   } },
    { MODKEY|ShiftMask, XK_l,      sspawn,         { .v  = lockcmd      } },
    { MODKEY,           XK_b,      togglebar,      { 0                  } },
    { MODKEY,           XK_j,      focusstack,     { .i  = +1           } },
    { MODKEY,           XK_k,      focusstack,     { .i  = -1           } },
    { MODKEY,           XK_i,      incnmaster,     { .i  = +1           } },
    { MODKEY,           XK_d,      incnmaster,     { .i  = -1           } },
    { MODKEY,           XK_h,      setmfact,       { .f  = -0.05        } },
    { MODKEY,           XK_l,      setmfact,       { .f  = +0.05        } },
    { MODKEY|ShiftMask, XK_Return, zoom,           { 0                  } },
    { MODKEY,           XK_Tab,    view,           { 0                  } },
    { MODKEY|ShiftMask, XK_c,      killclient,     { 0                  } },
    { MODKEY,           XK_t,      setlayout,      { .v  = &layouts[0]  } },
    { MODKEY,           XK_f,      setlayout,      { .v  = &layouts[1]  } },
    { MODKEY,           XK_m,      setlayout,      { .v  = &layouts[2]  } },
    { MODKEY,           XK_space,  setlayout,      { 0                  } },
    { MODKEY|ShiftMask, XK_space,  togglefloating, { 0                  } },
    { MODKEY,           XK_comma,  focusmon,       { .i  = -1           } },
    { MODKEY,           XK_period, focusmon,       { .i  = +1           } },
    { MODKEY|ShiftMask, XK_comma,  tagmon,         { .i  = -1           } },
    { MODKEY|ShiftMask, XK_period, tagmon,         { .i  = +1           } },
    { MODKEY|ShiftMask, XK_q,      quit,           { 0                  } },

    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2 ,1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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


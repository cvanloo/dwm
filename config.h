/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Atkinson Hyperlegible:size=10" };
static const char dmenufont[]       = "Atkinson Hyperlegible:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char dark[]        = "#c17a3f";
static const char dark[]        = "#191919";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, dark },
	[SchemeSel]  = { col_gray4, dark,  col_gray2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Nemo",     NULL,       NULL,       0,            1,           -1 },
    { "copyq",    NULL,       NULL,       0,            1,           -1 },
	//{ "firefox",  NULL,       NULL,       1 << 0,       0,           -1 },
};

/* layout(s) */
//static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask // 1 -> alt, 4 -> super
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", dark, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
//static const char *i3lock[]   = { "i3lock", "-i", "/home/kitty/Pictures/open-sourcerer-3440×1440.png", "-e", "-f", NULL };
static const char *i3lock[]   = { "i3lock", "-c", "000000", "-e", "-f", NULL };
/*static const char *lydv[]    = { "setxkbmap", "dvorak", NULL };
static const char *lydvp[]   = { "setxkbmap", "-layout", "us", "-variant", "dvp", NULL };*/
static const char *keyboard_switcher[] = { "__keyboard-switcher" };
//static const char *key_toggle[] = { "_keys", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_Escape, spawn,          {.v = i3lock } },
    { MODKEY,                       XK_o,      spawn,          {.v = keyboard_switcher } },
    /*{ MODKEY,                       XK_e,      spawn,          {.v = lydvp } },*/
    /*{ MODKEY,                       XK_e,      spawn,          {.v = key_toggle } },*/
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_asterisk, view,         {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_asterisk, tag,          {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
	//TAGKEYS(                        XK_1,                      0)
	//TAGKEYS(                        XK_2,                      1)
	//TAGKEYS(                        XK_3,                      2)
	//TAGKEYS(                        XK_4,                      3)
	//TAGKEYS(                        XK_5,                      4)
	//TAGKEYS(                        XK_6,                      5)
	//TAGKEYS(                        XK_7,                      6)
	//TAGKEYS(                        XK_8,                      7)
	//TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                       XK_parenleft,    0) /* 1( */
	TAGKEYS(                       XK_parenright,   1) /* 2) */
	TAGKEYS(                       XK_braceright,   2) /* 3} */
	TAGKEYS(                       XK_plus,         3) /* 4+ */
	TAGKEYS(                       XK_braceleft,    4) /* 5{ */
	TAGKEYS(                       XK_bracketright, 5) /* 6] */
	TAGKEYS(                       XK_bracketleft,  6) /* 7[ */
	TAGKEYS(                       XK_exclam,       7) /* 8! */
	TAGKEYS(                       XK_equal,        8) /* 9= */
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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


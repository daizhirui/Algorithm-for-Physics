/*
	This file is writen by Shen Junjie <email:sjjzd@163.com>
	Please reserve this CopyLeft.
*/

#define ORIGINAL 	1
#define COMPLEMENT	2
#define ORIGINAL_COMPLEMENT	3

#define	PORTRAIT	1
#define HISTOGRAM 	2
#define COMPRESULT	3

#define GUANINE		0
#define CYTOSINE	1
#define ADENINE		2
#define THYMINE		3

#define FASTA 		1
#define GenBank 	2
#define UNKNOWN 	3

#define HighContrast 0
#define AutoBalanced 1

#define ERROR 		1
#define WARNING		2

#define COLOR_SIZE 64
#define DIMENSION  8

typedef struct _Sequence {
	char	*	data[100];				//	restore the data of sequence
	guint8 		datalist;				//	the number of data pointer
	
	gchar 		filepath[200];			//	sequence file's path
	gchar    	locus[20];				//  the locus of a sequence
	gchar		description[200];		//  the brief descripton of a sequence
	gchar		format[20];				//	the format of a file type
	gchar		source[50];				//	the source of this genome
	
	guint32		amount_basepairs;		//  the amount of nucleotide base pairs
	guint32		amount_adenine;			//  the amount of adenine
	guint32		amount_cytosine;		//	the amount of cytosine
	guint32		amount_guanine;			//	the amount of guanine
	guint32		amount_thymine;			// 	the amount of thymine
	guint32		data_startpoint;		//	the startpoint of nucleotide data in sequence file
	
	struct 	Sequence	*last;				//  the last node of Sequence
	struct 	Sequence	*next;				//	the next node of Sequence
} Sequence;

typedef struct _Settings{
	gdouble		ratio_millions;			//  the amount of nucleotide base pairs
	gdouble		histogram_interface;	//	the interface in histogram
	gdouble		histogram_ratio;		//	the ratio in histogram
	int		*	histogram_array;		//	the array in histogram
	int			histogram_bin_length;	//	bin length
	guint8	 	k_tuples;				// 	k tuples from 1 to 9
	guint16		windows_size;			// 	from 1 to 256
	guint16		map_length;				// 	map length from 2 to 512
	guint32		map_square;				// 	map square from 2*2 to 512*512
	guint8		reading_mode;			// 	original=1 complement=2 original_complement=3	
	gboolean	randomization;			// 	FALSE if None or TRUE if Applicated
	guint8		rand_times;				// 	rand times from 1 to 80
	guint8		color_mode;				// 	high contrast in small number 0 or auto-balanced 1
	gboolean	comparation_reduction;  // 	FALSE if None or TRUE if Used
	guint8		comparation_DAN;		// 	difference area number from 4 to 32
	guint8		exp_table[11];			// 	{1,2,4,8,16,32,64,128,256,512,1024};
	guint8		color[64][3];			// 	drawing colormode value array
	guint8		drawing_mode;			// 	portrait 1 or histogram 0
} Settings;

typedef struct _Portrait{
	guint16		marker;					//	the marker of a Portrait
	gchar 		ID[100];				//	the ID of a portrait
	gchar		Description[100];		//	the Description of a portrait
	gchar		Detail[1000];			//	the detail of the sequence and the portrait
	gchar		filename[100];			//	the filename of the portrait
	guint8		portrait_type;			//	2D Portrait 1 or 1D Histogram 2 or Compresult 3
	int		*	portrait_data;			//	the data pointer of a portrait
	char	*	portrait_draw;			//	the draw pointer of a portrait	
	char	*	portrait_colorlist;		//	the colorlist pointer of a portrait
	int			area_mark[17];			//	color area mark
	
	Settings   *portrait_settings;		//	the settings of a portrait
	
	struct		Portrait *last;			//  the last node of struct Portrait
	struct  	Portrait *next;			//  the next node of struct Portrait	
} Portrait;

typedef struct _MousePress{
	GtkWidget 	*textview;
	Portrait	*portrait;
	gboolean	MousePressed;
	int			MousePosition[3];
} MousePress;

typedef struct _Console{
	GtkWidget 	*console;
	GtkCList 	*clist;
	GtkWidget	*textview;
	Portrait	*portrait;
} Console;

typedef struct _ConsoleColormode{
	GtkWidget 	*advancedsettings;
	GtkWidget 	*drawing_colormode;
	char		*colorlist;
} ConsoleColormode;

typedef struct _Node
{
	int value[COLOR_SIZE];
	struct Node *next[COLOR_SIZE];	
}	Node;


GtkWidget* create_console (void);
GtkWidget* create_portrait (Portrait *current_portrait);
GtkWidget* create_histogram (Portrait *current_histogram);
GtkWidget* create_compresult (Portrait *output);
GtkWidget* create_advancedsettings (ConsoleColormode *color_mode);
GtkWidget* create_comparation (Portrait *HEAD,Portrait *current_portrait);
GtkWidget* create_about (void);
GtkWidget* create_error (int error_type,char *message);

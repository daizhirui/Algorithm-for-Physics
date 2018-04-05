#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

////////// 	GLOBAL VARIANTS AREA 	//////////////////////////////////
Sequence 	*HEAD 		=	NULL;
Sequence 	*CURRENT	=	NULL;

Portrait	*HEAD_PORTRAIT		=	NULL;
Portrait    *COMPARATION_DESTINATION = NULL;

guint32		PORTRAIT_MARKER = 1;

GtkCList 	*currentlist;
guint16		currentrow = -1;

guint8	 	k_tuples	=	9;				
guint16		windows_size=	1;			
guint16		map_length	=	512;				
guint32		map_square	=	512*512;			
guint8		reading_mode=	ORIGINAL;		
gboolean	randomization=	FALSE;		
guint8		rand_times	=	1;			
guint8		color_mode	=	HighContrast;			
gboolean	comparation_reduction	=	TRUE;  
guint8		comparation_DAN	=	4;		
guint16		exp_table[11]	=	{1,2,4,8,16,32,64,128,256,512,1024};
gfloat		color_auto[16][3]=	{1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,0.1 ,0.8 ,1.0 ,0.1 ,1.0 ,0.84,1.0 ,
								 0.1 ,1.0 ,0.1 ,0.1 ,0.7 ,1.0 ,0.1 ,0.1 ,1.0,0.65,0.1 ,0.77,
								 0.77,0.07,0.34,0.54,0.47,0.03,0.11,0.54,0.0,0.0 ,0.49,0.54,
							     0.01,0.01,0.59,0.54,0.0 ,0.45,0.3 ,0.3 ,0.3,0.0 ,0.0 ,0.0 };
gfloat		color_high[16][3]=	{0.941,0.973,1.0,1.0,0.0,0.0,1.0,0.647,0.0,1.0 ,1.0,0.0,
								 0.0,1.0,0.0,0.604,0.804,0.196,0.0,1.0,1.0,0.529,0.808,0.922,
							 0.412,0.545,0.412,0.545,0.545,0.0,0.627,0.125,0.941,0.545,0.388,0.424,
							     0.0,0.0,1.0,0.0,0.0,0.545,0.545,0.0,0.0,0.0 ,0.0 ,0.0 };
guint8		drawing_mode	=	1;	
///////////		TEMP VALUES IN ADVANCED SETTINGS    ////////////////////////
guint8		temp_rand_times	=	1;			
guint8		temp_color_mode	=	HighContrast;			
gboolean	temp_comparation_reduction	=	FALSE; 
guint8		temp_comparation_DAN	=	4;	

char 	current_datafile_path[500];
char	current_exportfile_path[500];
int format_analysis(Sequence *new,int input)
{
	char 	   *block;
	int			MALLOC_SIZE	= 1024*1024,nread,n,m,format;	
	static	int	SEQUENCE_MARKER = 1;
	char		locus[100];
	block 		= (char*)malloc(MALLOC_SIZE*sizeof(char));
	
	if ((nread = read(input,block,MALLOC_SIZE*sizeof(char)))<= 0){
		GtkWidget *Error = create_error(ERROR,"Reading File Block Failed");
	  	gtk_widget_show(Error);
		return -3;
	}
///////////         analyse fasta format         /////////////////////////////
	if(block[0] == '>' ){
		format = FASTA;
		strcpy(new->format,"FASTA");
		n = 0;
		for(m=0;m<100;m++){if (block[n++] == '|') break;}
		for(m=0;m<200;m++){
			locus[m] = block[n++];
			if(locus[m] == '|' || !isdigit(locus[m])){
				locus[m] = '\0';
				break;
			}
		}
		sprintf(new->locus,"%s_F%d",locus,SEQUENCE_MARKER++);	
		for(m=0;m<200;m++){
			if(block[n] == 'r' && block[n+1] == 'e' && block[n+2] == 'f')
			{
				for(;;)	if(block[n++] == '|') break;
				for(;;)	if(block[n++] == '|') break;
				for(;;n++) if(block[n] != ' ') break;
			} 
		
			new->description[m] = block[n++];
			if(isalnum(new->description[m]) == NULL 
				&& new->description[m]!=',' && new->description[m]!='.' && new->description[m]!='\n')
				new->description[m] = ' ';
		
			if(new->description[m] == '\n'){
				new->description[m] = '\0';
				break;
			}
		}
		sprintf(new->source,"not_specific");
		for(;n<1000;n++){
			if(	block[n] == 'A' || block[n] == 'C' || block[n] == 'G' || block[n] == 'T' ||
				block[n] == 'a' || block[n] == 'c' || block[n] == 'g' || block[n] == 't'){
				new->data_startpoint = n;
				break;
			}
		}
	}	
////////////        analyse genbank foramt       ////////////////////////////
	else if(block[0]=='L' && block[1]=='O' && block[2]=='C'&& block[3]=='U' && block[4]=='S'){
	 	format = GenBank;
		strcpy(new->format,"GenBank");
		for(n=5;n<100;n++){if(block[n] != ' ') break;}
		for(m=0;m<20;m++){
			locus[m] = block[n++];
			if(locus[m] == ' '){
				locus[m] = '\0';
				break;
			}
		}
		sprintf(new->locus,"%s_F%d",locus,SEQUENCE_MARKER++);	
		
		for(;n<200;n++){
			if(block[n] == 'D' && block[n+1] == 'E' && block[n+2] == 'F'){
				n = n + 10;
				break; 
			}
		}
		for(;n<250;n++){if(block[n] != ' ') break;}
	 	for(m=0;m<200;m++){
			new->description[m] = block[n++];

			if(block[n] == 'A' && block[n+1] == 'C' && block[n+2] == 'C' && block[n+3] == 'E'   ){
				new->description[m] = '\0';
				break;
			}
			if(isalnum(new->description[m]) == NULL && new->description[m]!=',' && new->description[m]!='.')
				new->description[m] = ' ';
		}
////////////  appended in 2004.4.19 to recode information of genome source //////////////////
		for(;n<5000;n++){
			if(		block[n] == 'S' && block[n+1] == 'O' && block[n+2] == 'U' 
					   && block[n+3] == 'R' && block[n+4] == 'C' && block[n+5] == 'E') 
			{
				n = n+5;
				for(;;){if(block[++n] != ' ') break;}
				for(m=0;m<40;m++){
					new->source[m] = block[n++];
					if(isalnum(new->source[m]) == NULL)				
						new->source[m] = '_';
					if(block[n] == '.' || (block[n+1] == 'O' && block[n+2] == 'R' 
						&& block[n+3] == 'G')) 
						break;
				}
				new->source[m+1]= '\0';
				break;
			}
		}
////////////   by author Shen Junjie ///////////////////////////////////////////////////////////
		new->data_startpoint = 0;
		for(;n<MALLOC_SIZE-5;n++){
			if(block[n] == 'O' && block[n+1] == 'R' && block[n+2] == 'I' 
				&& block[n+3] == 'G' && block[n+4] == 'I' && block[n+5] == 'N'){
				new->data_startpoint = n+6;
				break;
			}
		}
		if(new->data_startpoint == 0){
			for(m=1;m<100;m++){
				lseek(input,(off_t)(m*(MALLOC_SIZE*sizeof(char) - 5)),SEEK_SET);	
				if ((nread = read(input,block,MALLOC_SIZE*sizeof(char)))<= 0){
					return -1;
				}
				for(n = 0;n<MALLOC_SIZE-5;n++){
					if(block[n] == 'O' && block[n+1] == 'R' && block[n+2] == 'I'
						&& block[n+3] == 'G' && block[n+4] == 'I' && block[n+5] == 'N'){
						new->data_startpoint = n+6 + m*(MALLOC_SIZE*sizeof(char)-5);
						break;
					}
				}
				if(new->data_startpoint != 0)
					break;
			}	
		}
	}		
	else{
		format = UNKNOWN;
	}
	free(block);
	return format;
}	

Sequence* data_process(char *file)
{
	int 		n,input,format,nread,buffer_point=0,bps=0,a=0,c=0,g=0,t=0,MALLOC_SIZE=1024*1024;
	char    	block[1024];
	int			exp_table1[4] = {63,207,243,252};
	int			exp_table2[4] = {64,16,4,1};
	Sequence 	*new;
	
	if((input = open(file,O_RDONLY))<0){
		return -2;
	}
	new = malloc(sizeof(Sequence));
	new->last = new->next = NULL;
	for(n = 0;n<200;n++){
		new->filepath[n] = file[n];
		if(new->filepath[n] == '\0')
			break;
	}
	
//// format analysis is an important process before reading data ////
	format = format_analysis(new,input);
/////////////////////////////////////////////////////////////////////

	if(format == -3)
		return format;
		
	if(format == UNKNOWN){
		return NULL;
	}
	new->datalist = 0;
////////////  reading sequence data   ////////////////////////////////////	
	lseek(input,(off_t)(new->data_startpoint),SEEK_SET);	
	new->data[new->datalist] = (char*)malloc(MALLOC_SIZE*sizeof(char));
	while((nread = read(input,block,sizeof(block))) > 0 ){
		for(n = 0;n<nread;n++){
			switch (block[n]){
				case 'g':
				case 'G':	new->data[new->datalist][buffer_point/4]&exp_table1[buffer_point%4];
					new->data[new->datalist][buffer_point/4]= new->data[new->datalist][buffer_point/4]+(GUANINE*exp_table2[buffer_point%4]);
							buffer_point++;
							g++;
							break;
				case 'c':	
				case 'C':	new->data[new->datalist][buffer_point/4]&exp_table1[buffer_point%4];
					new->data[new->datalist][buffer_point/4]= new->data[new->datalist][buffer_point/4]+(CYTOSINE*exp_table2[buffer_point%4]);
							buffer_point++;
							c++;
							break;
				case 'a':	
				case 'A':	new->data[new->datalist][buffer_point/4]&exp_table1[buffer_point%4];
							new->data[new->datalist][buffer_point/4] = new->data[new->datalist][buffer_point/4]+(ADENINE*exp_table2[buffer_point%4]);
							buffer_point++;
							a++;
							break;
				case 't':	
				case 'T':	new->data[new->datalist][buffer_point/4]&exp_table1[buffer_point%4];
					new->data[new->datalist][buffer_point/4]= new->data[new->datalist][buffer_point/4]+(THYMINE*exp_table2[buffer_point%4]);
							buffer_point++;
							t++;
							break;
				case '>':	if(format == FASTA){
								close(input);
								return NULL;
							}
				default:	break;
			}
			if(buffer_point >= MALLOC_SIZE*4){
				buffer_point = 0;
				new->datalist++;
				new->data[new->datalist] = (char*)malloc(MALLOC_SIZE*sizeof(char));
			}		
		}
	}
	new->amount_basepairs 	= 	bps = a+c+g+t;				
	new->amount_adenine		=	a;
	new->amount_cytosine	=	c;
	new->amount_guanine		=	g;
	new->amount_thymine		=	t;
	

	close(input);
	return new;
}

char*	Randomization(char **data,guint32 amount_basepairs,guint8 rand_times,guint32 MALLOC_SIZE)
{
	char*		randbuffer = NULL;
	guint8		exp_table[4] = {6,4,2,0};
	guint32 	n,m,column,row,temp;
	guint32		rand_position;
	guint8		rand_loop;
	guint32		rand_length;
	double 		amplification;
		
	randbuffer	= (char*)malloc(amount_basepairs*sizeof(char));	
	if (randbuffer == NULL){
		Memory_Error();
		return randbuffer;
	}
	for(m = 0;m< amount_basepairs;m++){
		row 	= 	m/(MALLOC_SIZE*4);
		column	=	m%(MALLOC_SIZE*4);
		temp	=((unsigned int)data[row][column/4]>>exp_table[column%4])%4;
		randbuffer[m] = temp;			
	}
	srand((int) time(0));
	for(rand_loop = 0;rand_loop < rand_times;rand_loop++){
		for(amplification=amount_basepairs-1;amplification>0;amplification--){
			rand_position =	(int)(amplification*rand()/(RAND_MAX+1.0));
			temp = randbuffer[rand_position];
			randbuffer[rand_position] = randbuffer[(int)amplification];
			randbuffer[(int)amplification] = temp;	
		}
	}
	return randbuffer;
}

////	sort function by author Shen Junjie 2004.10.4	////
int compar(const void *a,const void *b)
{
	int *aa=(int *)a,*bb=(int *)b;
	if	(*aa	>	*bb)	return 1;
	if	(*aa 	== 	*bb)	return 0;
	if	(*aa	<	*bb)	return -1;
}
/////////////////////////////////////////////////////////////

char** drawing(Sequence *drawing_sequence,Portrait *drawing_portrait)
{ 
	Settings 	*current	=	drawing_portrait->portrait_settings;
	int		 	*map_data	=	drawing_portrait->portrait_data;
	char	 	*map_draw	=	drawing_portrait->portrait_draw;
	char	 	*colorlist	=	drawing_portrait->portrait_colorlist;
	guint8		type		=	drawing_portrait->portrait_type;			
	guint32		MALLOC_SIZE	= 	1024*1024;	
	guint16		BUFFER_SIZE = 	1024;
	guint16		EXPTABLE[11]=	{1,2,4,8,16,32,64,128,256,512,1024};
	gint32  	areamark[17]=	{-1,0,2,3,4,5,6,8,10,12,14,17,20,24,30,55};
	gint32	 	n,m,column,row,original_complement=0,x,y,cx,cy;
	gint32		addrx,addry;
	gint64		addr;
	gint32		temp;
	char		*randbuffer = NULL;
	guint8		exp_table[4] = {6,4,2,0};
	areamark[16] = drawing_sequence->amount_basepairs;	
	guint32		map_maxvalue=0;
	double  	normalize;
	
	normalize = (double)1000000/((double)(drawing_sequence->amount_basepairs));
	
	if (current->randomization != FALSE){
		randbuffer =	Randomization(	drawing_sequence->data,
										drawing_sequence->amount_basepairs,
										drawing_portrait->portrait_settings->rand_times,
										MALLOC_SIZE);
		if(randbuffer == NULL)
			exit(0);
			
	}
	
	switch(current->reading_mode){
		case	ORIGINAL_COMPLEMENT:
			original_complement = 1;
		case	ORIGINAL:
			addrx=0;
			addry=0;
			for (n = 0;n<current->k_tuples;n++){
				row 	= 	(n)/(MALLOC_SIZE*4);
				column	=	(n)%(MALLOC_SIZE*4);
				if(current->randomization != FALSE)
					temp = randbuffer[n];
				else
					temp = ((unsigned int)drawing_sequence->data[row][column/4]>>exp_table[column%4])%4;
				addrx = addrx*2 + (temp%2);
				addry = addry*2 + (temp>>1);
			}
			addr = addry*current->map_length+addrx;
			map_data[addr]++;
			
//// modified by Shen Junjie 2004.10.16 to solve the problem of showing wrong number while K=1 ////
			
			for(m = current->k_tuples;m < drawing_sequence->amount_basepairs;m++){
				row 	= 	(m)/(MALLOC_SIZE*4);
				column	=	(m)%(MALLOC_SIZE*4);
				if(current->randomization != FALSE)
					temp = randbuffer[m];
				else
					temp = ((unsigned int)drawing_sequence->data[row][column/4]>>exp_table[column%4])%4;
				addrx 	= 	(addrx*2+(temp%2))%current->map_length;
				addry	=	(addry*2+(temp>>1))%current->map_length;
				addr = addry*current->map_length+addrx;
				map_data[addr]++;
			}
////////////////////////////////////////////////////////////////////////////////////////////////
			if(original_complement == 0)
				break;
		case	COMPLEMENT:
			addrx=0;
			addry=0;
			for (n = current->k_tuples-1;n>=0;n--){
				row 	= 	(n)/(MALLOC_SIZE*4);
				column	=	(n)%(MALLOC_SIZE*4);
				if(current->randomization != FALSE)
					temp = randbuffer[n];
				else
					temp = ((unsigned int)drawing_sequence->data[row][column/4]>>exp_table[column%4])%4;
				switch(temp){
					case GUANINE:temp = CYTOSINE;break;
					case CYTOSINE:temp = GUANINE;break;
					case ADENINE:temp = THYMINE;break;
					case THYMINE:temp = ADENINE;break;
					default:break;
				}
				addrx = addrx*2 + (temp%2);
				addry = addry*2 + (temp>>1);
			}
			addr = addry*current->map_length+addrx;
			map_data[addr]++;
			for(m = current->k_tuples;m< drawing_sequence->amount_basepairs;m++){
				row 	= 	(m)/(MALLOC_SIZE*4);
				column	=	(m)%(MALLOC_SIZE*4);
				if(current->randomization != FALSE)
					temp = randbuffer[m];
				else
					temp = ((unsigned int)drawing_sequence->data[row][column/4]>>exp_table[column%4])%4;
				switch(temp){
					case GUANINE:temp = CYTOSINE;break;
					case CYTOSINE:temp = GUANINE;break;
					case ADENINE:temp = THYMINE;break;
					case THYMINE:temp = ADENINE;break;
					default:break;
				}
				addrx 	= 	(addrx+(temp%2)*current->map_length)>>1;
				addry	=	(addry+(temp>>1)*current->map_length)>>1;
				addr = addry*current->map_length+addrx;
				map_data[addr]++;
			}
			break;
				
		default:break;
	}

	if(current->color_mode == AutoBalanced){
		int 	n,map_maxvalue=0;
		int		*division_area=NULL;
		double 	even_value = current->map_square/16;
		int		temp_sum = 0;
		int		temp_area_number = 1;
		int		area_number = 16;
		for(n = 0;n < current->map_square;n++){
			if (map_maxvalue < map_data[n])
				map_maxvalue = map_data[n];
		}
		division_area = (int*)malloc((map_maxvalue+2)*sizeof(int));
		for(n = 0;n <= map_maxvalue;n++)
			division_area[n] = 0;
		for(n = 0;n < current->map_square;n++)
			division_area[map_data[n]]++;
		for(n = 0;n < map_maxvalue;n++){
			temp_sum = temp_sum+division_area[n];
			if(temp_sum >= temp_area_number*even_value)
			{
				areamark[temp_area_number++] = n+1;
			}
			if(temp_area_number > 15)
				break;

		}	
	}
			
			
	for(n=0;n<17;n++)
		drawing_portrait->area_mark[n] = (int)((double)areamark[n]/normalize);	

	
/////////////////  drawing Portrait    ////////////////////////////////////////////	
	int 	min=100000,max=0;
	int		interval;
	int		remainder;
	int		center_begin;
	
	double	temp2 = 0.0;
	int 	colornumber=0;
	int		top=0;
	int 	MAX_BIN_NUMBER;	
	int		BIN_WIDTH;
	int		*BIN_AREA_MARK;
	int 	*map_data_temp;

	drawing_portrait->portrait_settings->histogram_array = (int*)g_malloc(512*sizeof(int));
	int *histogram = drawing_portrait->portrait_settings->histogram_array;
	switch(type){
		case PORTRAIT:
////	modified for the purpose of changing the color resolution when k = 1,2,3,4,5,6 ////		
		switch(drawing_portrait->portrait_settings->k_tuples){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				map_data_temp = (int*)malloc(current->map_square*sizeof(int));
				for(n=0;n<current->map_square;n++)
					map_data_temp[n]	=	map_data[n];
				qsort(map_data_temp,current->map_square,sizeof(int),compar);
				drawing_portrait->area_mark[0] = -1; 
				if(current->map_square>=16)
				{
					for(n=1;n<17;n++)
						drawing_portrait->area_mark[n] = 
								map_data_temp[n*current->map_square/16 - 1];	
				}
				else
				{
					for(n=1;n<17;n++)
						drawing_portrait->area_mark[n] = 
								map_data_temp[(n-1)/4]; 
				}
				for (n = 0;n < current->map_square;n++){
					temp2 = map_data[n];
					for(m = 0;m < 16;m++){
						if(	temp2 > drawing_portrait->area_mark[m] && 
							temp2 <= drawing_portrait->area_mark[m+1])
							break;	
					}
					x = (n%current->map_length)*current->windows_size;
					y = (n/current->map_length)*current->windows_size;
					for(cy=0;cy<current->windows_size;cy++){
						for(cx=0;cx<current->windows_size;cx++){
							map_draw[((cy+y)*512+cx+x)*4  ]	= current->color[m][0];
							map_draw[((cy+y)*512+cx+x)*4+1]	= current->color[m][1];
							map_draw[((cy+y)*512+cx+x)*4+2]	= current->color[m][2];
							map_draw[((cy+y)*512+cx+x)*4+3]	= m;
						}
					}
				}	
				for(colornumber=0;colornumber<16;colornumber++){
					for(n=0;n<20;n++){
						for(m=0;m<32;m++){
							colorlist[(n*512+m+colornumber*32)*4  ]=current->color[colornumber][0];
							colorlist[(n*512+m+colornumber*32)*4+1]=current->color[colornumber][1];
							colorlist[(n*512+m+colornumber*32)*4+2]=current->color[colornumber][2];
						}
					}
				}			
				break;

			case 7:
			case 8:
			case 9:
				for (m = 0;m < 16;m++){
					for (n = 0;n < current->map_square;n++){
						temp2 = map_data[n]*normalize;
						if(temp2 > areamark[m] && temp2 <= areamark[m+1]){
							x = (n%current->map_length)*current->windows_size;
							y = (n/current->map_length)*current->windows_size;
							for(cy=0;cy<current->windows_size;cy++){
								for(cx=0;cx<current->windows_size;cx++){
									map_draw[((cy+y)*512+cx+x)*4  ]	= current->color[m][0];
									map_draw[((cy+y)*512+cx+x)*4+1]	= current->color[m][1];
									map_draw[((cy+y)*512+cx+x)*4+2]	= current->color[m][2];
									map_draw[((cy+y)*512+cx+x)*4+3]	= m;
								}
							}
						}
					}
				}	
				for(colornumber=0;colornumber<16;colornumber++){
					for(n=0;n<20;n++){
						for(m=0;m<32;m++){
							colorlist[(n*512+m+colornumber*32)*4  ]=current->color[colornumber][0];
							colorlist[(n*512+m+colornumber*32)*4+1]=current->color[colornumber][1];
							colorlist[(n*512+m+colornumber*32)*4+2]=current->color[colornumber][2];
						}
					}
				}
				break;
			default:
				break;
		}
//// 	by author Shen Junjie 2004.10.4		////	

			break;
	//////////////////  drawing Histogram  ////////////////////////////////////////	
		case HISTOGRAM:
	//////////////////  Algorithm of 1D histogram is introduced by Hao Bailin ////////////
			for(n = 0;n<current->map_square;n++){
				if(map_data[n]>max)
					max = map_data[n];
				if(map_data[n]<min)
					min = map_data[n];
			}
			if(drawing_portrait->portrait_settings->k_tuples <=5)
				MAX_BIN_NUMBER = 32;
			else{
				if(drawing_portrait->portrait_settings->k_tuples==6)
					MAX_BIN_NUMBER = 64;
				else{

					temp = max - min;
					if(temp < 32)
						MAX_BIN_NUMBER = 16;
					else{
						if(temp <= 64)
							MAX_BIN_NUMBER = 32;
						else{
							if(temp <= 128)
								MAX_BIN_NUMBER = 64;
							else{
								if(temp <= 256)
								    MAX_BIN_NUMBER = 128;
								else
									MAX_BIN_NUMBER = 256;
							}
						}
					}
				}
			}
			BIN_WIDTH = 512/MAX_BIN_NUMBER;
			
			drawing_portrait->portrait_settings->histogram_bin_length = BIN_WIDTH;
			drawing_portrait->portrait_settings->histogram_array = g_malloc(sizeof(int)*MAX_BIN_NUMBER*3);;
			BIN_AREA_MARK 	= drawing_portrait->portrait_settings->histogram_array;
		
				interval	=	(max-min-1)/(MAX_BIN_NUMBER-2);
				remainder	=	(max-min-1)%(MAX_BIN_NUMBER-2);
    	        center_begin=	MAX_BIN_NUMBER/2-remainder/2;
    			        
				BIN_AREA_MARK[0  ]=min;
    	        BIN_AREA_MARK[0+1]=min;
    	        for(n=0;n<=MAX_BIN_NUMBER;n++)
					BIN_AREA_MARK[n*3+2]=0;        
    	        for(n=1;n< center_begin;n++)
    	        {
    	            BIN_AREA_MARK[n*3	]=BIN_AREA_MARK[(n-1)*3+1]+1;
    	            BIN_AREA_MARK[n*3+1	]=BIN_AREA_MARK[(n-1)*3+1]+interval;
    	        }
    	        for(n=center_begin;n< center_begin+remainder;n++)
    	        {
    	            BIN_AREA_MARK[n*3	]=BIN_AREA_MARK[(n-1)*3+1]+1;
    	            BIN_AREA_MARK[n*3+1	]=BIN_AREA_MARK[(n-1)*3+1]+interval+1;
    	        }
    	        for(n= center_begin+remainder ;n<MAX_BIN_NUMBER-1;n++)
    	        {
    	          	BIN_AREA_MARK[n*3	]=BIN_AREA_MARK[(n-1)*3+1]+1;
    	            BIN_AREA_MARK[n*3+1	]=BIN_AREA_MARK[(n-1)*3+1]+interval;
				}
    	       	BIN_AREA_MARK[(MAX_BIN_NUMBER-1)*3]=max;
    	        BIN_AREA_MARK[(MAX_BIN_NUMBER-1)*3+1]=max;
 		
 			
			for(m=0;m<MAX_BIN_NUMBER;m++){
				for (n = 0;n < current->map_square;n++){
					temp2 = map_data[n];
					if(temp2 >= BIN_AREA_MARK[m*3] && temp2 <= BIN_AREA_MARK[m*3+1]){
						BIN_AREA_MARK[m*3+2]++;
					}
				}		
			}
			
			for(m=0;m<MAX_BIN_NUMBER;m++){
				if(BIN_AREA_MARK[m*3+2] > top)
					top = BIN_AREA_MARK[m*3+2];		
			}
			drawing_portrait->portrait_settings->histogram_ratio = 512/((double)top);
			for(m=0;m<MAX_BIN_NUMBER;m++){		
				x=m*BIN_WIDTH;
				y=0;	
				for(cy=0;cy<512;cy++){
				//// modified to highlight small number not in proportion 2004.3.7 ////
					int temp_here;
					if(BIN_AREA_MARK[m*3+2] == 0)
						temp_here = 511;
					else{
						if((BIN_AREA_MARK[m*3+2]*512)/top < 1.0)
							temp_here = 510;
						else
							temp_here = 511 - (BIN_AREA_MARK[m*3+2]*512)/top;
					}
			  	//// by author Shen Junjie ////		
					if(cy > temp_here){
						for(cx=0;cx<BIN_WIDTH;cx++){
							map_draw[((cy+y)*512+cx+x)*4] 		= current->color[15][0];
							map_draw[((cy+y)*512+cx+x)*4+1] 	= current->color[15][1];
							map_draw[((cy+y)*512+cx+x)*4+2] 	= current->color[15][2];
							map_draw[((cy+y)*512+cx+x)*4+3] 	= 15;
						}
					}
					else{
						for(cx=0;cx<BIN_WIDTH;cx++){
							map_draw[((cy+y)*512+cx+x)*4  ] 	= current->color[0][0];
							map_draw[((cy+y)*512+cx+x)*4+1] 	= current->color[0][1];
							map_draw[((cy+y)*512+cx+x)*4+2] 	= current->color[0][2];
							map_draw[((cy+y)*512+cx+x)*4+3] 	= 0;
						}
					}
				} 	
			}
		}
	
	if(randbuffer != NULL)	
		free(randbuffer);

}

int	comparation_drawing(Portrait *current,Portrait *destination,Portrait *output)
{
	int		m,n;
	int		blue,red;
	char	*map_draw = output->portrait_draw;
	char	*colorlist=	output->portrait_colorlist;
	int		x,y,cx,cy;
	double	ratio = 1.0;
 	double	color_ratio;
 	int		color_range;
 	int		color_number;
 	int		DAN;
 	
//// modified by Shen Junjie 2004.10.16 for the purpose to change comparison color mode ////
	int		color_field[32][3] = {	0  ,  0,150,	0  ,0  ,200,	  0,  0,225,	  0,  0,255,
									100,100,255,	150,150,255,	175,175,255,	200,200,255,
									255,225,255,	255,200,255,	255,150,255,	255,100,255,
									255,  0,150,	255,  0, 50,	200,  0, 50,	150,  0, 50,
									
									150, 50,  0,	200, 50,  0,	255, 50,  0,	255,150,  0,
									255,255,100,	255,255,150,	255,255,200,	255,255,225,
									200,255,200,	175,255,175,	150,255,150,	100,255,100,
									0  ,255,  0,	0  ,225,  0,	0  ,200,  0,	0  ,150,  0,};
	int		color_index[32];
	color_range = (int)(256/((double)output->portrait_settings->comparation_DAN));
	DAN = output->portrait_settings->comparation_DAN;
	switch(DAN)
	{
		case 4:	for(n=0;n<4;n++)
					color_index[n] = n*4 + 1 + n%2;
				for(n=0;n<4;n++)
					color_index[n+4] = 16 + n*4 + 2 - (n+1)%2;
				break;
		case 8:	for(n=0;n<8;n++)
					color_index[n] = n*2 + 1;
				for(n=0;n<8;n++)
					color_index[n+8] = 16 + n*2;
				break;
		case 16:for(n=0;n<32;n++)
					color_index[n] = n;
				break;
		default:break;	
	}
////////////////////////////////////////////////////////////////////////////////////////////////	
	for(color_number=0;color_number<DAN*2;color_number++){
		output->portrait_settings->color[color_number][0] = 
					color_field[color_index[color_number]][0];
		output->portrait_settings->color[color_number][1] = 
					color_field[color_index[color_number]][1];
		output->portrait_settings->color[color_number][2] = 
					color_field[color_index[color_number]][2];
		for(n=0;n<10;n++){
			for(m=0;m<256/DAN;m++){
				colorlist[(n*512+m+color_number*(256/DAN))*4] 	= 
					color_field[color_index[color_number]][0];
				colorlist[(n*512+m+color_number*(256/DAN))*4+1] = 
					color_field[color_index[color_number]][1];
				colorlist[(n*512+m+color_number*(256/DAN))*4+2] = 
					color_field[color_index[color_number]][2];
			}
		}
	}
	
	for (n = 0;n < output->portrait_settings->map_square;n++){
		x = (n%output->portrait_settings->map_length)*output->portrait_settings->windows_size;
		y = (n/output->portrait_settings->map_length)*output->portrait_settings->windows_size;
		for(cy=0;cy<output->portrait_settings->windows_size;cy++){
			for(cx=0;cx<output->portrait_settings->windows_size;cx++){

////	Modified by Shenjunjie 2004.10.15 according to Mr. Hao's advice below	////
/*	In both options denote
    ai --- the counts of string type i from genome A
      bi --- the counts of string type i from genome B
         where i runs from 1 to 4**K

      Then define and display the difference

      di=(ai-bi)/(ai+bi)

      For displaying di using a crude color code. For example, divide the
      range into the following segments:
      -1 dark blue  -0.5 blue  -0.1 light blue  -0.01 white(?)  0.01 
      light orange 0.1 orange 0.5 drak orange 1.0
*/

/* this is original algorithm
				color_ratio = ( (((double)current->portrait_data[n]) + 0.01)/
					(((double)destination->portrait_data[n]) + 0.01) )*ratio;  
				if(	color_ratio >= 1.0){
					color_ratio = 1.0/color_ratio;
					color_number = DAN*2 - 1 - (int)(color_ratio*DAN);
				}
				else{
					color_number = (int)(color_ratio*DAN);
				}
*/

				if(output->portrait_settings->comparation_reduction==TRUE)
				{
					if((current->portrait_data[n] + destination->portrait_data[n]) == 0)
						color_ratio = 0.0;
					else
						color_ratio = 
				(((double)current->portrait_data[n])*current->portrait_settings->ratio_millions - 			((double)destination->portrait_data[n])*destination->portrait_settings->ratio_millions)/		(((double)current->portrait_data[n])*current->portrait_settings->ratio_millions + 
((double)destination->portrait_data[n])*destination->portrait_settings->ratio_millions);
				}
				else
				{
					if((current->portrait_data[n] + destination->portrait_data[n]) == 0)
						color_ratio = 0.0;
					else
						color_ratio = ((double)(current->portrait_data[n] - 
					destination->portrait_data[n]))/((double)(current->portrait_data[n] + 
					destination->portrait_data[n]));				
				}
				float di[8]			=	{-0.5,-0.1,-0.01, 0.0,0.01, 0.1,0.5,1.5};
				float di_length[8]	=	{0.5 , 0.4,0.09 ,0.01,0.01,0.09,0.4,0.5};
				
				int area_number = 8;
				int area_n;
				for(area_n=0;area_n<area_number;area_n++)
				{
					if(color_ratio <= di[area_n])
					{
						color_number = area_n*DAN/4 + 
						(int)((1.0 - (di[area_n] - color_ratio)/di_length[area_n])*(DAN/4));
						break;
					}	
				
				}
				
/////////////////////////////////////////////////////////////////////////////////

				output->portrait_data[n*2] = current->portrait_data[n];
				output->portrait_data[n*2+1] = destination->portrait_data[n];

				map_draw[((cy+y)*512+cx+x)*4  ]=output->portrait_settings->color[color_number][0];
				map_draw[((cy+y)*512+cx+x)*4+1]=output->portrait_settings->color[color_number][1];
				map_draw[((cy+y)*512+cx+x)*4+2]=output->portrait_settings->color[color_number][2];
				map_draw[((cy+y)*512+cx+x)*4+3]=color_number;
			}
		} 	
	}
}

int giftext(char *filename,Portrait* out_portrait)
{
	int		filelength;
	int 	out;
	filelength = strlen(filename);
	filename[filelength-4] = '.';
	filename[filelength-3] = 't';
	filename[filelength-2] = 'x';
	filename[filelength-1] = 't';
	
	out = open(filename,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	write(out,out_portrait->Detail,strlen(out_portrait->Detail));
	close(out);	
}
int gifout(char *filename,char *map,guint8 color[64][3])
{	
	char block[1024],*picture=NULL,*transfer=NULL,*data_buffer=NULL,input[9];
	int	out,n,pblock=0,ntransfer=0,m,current,dimension=6,count=0,*output=NULL,noutput=1;
	int number=0,nread=0,data_length,pbuffer=0,ptransfer=0,temp;
	int	SIZE= 512;
	Node *HEAD,*CURRENT;
	out = open(filename,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	HEAD = malloc(sizeof(Node));
	for(n = 0;n<COLOR_SIZE;n++){
		HEAD->value[n] = n;
		HEAD->next[n] = NULL;
	}
	for(n=0;n<COLOR_SIZE;n++){
		HEAD->next[n] = malloc(sizeof(Node));
		CURRENT = (Node*)HEAD->next[n];
		for(m = 0;m<COLOR_SIZE;m++){
			CURRENT->value[m] 	= -1;
			CURRENT->next[m] 	= NULL;
		}
	}
	CURRENT = HEAD;
	if((picture = (char*)malloc(SIZE*SIZE*sizeof(char))) == NULL)
	{
		Memory_Error();
		exit(0);
	}
	if((output	= (int*)malloc(SIZE*SIZE*sizeof(int)))	== NULL)
	{
		Memory_Error();
		exit(0);
	}
	output[0] = COLOR_SIZE*2;
//////////// init the picture  //////////////////////////////////////
	for(n=0;n<SIZE*SIZE;n++)
		picture[n] = map[n*4+3];
	int increment = COLOR_SIZE*2+2;	
	while(nread < SIZE*SIZE){
		current = picture[nread++];
		if(CURRENT->value[current] > -1 ){
			temp	=	CURRENT->value[current];
			CURRENT = 	(Node*)CURRENT->next[current];
		}
		else{
			output[noutput++] 		= temp;
			if(increment < 4096){
				CURRENT->value[current] = increment++;
				CURRENT->next[current] 	= malloc(sizeof(Node));
				CURRENT = (Node*)CURRENT->next[current];
				for(n = 0;n<COLOR_SIZE;n++){
					CURRENT->value[n] 	= -1;
					CURRENT->next[n] 	= NULL;
				}
			}
			CURRENT = 	(Node*)HEAD->next[current];
			temp	=	HEAD->value[current];
		}
	}
	output[noutput++] = temp;
	output[noutput++] =	COLOR_SIZE*2+1;
	if((transfer = (char*)malloc(noutput*12)) == NULL)
		exit(0);
	for(n=0;n<noutput*12;n++)
		transfer[n] = '0';
	ntransfer = 0;
	dimension = DIMENSION;
	count=0;
	int power = pow(2,dimension-1);
	for(n=0;n<noutput;n++,count++){	
		current = output[n];
		if(count>=power && dimension < 12){
			dimension++;
			count=0;
			power = pow(2,dimension-1);
		} 
		for(m=0;m<dimension && m < 12;m++){
			transfer[ntransfer++] = current%2 + '0';
			current = current/2;	
		}
	}
	count = ntransfer/8 + 1;
//////////  write data  /////////////////////////////////////////////
	block[pblock++] = 'G';
	block[pblock++] = 'I';
	block[pblock++] = 'F';
	block[pblock++] = '8';
	block[pblock++] = '9';
	block[pblock++] = 'a';
	block[pblock++] = 0;
	block[pblock++] = 2;
	block[pblock++] = 0;
	block[pblock++] = 2;
	block[pblock++] = 133;
	block[pblock++] = 0;
	block[pblock++] = 0;
	for(n=0;n<64;n++){
		block[pblock++] = color[n][0];
		block[pblock++] = color[n][1];
		block[pblock++] = color[n][2];
	}
	block[pblock++] = 44;
	block[pblock++] = 0;
	block[pblock++] = 0;
	block[pblock++] = 0;
	block[pblock++] = 0;
	block[pblock++] = 0;
	block[pblock++] = 2;
	block[pblock++] = 0;
	block[pblock++] = 2;
	block[pblock++] = 0;
	block[pblock++] = DIMENSION - 1;
	write(out,block,pblock);
	input[8] = '\0';
	data_length = count + count/255 + 10;
	data_buffer	= malloc(data_length*sizeof(char));
	for (;count>0;count= count - temp)
	{
		temp = count;
		if(temp>=255)
			temp = 255;
		data_buffer[pbuffer++] = temp;
		for(m=0;m<temp;m++){
			for(n=0;n<8;n++){
				input[n] = transfer[ptransfer*8 + 7-n];
			}
			ptransfer++;
			data_buffer[pbuffer++] = strtol(input,NULL,2);
		}	
	}
	data_buffer[pbuffer++] = 0;
	data_buffer[pbuffer++] = 59;
	write(out,data_buffer,pbuffer);	
	close(out);
	
	free(data_buffer);
	free(output);
	free(picture);
	free(transfer);	
	return 0;
}

int Memory_Error()
{
  	GtkWidget *Error = create_error(ERROR,"Not Enough Memory");
  	gtk_widget_show(Error);
}

Portrait * generat_portrait(guint8 portrait_type,Sequence *sequence)
{
///////////////////  CREATE CURRENT PORTRAIT DATA  ////////////////////////
	Portrait *current_portrait = 	g_malloc(sizeof(Portrait));
	current_portrait->marker	=	PORTRAIT_MARKER++;	
	sprintf(current_portrait->ID,"P%d_%s",current_portrait->marker,sequence->locus);			
	char 	Read[3][20]={"Original","Complement","Orig+Comp"};
	char	Rand[2][10]={"","Rand"};
	if(randomization == TRUE)
		sprintf(current_portrait->Description,"K=%d %s %s %d",k_tuples,Read[reading_mode-1],Rand[randomization],rand_times);	
	else
		sprintf(current_portrait->Description,"K=%d %s",k_tuples,Read[reading_mode-1]);	

//////////////	appended in 2004.4.20 by Shen Junjie   ///////////////////////////////		
	sprintf(current_portrait->Detail,
			   "Locus: %s\nDefinition: %s\nGenome Source: %s\nTotal bps: %d\nAdenine:   %d\nCytosine:  %d\nGuanine:   %d\nThymine:   %d\nPortrait Information: \n    K tuples = %d\n    Reading mode is %s\n    Randomization is %s %d %s",
				sequence->locus,
				sequence->description,
				sequence->source,
				sequence->amount_basepairs,
				sequence->amount_adenine,
				sequence->amount_cytosine,
				sequence->amount_guanine,
				sequence->amount_thymine,
				k_tuples,
				Read[reading_mode-1],
				(randomization?"used for ":"not used "),
				(randomization?rand_times:0),
				(randomization?"time(s)":""));
				
	sprintf(current_portrait->filename,"%s_%s",sequence->source,current_portrait->ID);
//////////////////////////////////////////////////////////////////////////////////////////

	current_portrait->portrait_type	=	portrait_type;
	current_portrait->portrait_data	= 	NULL;
	current_portrait->portrait_draw	=	NULL;
	current_portrait->portrait_colorlist	=	NULL;
	current_portrait->last	=	NULL;
	current_portrait->next	=	NULL;	
///////////////////		SETTINGS     //////////////////////////////////////	
	current_portrait->portrait_settings	=	g_malloc(sizeof(Settings));	
	current_portrait->portrait_settings->k_tuples		= k_tuples;
	current_portrait->portrait_settings->windows_size 	= windows_size;
	current_portrait->portrait_settings->map_length		= map_length;
	current_portrait->portrait_settings->map_square		= map_square;
	current_portrait->portrait_settings->reading_mode	= reading_mode;
	current_portrait->portrait_settings->randomization	= randomization;
	current_portrait->portrait_settings->rand_times		= rand_times;
	current_portrait->portrait_settings->color_mode		= color_mode;
	current_portrait->portrait_settings->comparation_reduction=comparation_reduction;
	current_portrait->portrait_settings->comparation_DAN= comparation_DAN;
	current_portrait->portrait_settings->exp_table[0]   = 1;
	int n;
	for(n=1;n<11;n++)
		current_portrait->portrait_settings->exp_table[n] 
			= current_portrait->portrait_settings->exp_table[n-1]*2;
	current_portrait->portrait_draw	=	(char *)g_malloc(512*512*4*sizeof(char));
	if(current_portrait->portrait_draw == NULL){
		Memory_Error();
		return NULL;
	}
	switch(portrait_type)
	{
		case	PORTRAIT:
			current_portrait->portrait_settings->ratio_millions = 
												1000000/((double)CURRENT->amount_basepairs);	
			current_portrait->portrait_colorlist=(char *)g_malloc(512*20*4*sizeof(char));
			if(current_portrait->portrait_colorlist==NULL){
				Memory_Error();
				return NULL;
			}
		case	HISTOGRAM:
			if (color_mode == HighContrast){ 
				for(n=0;n<48;n++)
					current_portrait->portrait_settings->color[n/3][n%3]=color_high[n/3][n%3]*255;
			}
			else{
				for(n=0;n<48;n++)
					current_portrait->portrait_settings->color[n/3][n%3]=color_auto[n/3][n%3]*255;
			}
			current_portrait->portrait_data=(int *)g_malloc(map_square*sizeof(int));
			if(current_portrait->portrait_data == NULL){
				Memory_Error();
				return NULL;
			}
			for(n=0;n<map_square;n++)
				current_portrait->portrait_data[n] = 0;
			break;
		case 	COMPRESULT:
			current_portrait->portrait_colorlist=(char *)g_malloc(512*10*4*sizeof(char));
			if(current_portrait->portrait_colorlist==NULL){
				Memory_Error();
				return NULL;
			}
			current_portrait->portrait_data=(int *)g_malloc(map_square*sizeof(int)*2);
			if(current_portrait->portrait_data == NULL){
				Memory_Error();
				return NULL;
			}
			for(n=0;n<map_square*2;n++)
				current_portrait->portrait_data[n] = 0;
			break;
	}
	return current_portrait;
}	

void file_dlg_ok(GtkButton *button,gpointer data)
{
	gchar *filepath;
	filepath = (char*)gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));

	
	strcpy(current_datafile_path,filepath);
	if(current_datafile_path[strlen(current_datafile_path) - 1]=='/')
		return;
	char *position;
	position = rindex(current_datafile_path,'/');
/*	if(((position[strlen(position)-3] == 'g'||position[strlen(position)-3] == 'G' )
	 &&	(position[strlen(position)-2] == 'b'||position[strlen(position)-2] == 'B' )
	 &&	(position[strlen(position)-1] == 'k'||position[strlen(position)-1] == 'K' )) 
	 ||((position[strlen(position)-3] == 'f'||position[strlen(position)-3] == 'F' )
	 && (position[strlen(position)-2] == 'n'||position[strlen(position)-2] == 'N' )
	 &&	(position[strlen(position)-1] == 'a'||position[strlen(position)-1] == 'A' )))
	{
	}
	else
	{
		GtkWidget *Error = create_error(ERROR,"Please check file type\n *.gbk and *.fna\n");
 	 	gtk_widget_show(Error);
		return;
	}
*/

	position[0] = '\0';

////////		data process     //////////////////////////////////////////////
	Sequence *new = data_process(filepath);
	if(new == -2){
 	 	GtkWidget *Error = create_error(ERROR,"Open File Failed\nTry again");
 	 	gtk_widget_show(Error);
		return;
	}
	if(new == NULL){
 	 	GtkWidget *Error = create_error(WARNING,"Unsupported File Format\nTry again");
 	 	gtk_widget_show(Error);
		return;
	}

	gtk_widget_destroy(GTK_WIDGET(data));
	if(new == -3){
		return;
	}
///////////////////////////////////////////////////////////////////////////////
	gchar *text[4];
	text[0] = new->locus;
    text[1] = new->description;
    text[2] = new->format;
	text[3] = new->filepath;
	gtk_clist_append(currentlist,text);

	if (HEAD == NULL)
		HEAD = new;
	else{
		Sequence *temp = HEAD;	
		for(;;){
			if(temp->next != NULL)
				temp = (Sequence*)temp->next;
			else{
				(Sequence*)temp->next = new;
				(Sequence*)new->last = temp;
				break;
			}	
		}
	}
	CURRENT = new;
	
}

void file_dlg_cancel(GtkButton *button,gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}

void expertfile_dlg_ok(GtkButton *button,gpointer data)
{
	typedef struct _ExportBox{
		GtkWidget 	*exportfile_dlg;	
		Portrait	*portrait;
	}ExportBox;
	
	gchar *filepath;
	filepath = (char*)gtk_file_selection_get_filename(GTK_FILE_SELECTION(((ExportBox *)data)->exportfile_dlg));
	
	strcpy(current_exportfile_path,filepath);
	char *position;
	position = rindex(current_exportfile_path,'/');
	position[0] = '\0';
	
	gtk_widget_destroy(GTK_WIDGET( ((ExportBox *)data)->exportfile_dlg) );
	
	gifout(filepath,((Portrait *)((ExportBox *)data)->portrait)->portrait_draw,
					((Portrait *)((ExportBox *)data)->portrait)->portrait_settings->color);
///////////////////  appended in 2004.4.20 to add some information about portrait   ///////////
	giftext(filepath,(Portrait *)((ExportBox *)data)->portrait);
	
///////////////////  by Shen Junjie  //////////////////////////////////////////////////////////	
}

void expertfile_dlg_cancel(GtkButton *button,gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}

void export_image(gpointer user_data)
{
	typedef struct _ExportBox{
		GtkWidget 	*exportfile_dlg;	
		Portrait	*portrait;
	}ExportBox;
	
	ExportBox *exportbox = (ExportBox *)g_malloc(sizeof(ExportBox));

	chdir(current_exportfile_path);
		
	GtkWidget *exportfile_dlg;
	exportfile_dlg = gtk_file_selection_new("Export the Image to a GIF");
	
	exportbox->exportfile_dlg 	= 	exportfile_dlg;
	exportbox->portrait			=	(Portrait *)user_data;
	
	char output_filename[100];
	sprintf(output_filename,"%s.gif",exportbox->portrait->filename);
	
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(exportfile_dlg)->ok_button),"clicked",
						GTK_SIGNAL_FUNC(expertfile_dlg_ok),exportbox);
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(exportfile_dlg)->cancel_button),"clicked",
						GTK_SIGNAL_FUNC(expertfile_dlg_cancel),exportfile_dlg);
	gtk_file_selection_complete(GTK_FILE_SELECTION(exportfile_dlg),output_filename);
	gtk_window_set_modal(GTK_WINDOW(exportfile_dlg),TRUE);
	gtk_widget_show(exportfile_dlg);
}

void
on_open_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

	chdir(current_datafile_path);
	
	GtkWidget *sequencefile_dlg;
	sequencefile_dlg = gtk_file_selection_new("Select A Sequence File");
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(sequencefile_dlg)->ok_button),"clicked",
						GTK_SIGNAL_FUNC(file_dlg_ok),sequencefile_dlg);
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(sequencefile_dlg)->cancel_button),"clicked",
						GTK_SIGNAL_FUNC(file_dlg_cancel),sequencefile_dlg);
	gtk_file_selection_complete(GTK_FILE_SELECTION(sequencefile_dlg),"*.gbk;*.fna");
	gtk_window_set_modal(GTK_WINDOW(sequencefile_dlg),TRUE);
	gtk_widget_show(sequencefile_dlg);
	currentlist = ((Console*)user_data)->clist;
}

void
on_close_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
//	currentlist = ((Console*)user_data)->clist;
	
	if(CURRENT!=NULL){	
		int n;
		for(n=0;n<CURRENT->datalist;n++)
			free(CURRENT->data[n]);
		CURRENT = NULL;
		gtk_clist_remove(((Console*)user_data)->clist,currentrow);
	

	}
}


void
on_quit_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         console)
{
	gtk_widget_destroy(GTK_WIDGET(console));
}


void
on_preferences_console_activate        (GtkMenuItem     *menuitem,
                                        gpointer         colormode)
{
	temp_rand_times=	1;			
	temp_color_mode=	0;			
	temp_comparation_reduction=TRUE;  
	temp_comparation_DAN=4;	

   	GtkWidget *advancedsettings	= create_advancedsettings (colormode);
   	gtk_widget_show (advancedsettings);

}


void
on_about_console_activate              (GtkMenuItem     *menuitem,
                                        gpointer         about)
{
   	about	= create_about ();
   	gtk_widget_show (about);	
}


void
on_clist_console_sequencefile_select_row
                                        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
//// original buffer size 200 is too small and causes segmentation fault problem /////
	gchar 		*text,buffer[2000];
//// modified 2004.10.3 by author Shen Junjie	//////////////	
	Sequence 	*temp = HEAD;
	gtk_clist_get_text(GTK_CLIST(clist),row,0,&text);

//// modified 2004.3.4 by author Shen Junjie ////
	currentrow = row;	
/////////////////////////////////////////////////

	for(;temp != NULL;){
		if(!strcmp(text,temp->locus)){
			CURRENT = temp;
			break;
		}
		else{
			temp = (Sequence*)temp->next;
		}
	}

	sprintf(buffer," %s\n genome source: %s\n Total base pairs: %d bps\n Adenine:	%d\n Cytosine:	%d\n Guanine:	%d\n Thymine:	%d\n",	CURRENT->description,
					CURRENT->source,
					CURRENT->amount_basepairs,
					CURRENT->amount_adenine,
					CURRENT->amount_cytosine,
					CURRENT->amount_guanine,
					CURRENT->amount_thymine);
 	gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (((Console*)user_data)->textview)),buffer, -1);
 	
}


void
on_button_console_drawingpanel_histogram_clicked
                                        (GtkButton       *button,
                                        gpointer         histogram)
{
	if(CURRENT == NULL)
		return;

	Portrait *new_histogram = generat_portrait(HISTOGRAM,CURRENT);
	drawing(CURRENT,new_histogram);
	
	GtkWidget *show_histogram;
	show_histogram = create_histogram (new_histogram);
  	gtk_widget_show (show_histogram);
}


void
on_button_console_drawingpanel_portrait_clicked
                                        (GtkButton       *button,
                                        gpointer         portrait)
{
	if(CURRENT == NULL)
		return;
	Portrait *temp;
	Portrait *new_portrait = generat_portrait(PORTRAIT,CURRENT);
	drawing(CURRENT,new_portrait);
	
	if(HEAD_PORTRAIT == NULL)
		HEAD_PORTRAIT = new_portrait;
	else{
		temp = HEAD_PORTRAIT;
		for(;;){
			if(temp->next!=NULL)
				temp = (Portrait*)temp->next;
			else{
				(Portrait*)temp->next = new_portrait;
				(Portrait*)new_portrait->last = temp;
				break;
			}
		}
	}
	GtkWidget *show_portrait;
	show_portrait = create_portrait (new_portrait);
  	gtk_widget_show (show_portrait);

}


gboolean
on_drawingarea_console_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	if (color_mode == 0)
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							2, 2,192,20,GDK_RGB_DITHER_NONE,
							(void *)user_data,768);
	else
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							2, 2,192,20,GDK_RGB_DITHER_NONE,
							(void *)(user_data+192*20*4),768);
	return FALSE;
}


void
on_radiobutton_console_randomization_none_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	randomization=	FALSE;
}


void
on_radiobutton_console_randomization_applicated_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	randomization=	TRUE;
}


void
on_radiobutton_console_readingmethod_original_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	reading_mode=	ORIGINAL;	
}


void
on_radiobutton_console_readingmethod_reverse_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	reading_mode=	COMPLEMENT;
}


void
on_radiobutton_console_readingmethod_originalandreverse_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	reading_mode=	ORIGINAL_COMPLEMENT;
}


void
on_spinbutton_console_ktuples_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         ktuples)
{
	k_tuples 		= 	gtk_spin_button_get_value_as_int(ktuples);
	windows_size	=	512/(exp_table[k_tuples]);
	map_length		=   exp_table[k_tuples];
	map_square		=	map_length*map_length;
}


void
on_button_console_advancedsettings_clicked
                                        (GtkButton       *button,
                                        gpointer         colormode)
{
	temp_rand_times=	1;			
	temp_color_mode=	0;			
	temp_comparation_reduction=TRUE;  
	temp_comparation_DAN=4;	
	
   	GtkWidget *advancedsettings	= create_advancedsettings (colormode);
   	gtk_widget_show (advancedsettings);
}


gboolean
on_drawingarea_portrait_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

/*	
	int	color_index;
	color_index = current->portrait->portrait_draw[(((int)event->y)*512+(int)event->x)*4 + 3];
	printf("color index is %d\n",color_index);
	
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	
	for(n=0;n<10;n++){
	for(y=0;y<512;y++){
		for(x=0;x<512;x++){
			if(color_index == current->portrait->portrait_draw[(y*512+x)*4 + 3])
				gdk_draw_point(drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],x,y);
		}	
	
	}
		sleep(1);
	gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,512,GDK_RGB_DITHER_NONE,
							(void *)current->portrait->portrait_draw,2048);
	    sleep(1);
	}
  */
  

  return FALSE;
}
gboolean
on_drawingarea_portrait_drawing_motion_notify_event
                                        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	MousePress *current = (MousePress *)user_data;
	int		EXPTABLE[11]={1,2,4,8,16,32,64,128,256,512,1024};
	char buffer[200];
	int x,y,count,size,K = current->portrait->portrait_settings->k_tuples;
	size = EXPTABLE[9 - K];
	x = (int)event->x;
	y = (int)event->y;
	count = current->portrait->portrait_data[x/size+(y/size)*EXPTABLE[K]];
	char tuples[10];
	int	n;
	int	temp;
	for(n = 0;n < K;n++){
		temp = x/EXPTABLE[8-n] + (y/EXPTABLE[8-n])*2;
		x = x%EXPTABLE[8-n];
		y = y%EXPTABLE[8-n];
		switch(temp){
			case 0:tuples[n] = 'g';break;
			case 1:tuples[n] = 'c';break;
			case 2:tuples[n] = 'a';break;
			case 3:tuples[n] = 't';break;
			default:tuples[n]= 'u';break;
		}	
	}	
	tuples[n] = '\0';
	sprintf(buffer,"K = %d tuples: \"%s\" count is %d\n",
			K,
			tuples,
			count);
	gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (current->textview)),buffer, -1);
  return TRUE;
}

gboolean
on_drawingarea_portrait_expose_event   (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         map)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	if (CURRENT != NULL)
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,512,GDK_RGB_DITHER_NONE,
							(void *)map,2048);
  	return FALSE;
}


gboolean
on_drawingarea_portrait_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         colormode)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	if (CURRENT != NULL)
	gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,20,GDK_RGB_DITHER_NONE,
							(void *)colormode,2048);
	return FALSE;
}


void
on_button_portrait_compare_clicked     (GtkButton       *button,
                                        gpointer         current_portrait)
{
	GtkWidget *comparation	=	create_comparation(HEAD_PORTRAIT,current_portrait);
	gtk_widget_show(comparation);
	
}


void
on_button_portrait_export_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	export_image(user_data);
}

void
on_portrait_destroy						(GtkObject 		*window,
										gpointer 		portrait)
{
	Portrait *temp_portrait = HEAD_PORTRAIT;
	switch(((Portrait*)portrait)->portrait_type)
	{
		case 	PORTRAIT:
			if(temp_portrait->marker == ((Portrait*)portrait)->marker){
				HEAD_PORTRAIT=temp_portrait = (Portrait*)temp_portrait->next;
				if(temp_portrait != NULL)
					temp_portrait->last = NULL;
			}
			else{
				for(;;temp_portrait = (Portrait*)temp_portrait->next){
					if(((Portrait*)portrait)->marker == ((Portrait*)temp_portrait->next)->marker)
					{
						temp_portrait->next = ((Portrait*)temp_portrait->next)->next;
						if(temp_portrait->next!= NULL)
							(Portrait*)((Portrait*)temp_portrait->next)->last = temp_portrait;
						break;	
					}
				}
			}
			free(((Portrait*)portrait)->portrait_data);
			free(((Portrait*)portrait)->portrait_draw);
			free(((Portrait*)portrait)->portrait_colorlist);
			free(((Portrait*)portrait)->portrait_settings);
			free((Portrait*)portrait);
			break;
		case	HISTOGRAM:
			free(((Portrait*)portrait)->portrait_data);
			free(((Portrait*)portrait)->portrait_draw);
			free(((Portrait*)portrait)->portrait_settings);
			free((Portrait*)portrait);
			break;
		case	COMPRESULT:
			free(((Portrait*)portrait)->portrait_data);
			free(((Portrait*)portrait)->portrait_draw);
			free(((Portrait*)portrait)->portrait_colorlist);
			free(((Portrait*)portrait)->portrait_settings);
			free((Portrait*)portrait);
			break;
	}

}



gboolean
on_drawingarea_histogram_expose_event  (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	
	char *map = ((Portrait*)((MousePress*)user_data)->portrait)->portrait_draw;

	if (CURRENT != NULL){
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,512,GDK_RGB_DITHER_NONE,
							(void *)map,2048);
		if(((MousePress*)user_data)->MousePressed == TRUE)					
/*			gdk_draw_line(drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
						((MousePress*)user_data)->MousePosition[0],
						512 - ((MousePress*)user_data)->MousePosition[1],
						((MousePress*)user_data)->MousePosition[0],512);
*/						
			gdk_draw_rectangle(drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],TRUE,
			((MousePress*)user_data)->MousePosition[0],
			512-((MousePress*)user_data)->MousePosition[1],
			((MousePress*)user_data)->MousePosition[2],
			((MousePress*)user_data)->MousePosition[1]);
	}

  return FALSE;
}


gboolean
on_drawingarea_histogram_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	char *map = ((Portrait*)((MousePress*)user_data)->portrait)->portrait_draw;
	int x,y;
	int	tempx1,tempx2;
	x = (int)event->x;
	y = (int)event->y;
	
	tempx1	= x - (x%(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_bin_length));
	tempx2  = x/(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_bin_length);
	y = ((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_array[tempx2*3+2]*(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_ratio);
	if(y >512)
		y = 512;
	((MousePress*)user_data)->MousePressed = TRUE;
	((MousePress*)user_data)->MousePosition[0] = tempx1;
	((MousePress*)user_data)->MousePosition[1] = y;
	((MousePress*)user_data)->MousePosition[2] = ((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_bin_length;
	if (CURRENT != NULL){
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,512,GDK_RGB_DITHER_NONE,
							(void *)map,2048);
		//gdk_draw_line(drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],x,512 - y,x,512);	
		gdk_draw_rectangle(drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],TRUE,
			tempx1,512-y,
			((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_bin_length,
			y);
			
	}
	char buffer[100];
	sprintf(buffer,"Count Area <%d,%d> total count is %d\n",
			(int)(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_array[tempx2*3]),
			(int)(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_array[tempx2*3+1]),
			(int)(((Settings*)((Portrait*)((MousePress*)user_data)->portrait)->portrait_settings)->histogram_array[tempx2*3+2]));
	gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (((MousePress*)user_data)->textview)),buffer, -1);
    return FALSE;
}


void
on_button_histogram_export_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	export_image(user_data);
}


gboolean
on_drawingarea_compresult_drawing_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         map)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	if (CURRENT != NULL)
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0, 0,512,512,GDK_RGB_DITHER_NONE,
							(void *)map,2048);
  	return FALSE;

}


gboolean
on_drawingarea_compresult_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         colormode)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0,0,512,10,GDK_RGB_DITHER_NONE,(void *)colormode,2048);		
  	return FALSE;
}


void
on_button_compresult_export_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	export_image(user_data);
}

gboolean
on_drawingarea_compresult_drawing_motion_notify_event
                                        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	MousePress *current = (MousePress *)user_data;
	int		EXPTABLE[11]={1,2,4,8,16,32,64,128,256,512,1024};
	char buffer[200];
	int x,y,count_1,count_2,size,K;
	K	= current->portrait->portrait_settings->k_tuples;
	size = EXPTABLE[9 - K];
	x = (int)event->x;
	y = (int)event->y;
	count_1 = current->portrait->portrait_data[(x/size+(y/size)*EXPTABLE[K])*2];
	count_2 = current->portrait->portrait_data[(x/size+(y/size)*EXPTABLE[K])*2+1];
	char tuples[10];
	int	n;
	int	temp;
	for(n = 0;n < K;n++){
		temp = x/EXPTABLE[8-n] + (y/EXPTABLE[8-n])*2;
		x = x%EXPTABLE[8-n];
		y = y%EXPTABLE[8-n];
		switch(temp){
			case 0:tuples[n] = 'g';break;
			case 1:tuples[n] = 'c';break;
			case 2:tuples[n] = 'a';break;
			case 3:tuples[n] = 't';break;
			default:tuples[n]= 'u';break;
		}	
	}	
	tuples[n] = '\0';
	sprintf(buffer,"K = %d tuples: \"%s\" Current: %d Target:%d\n",
			K,
			tuples,
			count_1,count_2);


	gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (current->textview)),buffer, -1);
	
	
  return FALSE;
}

void
on_entry_advancedsettings_random_times_changed
                                        (GtkEditable     *editable,
                                        gpointer         entry)
{
	temp_rand_times = atoi(gtk_entry_get_text (GTK_ENTRY (entry)));
	if(temp_rand_times < 1 || temp_rand_times > 80)
		temp_rand_times = 1;
}


gboolean
on_drawingarea_advancedsettings_colormode_high_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         colormode)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0,0,320,20,GDK_RGB_DITHER_NONE,(void *)colormode,1280);		
  	return FALSE;
}


gboolean
on_drawingarea_advancedsettings_colormode_auto_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         colormode)
{
	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET(widget);
	drawable	=	drawingarea->window;
	gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							0,0,320,20,GDK_RGB_DITHER_NONE,(void *)colormode,1280);
	return FALSE;
}


void
on_radiobutton_advancedsettings_colormode_highcontrast_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	temp_color_mode	=	0;	
}


void
on_radiobutton_advancedsettings_colormode_autobalanced_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	temp_color_mode	=	1;
}


void
on_radio_advancedsettings_cmp_reduction_yes_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	temp_comparation_reduction	=	TRUE; 
}


void
on_radio_advancedsettings_cmp_reduction_no_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	temp_comparation_reduction	=	FALSE; 
}


void
on_combo_entry_advancedsettings_cmp_DAN_changed
                                        (GtkEditable     *editable,
                                        gpointer         entry)
{
	temp_comparation_DAN = atoi(gtk_entry_get_text (GTK_ENTRY (entry)));
	if(temp_comparation_DAN < 4 || temp_comparation_DAN > 32)
		temp_comparation_DAN = 4;
}


void
on_button_advancedsettings_OK_clicked  (GtkButton       *button,
                                        gpointer         colormode)
{
	rand_times = temp_rand_times;
	color_mode = temp_color_mode;			
	comparation_reduction = temp_comparation_reduction; 
	comparation_DAN = temp_comparation_DAN;	

	GdkDrawable	*	drawable;
	GtkWidget	*	drawingarea;
	drawingarea	=	GTK_WIDGET( ((ConsoleColormode*)colormode)->drawing_colormode );
	drawable	=	drawingarea->window;
	if (color_mode == 0)
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							2, 2,192,20,GDK_RGB_DITHER_NONE,
							(void *)( ((ConsoleColormode*)colormode)->colorlist ),768);
	else
		gdk_draw_rgb_32_image (drawable,drawingarea->style->fg_gc[GTK_STATE_NORMAL],
							2, 2,192,20,GDK_RGB_DITHER_NONE,
							(void *)( ((ConsoleColormode*)colormode)->colorlist+192*20*4),768);
	gtk_widget_destroy( ((ConsoleColormode*)colormode)->advancedsettings );
}


void
on_button_advancedsettings_CANCEL_clicked
                                        (GtkButton       *button,
                                        gpointer         advancedsettings)
{
	gtk_widget_destroy(advancedsettings);
}


void
on_button_advancedsettings_APPLY_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	rand_times = temp_rand_times;
	color_mode = temp_color_mode;			
	comparation_reduction = temp_comparation_reduction; 
	comparation_DAN = temp_comparation_DAN;	
}


void
on_button_comparation_OK_clicked       (GtkButton       *button,
                                        gpointer         com_box)
{
  	typedef struct _ComparationBox{
		GtkWidget 	*comparation_window;	
		Portrait	*current;
  	} ComparationBox;
  	if(COMPARATION_DESTINATION == NULL){
  		GtkWidget *Error = create_error(WARNING,"Please Select One \nTarget Portrait");
  		gtk_widget_show(Error);
  		return;
  	}
  	Portrait	*compresult_portrait = generat_portrait(COMPRESULT,CURRENT);
  	
  	
	compresult_portrait->portrait_settings->k_tuples = 
		((ComparationBox*)com_box)->current->portrait_settings->k_tuples;
	compresult_portrait->portrait_settings->windows_size= 
		((ComparationBox*)com_box)->current->portrait_settings->windows_size;
	compresult_portrait->portrait_settings->map_length	= 
		((ComparationBox*)com_box)->current->portrait_settings->map_length;
	compresult_portrait->portrait_settings->map_square	= 
		((ComparationBox*)com_box)->current->portrait_settings->map_square;
  	
	comparation_drawing(((ComparationBox*)com_box)->current,
						COMPARATION_DESTINATION,
						compresult_portrait);
	sprintf(compresult_portrait->ID,"Comparation Result < %s , %s >",((ComparationBox*)com_box)->current->ID,COMPARATION_DESTINATION->ID);	
	GtkWidget	*compresult	=	create_compresult(compresult_portrait);
	gtk_widget_show(compresult);
	gtk_widget_destroy(((ComparationBox*)com_box)->comparation_window);
	COMPARATION_DESTINATION = NULL;
}


void
on_button_comparation_Cancel_clicked   (GtkButton       *button,
                                        gpointer         comparation)
{
	gtk_widget_destroy(comparation);
	COMPARATION_DESTINATION = NULL;
}


void
on_clist_comparation_destination_select_row
                                        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         destination)
{
	gchar 		*text,buffer[200];
	Portrait 	*temp = HEAD_PORTRAIT;
	gtk_clist_get_text(GTK_CLIST(clist),row,0,&text);	
	for(;temp != NULL;){
		if(!strcmp(text,temp->ID)){
			break;
		}
		else{
			temp = (Portrait*)temp->next;
		}
	}
	COMPARATION_DESTINATION = temp;
}


void
on_button_about_clicked                (GtkButton       *button,
                                        gpointer         about)
{
	gtk_widget_destroy(GTK_WIDGET(about));
}
void
on_okbutton_error_clicked              (GtkButton       *button,
                                        gpointer         error)
{
	gtk_widget_destroy(GTK_WIDGET(error));
}

	#include <stdlib.h>
	#include <stdio.h>
	#include <time.h>
	#include <math.h>
	#include <png.h>
	#include <malloc.h>
	#include <string.h>
	#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#define gtk_file_chooser_set_filename gtk_file_chooser_set_filename_utf8



typedef struct {
    GtkBuilder *builder;
    GdkPixbuf *pixbuf;
    GdkCursor *cursor; 
    GtkClipboard *clipboard;
    GtkWidget *window1;
    GtkWidget *spinner1;
    GtkWidget *spinbutton4;
    GtkWidget *spinbutton5;
    GtkWidget *spinbutton1;
    GtkWidget *spinbutton2;
    GtkWidget *spinbutton3;
    GtkWidget *button3;
    GtkWidget *label;
    GtkWidget *entry3;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *label7;
    GtkWidget *label8;
    GtkWidget *button4;
    GtkWidget *button5;
    GtkWidget *button8;
    GtkWidget *label9;
    GtkWidget *entry4;
    GtkWidget *label10;
    GtkWidget *image6;
    GtkWidget *scrolledwindow1;
    GtkWidget *eventbox1;
    GtkWidget *imagemenuitem4;
    GtkWidget *filechooserdialog1;
    GtkWidget *viewport1;
    
    float *tempo;
    char *pasta;
    int empty;
    int pan_toggle;
    int img_cont;
    char nome[500];
    char copiar[500];
    char *buf;
    int taman;
    int qtd;
    int npart;
    int rlanc;
    float rmort;
    int prop;
    char img[20];
    int cont;
    int cont_frac;

    int qntParticulas;
    int linhas;
    //int colunas;        
}Tfractal;

//Salva arquivos

	

	void files_delete (Tfractal *info){
		sprintf(info->copiar, "rm *.png");
		system(info->copiar);	
	}

	void sair (GtkWidget *widget, Tfractal *info){
		files_delete(info);
		gtk_main_quit();
	}


	void pan_image (GtkWidget *widget, Tfractal *info){
		
		if ( info->empty )
		{
			
		if ( info->pan_toggle == 0)
		{
			info->pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(info->image6));
			info->pixbuf = gdk_pixbuf_scale_simple(info->pixbuf, info->scrolledwindow1->allocation.height+info->img_cont, info->scrolledwindow1->allocation.height+info->img_cont, GDK_INTERP_BILINEAR);
			gtk_image_set_from_pixbuf(GTK_IMAGE(info->image6), info->pixbuf);
			info->pan_toggle = 1;
		}else
		{
			sprintf(info->img, "img0%d.png",info->cont);
			gtk_image_set_from_file(GTK_IMAGE(info->image6),info->img);
			/*info->pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(info->image6));
			gtk_image_set_from_pixbuf(GTK_IMAGE(info->image6), info->pixbuf);*/
			info->pan_toggle = 0;
		}
		}

		//update_clipboard(info);
		//gtk_clipboard_store(info->clipboard);

		/*info->linhas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)); //Pega Tamanho da imagem 
		//info->colunas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4));
		info->qtd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton5)); //Pega Quantidade de imagens
		info->qntParticulas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton1)); //Pega Quantidade de Partículas*/
	}

	void update_clipboard (GtkWidget *widget, Tfractal *info){
		sprintf(info->copiar, "./dlasim %d %d %d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)),
												   gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton1)),
												   gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton5)) );
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), info->copiar, strlen(info->copiar));
	}

	void update_clipboard_entry (GtkWidget *widget, Tfractal *info){
		sprintf(info->copiar, "./dlasim %d %d %d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)),
												gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton1)),
												gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton5)) );
		gtk_entry_set_text(GTK_ENTRY(info->entry3), info->copiar);
		// sprintf(info->copiar, "./dlasim %d %d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)),
		// 										gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton1)) );
		// gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), info->copiar, strlen(info->copiar));
	}
	

	void salvar (Tfractal *info){
		info->pasta = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(info->filechooserdialog1));
		//sprintf(info->nome, "img");
		sprintf(info->copiar, "cp -r *.png %s", info->pasta);
		system(info->copiar);
		gtk_widget_hide(info->filechooserdialog1);
	}

	void save_menu (GtkWidget *widget, Tfractal *info){
        //gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(info->filechooserdialog1), "Untitled document");
        //gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(info->filechooserdialog1), "Untitled document");

		gint result = gtk_dialog_run (GTK_DIALOG (info->filechooserdialog1));
		switch (result){
    
    		case 3:
    		sprintf(info->nome, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (info->filechooserdialog1)));
    		salvar(info);
    		//save_to_file (gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (info->filechooserdialog1)));
    		break;
    default:
		gtk_widget_hide((info->filechooserdialog1));
       break;
        
       

  }
	}

//Sincroniza os valores com a proporção
	void update_spin (GtkWidget *widget, Tfractal *info){
		info->prop = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)); //prop = Tamanho da imagem  
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton1), (info->prop*info->prop)/100*4); //Coloca partículas na proporção
		//update_clipboard_entry(info);
	}


//Pega os valores e gera o fractal
	void entries_get (GtkWidget *widget, Tfractal *info ){
		info->linhas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4)); //Pega Tamanho da imagem 
		//info->colunas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton4));
		info->qtd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton5)); //Pega Quantidade de imagens
		info->qntParticulas = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton1)); //Pega Quantidade de Partículas
	info->rlanc = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton2));
	info->rmort = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(info->spinbutton3));
		files_delete(info);
	//Chama a função gerar n vezes

		gtk_widget_show(info->spinner1);
		free(info->tempo);
		info->tempo = malloc(info->qtd * sizeof(float));
		//gdk_threads_enter ();
		for(info->cont_frac=0;info->cont_frac < info->qtd; info->cont_frac++){
			//printf("%d",info->cont_frac);
			//g_thread_new(gerar);
			gerar(info, info->cont_frac); //Passa a estrutura e o contador
		}
		//gdk_threads_leave ();
		gtk_widget_hide(info->spinner1);
		

		gtk_image_set_from_file(GTK_IMAGE(info->image6), "img00.png"); //Seta a primeira imagem gerada
		
		sprintf(info->copiar, "%dx%d", info->linhas, info->linhas);
		gtk_label_set_text(GTK_LABEL(info->label7), info->copiar);

		sprintf(info->copiar, "%.2fs", info->tempo[0]);
		gtk_label_set_text(GTK_LABEL(info->label8), info->copiar);

		sprintf(info->copiar, "%d", info->cont_frac);
		gtk_label_set_text(GTK_LABEL(info->label10), info->copiar);

		info->cont_frac=0; //Reseta o contador
		info->cont=0; //Reseta o contador de imagem
		info->empty=1;
	}

//Limpa os campos
	void entries_clear (GtkWidget *widget, Tfractal *info ){
		//info->prop=0;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton4), 300);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton5), 1);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton1), (info->prop*info->prop)/100*4);
		//gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton2), info->prop);
		//gtk_spin_button_set_value(GTK_SPIN_BUTTON(info->spinbutton3), info->prop);
	}
		
	//info->rmort = gtk_spin_button_get_value_as_int(info->spinbutton3);

	

// Seta para esquerda
	void image_prev (GtkWidget *widget, Tfractal *info){ 
		info->cont--;
		sprintf(info->img, "img0%d.png",info->cont);
		gtk_image_set_from_file(GTK_IMAGE(info->image6),info->img);
		if (gtk_image_get_storage_type(GTK_IMAGE(info->image6))== 4){
			info->cont++; 
			sprintf(info->img, "img0%d.png",info->cont);                
			gtk_image_set_from_file(GTK_IMAGE(info->image6),info->img);
		}
		sprintf(info->copiar, "%.2fs", info->tempo[info->cont]);
		gtk_label_set_text(GTK_LABEL(info->label8), info->copiar);
	}

// Seta para direita
	void image_next (GtkWidget *widget, Tfractal *info){
		info->cont++;
		sprintf(info->img, "img0%d.png",info->cont);
		gtk_image_set_from_file(GTK_IMAGE(info->image6),info->img);
		if (gtk_image_get_storage_type(GTK_IMAGE(info->image6))== 4){
			info->cont--; 
			sprintf(info->img, "img0%d.png",info->cont); 
			gtk_image_set_from_file(GTK_IMAGE(info->image6),info->img);
		}
		sprintf(info->copiar, "%.2fs", info->tempo[info->cont]);
		gtk_label_set_text(GTK_LABEL(info->label8), info->copiar);
	}


////////////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////
	
int main(int argc, char *argv[])	{
//Cria Builder
    //g_thread_init (NULL);
  	
	
    Tfractal *info = malloc(sizeof(Tfractal));
    info->cont=1;
    info->cont_frac=0;
    info->img_cont=0;
    info->pan_toggle=0;
    info->empty=0;

    //gerando numeros aleatórios
    if(argc == 3){
		info->linhas = atoi(argv[1]);
		info->qntParticulas = atoi(argv[2]);
		/*printf("%d\n", info->linhas );
		printf("%d\n", info->qntParticulas );*/
		gerar(info, info->cont_frac);
		return 0;
	}
	if(argc == 4){
		int i;
		info->linhas = atoi(argv[1]);
		info->qntParticulas = atoi(argv[2]);
		info->qtd = atoi(argv[3]);
		/*printf("%d\n", info->linhas );
		printf("%d\n", info->qntParticulas );*/
		for (info->cont_frac = 0; info->cont_frac < info->qtd ; info->cont_frac++)
		{
			gerar(info, info->cont_frac);
		}
		return 0;
	}

//Pega nome da pasta
	long size;
		//char *buf;
		char *ptr;
		size = 1000;
		if ((info->buf = (char *)malloc((size_t)size)) != NULL)
		ptr = getcwd(info->buf, (size_t)size);
    /*char cwd[500];
	getcwd(cwd, sizeof(cwd));*/
	printf("%s", info->buf);
	
	//g_thread_init();
	
  	

//Inicia gtk e builder
    gtk_init(&argc, &argv);

    
    info->builder = gtk_builder_new();
    gtk_builder_add_from_file(info->builder, "DLA2.xml", NULL);

//Connecta o builder
    info->window1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"window1"));
    gtk_window_set_default_size(GTK_WINDOW (info->window1), 600, 500);
    info->spinbutton4 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinbutton4"));
    info->spinbutton5 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinbutton5"));
    info->spinbutton1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinbutton1"));
    info->spinbutton2 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinbutton2"));
    info->spinbutton3 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinbutton3"));
    info->button3 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button3"));
    info->entry3 = GTK_WIDGET(gtk_builder_get_object(info->builder,"entry3"));
    info->button1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button1"));
    info->button2 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button2"));
    info->label7 = GTK_WIDGET(gtk_builder_get_object(info->builder,"label7"));
    info->label8 = GTK_WIDGET(gtk_builder_get_object(info->builder,"label8"));
    info->button4 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button4"));
    info->button5 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button5"));
    info->button8 = GTK_WIDGET(gtk_builder_get_object(info->builder,"button8"));
    info->label9 = GTK_WIDGET(gtk_builder_get_object(info->builder,"label9"));
    info->entry4 = GTK_WIDGET(gtk_builder_get_object(info->builder,"entry4"));
    info->label10 = GTK_WIDGET(gtk_builder_get_object(info->builder,"label10"));
    info->image6 = GTK_WIDGET(gtk_builder_get_object(info->builder,"image6"));
    info->scrolledwindow1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"scrolledwindow1"));
    info->imagemenuitem4 = GTK_WIDGET(gtk_builder_get_object(info->builder,"imagemenuitem4"));
    info->filechooserdialog1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"filechooserdialog1"));
    info->spinner1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"spinner1"));
    info->viewport1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"viewport1"));
    info->eventbox1 = GTK_WIDGET(gtk_builder_get_object(info->builder,"eventbox1"));
    //info->cursor = gdk_cursor_new(GDK_WATCH);
	

		

    


    //GdkColor red = {0, 0x5000, 0x5000, 0x5000};
    //gtk_widget_modify_bg(info->eventbox1, GTK_STATE_NORMAL, &red);


//Connecta os sinais? e desliga o builder
    
    gtk_builder_connect_signals(info->builder,NULL);
    g_object_unref(G_OBJECT(info->builder));
    gtk_widget_show_all(info->window1);


//Sinais
    g_signal_connect(info->window1,"destroy",G_CALLBACK(sair), info);
    
    g_signal_connect(info->button2,"clicked",G_CALLBACK(entries_get), info);
    
    
    g_signal_connect(info->button3,"clicked",G_CALLBACK(entries_clear), info);
    g_signal_connect(info->button5,"clicked",G_CALLBACK(image_next), info);
    g_signal_connect(info->button4,"clicked",G_CALLBACK(image_prev), info);
    g_signal_connect(info->button8,"clicked",G_CALLBACK(pan_image), info);
    g_signal_connect(info->button1,"clicked",G_CALLBACK(update_clipboard), info);
    g_signal_connect(info->spinbutton4,"value-changed",G_CALLBACK(update_spin), info);
    g_signal_connect(info->spinbutton1,"value-changed",G_CALLBACK(update_clipboard_entry), info);
    g_signal_connect(info->spinbutton5,"value-changed",G_CALLBACK(update_clipboard_entry), info);
    //g_signal_connect(info->eventbox1,"button-press-event",G_CALLBACK(entries_clear), info);
    g_signal_connect(info->imagemenuitem4,"activate",G_CALLBACK(save_menu), info);
    //g_signal_connect(info->imagemenuitem3,"activate",G_CALLBACK(save_menu), info);


    
//Execução
    gtk_main();
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
    return 0;  
	}

int gerar(Tfractal *info, int cont_frac){
	srand(time(NULL));	
	clock_t tic = clock();
	char **mat, seed=0;
	int lin=info->linhas, qntPt=info->qntParticulas; 
	int i, j, semente_x, semente_y, seed_place=0, ang, r_lan=2, kill=5, agrRad=0, k=0, x, y, v, particulas, agr=1, teste=0, agregado=0, r_max=r_lan+kill+teste, meio_lin;
	
	int r_lan_prop = info->rlanc;
	float kill_prop = info->rmort/100;


//Alocando e inicializando matriz				
    mat = malloc((lin) * sizeof(char *));

    if(mat == NULL){
        free(mat);
        return 1;
    }

    for(i=0; i<lin; i++){
        mat[i] = malloc((lin) * sizeof(char));
        if(mat[i] == NULL){
            printf("ERRO");
            for(j=0;j<=i;j++)
                free(mat[j]);
            free(mat);
            return 1;
        }
    }

    for(i=0;i<lin;i++)
    	for(j=0;j<lin;j++)
    		mat[i][j] = 252;

//Posicionando Semente

    //if (lin/2!=0){
        mat[lin/2][lin/2] = seed; semente_x=semente_y=(lin/2);
    //}
	/*else
        seed_place = rand()%4;

        switch (seed_place){
            case 0:
                mat[lin/2][lin/2] = seed; semente_x=semente_y=lin/2;
                break;
            case 1:
                mat[lin/2][lin/2-1] = seed; semente_x=lin/2;semente_y=lin/2-1;
                break;
            case 2:
                mat[lin/2-1][lin/2] = seed;semente_x=lin/2-1;semente_y=lin/2;
                break;
            case 3:
                mat[lin/2-1][lin/2-1] = seed;semente_x=semente_y=lin/2-1;
                break;

    	}*/

        mat[semente_x-1][semente_y] = mat[semente_x+1][semente_y] = mat[semente_x][semente_y-1] = mat[semente_x][semente_y+1] = 2;
//---------------------------------------------FIM--semente-------------------------------------------------------------

//Tabela de Distâncias
	int **dist;
	dist = malloc(lin*sizeof(int *));
    
    for(i=0;i<lin;i++){
    	dist[i] = malloc(lin*sizeof(i));
    }

    k=0;
    v=lin/2;

    for(k=0;k<lin/2+1;k++){
        for(i=k;i<lin-k;i++){
            for(j=k;j<lin-k;j++){
                dist[i][j]=v;
            }
        }
        v--;
    }

//Tabela de Seno/Cos
    float randsin[361], randcos[361];
	for (i = 0; i < 361; i++)
	{
		randsin[i]=sin(i);
		randcos[i]=cos(i);
	}

//---------------------------------------------agregado-----------------------------------------------------------------
k=0;
v=lin/2*.95;

	while(qntPt){

//Lançando partículas
		ang = rand()%361;
        i = (int) semente_x + (r_lan * randcos[ang]); // ponto x
        j = (int) semente_y + (r_lan * randsin[ang]); // ponto y
        agr=1;
        
        if(mat[i][j] == 0){
	        	agr=0;
		      
	    }

		while(agr){
			switch (rand()%4){//escolhe o lado

		        case 0:
		            --i;
		            break;
		        case 1:
		            ++i;
		            break;
		        case 2:
		            --j;
		            break;
		        case 3:
		            ++j;
		            break;
	        }
	        
	      	if (mat[i][j] & 2){
	      		agr = seed; //printf("\n%d", k++);// printf("------%d", kill);printf("------%d", teste);
	      		qntPt--;
	      		mat[i][j] = seed;
	      		if (mat[i+1][j] != seed)
	      			mat[i+1][j]= 2;
	      		if (mat[i-1][j] != seed)
	      			mat[i-1][j]= 2;
	      		if (mat[i][j+1] != seed)
	      			mat[i][j+1]= 2;
	      		if (mat[i][j-1] != seed)
	      			mat[i][j-1]= 2;
			
				agregado = dist[i][j];
	      		if ((kill < (lin/2)*.95)){
				
						if(agregado>agrRad){
							agrRad=agregado;
							r_lan=agregado+r_lan_prop;
							kill = r_lan*kill_prop;
							
						}
				}
				else{
					kill = (lin/2)*.97;
					if(agregado>agrRad && r_lan<kill){
							agrRad=agregado;
							r_lan=agregado+r_lan_prop;
					}else if(r_lan > kill*0.90){
							r_lan = kill*0.90;
					}
				}

	      	}else if(dist[i][j] > kill)
            	agr = 0; 
		}
	}

   	for(i=0;i<lin;i++)
		for(j=0;j<lin;j++){
    		if(mat[i][j] == 2)
                mat[i][j] = 252;
    }

    FILE *fp;
    char filename[128];//cont_frac
    sprintf(filename, "img0%d.png", info->cont_frac);
    char *title = "titulo fractal";
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep row;

    // Open file for writing (binary mode)
    fp = fopen(filename, "wb");
    if (fp == NULL) {
    fprintf(stderr, "Could not open file %s for writing\n", filename);
    return 1;
    }

    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
    fprintf(stderr, "Could not allocate write struct\n");
    return 1;
    }

    // Initialize info structure
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
    fprintf(stderr, "Could not allocate info struct\n");
    return 1;
    }

    // Setup Exception handling
    if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "Error during png creation\n");
    return 1;
    }

    png_init_io(png_ptr, fp);

    // Write header (8 bit colour depth)
    png_set_IHDR(png_ptr, info_ptr, lin, lin,
    8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

   // Set title
    if (title != NULL) {
    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Title";
    title_text.text = title;
    png_set_text(png_ptr, info_ptr, &title_text, 1);
    }

    png_write_info(png_ptr, info_ptr);

    // Write image data

    for (x=0; x<lin; x++) {
	    row = mat[x];
	    png_write_row(png_ptr, row);
    //free(row);
    }

    // End write
    png_write_end(png_ptr, NULL);

    if (fp != NULL) fclose(fp);
    if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    //if (row != NULL) free(row);

//-------------------------------------png--------------------------------------------------------------------------------------

			    for(i=0;i<lin;i++)
			    	free(mat[i]);
			    free(mat);

	clock_t toc = clock();
	info->tempo[info->cont_frac] = ((double)toc - tic) / CLOCKS_PER_SEC;
	printf("%f\n", info->tempo[info->cont_frac]);		    
	return 0;

	}


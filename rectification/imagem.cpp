#include <q3scrollview.h>
#include <qimage.h>
#include <qwidget.h>
#include <qstring.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include <stdio.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include "imagem.h"
#include "form1.h"
#include "form2.h"

extern Form1 *form1; 
extern Form2 *form2; 
 
Imagem::Imagem(int orids)
{ 
  // Construtor da classe imagem
 figura = new QImage(1,1,8,256); // Cria imagem vazia de 1x1
 setGeometry(0,0,1,1);
 setBackgroundMode(Qt::NoBackground);
 setMouseTracking(1);
 zeroPontos(0); 
 pix = new QPixmap;
 orides=orids;
}

void Imagem::zeroPontos(int inicio)
{
    for (int i=inicio; i<20; i++)
    {
         pontos[i][0]=0;
         pontos[i][1]=0;
         pontos[i][2]=0;
    }
}

void Imagem::openImage(QString arquivo)
{ 
  if (!figura->load(arquivo))
      printf("Image could not be loaded!\n");
  this->setGeometry(0,0,figura->width(),figura->height());
  fixImageDepth();
  pix->convertFromImage(*figura, QPixmap::Auto );
}

void Imagem::fixImageDepth()
{
	if (figura->depth()<32)
	{
		QImage *oldPicture;
		oldPicture = figura;
		*figura = figura->convertDepth(32,Qt::AutoColor);
//		delete oldPicture;
	}
}

void Imagem::saveImage(QString arquivo)
{     
  if (!figura->save(arquivo,"BMP"))
      printf("Error while saving!\n");
}

void Imagem::paintEvent(QPaintEvent *e)
{   
     // Desenha as marcas        
     QPixmap *pix = new QPixmap;
     pix->convertFromImage(*figura, QPixmap::Auto );   
     QPainter paint; 
     QBrush brush( Qt::yellow, Qt::NoBrush );
     QPen yellow(Qt::yellow,1,Qt::SolidLine);
     QPen red(Qt::red,1,Qt::SolidLine);
     paint.begin(pix);
     paint.setBrush( brush );
     int i=0, j;
     // Conta o total de pontos selecionados
     while ((i<21)&&(pontos[i][2]))
         i++;
     //  Desenha o retângulo de ajuda proporcinal
     if ((i>=2)&&(form1->checkBox1->isChecked())&&(orides))
     {
         paint.setPen(red);
         int vr_width=abs(pontos[0][0]-pontos[1][0])+1;
         int vr_height=vr_width*(1/form1->ratioLabel->text().toDouble())+1;
         if (abs(pontos[0][0]-pontos[1][0])<abs(pontos[0][1]-pontos[1][1]))
         {
             vr_height=abs(pontos[0][1]-pontos[1][1])+1;
             vr_width=vr_height*(form1->ratioLabel->text().toDouble())+1;
         }
         int vr_x = pontos[0][0];
         int vr_y = pontos[0][1];
         if (pontos[1][0]<vr_x)
             vr_x=pontos[1][0];
         if (pontos[1][1]<vr_y)
             vr_y=pontos[1][1];
         if ((vr_x)>figura->width()/2)
             vr_width=vr_width*-1;
         if ((vr_y)>figura->height()/2)
             vr_height=vr_height*-1;
         paint.drawRect(vr_x,vr_y,vr_width,vr_height);
     }
     // Desenha os pontos na tela
     paint.setPen(yellow);
     for (j=0; j<i; j++)
     {
          paint.drawPoint(pontos[j][0],pontos[j][1]);
          paint.drawEllipse(pontos[j][0]-6,pontos[j][1]-6,12,12);
          paint.drawText(QPoint(pontos[j][0]-2,pontos[j][1]+20),QString::number(j+1),-1/*,QPainter::Auto*/);
          // Liga os pontos, se selecionado
          if ((j>0)&&(form1->spinReturn(3)))
             paint.drawLine(pontos[j-1][0],pontos[j-1][1],pontos[j][0],pontos[j][1]);
     }
     // Liga os últimos pontos
     if ((i>2)&&(form1->spinReturn(3)))
         paint.drawLine(pontos[i-1][0],pontos[i-1][1],pontos[0][0],pontos[0][1]);
     paint.end();
     bitBlt(this,0,0,pix);
     delete pix; 
}

void Imagem::mouseMoveEvent(QMouseEvent *e)
{ 
 // Informa as coordenadas
 if ((e->x()>=0)&&(e->y()>=0)&&(e->x()<figura->width())&&(e->y()<figura->height()))
 {
    form1->coluna->setText(QString::number(e->x()));
    form1->linha->setText(QString::number(e->y()));
 }
 drawZoom(e->x(),e->y());
}

void Imagem::drawZoom(int x, int y)
{
 // Desenha o zoom
 QPixmap *pix = new QPixmap(20,20);
 //bitBlt(pix,0,0,this,x-10,y-10,20,20);
 QPainter paint;
 QBrush brush( Qt::yellow, Qt::SolidPattern );
 QBrush bgbrush( Qt::green, Qt::SolidPattern );
 paint.begin(pix);
 // Imagem
 paint.drawImage(0,0,*figura,x-10,y-10,20,20);
 // Bordas
 if (x-10<0)
   paint.fillRect(0,0,10-x,20,bgbrush);
 if (y-10<0)
   paint.fillRect(0,0,20,10-y,bgbrush);
 if (x+9>figura->width()-1)
   paint.fillRect(19,0,(figura->width()-1)-x-9,20,bgbrush);
 if (y+9>figura->height()-1)
   paint.fillRect(0,19,20,(figura->height()-1)-y-9,bgbrush);
 // Desenha ponto central
 paint.fillRect(10,10,1,1,brush);
 paint.end();
 // Copia do buffer para o Label
 form1->zoomLabel->setPixmap(*pix);
 delete pix;
}

void Imagem::mousePressEvent(QMouseEvent *e)
{
 int pt = form1->spinReturn(0)-1;
 if ((pt>0)&&(!pontos[pt-1][2]))
 {    
     QMessageBox::warning( this, "Warning:",
        "You must select points in sequence !\n\n ",
        "Ok",
        0);
     return;
 }
 pontos[pt][0]=e->x();
 pontos[pt][1]=e->y();
 pontos[pt][2]=1; 
 repaint();
 drawZoom(e->x(),e->y());
 form1->recebePontos(e->x(),e->y());
}

void Imagem::imageInfo(int enable)
{
    // Largura, altura, enabled    
    form1->dadosImagem(figura->width(),figura->height(),enable);
    form1->varLarguraLabel->setText("(0-"+QString::number(figura->width()-1)+")");
    form1->varAlturaLabel->setText("(0-"+QString::number(figura->height()-1)+")");
}

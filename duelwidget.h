#ifndef __DUEL_WIDGET_H
#define __DUEL_WIDGET_H

#include <qwidget.h>
#include <kconfig.h>
#include "playerinfo.h"
#include "mainview.h"

class DuelWidget:public QWidget
{
   Q_OBJECT
public:
   DuelWidget(QWidget *parent=0,const char *name=0);
   void readConfig(KConfig *cfg);
public slots:
   void newGame();
   void newRound();
   void keySetup();
   void pause();
   void aiSetup();
   void hitpointSetup();
   void graphicSetup();
   void gameSetup();
   void writeConfig();

   void energy(int pn,int en);
   void hitPoints(int pn,int hp);
   void wins(int pn,int w);
signals:   
   void setStatusText(const char* str,int id);
private:
   MyMainView *playfield;
   PlayerInfo *playerinfo[2];
};

#endif

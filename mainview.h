#ifndef __MY_MAIN_VIEW_H
#define __MY_MAIN_VIEW_H

#include <qwidget.h>
#include <qimage.h>
#include <kconfig.h>
#include <krandomsequence.h>
#include "sprites.h"
#include "dialogs.h"
#include "ai.h"

#ifdef sun
#undef sun
#endif

class MyMainView:public QWidget
{
   Q_OBJECT
public:
   MyMainView(QWidget *parent=0, const char *name=0);
   ~MyMainView();
   void readConfig(KConfig *cfg);
   
public slots:   
   void newRound();
   void newGame();
   void pause();
   void resume();
   void gameSetup();
   void keySetup();
   void writeConfig();
   void aiSetup();
   void hitpointSetup();
   void graphicSetup();
signals:
   void hitPoints(int pn,int hp);
   void energy(int pn,int en);
   void wins(int pn,int w);
   void setStatusText(const char* str,int id);
   
protected:
   virtual void resizeEvent(QResizeEvent *event);
   virtual void timerEvent(QTimerEvent *event);
   virtual void keyPressEvent(QKeyEvent *event);
   virtual void keyReleaseEvent(QKeyEvent *event);
   SConfig modifyConfig(SConfig conf);
   QCanvasPixmapArray* loadOldPixmapSequence(const QString& datapattern,
                           const QString& maskpattern, int framecount=1);
   void moveShips();
   void moveBullets();
   void moveMines();
   void moveExplosions();
   void calculatePowerups();
   void collisions();
private:
   QCanvas field;
   QCanvasView view;
   
   SOptions options;
   SConfig customConfig,config;

   int timerID;
   bool playerKeyPressed[2][PlayerKeyNum];
   bool functionKeyPressed[FunctionKeyNum];
   bool bulletShot[2];
   bool minePut[2];
   bool waitForStart;
   double gameEnd;
   double timeToNextPowerup;
   
// sprites
   QList<QImage> shipImages;
   QList<QPoint> points;
   QImage bulletImage;
   QCanvasPixmapArray *bulletsequence[2];
   QCanvasPixmapArray *shipsequence[2];
   QCanvasPixmapArray *explosionsequence;
   QCanvasPixmapArray *minesequence[2];
   QCanvasPixmapArray *mineexplosionsequence;
   QCanvasPixmapArray *powerupsequence[PowerupSprite::PowerupNum];
   

   ShipSprite *ship[2];
   SunSprite *sun;
   QCanvasText *textSprite;
   QList<BulletSprite> *bullets[2];
   QList<MineSprite> *mines[2];
   QList<ExplosionSprite> explosions;
   QList<PowerupSprite> powerups;

   KRandomSequence random;

//Ai
   Ai *ai[2];
   
   
};



#endif

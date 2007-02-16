/* Copyright (C) 1998-2001 Andreas Zehender <az@azweb.de>

This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __SPRITE_BASE_H
#define __SPRITE_BASE_H

#include <QGraphicsSvgItem>
class QGraphicsScene;

//#include "defines.h"
#include "spritebase.h"
#include "structs.h"

class SimpleSprite: public QGraphicsSvgItem
{
   public:
      int width();
      int height();
      QPointF center();
   protected:
      void init();

    private:
      int m_width;
      int m_height;
      QPointF m_center;
   protected:
      SimpleSprite(QSvgRenderer* svg, const QString& element);
};

class MobileSprite:public SimpleSprite
{
public:
   MobileSprite(QSvgRenderer* svg, const QString&, int pn);

   virtual void forward(double mult,int frame);
   virtual void forward(double mult);
   virtual void calculateGravity(double gravity,double mult);
   int spriteFieldWidth();
   int spriteFieldHeight();
   double xVelocity(){return xvel;}
   double yVelocity(){return yvel;}
   void setVelocity(double vx, double vy);
   AiSprite toAiSprite();

   bool isStopped() {return stopped;}
   void stop(bool s=true) {stopped=s;}
   int getPlayerNumber() {return playerNumber;}
protected:
   void checkBounds();
   bool stopped;
   int playerNumber;
   double xvel;
   double yvel;
};

class AnimatedSprite:public MobileSprite
{
public:
   explicit AnimatedSprite(QSvgRenderer* svg, const QList<QString> &animation, int pn=0);

   void setFrame(int frame);
   inline int frame() const
   { return currentFrame; }
   inline int frameCount() const
   { return frames.size(); }
   inline QString element(int frame) const
   { return frames.isEmpty() ? QString() : frames.at(frame % frames.size()); }
   QPainterPath shape() const;
   void setAnimation(const QList<QString> &animation);

   void advance(int phase);

private:
   int currentFrame;
   QList<QString> frames;
};

#endif

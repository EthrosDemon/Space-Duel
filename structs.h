#ifndef __SP_STRUCTS_H
#define __SP_STRUCTS_H

enum Difficulty {DTRAINEE=0,DNORMAL,DHARD,DINSANE,DNUM};

struct SOptions
{
   double timeAfterKill;
   int playerKey[2][PlayerKeyNum];
   int functionKey[FunctionKeyNum];
   unsigned refreshTime,startHitPoints[2],lastConfig;
   bool isAi[2];
   Difficulty aiDifficulty[2];
};

struct SConfig
{
   double gamespeed,gravity,acc,energyNeed,sunEnergy,rotationSpeed,
      mineActivateTime,mineFuel,shotSpeed,shotEnergyNeed,mineEnergyNeed,
      rotationEnergyNeed,startPosX,startPosY,startVelX,startVelY,
      bulletLifeTime,mineReloadTime,bulletReloadTime;
   unsigned bulletDamage,shipDamage,mineDamage,maxBullets,maxMines;
};
#define predefinedConfigNum 4
const SConfig predefinedConfig[]={{1.0, 2200.0, 0.2, 1.0, 9000.0, 1.0,
                                   15.0, 65.0, 3.0, 10.0, 5.0,
                                   0.2, -130.0, -100.0, 3.0, -1.7,
                                   500.0,10.0,10.0,
                                   20, 50, 30, 5, 3},
                                  {1.0, 2200.0, 0.2, 1.0, 9000.0, 1.0,
                                   15.0, 40.0, 5.0, 20.0, 10.0,
                                   0.2, -50.0, -150.0, 3.5, 0.9,
                                   500.0,10.0,10.0,
                                   20, 50, 30, 6, 2},
                                  {1.3, 2200.0, 0.2, 1.0, 13000.0, 1.0,
                                   15.0, 50.0, 4.0, 10.0, 10.0,
                                   0.2, -50.0, -150.0, 3.2, -0.9,
                                   500.0,10.0,10.0,
                                   20, 50, 30, 7, 5},
                                  {1.0, 2200.0, 0.2, 1.0, 9000.0, 1.0,
                                   15.0, 40.0, 5.0, 60.0, 50.0,
                                   0.4, -50.0, -170.0, 3.0, -0.5,
                                   500.0,10.0,10.0,
                                   20, 50, 30, 5, 3}};
const char predefinedConfigName[predefinedConfigNum][15]=
{"Default","Bullet","Chaos","Lack of energy"}; 

#endif

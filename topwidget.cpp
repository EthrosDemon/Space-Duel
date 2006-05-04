#include <klocale.h>

#include <kkeydialog.h>
#include <kaction.h>
#include <kstdgameaction.h>
#include <qlayout.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QBoxLayout>
#include <kstatusbar.h>

#include "topwidget.h"
#include "mainview.h"
#include "playerinfo.h"

MyTopLevelWidget::MyTopLevelWidget()
{
   initGameWidgets();
   initStatusBar( );
   initActions( );
   setupGUI( );
}

void MyTopLevelWidget::initGameWidgets( ){
   QWidget *w = new QWidget(this);

   playerinfo[0]=new PlayerInfo(0,w);
   playerinfo[1]=new PlayerInfo(1,w);
   playfield=new MyMainView(w);

   QBoxLayout *toplayout=new QHBoxLayout(w);
   toplayout->addWidget(playerinfo[0]);
   toplayout->addWidget(playfield);
   toplayout->addWidget(playerinfo[1]);
   toplayout->activate();

   playfield->setFocusPolicy(Qt::StrongFocus);
   playfield->setFocus();

   QObject::connect(playfield,SIGNAL(energy(int,int)),
                    SLOT(energy(int,int)));
   QObject::connect(playfield,SIGNAL(hitPoints(int,int)),
                    SLOT(hitPoints(int,int)));
   QObject::connect(playfield,SIGNAL(wins(int,int)),SLOT(wins(int,int)));
   QObject::connect(playfield,SIGNAL(setStatusText(const QString &,int)),
                    SLOT(setStatusText(const QString &,int)));

   setCentralWidget(w);
}

void MyTopLevelWidget::energy(int pn,int en)
{
   playerinfo[pn]->setEnergy(en);
}

void MyTopLevelWidget::hitPoints(int pn,int hp)
{
   playerinfo[pn]->setHitpoints(hp);
}

void MyTopLevelWidget::wins(int pn,int w)
{
   playerinfo[pn]->setWins(w);
}

void MyTopLevelWidget::initActions( )
{
   KStdGameAction::quit(this, SLOT(close()), actionCollection());
   KStdGameAction::gameNew(playfield, SLOT(newGame()), actionCollection());
   ( void )new KAction( i18n( "&New Round" ), "spnewround",
                        Qt::CTRL + Qt::Key_N, playfield, SLOT( newRound( ) ),
                        actionCollection( ), "new_round" );
   MyMainView::pauseAction =
       KStdGameAction::pause(playfield, SLOT(togglePause()), actionCollection());
   MyMainView::pauseAction->setChecked( false );
   KAction *gameStart = new KAction( i18n( "Start" ), actionCollection( ), "game_start" );
   connect(gameStart, SIGNAL(triggered(bool) ), playfield, SLOT( start( ) ));
   gameStart->setShortcut(GAME_START_SHORTCUT);

   KStdAction::preferences(playfield, SLOT(gameSetup()), actionCollection());

   // Default keys
#warning assuming this is not neccessary anymore
   // actionCollection()->setAutoConnectShortcuts(false);
   KAction* ac;
   ac = new KAction(i18n("Player 1 Rotate Left"), Qt::Key_S, 0, 0,
		    actionCollection(), "P1KeyLeft");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 1 Rotate Right"), Qt::Key_F, 0, 0,
		     actionCollection(), "P1KeyRight");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 1 Accelerate"), Qt::Key_E, 0, 0,
		    actionCollection(), "P1KeyAcc");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 1 Shot"), Qt::Key_D, 0, 0,
		    actionCollection(), "P1Shot");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 1 Mine"), Qt::Key_A, 0, 0,
		    actionCollection(), "P1Mine");
   ac->setEnabled( false );

   ac = new KAction(i18n("Player 2 Rotate Left"), Qt::Key_Left, 0, 0,
		    actionCollection(), "P2KeyLeft");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 2 Rotate Right"), Qt::Key_Right, 0, 0,
		    actionCollection(), "P2KeyRight");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 2 Accelerate"), Qt::Key_Up, 0, 0,
		    actionCollection(), "P2KeyAcc");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 2 Shot"), Qt::Key_Down, 0, 0,
		    actionCollection(), "P2Shot");
   ac->setEnabled( false );
   ac = new KAction(i18n("Player 2 Mine"), Qt::Key_Insert, 0, 0,
		    actionCollection(), "P2Mine");
   ac->setEnabled( false );

   // actionCollection()->setAutoConnectShortcuts(true);
   playfield->setActionCollection(actionCollection());
}

void MyTopLevelWidget::initStatusBar( )
{
   statusBar( )->insertItem(i18n(" paused "),IDS_PAUSE,1);
   statusBar( )->insertItem("   ",IDS_MAIN,1);
   statusBar( )->insertItem("",42,2);
}

void MyTopLevelWidget::start()
{
   playfield->newGame();
   playfield->newRound();
}

void MyTopLevelWidget::setStatusText(const QString & str,int id)
{
   statusBar( )->changeItem(str,id);
}

void MyTopLevelWidget::keySetup()
{
   playfield->pause();
   KKeyDialog::configure( actionCollection( ), KKeyChooser::LetterShortcutsAllowed, this, true );
}

#include "topwidget.moc"

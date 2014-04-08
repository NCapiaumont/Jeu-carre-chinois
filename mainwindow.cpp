#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emplacement.h"
#include <QStatusBar>
#include <QTimer>
#include <QInputDialog>
#include <QDebug>
#include <help.h>
#include <ui_help.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixmapEmptyEmplacement=QPixmap(":images/emptyEmplacement");
    qsrand(time(NULL));
    joueurHumain=new joueur("0","rouge",this);
    ui->horizontalLayoutJoueurs->addStretch();
    ui->horizontalLayoutJoueurs->addWidget(joueurHumain);
    ui->horizontalLayoutJoueurs->addStretch();
    joueurOrdi=new joueur("+","bleu",this);
    ui->horizontalLayoutJoueurs->addWidget(joueurOrdi);
    ui->horizontalLayoutJoueurs->addStretch();
    for(int noLigne=0;noLigne<3;noLigne++)
    {
        for (int noCol=0;noCol<3;noCol++)
        {
            tabEmplacement[noLigne][noCol]=new emplacement(this,".",this);
            tabEmplacement[noLigne][noCol]->ligne=noLigne;
            tabEmplacement[noLigne][noCol]->col=noCol;
            ui->gridLayoutJeu->addWidget(tabEmplacement[noLigne][noCol],noLigne,noCol);
        }
    }
    timerTour=new QTimer(this);
    connect(timerTour,SIGNAL(timeout()),this,SLOT(raffraichirBarreProgression()));
    tirage();
    timerTour->start(1000);
    emplacementDeplace=NULL;
    normal =cursor();
    partieTerminee=false;
    ui->pushButtonNouvellePartie->setEnabled(false);
    //gestion du curseur de souris
#ifdef ANDROID
    labelCurseur=new QLabel("",this);
#endif
}
void MainWindow::setCurseur(QCursor & curseur)
{
    setCursor(curseur);
#ifdef ANDROID
    labelCurseur->setPixmap(curseur.pixmap());
#endif
}
void MainWindow::resetCurseur()
{
    //reprend le curseur de souris
    setCursor(normal);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tirage()
{
    //choisi le joueur qui démarre
    if(qrand()%2==0)
        joueurActif=joueurOrdi;
    else joueurActif=joueurHumain;
    joueurActif->surBrille(true);
}
bool MainWindow::ligne(int no)
{
    //renvoie vrai si la ligne no est remplie
    return(!tabEmplacement[no][0]->estVide() &&
            tabEmplacement[no][0]->leJoueur==tabEmplacement[no][1]->leJoueur &&
            tabEmplacement[no][1]->leJoueur==tabEmplacement[no][2]->leJoueur);
}
bool MainWindow::col(int no)
{
    //renvoie vrai si la colonne no est remplie
    return(!tabEmplacement[0][no]->estVide() &&
            tabEmplacement[0][no]->leJoueur==tabEmplacement[1][no]->leJoueur &&
            tabEmplacement[1][no]->leJoueur==tabEmplacement[2][no]->leJoueur);
}
bool MainWindow::diag(int no)
{
    //deux diagonales: la 0 et la 1 renvoie vrai si une des diagonale est remplie
    if(no==0) return(!tabEmplacement[0][0]->estVide() && tabEmplacement[0][0]->leJoueur==tabEmplacement[1][1]->leJoueur&& tabEmplacement[1][1]->leJoueur==tabEmplacement[2][2]->leJoueur);
    else return(!tabEmplacement[0][2]->estVide() && tabEmplacement[0][2]->leJoueur==tabEmplacement[1][1]->leJoueur&& tabEmplacement[1][1]->leJoueur==tabEmplacement[2][0]->leJoueur);
}

bool MainWindow::dejaGagne(joueur * unJoueur)
{
    //renvoie vrai si un des joueurs a gagné
    bool gagne=ligne(0) || ligne(1) || ligne(2) || col(0) || col(1) || col(2) || diag(0) || diag(1);
    if(gagne)
    {
        statusBar()->showMessage(tr("The player ")+unJoueur->getCouleur() +tr(" has won"));
        partieTerminee=true;
        timerTour->stop();
        ui->pushButtonNouvellePartie->setEnabled(true);
    }
    return(gagne);
}

void MainWindow::changement()
{
    //changement de joueur
    joueurActif->surBrille(false);
    if (joueurActif==joueurOrdi)
    {
        joueurActif=joueurHumain;
    }
    else
    {
        joueurActif=joueurOrdi;
    }
    joueurActif->surBrille(true);
    //on repart de 0
    ui->progressBarTour->setValue(0);
    QString message=tr("The player ")+ joueurActif->getCouleur() +tr(" play.");
    statusBar()->showMessage(message);
}
bool MainWindow::estCoince(emplacement *)
{
    bool resultat=false;
    return resultat;
}
bool MainWindow::accessible(emplacement* e1,emplacement* e2)
{
    //renvoie vrai si e2 est un emplacement correct pour e1
    return e2->estVide()&& e1->jouxte(e2);
}
void MainWindow::initialiseJeu()
{

    joueurHumain->resetJeton();
    joueurOrdi->resetJeton();
    for(int noLigne=0;noLigne<3;noLigne++)
    {
        for (int noCol=0;noCol<3;noCol++)
        {
            tabEmplacement[noLigne][noCol]->vider();
        }
    }
    changement();
    emplacementDeplace=NULL;
    partieTerminee=false;
}
void MainWindow::on_pushButtonNouvellePartie_clicked()
{
    if(partieTerminee)
    {
        initialiseJeu();
        ui->pushButtonNouvellePartie->setEnabled(false);
        statusBar()->showMessage(tr("Let's go"));
    }
}
void MainWindow::on_pushButtonQuitter_clicked()
{
    close();
}
void MainWindow::raffraichirBarreProgression()
{
    //on donne 30 secondes pour chaque tour
    int tempMax=30;
    int progression=ui->progressBarTour->maximum()/tempMax;
    ui->progressBarTour->setValue(ui->progressBarTour->value()+progression);
    //si la progressbar est au maxi le joueur actif a perdu
    if(ui->progressBarTour->value()==ui->progressBarTour->maximum())
    {
        joueur * leGagnant;
        if(joueurActif==joueurHumain)
        {
            leGagnant=joueurOrdi;
        }
        else
        {
            leGagnant=joueurHumain;
        }
        QString message=tr("The player ")+leGagnant->getCouleur() +tr(" has won by timeout");
        statusBar()->showMessage(message);
        partieTerminee=true;
        timerTour->stop();
        ui->pushButtonNouvellePartie->setEnabled(true);
    }
}
void MainWindow::on_action_Quitter_triggered()
{
    this->close();
}
///// DEBUT GESTION RESEAU /////////////////////////////////////////////////////
void MainWindow::on_checkBoxServeur_clicked(bool checked)
{
    if(checked)
    {
        socketServeur=new QTcpServer(this);
        //écoute sur toutes ses interfaces réseau et sur le port 9999
        socketServeur->listen(QHostAddress::Any,9999);
        connect(socketServeur,SIGNAL(newConnection()),this,SLOT(nouvelleConnexion()));
        qDebug()<<"Serveur, écoute sur le port 9999";
    }
    else
    {
        //arrete d'écouter sur le port 9999
        socketServeur->close();
        qDebug()<<"n'écoute plus sur le port 9999";
    }
}
void MainWindow::nouvelleConnexion()
{
    qDebug()<<"nouvelleConnexion";
    laSocketDuClient=socketServeur->nextPendingConnection();
    connect(laSocketDuClient,SIGNAL(readyRead()),this,SLOT(repondreAuClient()));
}
void MainWindow::repondreAuClient()
{
    qDebug()<<"repondreAuClient";
    QString coordonees=laSocketDuClient->readAll();
    ui->label->setText(coordonees);
    //coordonnée du jeton déplacé : ancienX,ancienY,nouveauX,nouveauY
}
void MainWindow::on_action_Connection_r_seau_triggered()
{
    //on va le connecter
    bool ok;
    QString adresseDuServeur=QInputDialog::getText(this,tr("Nice network game"),tr("Server address"),QLineEdit::Normal,"172.16.56.",&ok);
    if(ok)
    {
        laSocketServeur=new QTcpSocket(this);
        laSocketServeur->connectToHost(adresseDuServeur,9999);
        connect(laSocketServeur,SIGNAL(readyRead()),this,SLOT(traiterMessageDuServeur()));
        ui->checkBoxServeur->setEnabled(false);
        ui->checkBoxServeur->setCheckState(Qt::Unchecked);
        qDebug()<<"Creation d'une socket";
    }
}
void MainWindow::traiterMessageDuServeur()
{
    qDebug()<<"traiterMessageDuServeur";
    QString coordonees=laSocketServeur->readAll();
    ui->label->setText(coordonees);
    //coordonnée du jeton déplacé : ancienX,ancienY,nouveauX,nouveauY
}
void MainWindow::on_pushButtonEnvoyer_clicked()
{
    gererNetwork(0,0);
}
void MainWindow::gererNetwork(int noPierre, int noPoint)
{
    QString message;
    if(ui->checkBoxServeur->isChecked())
    {
        message=QString::number(noPierre)+"/"+QString::number(noPoint);
        laSocketDuClient->write(message.toLatin1());
        qDebug()<<"gererNetwork (est serveur)";
    }
    else
    {
        message=QString::number(noPierre)+"/"+QString::number(noPoint);
        laSocketServeur->write(message.toLatin1());
        qDebug()<<"gereNetwork (est client)";
    }
}
/// ////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_action_R_gles_du_jeu_triggered()
{
    //ouvre le popup aide
    help win;
    win.exec();
}
/// ////////////////////////////////////////////////////////////////////////////////

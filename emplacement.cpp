#include "emplacement.h"
#include <QDebug>
#include <QPainter>
#include <QStatusBar>
#include <QMouseEvent>
emplacement::emplacement(MainWindow * maman,QString texte,QWidget *parent) :
    QLabel(parent)
{
    mum=maman;
    leJoueur=NULL;
    setPixmap(mum->pixmapEmptyEmplacement);
}
bool emplacement::estVide()
{
    return leJoueur==NULL;
}
void emplacement::vider()
{
    setPixmap(mum->pixmapEmptyEmplacement);
    leJoueur=NULL;
}
void emplacement::setJoueur(joueur * j)
{
    leJoueur=j;
    if (leJoueur!=NULL)
    {
        setPixmap(*leJoueur->pixmap());
    }
    else
    {
        setPixmap(mum->pixmapEmptyEmplacement);
    }
}
void emplacement::mousePressEvent(QMouseEvent *ev)
{
    if(!mum->partieTerminee)
    {
        //si l'emplacement est vide
        if(estVide())
        {
            //s'il reste des jetons au joueur
            if(mum->joueurActif->getNbJeton()>0)
            {
                setJoueur(mum->joueurActif);
                //diminution du nb de jeton du joueur
                mum->joueurActif->diminueNbJeton();
                //changement de joueur actif si ce n'est pas déjà Gagne
                if(! mum->dejaGagne(mum->joueurActif))
                {
                    mum->changement();
                }
            }
        }
        else //emplacement déjà occupé
        {
            //si c'est le bon joueur
            if(leJoueur==mum->joueurActif)
            {
                //s'il n'est pas coincé
                if(! mum->estCoince(this))
                {
                    //on part sur le déplacer
#ifdef ANDROID
                    mum->labelCurseur->setGeometry(mapToParent(ev->pos()).x(),mapToParent(ev->pos()).y(),32,32);
                    mum->labelCurseur->setVisible(true);

#endif
                    mum->setCurseur(*mum->joueurActif->getSonCurseur("normal"));

                    mum->setEmplacementDeplace(this);
                }
                else mum->statusBar()->showMessage(tr("This jeton is stuck"));
            }
            else mum->statusBar()->showMessage(tr("It's not your jeton"));
        }
    }
}
void emplacement::mouseMoveEvent(QMouseEvent *ev)
{
    if(mum->emplacementDeplace!=NULL)
    {
        //en fonction de l'elt survolé signale une possibilité de relâchement
        QPoint lePointSurvole =mapToParent(ev->pos());
        #ifdef ANDROID
        lePointSurvole.setX(lePointSurvole.x()-1);
        lePointSurvole.setY(lePointSurvole.y()-1);
        #endif
        emplacement* emplacementSurvole=(emplacement *)mum->childAt(lePointSurvole);

        if(emplacementSurvole!=NULL && emplacementSurvole->inherits("emplacement") && emplacementSurvole->estVide() && jouxte(emplacementSurvole))
        {

            mum->setCurseur(*mum->joueurActif->getSonCurseur("ok"));
        }
        else
        {
            mum->setCurseur(*mum->joueurActif->getSonCurseur("normal"));
        }
        #ifdef ANDROID
        mum->labelCurseur->setGeometry(mapToParent(ev->pos()).x(),mapToParent(ev->pos()).y(),32,32);
        #endif
    }
}
void emplacement::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint lePointSurvole =mapToParent(ev->pos());
    #ifdef ANDROID
    lePointSurvole.setX(lePointSurvole.x()-1);
    lePointSurvole.setY(lePointSurvole.y()-1);
    mum->labelCurseur->setVisible(false);
    #endif
    emplacement* emplacementRelache=(emplacement *)mum->childAt(lePointSurvole);

    if(emplacementRelache!=NULL && emplacementRelache->inherits("emplacement") && emplacementRelache->estVide()&& jouxte(emplacementRelache))
    {
        if(mum->emplacementDeplace!=NULL)
        {        
            emplacementRelache->setJoueur(mum->emplacementDeplace->leJoueur);
            mum->emplacementDeplace->vider();
            mum->emplacementDeplace=NULL;
            if(! mum->dejaGagne(mum->joueurActif)) mum->changement();
        }
        else
        {
            mum->statusBar()->showMessage(tr("Location null"));
        }
    }
    //retour au curseur normal
    mum->resetCurseur();
}
bool emplacement::jouxte(emplacement *e)
{
    //renvoie vrai si l'emplacement en cours est à côté de l'emplacement e
    bool resultat;
    resultat=(ligne==e->ligne && abs(col-e->col)==1) ||(col==e->col && abs(ligne-e->ligne)==1)||(abs(col-e->col)==1 && abs(ligne-e->ligne)==1&&((e->ligne==1 && e->col==1)||(col==1 && ligne==1)));
    return resultat;
}

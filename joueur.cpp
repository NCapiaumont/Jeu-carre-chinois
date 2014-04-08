#include "joueur.h"
#include <QPainter>

joueur::joueur(QString l,QString coul,QWidget *parent) :
    QLabel(parent), lettre(l)
{
    setText(l);
    normalStyleSheet=styleSheet();
    nbJeton=3;
    couleur=coul;
    //le curseur normal (rouge ou bleu)
    QPixmap lePixmap(":/images/"+coul);
    setPixmap(lePixmap);
    sonCurseurNormal=new QCursor(lePixmap);
    //le curseur ok
    QPixmap lePixmap2(32,32);
    QPainter monPainter2(&lePixmap2);
    monPainter2.fillRect(lePixmap2.rect(),Qt::green);
    monPainter2.drawPixmap(lePixmap2.rect(),lePixmap);
    sonCurseurOk=new QCursor(lePixmap2);
}
void joueur::surBrille(bool active)
{
    if(active)
    {
        setStyleSheet("background:rgb(133, 255, 52);");
    }
    else
    {
        setStyleSheet(normalStyleSheet);
    }
}
QString joueur::getLettre()
{
    return(lettre);
}
void joueur::setLettre(QString l)
{
    lettre=l;
}

#ifndef JOUEUR_H
#define JOUEUR_H

/*!
 *  \brief     Classe joueur "joueur.h"
 *  \details   Cette classe est la classe joueur
 *  \author    Nicolas Capiaumont
 *  \version   1
 *  \date      06/12/13
 *  \copyright GNU Public License.
 */
#include <QLabel>
/*!
 * \brief The joueur class
 */
class joueur : public QLabel
{
    Q_OBJECT
    /*!
     * \publicsection
     */
public:
    /*!
     * \brief explicit joueur(QString l,QString stringCouleur, QWidget *parent = 0)
     * \param QString l
     * \param QString stringCouleur
     * \param QWidget parent
     */
    explicit joueur(QString l,QString stringCouleur, QWidget *parent = 0);
    /*!
     * \brief void setLettre(QString)
     * \detail change la lettre du joueur
     */
    void setLettre(QString);
    /*!
     * \brief QString getLettre()
     * \return renvoie la lettre
     * \detail renvoie la lettre du joueur
     */
    QString getLettre();
    /*!
     * \brief QCursor* getSonCurseur(QString lequel)
     * \param QString lequel
     * \return renvoie le curseur normal quand il est normal sinon renvoie son curseur ok
     */
    QCursor* getSonCurseur(QString lequel){if(lequel=="normal") return sonCurseurNormal;else return sonCurseurOk;};
    /*!
     * \brief getNbJeton
     * \return renvoie le nombre de jeton
     * \detail revoie le nombre de jeton que le joueur a "dans sa main" (le nombre de jeton qu'il lui reste à poser sur le plateau)
     */
    int getNbJeton(){return nbJeton;};
    /*!
     * \brief void resetJeton()
     * \detail remet le nombre de jeton a 3 aux deux joueurs
     */
    void resetJeton(){nbJeton=3;};
    /*!
     * \brief void diminueNbJeton()
     * \detail diminue le nombre des jetons d'un joueur (au moment ou il le place sur le plateau)
     */
    void diminueNbJeton(){nbJeton--;};
    /*!
     * \brief QString getCouleur()
     * \return renvoie la couleur
     * \detail renvoie la couleur du joueur (bleu ou rouge)
     */
    QString getCouleur(){return couleur;};
signals:

public slots:
    /*!
     * \brief void surBrille(bool active)
     * \param active
     * \detail met une couleur verte sur le joueur actif (au tour du joueur)
     */
    void surBrille(bool active);      
    /*!
    * \privatesection
    */
private:
    /*!
     * \property QString normalStyleSheet
     * \brief QString normalStyleSheet
     */
    QString normalStyleSheet;
    /*!
     * \property int nbJeton
     * \brief int nbJeton
     */
    int nbJeton;
    /*!
     * \property QString lettre
     * \brief QString lettre
     */
    QString lettre;
    /*!
     * \property QCursor* sonCurseurNormal
     * \brief QCursor sonCurseurNormal
     */
    QCursor* sonCurseurNormal;
    /*!
     * \property QCursor* sonCurseurOk
     * \brief QCursor sonCurseurOk
     */
    QCursor* sonCurseurOk;
    /*!
     * \property QString couleur
     * \brief QString couleur
     */
    QString couleur;
};

#endif // JOUEUR_H

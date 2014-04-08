#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H
/*!
 *  \brief     Classe emplacement "emplacement.h"
 *  \details   Cette classe est la classe emplacement
 *  \author    Nicolas Capiaumont
 *  \version   1
 *  \date      06/12/13
 *  \copyright GNU Public License.
 */
#include <QLabel>
#include "mainwindow.h"
#include "joueur.h"
class MainWindow;
/*!
 * \brief The emplacement class
 */
class emplacement : public QLabel
{
    Q_OBJECT
/*!
* \privatesection
*/
private:
    /*!
     * \property MainWindow* mum
     * \brief mum
     */
    MainWindow* mum;
/*!
 * \publicsection
 */
public:
    /*!
     * \brief explicit emplacement(MainWindow * maman,QString texte,QWidget *parent = 0)
     * \param MainWindow maman
     * \param QString texte
     * \param QWidget parent
     */
    explicit emplacement(MainWindow * maman,QString texte,QWidget *parent = 0);
    /*!
     * \property int ligne
     * \brief ligne
     */
    int ligne;
    /*!
     * \property int col
     * \brief col
     */
    int col;
    /*!
     * \property joueur* leJoueur
     * \brief leJoueur
     */
    joueur* leJoueur;
signals:
public slots:
    /*!
      * \brief bool estVide()
      * \return renvoie vrai si l'emplacement est vide
      * \detail indique sur l'emplacement est vide ou non
      */
     bool estVide();
     /*!
      * \brief bool jouxte(emplacement* e)
      * \param emplacement e
      * \return renvoie vrai si l'emplacement en cours est à côté de l'emplacement e
      * \detail indique si l'emplacement est vide a coté du jeton selectionné
      */
     bool jouxte(emplacement* e);
     /*!
      * \brief void setJoueur(joueur*)
      */
     void setJoueur(joueur*);
     /*!
      * \brief void vider()
      * \detail vide tous les emplacement sur le plateau (met les images des emplacements vide (rond noir))
      */
     void vider();
private slots:
     /*!
     * \brief void mousePressEvent(QMouseEvent *ev)
     * \param QMouseEvent ev
     * \detail événement de cliquer sur le un élément
     */
    void mousePressEvent(QMouseEvent *ev);
    /*!
     * \brief void mouseReleaseEvent(QMouseEvent *ev)
     * \param QMouseEvent ev
     * \detail événement de relaver le bouton de la souris
     */
    void mouseReleaseEvent(QMouseEvent *ev);
    /*!
     * \brief void mouseMoveEvent(QMouseEvent *ev)
     * \param QMouseEvent ev
     * \detail événement de bouger la souris
     */
    void mouseMoveEvent(QMouseEvent *ev);
};
#endif // EMPLACEMENT_H

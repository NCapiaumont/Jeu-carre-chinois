#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*!
 *  \brief     Classe MainWindow "mainwindow.h"
 *  \details   Cette classe est la classe mainwindow de notre application jeu en réseau
 *  \author    Nicolas Capiaumont
 *  \version   1.0
 *  \date      06/12/13
 *  \copyright GNU Public License.
 * \todo coder l'envoi du message (socket...)
 * \todo gérer le bouton envoyer(griser ou non en fonction si le jeu est en réseau ou non)
 * \bug ferme l'application à l'appui du bouton envoyer
 */
#include <QMainWindow>
#include "joueur.h"
#include "emplacement.h"
#include <QTcpSocket>
#include <QTcpServer>
namespace Ui {
class MainWindow;
}
class emplacement;
/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    /*!
     *  \publicsection
     */
public:
    /*!
     * \brief MainWindow
     * \param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    //! Le destructeur
    /*!
        Le destructeur détruit l'instance et libère la mémoire allouée dynamiquement
     */
    ~MainWindow();
    /*!
     * \property joueur * joueurActif
     * \brief joueur joueurActif
     * \detail définie le joueur actif
     */
    joueur * joueurActif;
    /*!
     * \brief bool ligne(int no)
     * \param int no
     * \return retourne vrai si la ligne no est pleine
     * \detail ligne sur le plateau de jeu
     */
    bool ligne(int no);
    /*!
     * \brief bool col(int no)
     * \param int no
     * \return retourne vrai si la col no est pleine
     * \detail colonne sur le plateau de jeu
     */
    bool col(int no);
    /*!
     * \brief bool diag(int no)
     * \param int no
     * \return retourne vrai si la diag no est pleine
     * \detail diagonal sur le plateau de jeu
     */
    bool diag(int no);
    /*!
     * \property emplacement* emplacementDeplace
     * \brief emplacement emplacementDeplace
     * \detail l'emplacement du jeton déplacé
     */
    emplacement* emplacementDeplace;
    /*!
     * \brief void setEmplacementDeplace(emplacement* e)
     * \param emplacement e
     * \detail emplacementDeplace prendre la valeur de l'emplacement e
     */
    void setEmplacementDeplace(emplacement* e){emplacementDeplace=e;};
    /*!
     * \brief void resetCurseur()
     * \detail remet le curseur normal
     */
    void resetCurseur();
    /*!
     * \brief bool dejaGagne(joueur * unJoueur)
     * \param unJoueur joueur*
     * \return renvoie vrai si un joueur a déjà gagné
     */
    bool dejaGagne(joueur * unJoueur);
    /*!
     * \brief void changement()
     * \detail change de joueur actif
     */
    void changement();
    /*!
     * \property joueur * joueurHumain
     * \brief joueur joueurHumain
     * \detail création d'un joueur humain (joueur1)
     */
    joueur * joueurHumain;
    /*!
     * \property joueur * joueurOrdi
     * \brief joueur joueurOrdi
     * \detail création d'un joueur ordinateur (joueur2)
     */
    joueur * joueurOrdi;
    /*!
     * \property QPixmap pixmapEmptyEmplacement
     * \brief QPixmap pixmapEmptyEmplacement
     * \detail définie les emplacement vide sur le plateau (image rond noir)
     */
    QPixmap pixmapEmptyEmplacement;
    /*!
     * \brief bool partieTerminee
     * \detail renvoie vrai quand une partie est terminée
     */
    bool partieTerminee;
    /*!
     * \property QTimer * timerTour
     * \brief timerTour
     * \detail temps du tour, 30 secondes par tour par personne
     */
    QTimer * timerTour;
#ifdef ANDROID
    /*!
     * \brief QLabel* labelCurseur
     * \detail QLabel pour le curseur sur android
     */
    QLabel* labelCurseur;
#endif
    /*!
    * \privatesection
    */
private:
    /*!
     * \brief Ui::MainWindow *ui
     */
    Ui::MainWindow *ui;
    /*!
     * \brief void tirage()
     * \detail permet de choisir le joueur qui commence (aléatoirement)
     */
    void tirage();
    /*!
     * \property QCursor normal
     * \brief normal
     * \detail définie le QCursor en normal
     */
    QCursor normal;
    /*!
     * \property emplacement*  tabEmplacement[3][3]
     * \brief tabEmplacement
     * \detail création d'un tableau 3x3 pour chaques cases du plateau
     */
    emplacement*  tabEmplacement[3][3];
    /*!
     * \property QTcpServer * socketServeur
     * \brief socketServeur
     * \detail la socket qui est serveur
     */
    QTcpServer * socketServeur;
    /*!
     * \property QTcpSocket * laSocketDuClient
     * \brief laSocketDuClient
     * \detail La socket du coté du client
     */
    QTcpSocket * laSocketDuClient;
    /*!
     * \property QTcpSocket * laSocketServeur
     * \brief laSocketServeur
     * \detail La socket du coté du serveur
     */
    QTcpSocket * laSocketServeur;
public slots:
    /*!
     * \brief bool estCoince(emplacement*)
     * \param emplacement* l'emplacement du jeton selectionné
     * \return renvoie faux
     */
    bool estCoince(emplacement*);
    /*!
     * \brief bool accessible(emplacement* e1,emplacement* e2)
     * \param e1 : emplacement inital du jeton
     * \param e2 : emplacement destination du jeton
     * \return renvoie vrai si l'emplacement (e2) est accessible pour le jeton selectionné qui était en (e1)
     */
    bool accessible(emplacement* e1,emplacement* e2);
    /*!
     * \brief void setCurseur(QCursor & cuseur)
     * \param QCursor cuseur
     */
    void setCurseur(QCursor & cuseur);
private slots:
    /*!
     * \brief void raffraichirBarreProgression()
     * \detail réinitialise la barre de progression a 0% et met le temps maximum à 30 seconde
     */
    void raffraichirBarreProgression();
    /*!
     * \brief void on_pushButtonNouvellePartie_clicked()
     * \detail crée une nouvelle partie quand une partie est terminé
     */
    void on_pushButtonNouvellePartie_clicked();
    /*!
     * \brief void initialiseJeu()
     * \detail initialise le jeu en donnant 3 jetons au deux joueurs
     */
    void initialiseJeu();
    /*!
     * \brief void on_pushButtonQuitter_clicked()
     * \detail quitte l'application (ferme toutes les fenetres)
     */
    void on_pushButtonQuitter_clicked();
    /*!
     * \brief void on_action_Quitter_triggered()
     * \detail quitte l'application (ferme toutes les fenetres)
     */
    void on_action_Quitter_triggered();
    /*!
     * \brief void on_checkBoxServeur_clicked(bool checked)
     * \param bool checked
     * \detail permet d'être le serveur (écoute sur le port 9999) 0 : client, 1 : serveur
     */
    void on_checkBoxServeur_clicked(bool checked);
    /*!
     * \brief void on_action_Connection_r_seau_triggered()
     * \detail permet de créer une socket et de contacter un serveur
     */
    void on_action_Connection_r_seau_triggered();
    /*!
     * \brief void nouvelleConnexion()
     * \detail connecte le socket au serveur
     */
    void nouvelleConnexion();
    /*!
     * \brief void repondreAuClient()
     * \detail écrit et envoie les coordonnées du jeton déplacé : ancienX,ancienY,nouveauX,nouveauY (serveur -> client)
     */
    void repondreAuClient();
    /*!
     * \brief void traiterMessageDuServeur()
     * \detail lis les coordonnées du jeton déplacé : ancienX,ancienY,nouveauX,nouveauY (du coté du client)
     */
    void traiterMessageDuServeur();
    /*!
     * \brief void on_pushButtonEnvoyer_clicked()
     * \detail permet d'envoyer un message à l'adversaire (en réseau)
     */
    void on_pushButtonEnvoyer_clicked();
    /*!
     * \brief void gererNetwork(int noPierre, int noPoint)
     * \param int noPierre
     * \param int noPoint
     */
    void gererNetwork(int noPierre, int noPoint);
    /*!
     * \brief void on_action_R_gles_du_jeu_triggered()
     * \detail affiche les règles du jeu
     */
    void on_action_R_gles_du_jeu_triggered();
};
#endif // MAINWINDOW_H

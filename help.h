#ifndef HELP_H
#define HELP_H
/*!
 *  \brief     Classe help "help.h"
 *  \details   Cette classe est la classe help elle permet d'afficher les règles du jeu
 *  \author    Nicolas Capiaumont
 *  \version   1
 *  \date      06/12/13
 *  \copyright GNU Public License.
 */
#include <QDialog>
#include <ui_help.h>
namespace Ui {
class help;
}
/*!
 * \brief The help class
 */
class help : public QDialog
{
    Q_OBJECT
    /*!
     * \publicsection
     */
public:
    explicit help(QWidget *parent = 0);
    //! Le destructeur
    /*!
        Le destructeur détruit l'instance et libère la mémoire allouée dynamiquement
    */
    ~help();
private slots:
    /*!
     * \brief void on_pushButtonOk_clicked()
     * \detail ferme la fenetre avec les règles du jeu
     */
    void on_pushButtonOk_clicked();
    /*!
    * \privatesection
    */
private:
    /*!
     * \brief Ui::help *ui
     */
    Ui::help *ui;
};
#endif // HELP_H

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.UI;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ElectionComunautaire
{
    /// <summary>
    /// Logique d'interaction pour Page1.xaml
    /// </summary>
    public partial class Page1: System.Windows.Controls.UserControl
    {
        //quelques variables
        MainWindow win;
        public int elem;

        public string name;
        public int nbVotesI = 0;
        public float percentI = 0;

        public bool checkedflag = false;
        
        // initialisation d'une personne
        public Page1(string _name, MainWindow _win, bool _SetColor, bool disabledel, bool disableactive)
        {
            name = _name;
            win = _win;
            InitializeComponent();

            if (_SetColor)
                StackPannel.Background = new SolidColorBrush(Color.FromRgb(200, 200, 200));

            if (disabledel)
                destroyer.IsEnabled = false;

            if (disableactive)
                check.IsEnabled = false;
            else
                check.IsChecked = true;
            Persone.Text = name;
            nbVotes.Text = nbVotesI.ToString();
            percent.Text = percentI.ToString("n2") + " %";
        }

        //systeme envoy de data
        private void send_data(int _elem)
        {
            elem = _elem;
        }

        /* ==== made by the page ==== */

        // auto destruction (comme le bouton de destruction ce trouve sur lui en personne il doit s auto detruire)
        private void self_Destroy(object sender, RoutedEventArgs e)
        {
            MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Êtes-vous sûr ?", "Confirmation ", System.Windows.MessageBoxButton.YesNo);
            if (messageBoxResult == MessageBoxResult.Yes)
                win.Del_personne(elem);
            else
                return;
        }

        //demander ♪ ♫ + ♪ + ♫ a votre assurance (♫ slogant ♪♪) ajouter une voie
        private void Add_value(object sender, RoutedEventArgs e)
        {
            nbVotesI++;
            nbVotes.Text = nbVotesI.ToString();
            win.update(@"c:\temp\IPC.ipc");
        }

        //suprimer une voie
        private void Sub_Value(object sender, RoutedEventArgs e)
        {
            if(nbVotesI > 0)
            {
                nbVotesI--;
                nbVotes.Text = nbVotesI.ToString();
                win.update(@"c:\temp\IPC.ipc");
            }
        }

        // en cas d'appuis sur une boite a check $$
        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            checkedflag = true;
            win.update(@"c:\temp\IPC.ipc");
        }

        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            checkedflag = false;
            win.update(@"c:\temp\IPC.ipc");
        }

        // call by the main window

        // permet de changer le font pour avoir une ligne sur deux plus grizer
        public void setBackGround(bool setter) 
        {
            if (setter)
                StackPannel.Background = new SolidColorBrush(Color.FromRgb(200, 200, 200));
            else
                StackPannel.Background = new SolidColorBrush(Color.FromRgb(255, 255, 255));
        }

        // ecrit le porcentage
        public void setNbPercent(float _percent)
        {
            percentI = _percent;
            percent.Text = percentI.ToString("n2") + " %";
        }

        //recupere  le nombre de vote
        public int getNbVotes()
        {
            return nbVotesI;
        }

        //reset 
                //-- "Capitaine Obvious 2020"
        public void reset()
        {
            nbVotesI = 0;
            percentI = 0;
            var last_flag = checkedflag;
            checkedflag = false;
            win.update(@"c:\temp\IPC.ipc");
            nbVotes.Text = nbVotesI.ToString();
            checkedflag = last_flag;
        }

        // toto teubdate
        public void selfUpdate(int TotalVotes)
        {
            if (TotalVotes != 0 && getNbVotes() != 0 && !checkedflag)
                setNbPercent(((float)getNbVotes() / (float)TotalVotes) * 100);
            else
                setNbPercent(0);
        }

        // appeler pour la generation du protocole
        public string Protocole()
        {
            string ret = ";" + name + ";" + percent.Text + ";" + nbVotes.Text;
            return ret;
        }
    }
}

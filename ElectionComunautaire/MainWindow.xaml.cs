using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System;
using System.IO;
using System.Text;
using System.Windows;
using Microsoft.Win32;

namespace ElectionComunautaire
{

    public partial class MainWindow : Window
    {

        //declaration de variables
        int UID = 0;

        int nbr_buletinI;
        private List<Page1> People = new List<Page1>();
        private Page1 Vblank;
        private Page1 Vnull;
        const string Blank = "Votes blancs";
        const string Nulle = "Votes nuls";

        private string F_ppl;
        private string F_steps;
        private string F_round;

        // initialisation de debut
        public MainWindow()
        {
            InitializeComponent();

            // build and add Vote Blanc at the botom of the page
            Vblank = new Page1(Blank, this, true, true, false);
            vblank.Children.Add(Vblank);
            Vnull = new Page1(Nulle, this, true, true, false);
            vnull.Children.Add(Vnull);

            // system de BackUP si ca crash
            BackUp();
        }


        //system de backup
        private void BackUp()
        {
            //si le fichier exist pas ... ca crash pas
            try
            {
                string text = System.IO.File.ReadAllText(@"c:\temp\IPC.ipc");
                string[] protocole = text.Split(';');

                // recupere le fichier et re atribut tout comme sa doit etre
                F_steps = protocole[0];
                F_round = protocole[1];
                F_ppl = protocole[2];
                openBack();

                step.SelectedIndex = int.Parse(protocole[3]);
                round.SelectedIndex = int.Parse(protocole[4]);
                var nb_ppl = int.Parse(protocole[5]);

                nbr_buletinI = int.Parse(protocole[6]);

                
                Vblank.nbVotesI = int.Parse(protocole[7]);
                Vblank.nbVotes.Text = protocole[7];
                
                Vnull.nbVotesI = int.Parse(protocole[8]);
                Vnull.nbVotes.Text = protocole[8];

                majo.Content = int.Parse(protocole[10]);

                for (int i = 0; i < nb_ppl; i++)
                {
                    int isodd = People.Count() % 2;
                    var tmp = new Page1(protocole[i * 3 + 10], this, isodd == 0 ? true : false, false, true);
                    tmp.percent.Text = protocole[i * 3 + 11];
                    tmp.nbVotesI = int.Parse(protocole[i * 3 + 12]);
                    tmp.nbVotes.Text = protocole[i * 3 + 12];
                    People.Add(tmp);
                    PeopleContainer.Children.Add(People[People.Count - 1]);
                }
                // update du protocole / Fix Possible mistakes
                update(@"c:\temp\IPC.ipc");
            }
            catch {
                return ;
            }
        }

        /* ==== made by the window ==== */

        // add_personne is used to add someone to the list correctly and syncronize with everything 
        private void Add_personne(object sender, RoutedEventArgs e)
        {
            int isodd = People.Count() % 2;
            if (name_ppl.Text.Length != 0)
            {
                // si le nom est rentré manuellement
                People.Add(new Page1(name_ppl.Text, this, isodd == 1 ? true : false, false, true));
                PeopleContainer.Children.Add(People[People.Count - 1]);
                People[People.Count - 1].elem = UID++;
                name_ppl.Text = "";
                update(@"c:\temp\IPC.ipc");
                name_ppl.Focus();
            }
            else 
            {
                // si il y a rien a faire
                if (fileparsed.SelectedIndex == 0)
                    return;
                //si le nom est rentré avec la list deroulante
                People.Add(new Page1(fileparsed.SelectedItem.ToString(), this, isodd == 1 ? true : false, false, true));
                PeopleContainer.Children.Add(People[People.Count - 1]);
                People[People.Count - 1].elem = UID++;
                fileparsed.SelectedIndex = 0;
                update(@"c:\temp\IPC.ipc");
            }
        }

        // Del_personne est utiliser pour suprimer qqn de la list
        public void Del_personne(int UID)
        {
            int i = 0;
            int place = -1;
            People.ForEach(delegate (Page1 personne)
            {
                if (personne.elem == UID)
                {
                    PeopleContainer.Children.Remove(personne);
                    place = i;
                }
                i++;
            });
            People.RemoveAt(place);
            update(@"c:\temp\IPC.ipc");
        }

        // RAZ (remiz a zero) reset
        private void RAZ(object sender, RoutedEventArgs e)
        {
            MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Êtes-vous sûr ?", "Confirmation ", System.Windows.MessageBoxButton.YesNo);
            if (messageBoxResult == MessageBoxResult.Yes)
            {

                screenshot(sender, null);

                PeopleContainer.Children.Clear();
                if (People.Count >= 1)
                    People.RemoveRange(0, People.Count);
                Vblank.reset();
                Vnull.reset();
                step.SelectedIndex = 0;
                round.SelectedIndex = 0;
                majo.Content = 0;
                sufrage.Content = 0;
                nbr_buletinI = 0;
                Nbr_buletin.Text = "0";
                update(@"c:\temp\IPC.ipc");
            }
            else
                return;
            
            
        }

        // fait un screenshot + fait une save du fichier IPC
        private void screenshot(object sender, RoutedEventArgs e)
        {
            double screenLeft = SystemParameters.VirtualScreenLeft;
            double screenTop = SystemParameters.VirtualScreenTop;
            double screenWidth = SystemParameters.VirtualScreenWidth;
            double screenHeight = SystemParameters.VirtualScreenHeight;

            string path = @"C:\Screenshots";

            if (!Directory.Exists(path))
            {
                DirectoryInfo di = Directory.CreateDirectory(path);
                Console.WriteLine("The directory was created successfully at {0}.", Directory.GetCreationTime(path));
            }

            using (Bitmap bmp = new Bitmap((int)screenWidth,
                (int)screenHeight))
            {
                using (Graphics g = Graphics.FromImage(bmp))
                {
                    String filename = "ScreenCapture-" + DateTime.Now.ToString("ddMMyyyy-hhmmss") + ".png";
                    Opacity = .0;
                    g.CopyFromScreen((int)screenLeft, (int)screenTop, 0, 0, bmp.Size);
                    bmp.Save("C:\\Screenshots\\" + filename);
                    Opacity = 1;
                }

            }
            update(@"c:\Screenshots\" + "SaveIPC" + DateTime.Now.ToString("ddMMyyyy-hhmmss") + ".ipc");
        }

        // trigered by the people

        // Update tout les elements et met a jour le protocole 
        public void update(String path)
        {
            if (Vblank == null || Vnull == null)
                return;
            
            //get the total number of votes
            var TotalVotes = 0;
            People.ForEach(delegate (Page1 personne)
            {
                if (!personne.checkedflag)
                    TotalVotes += personne.getNbVotes();
            });
            if (!Vblank.checkedflag)
                TotalVotes += Vblank.getNbVotes();
            if (!Vnull.checkedflag)
                TotalVotes += Vnull.getNbVotes();

            // update every personne TotalVotes is used to compute a percent  
            People.ForEach(delegate (Page1 personne)
            {
                personne.selfUpdate(TotalVotes);
            });
            Vblank.selfUpdate(TotalVotes);
            Vnull.selfUpdate(TotalVotes);


            var Sorted = People;
            Sorted.Sort(delegate (Page1 x, Page1 y)
            {
                if (x.name == null && y.name == null) return 0;
                else if (x.name == null) return -1;
                else if (y.name == null) return 1;
                else return x.name.CompareTo(y.name);
            });

            //mise a jour en graphiques des personnes
            PeopleContainer.Children.Clear();
            PeopleContainer.Children.RemoveRange(0, People.Count());
            bool firstskipe = false;
            int IsOdd = 0;
            Sorted.ForEach(delegate (Page1 personne)
            {
                if (firstskipe || personne.name != Blank)
                {
                    PeopleContainer.Children.Add(personne);
                    personne.setBackGround(IsOdd++ % 2 == 0 ? true : false);
                }
                else
                    firstskipe = true;
            });

            // attribut le sufrage
            sufrage.Content = TotalVotes.ToString();

            //generation du protocole
            string protocole = F_steps + ";" + F_round + ";" + F_ppl + ";" + step.SelectedIndex.ToString() + ";" + round.SelectedIndex.ToString() + ";" +
                               People.Count.ToString() + ";";

            //generation du protocole (envoye des personnes)
            string pplProtocole = null;
            People.ForEach(delegate (Page1 personne)
             {
                 if (!personne.checkedflag)
                     pplProtocole += personne.Protocole();
             });

            //generation du protocole (envoye des donnee complementaires)
            string endProtocole;
            if (round.SelectedIndex.ToString()[0] == '3')
                endProtocole = nbr_buletinI.ToString() + ";" + Vblank.nbVotesI.ToString() + ";" + Vnull.nbVotesI.ToString() + ";" + TotalVotes + ";" + GetMaxVoice();
            else
                endProtocole = nbr_buletinI.ToString() + ";" + Vblank.nbVotesI.ToString() + ";" + Vnull.nbVotesI.ToString() + ";" + TotalVotes + ";" + majo.Content.ToString();

            protocole = protocole + endProtocole + pplProtocole;

            // envoy le protocole
            System.IO.File.WriteAllText(path, protocole, Encoding.GetEncoding(28591));

        }

        // est utiliser pour calculer la majoriter (tour 1 et 2)
        private void validate_Nbr_buletin(object sender, RoutedEventArgs e)
        {
            if (Nbr_buletin.Text == "")
                return ;
            nbr_buletinI = int.Parse(Nbr_buletin.Text);
            if (nbr_buletinI == 0)
                majo.Content = 0;
            else
            {
                int majority = (nbr_buletinI / 2) + 1;
                majo.Content = majority.ToString();
            }
            update(@"c:\temp\IPC.ipc");
        }

        // ajout de personnes + mieux faciles
        private void KeyPressed(object sender, KeyEventArgs e)
        {
            if (e.Key.ToString() == "Return")
            {
                Add_personne(sender, null);
            }
        }

        // changement d'etape (president / vice president)
        private void step_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            update(@"c:\temp\IPC.ipc");
        }

        // parametrage du fichier de nom des potenciel votant
        private void set_File(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            string[] allLines;
            if (openFileDialog.ShowDialog() == true)
            {
                allLines = File.ReadAllLines(openFileDialog.FileName);
            }
            else
                return;

            fileparsed.Items.Clear();
            fileparsed.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                fileparsed.Items.Add(file);
            }
            F_ppl = openFileDialog.FileName;
        }

        // parametrage du fichier des etapes
        private void set_step_File(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            string[] allLines;
            if (openFileDialog.ShowDialog() == true)
            {
                allLines = File.ReadAllLines(openFileDialog.FileName);
            }
            else
                return;

            step.Items.Clear();
            step.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                step.Items.Add(file);
            }
            F_steps = openFileDialog.FileName;
        }

        // parametrage du fichier des etapes
        private void set_round_File(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            string[] allLines;
            if (openFileDialog.ShowDialog() == true)
            {
                allLines = File.ReadAllLines(openFileDialog.FileName);
            }
            else
                return;

            round.Items.Clear();
            round.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                round.Items.Add(file);
            }
            F_round = openFileDialog.FileName;
        }

        private void openBack()
        {
            var allLines = File.ReadAllLines(F_ppl);

            fileparsed.Items.Clear();
            fileparsed.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                fileparsed.Items.Add(file);
            }

            allLines = File.ReadAllLines(F_steps);

            step.Items.Clear();
            step.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                step.Items.Add(file);
            }

            allLines = File.ReadAllLines(F_round);

            round.Items.Clear();
            round.Items.Add("- Select -");
            foreach (string file in allLines)
            {
                round.Items.Add(file);
            }
        }

        //recupere le nombre de voie maximum sur une personne
        private int GetMaxVoice()
        {
            int ret = 0;
            People.ForEach(delegate (Page1 personne)
            {
                ret = ret < personne.nbVotesI ? personne.nbVotesI : ret;
            });
            return ret;
        }

        private void Nbr_buletin_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key.ToString() == "Return")
            {
                validate_Nbr_buletin(sender, null);
            }
        }
    }
}
